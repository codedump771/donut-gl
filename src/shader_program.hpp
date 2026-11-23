#pragma once

#include <glad/gl.h>
#include <vector>
#include <string>
#include <optional>
#include "shader.hpp"


using Shaders = std::vector<Shader>;

class ShaderProgram {
private:
    uint32_t id_;
    Shaders shaders_;

    bool check_shader_compilation(uint32_t shader);
    bool check_program_compilation(uint32_t program);
    
public: 
    explicit ShaderProgram(Shaders& shaders) : 
        id_(glCreateProgram()),
        shaders_{std::move(shaders)}
        {}

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;
        
    ~ShaderProgram() { glDeleteProgram(id_); }
    
    std::optional<uint32_t> compile();
};