#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <optional>
#include <vector>

#include "shader.hpp"

using Shaders = std::vector<Shader>;

class ShaderProgram {
private:
    uint32_t id_;
    Shaders shaders_;
    bool compiled_ { false };

    bool check_shader_compilation(uint32_t shader);
    bool check_program_compilation(uint32_t program);

public:
    explicit ShaderProgram(Shaders &shaders)
        : id_(glCreateProgram())
        , shaders_ { std::move(shaders) } { }

    ShaderProgram(const ShaderProgram &other) = delete;
    ShaderProgram &operator=(const ShaderProgram &other) = delete;

    ShaderProgram(ShaderProgram &&other) noexcept
        : id_(std::exchange(other.id_, 0))
        , shaders_(std::move(other.shaders_))
        , compiled_(std::exchange(other.compiled_, false)) {}
 
    ShaderProgram& operator=(ShaderProgram&& other) {
        glDeleteProgram(id_);
        
        id_ = std::exchange(other.id_, 0);
        shaders_ = std::move(other.shaders_);
        compiled_ = std::exchange(other.compiled_, false);

        return *this;
    }

    ~ShaderProgram() { glDeleteProgram(id_); }

    uint32_t get_id() const { return id_; }

    void add_uniform_Matrix4fv(const glm::mat4 &mat, std::string_view name);
    
    std::optional<uint32_t> compile();
    void use();
};
