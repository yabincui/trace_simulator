#ifndef _MACRO_UTILS_H
#define _MACRO_UTILS_H

#define __STRINGIFY_1(x)  #x
#define __STRINGIFY(x)  __STRINGIFY_1(x)

#define __CONCAT_TWO_1(a, b) a ## b
#define __CONCAT_TWO(a, b) __CONCAT_TWO_1(a, b)


#endif  // _MACRO_UTILS_H
