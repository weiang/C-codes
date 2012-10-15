/*ino.h*/
/*I node structue as it on a disk block*/

typedef unsigned short ushort

struct d_inode
{
	ushort	di_mode;
	short	di_nlink;
	ushort	di_uid;
	ushort	di_gid;
	off_t	di_size;
	char	di_addr[40];
	time_t	di_atime;
	time_t	di_mtime;
	time_t	di_ctime;	/*time created*/
};
