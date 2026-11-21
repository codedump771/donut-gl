#include "shader.hpp"
#include <SDL3/SDL.h>
#include <fstream>
#include <sstream>
#include <print>
#include <algorithm>

void Shader::add_shader(GLenum type, const std::string& dir) {

    std::ifstream in{dir};
    if (!in) {
        std::println(stderr, "[ERROR] Failed to open shader: {}", dir);
        return;
    }

    std::string code;
    std::stringstream buffer;
    buffer << in.rdbuf();
    code = buffer.str();

    sources_.push_back(std::move(code));
    shaders_.push_back(glCreateShader(type));
}

std::optional<uint32_t> Shader::compile() {
    for (int i = 0; i < shaders_.size(); i++) {
        uint32_t shader = shaders_[i];
        const char* source_ptr = sources_[i].c_str();
        glShaderSource(shader, 1, &source_ptr, nullptr);
        glCompileShader(shader);

        int success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            int len = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
            std::vector<char> info_log(len ? len : 1);
            
            glGetShaderInfoLog(shader, len, nullptr, info_log.data());
            std::println("[ERROR] {}", info_log.data());

            return std::nullopt;
        }

        glAttachShader(id_, shader);
    }

    glLinkProgram(id_);

    int success = 0;
    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success) {
        int len = 0;
        glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> info_log(len ? len : 1);
        
        glGetProgramInfoLog(id_, len, nullptr, info_log.data());
        std::println("[ERROR] {}", info_log.data());

        return std::nullopt;    
    }

    std::for_each(shaders_.begin(), shaders_.end(), glDeleteShader);

    return id_;
}