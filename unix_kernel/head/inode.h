/*inode.h*/
/*the I node is the focus of all
 *file activity in unix.There is a 
 *unique inode allocated for each active 
 *file,each current directory,each mounted-on file,
 *text file,and the root.
 *An inode is 'named' by its dev/inumber pair.
 *(iget/iget.c) Data,from mode on ,is read in from
 *permanent inode on volume.
 */

#define	NADDR	13
#define	NSADDR	(NADDR * sizeof(daddr_t) / sizeof(short))

struct inode
{
	struct	inode	*i_forw;
	struct	inode	*i_back;
	char	i_flag;
	cnt_t	i_count;
	dev_t	i_dev;
	ino_t	i_number;
	ushort	i_mode;
	short	i_nlink;
	ushort	i_uid;
	ushort	i_gid;
	off_t	i_size;
	struct {
		union {
			daddr_t	i_a[NADDR];	/*if normal file/directory*/
			short	i_f[NSADDR];	/*if fifo*/
		} i_p;
		daddr_t	i_l;
	} i_blks;
};


