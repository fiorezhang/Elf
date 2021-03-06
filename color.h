#ifndef COLOR_H
#define COLOR_H

#include "defines.h"

#if PRINT_TO_BASH
#define CDEF "\033[0m"
#define CBLA "\033[0;30m"
#define CRED "\033[0;31m"
#define CGRE "\033[0;32m"
#define CYEL "\033[0;33m"
#define CBLU "\033[0;34m"
#define CPUR "\033[0;35m"
#define CCYA "\033[0;36m"
#define CWHI "\033[0;37m"
#define LBLA "\033[1;30m"
#define LRED "\033[1;31m"
#define LGRE "\033[1;32m"
#define LYEL "\033[1;33m"
#define LBLU "\033[1;34m"
#define LPUR "\033[1;35m"
#define LCYA "\033[1;36m"
#define LWHI "\033[1;37m"
#else
#define CDEF ""
#define CBLA ""
#define CRED ""
#define CGRE ""
#define CYEL ""
#define CBLU ""
#define CPUR ""
#define CCYA ""
#define CWHI ""
#define LBLA ""
#define LRED ""
#define LGRE ""
#define LYEL ""
#define LBLU ""
#define LPUR ""
#define LCYA ""
#define LWHI ""
#endif

#endif//COLOR_H
