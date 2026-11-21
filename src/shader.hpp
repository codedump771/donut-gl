#pragma once

#include <glad/gl.h>
#include <vector>
#include <string>
#include <optional>

class Shader {
private:
    std::vector<uint32_t> shaders_;
    std::vector<std::string> sources_;
    uint32_t id_;
public:

    Shader() {
        id_ = glCreateProgram();
    }
    
    void add_shader(GLenum type, const std::string& source);
    std::optional<uint32_t> compile();
};