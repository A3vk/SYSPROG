#ifndef __throw__
#define __throw__

void _throw_if_min1(int x, const char* file, unsigned int line);

#define throw_if_min1(___x___) _throw_if_min1((___x___), __FILE__, __LINE__)

#endif
