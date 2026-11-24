#include "shader_program.hpp"
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glad/gl.h>
#include <print>

struct Vertex {
    float x, y;
};

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::println(stderr, "[ERROR] {}", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window *window = SDL_CreateWindow(
        "Donut",
        1200,
        800,
        SDL_WINDOW_OPENGL);

    if (!window) {
        std::println(stderr, "[ERROR] {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        std::println(stderr, "[ERROR] {}", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
    if (version) {
        std::println("OpenGL {}.{} succesfuly loaded", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    } else {
        std::println(stderr, "[ERROR] OpenGL failed loading");
    }

    uint32_t vao, vbo;
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);

    Vertex vertices[] {
        { 0.0f, 0.5f },
        { -0.5f, -0.5f },
        { 0.5f, -0.5f }
    };
    
    glNamedBufferStorage(vbo, 3 * sizeof(Vertex), vertices, 0);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(Vertex));
    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, 0, 0);
    glBindVertexArray(vao);

    Shaders shaders;
    shaders.emplace_back(GL_VERTEX_SHADER, "./shaders/shader.vert");
    shaders.emplace_back(GL_FRAGMENT_SHADER, "./shaders/shader.frag");
    ShaderProgram program { shaders };
    
    if (!program.compile()) {
        std::exit(1);
    }

    program.use();

    bool running { true };

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
