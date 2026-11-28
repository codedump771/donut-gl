#include "mesh.hpp"
#include "glad/gl.h"

void Mesh::initialize() {
    glCreateVertexArrays(1, &vao_);
    glCreateBuffers(1, &vbo_);
    glCreateBuffers(1, &ebo_);

    glNamedBufferStorage(vbo_, count() * sizeof(Vertex), data(), 0);
    glVertexArrayVertexBuffer(vao_, 0, vbo_, 0, sizeof(Vertex));

    glVertexArrayAttribBinding(vao_, 0, 0);
    glVertexArrayAttribFormat(vao_, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, pos));
    glEnableVertexArrayAttrib(vao_, 0);

    glVertexArrayAttribBinding(vao_, 1, 0);
    glVertexArrayAttribFormat(vao_, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, norm));
    glEnableVertexArrayAttrib(vao_, 1);
}

void Mesh::bind() {
    glBindVertexArray(vao_);
}

void Mesh::draw() {
    glDrawArrays(GL_TRIANGLES, 0, count());
}
