#include "shader_program.hpp"

#include <SDL3/SDL.h>

#include <optional>
#include <print>

#include "io.hpp"

bool ShaderProgram::check_shader_compilation(uint32_t shader) {
    int success = 0;
    char info_log[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, info_log);
        std::println("[ERROR] {}", info_log);
        return false;
    }

    return true;
}

bool ShaderProgram::check_program_compilation(uint32_t program) {
    int success = 0;
    char info_log[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, info_log);
        std::println("[ERROR] {}", info_log);
        return false;
    }

    return true;
}

std::optional<uint32_t> ShaderProgram::compile() {
    for (auto &shader : shaders_) {
        std::string source = io::load_file(shader.get_dir());
        const char *source_ptr = source.c_str();

        glShaderSource(shader.get_id(), 1, &source_ptr, nullptr);
        glCompileShader(shader.get_id());

        if (!check_shader_compilation(shader.get_id())) {
            return std::nullopt;
        }

        glAttachShader(id_, shader.get_id());
    }

    glLinkProgram(id_);

    if (!check_program_compilation(id_)) {
        return std::nullopt;
    }

    compiled_ = true;
    return id_;
}

void ShaderProgram::use() {
    if (compiled_) {
        glUseProgram(id_);
    } else {
        std::println("[WARNING] Tried to use program before compilation");
    }
}
