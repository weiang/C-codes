/*dir.h*/

#ifndef	DIRSIZ
#define	DIRSIZ	14
#endif

struct	dirent
{
	ino_t	d_ino;
	char	d_name[DIRSIZ];
};
