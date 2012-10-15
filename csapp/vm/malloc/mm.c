/* mm.c */
#include <stdlib.h>
#include "memlib.h"
#include <string.h>
#include <stdio.h>

/* Basic constants and macros */
#define WSIZE	4	/* Word and header/footer size (bytes) */
#define DSIZE	8	/* Double word size (bytes) */
#define CHUNKSIZE	(1 << 12)	/* Extend heap by this amount (bytes) */

#define MAX(x, y)	((x) > (y) ? (x) : (y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc)	((size) | (alloc))

/* Read and write a word at address p */
#define GET(p)	(*(unsigned int *)(p))
#define PUT(p, val)	(*(unsigned int *)(p) = (val))

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)	((char *)(bp) - WSIZE)
#define	FTRP(bp)	((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)	((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp)	((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

/* Get size and allocated bit of a block */
#define GET_ALLOC(p)	((GET(p)) & 0x1)
#define GET_SIZE(p)	((GET(p)) & ~0x7)

static char	*heap_listp;	/* Points to the prologue block */

int 	mm_init(void);
static void 	*extend_heap(size_t);
static void 	*coalesce(void *bp);
static void 	*find_fit(size_t size);
static void 	place(void *bp, size_t size);

/* mm_init() - Gets four words from the memory system and initializes them 
 *		to creat the empty free list 
 */
int mm_init(void)
{
	/* Creat the initial empty heap */
	if ((heap_listp =  mem_sbrk(4 * WSIZE)) == (void *)-1)
		return -1;
	PUT(heap_listp, 0);	/* Alignment padding */
	PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1));	/* Prologue header */
	PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1));	/* Prologue footer */
	PUT(heap_listp + (3 * WSIZE), PACK(0, 1));	/* Epilogue header */
	heap_listp += (2 * WSIZE);
	
	/* Extend the empty heap with a free block of CHUNKSIZE bytes */
	if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
		return -1;
	return 0;
}

static void *extend_heap(size_t words)
{
	char	*bp;
	size_t	size;

	/* Allocate an even number of words to maintain alignment */
	size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
	if ((long)(bp = mem_sbrk(size)) == -1)
		return NULL;
	
	/* Initialize free block header/footer and the epilogue header*/
	PUT(HDRP(bp), PACK(size, 0));	/* Free block header */
	PUT(FTRP(bp), PACK(size, 0));	/* Free block footer */
	PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));	/* New epilogue header */

	/* Coalesce if the previous block was free */
	return coalesce(bp);
}

void mm_free(void *bp)
{
        PUT(HDRP(bp), PACK(GET_SIZE(bp), 0));
        PUT(FTRP(bp), PACK(GET_SIZE(bp), 0));
        coalesce(bp);
}

/* coalesce() - Merge the free blocks */
static void *coalesce(void *bp)
{
	size_t	prev_alloc = GET_ALLOC(HDRP(PREV_BLKP(bp)));
	size_t	next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
	size_t	size = GET_SIZE(HDRP(bp));

	/* Case 1:
	 *	Both of the previous block and next block of block bp are allocated 
	 */
	if (prev_alloc && next_alloc)
		return bp;
	
	/* Case 2:
	 *	previous block of block bp is free 
	 *	while next block is allocated 
	 */
	else if (!prev_alloc && next_alloc) {
			size += GET_SIZE(HDRP(PREV_BLKP(bp)));
			PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
			PUT(FTRP(bp), PACK(size, 0));
			return PREV_BLKP(bp);
	}
	
	/* Case 3:
	 *	previous block of block bp is allocated 
	 *	while next block is free 
 	 */
	else if (prev_alloc && ! next_alloc) {
		size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));	/* !!!NOTICE(Where error happened): NOT "PUT(FTRP(bp), PACK(size, 0))",BUT"PUT(FTRP(bp), PACK(size, 0))" */
		return bp;
	}
		
	/* Case 4:
	 * 	Both previous block and next block are free 
	 */
	else if (!prev_alloc && !next_alloc) {
			size += GET_SIZE(HDRP(PREV_BLKP(bp)));
			size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
			PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
			PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
			return PREV_BLKP(bp);
	}
}

void *mm_malloc(size_t request_size)
{
	size_t	size;
	size_t	extendsize;	/* Amount to extend heap if no fit */
	void	*bp;

	/* Ignore spurious requests */
	if (request_size <= 0)
		return NULL;

	/* Adjust block size to include overhead and alignment reqs */
/*	if (request_size % DSIZE == 0)
		size = (request_size / DSIZE + 1) * DSIZE;
	else
		size = (request_size / DSIZE + 2) * DSIZE;
*/
	if (request_size <= DSIZE)
		size = 2 * DSIZE;
	else 
		size = DSIZE * ((request_size + DSIZE + (DSIZE - 1)) / DSIZE);

	/* Search the free list for a fit */
	if ((bp = find_fit(size)) != NULL) {
		place(bp, size);	
		return bp;
	}
 
	/* No fit found. Get more memory and place the block */
	extendsize = MAX(size, CHUNKSIZE);
	if ((bp = extend_heap(extendsize / WSIZE)) == NULL) 
		return NULL;
	place(bp, size);
	return bp;
}

static void *find_fit(size_t size)
{
	void	*bp;
	
	/* First fit search */
	for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
		if ((!GET_ALLOC(HDRP(bp))) && (size <= GET_SIZE(HDRP(bp)))) {
			return bp;
		}
	}
	
	return NULL;	/* No fit */
}

static void place(void *bp, size_t size)
{
	size_t	prev_size = GET_SIZE(HDRP(bp));

	if ((prev_size - 2 * DSIZE) >= size) {
		PUT(HDRP(bp), PACK(size, 1));
		PUT(FTRP(bp), PACK(size, 1));
		bp = NEXT_BLKP(bp);
		PUT(HDRP(bp), PACK(prev_size - size, 0));
 		PUT(FTRP(bp), PACK(prev_size - size, 0));
	}
	else {
		PUT(HDRP(bp), PACK(prev_size, 1));
		PUT(FTRP(bp), PACK(prev_size, 1));
	}
	return;
}


int main(void)
{
	char	*p;

	p = (char*)mm_malloc(13);
	strcpy(p,"Hello world\n");
	printf("%s",p);
	return 0;
}
