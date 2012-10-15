#ifndef _ERROR_H_
#define _ERROR_H_

extern void err_ret(const char *,...);
extern void err_sys(const char *,...);
extern void err_exit(int,const char *,...);
extern void err_dump(const char *,...);
extern void err_msg(const char *,...);
extern void err_quit(const char *,...);

#endif
