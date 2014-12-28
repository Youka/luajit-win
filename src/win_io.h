#ifndef _WIN_IO_H
#define _WIN_IO_H

#include <stdio.h>
#include <stdlib.h>

FILE* _ufopen(const char*, const char*);
FILE* _ufreopen (const char*, const char*, FILE*);
FILE* _upopen(const char*, const char*);
int _uremove(const char*);
int _urename(const char*, const char*);
int _usystem(const char*);
#define fopen _ufopen
#define freopen _ufreopen
#define popen _upopen
#define remove _uremove
#define rename _urename
#define system _usystem

#endif
