#include "apue.h"
#include "dirent.h"
#include "limits.h"
#include "errno.h"

#ifdef PATH_MAX 
	static int	pathmax = PATH_MAX;
#else	
	static int 	pathmax = 0;
#endif
#define SUSV3 	200112L

static long	posix_version = 0;
/*If PATH_MAX is indeterminate,no guarantee this is adequate*/
#define PATH_MAX_GUESS	1024

/*function type that is called for each filename*/
typedef int	Myfunc(const char *,const struct stat *,int);
static Myfunc	myfunc;
static int	myftw(char *,Myfunc *);
static int 	dopath(Myfunc *);

/*grobal data*/
static long	nreg,ndir,nblk,nchr,nfifo,nslink,nsock,ntot;

int main(int argc,char *argv[])
{
	int ret;

	if (argc != 2)
		err_quit("Usage:ftw <starting_pathname>");

	ret = myftw(argv[1],myfunc);	/*does it all*/

	ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
	if (ntot == 0)
		ntot = 1;	/*avoid divide by 0;print 0 for all counts*/

	/*print the result*/
	printf("regular files	= %7ld,%5.2f%%\n",nreg,nreg * 100.0 / ntot);
	printf("directories	= %7ld,%5.2f%%\n",ndir,ndir * 100.0 / ntot);
	printf("block special 	= %7ld,%5.2f%%\n",nblk,nblk * 100.0 / ntot);
	printf("character special = %7ld,%5.2f%%\n",nchr,nchr * 100.0 / ntot);
	printf("FIFOs 		= %7ld,%5.2f%%\n",nfifo,nfifo * 100.0 /ntot);
	printf("symbolic links 	= %7ld,%5.2f%%\n",nslink,nslink * 100.0 / ntot);
	printf("sockets 	= %7ld,%5.2f%%\n",nsock,nsock * 100.0 / ntot);
	
	exit (0);
}

/*
 *Descend through the hierarchy,starting at "pathname".
 *The caller's func() is called for every file.
 */
#define FTW_F	1	//file other than dirtory
#define FTW_D	2	//directory
#define FTW_DNR	3	//directory that can't be read
#define FTW_NS	4	//file that we can't stat

static char 	*fullpath;	//contains full pathname for every file

/*we return whatever func() returns*/
static int	myftw(char *pathname,Myfunc *func)
{
	int 	len;
	char 	*path_alloc(int *);

	fullpath = path_alloc(&len);	/*malloc's for PATH_MAX + 1 bytes*/
	strncpy(fullpath,pathname,len);	/*protect against*/
	fullpath[len - 1] = 0;	/*buffer overrun*/

	return (dopath(func));
}


/*
 *Descend through the hierarchy,starting at "fullpath".
 *if "fullpath" is anything other than a directory,we lstat() it.
 *Call func().and return.For a diretory,we call ourself recursively
 *each name in the directory.

*/
/*we return whatever func() returns*/
static int	dopath(Myfunc *func)
{
	struct stat	statbuf;
	struct dirent	*dirp;
	DIR	*dp;
	int 	ret;
	char	*ptr;

	if (lstat(fullpath,&statbuf) < 0)
		return (func(fullpath,&statbuf,FTW_NS));	/*stat error*/
	if (S_ISDIR(statbuf.st_mode) == 0)
		return (func(fullpath,&statbuf,FTW_F));		/*not a directory*/

/*
 *It's a directory.First call func() for the directory.
 *Then process each filename in the directory.
 */
	if ((ret = func(fullpath,&statbuf,FTW_D)) != 0)
		return (ret);

	ptr = fullpath + strlen(fullpath);	/*point to end of fullpath*/
	*ptr++ = '/';
	*ptr = 0;

	if ((dp = opendir(fullpath)) == NULL)
		return (func(fullpath,&statbuf,FTW_DNR));	/*can't read directory*/
	while ((dirp = readdir(dp)) != NULL){
		if (strcmp(dirp -> d_name,".") == 0 ||
			strcmp(dirp -> d_name,"..") == 0)
				continue;	/*ignore dot and dor-dot*/
		strcpy(ptr,dirp -> d_name);	/*append name after slash*/
	
	if ((ret = dopath(func)) != 0)
		break;	/*recursive*/
	}
	ptr[-1] = 0;	/*erase every thing from slash onwards*/
	
	if (closedir(dp) < 0)
		err_ret("can't close directory %s",fullpath);
	return (ret);
}

static int	myfunc(const char *pathname,const struct stat *statptr,int type){
	switch(type){
		case FTW_F:
			switch(statptr -> st_mode & S_IFMT){
				case S_IFREG:
					nreg ++;
					break;
				case S_IFDIR:
					err_dump("for S_IFDIR for %s",pathname);
					break;	/*dir should have type = FTW_D*/
				case S_IFBLK:
					nblk ++;
					break;
				case S_IFCHR:
					nchr ++;
					break;
				case S_IFIFO:
					nfifo ++;break;
				case S_IFLNK:
					nslink ++;break;
				case S_IFSOCK:
					nsock ++;break;
			}
		case FTW_D:
			ndir ++;
			break;
		case FTW_DNR:
			err_ret("cat't read dir %s",pathname);
			break;
		case FTW_NS:
			err_ret("stat error for %s",pathname);
			break;
		default:
			err_dump("unknown type %d for pathname %s",type,pathname);
	}
	return 0;
}

char	*path_alloc(int *sizep)
{
	char	*ptr;
	int	size;

	if (posix_version == 0)
		posix_version = sysconf(_SC_VERSION);
	if (pathmax == 0){
		errno = 0;
		if ((pathmax = pathconf("/",_PC_PATH_MAX)) < 0){
			if (errno == 0)
				pathmax = PATH_MAX_GUESS;
			else 
				err_sys("pathconf error for _PC_PATH_MAX");
		}
	else {
		pathmax ++;
	}
	}
	if (posix_version < SUSV3)
		size = pathmax + 1;
	else size = pathmax;
	
	if ((ptr = malloc(size)) == NULL)
		err_sys("malloc error for pathname");

	if (sizep != NULL)
		*sizep = size;
	return (ptr);
}


