#ifndef __COMMON_H_INCLUDED__
#define __COMMON_H_INCLUDED__

#include <stdint.h>

#if !defined(TRUE) && !defined(FALSE)
typedef int32_t BOOL;
const BOOL TRUE = 1;
const BOOL FALSE = 0;
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)	                                   if (x) { (x)->Release(); (x) = NULL; }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	                                   if (x) { delete (x); (x) = NULL; }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	                           if (x) { delete [] (x); (x) = NULL; }
#endif

#define MAX(a, b)                                          ( (a) > (b) ? (a) : (b) )
#define MIN(a, b)                                          ( (a) < (b) ? (a) : (b) )

#endif
