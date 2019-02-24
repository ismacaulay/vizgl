#pragma once
#include <cassert>

void glClearError();
bool glLogCall(const char* function, const char* file, int line);

// Dont call this all the time in a release build
#define GL_CALL(x) glClearError();\
    x;\
    assert(glLogCall(#x, __FILE__, __LINE__))
