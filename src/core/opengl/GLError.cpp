#include "GLError.h"

#include <GLES2/gl2.h>
#include <stdio.h>

void glClearError() {
    while(glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char* file, int line) {
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        printf("[opengl error] %s::%s:%d: %d\n", file, function, line, err);
        return false;
    }
    return true;
}
