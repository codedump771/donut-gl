#pragma once

#include "vertex.hpp"
#include <vector>

using Vertices = std::vector<Vertex>;
using Indices = std::vector<uint32_t>;

class Mesh {
private:
    Vertices vertices_;
    Indices indices;
    uint32_t vao_, vbo_, ebo_;

    void initialize();

public:
    explicit Mesh(const Vertices &vertices)
        : vertices_(vertices) { initialize(); }

    Mesh(const Mesh &other);
    Mesh &operator=(const Mesh &other);

    Mesh(Mesh &&other);
    Mesh &operator=(Mesh &&other);

    const Vertex *data() const { return vertices_.data(); }
    size_t count() const { return vertices_.size(); }

    void bind();
    void draw();
};
