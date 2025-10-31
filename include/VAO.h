#pragma once
#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
    GLuint ID;
    VAO();

    void LinkAttrib(VBO& VBO, GLuint layout, GLint numComponents, GLenum type, GLsizei stride, void* offset);
    void Bind() const;
    void Unbind() const;
    void Delete() const;
};
