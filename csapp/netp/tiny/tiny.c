/* 
 * tiny.c - A simple, iterative http/1.0 Web server that uses the GET 
 * 	method to serve static and dynamic content.
 */

#include "../../csapp.h"

void doit(int fd);
void read_requesthdrs(rio_t *rp);
int parse_uri(char *uri, char *filename, char *agiargs);
void serve_static(int fd, char *filename, int filesize);

