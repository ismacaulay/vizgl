#pragma once
#include <cassert>

void glClearError();
bool glLogCall(const char* function, const char* file, int line);

#ifdef NDEBUG
#define GL_CALL(x) x;
#else
#define GL_CALL(x) glClearError();\
    x;\
    assert(glLogCall(#x, __FILE__, __LINE__))
#endif
