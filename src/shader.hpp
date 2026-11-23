#pragma once

#include <glad/gl.h>
#include <string>

class Shader {
private:
    uint32_t id_;
    GLenum kind_;
    std::string dir_;

public:
    Shader(GLenum kind, std::string_view dir) :
        kind_(kind),
        dir_(dir),
        id_(glCreateShader(kind))
        {}

    Shader(Shader&& other) noexcept :
        kind_(std::exchange(other.kind_, 0)),
        dir_(std::move(other.dir_)),
        id_(std::exchange(other.id_, 0))
        {}

    Shader& operator=(Shader&& other) noexcept {
        kind_ = std::exchange(other.kind_, 0);
        dir_ = std::move(other.dir_);

        glDeleteShader(id_);
        id_ = std::exchange(other.id_, 0);
    }
    
    Shader(const Shader& other) = delete;
    Shader& operator=(const Shader& other) = delete;

    ~Shader() { glDeleteShader(id_); }
    
    uint32_t get_id() const { return id_; }
    GLenum get_kind() const { return kind_; }
    std::string get_dir() const { return dir_; }
};