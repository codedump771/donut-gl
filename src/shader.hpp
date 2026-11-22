#pragma once

#include <glad/gl.h>
#include <vector>
#include <string>
#include <optional>

class Shader {
private:
    uint32_t id_;
    GLenum kind_;
    std::string dir_;

public:
    Shader(GLenum kind, std::string_view dir) : kind_(kind), dir_(dir) { id_ = glCreateShader(kind_); }
    ~Shader() { glDeleteProgram(id_); }
    
    uint32_t get_id() const { return id_; }
    GLenum get_kind() const { return kind_; }
    std::string get_dir() const { return dir_; }
};

using Shaders = std::vector<Shader>;

class ShaderProgram {
private:
    uint32_t id_;
    const Shaders shaders_;

    bool check_shader_compilation(uint32_t shader);
    bool check_program_compilation(uint32_t program);
    
public: 
    ShaderProgram(const Shaders& shaders) : 
        id_(glCreateProgram()),
        shaders_{shaders}
        {}

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;
        
    ~ShaderProgram() { glDeleteProgram(id_); }
    
    std::optional<uint32_t> compile();
};