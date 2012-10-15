#ifndef	_TIMEDATE_H_
#define	_TIMEDATE_H_

typedef	struct
{
	int	year;
	int	mon;
	int	day;
}DATETYPE;

typedef	struct
{
	char	hour;
	char	min;
	char	sec;
}TIMETYPE;

#ifdef	SHARED
	int	(*getdate)(DATETYPE *d);
#else
	int	getdate(DATETYPE *d);
#endif

#ifdef	SHARED
	int	(*gettime)(TIMETYPE *t);
#else
	int 	gettime(TIMETYPE *t);
#endif

#endif	/*_DATETIME_H_*/
