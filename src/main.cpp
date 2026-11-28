#include "mesh.hpp"
#include "shader_program.hpp"
#include <SDL3/SDL.h>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <print>

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::println(stderr, "[ERROR] {}", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window *window = SDL_CreateWindow(
        "OpenGL",
        800,
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

    Mesh pyramid = Mesh({ { { -0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f } },
        { { 0.0f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
        { { -0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f } },
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f } },
        { { 0.0f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
        { { 0.5f, -0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } } });

    pyramid.bind();

    Shaders shaders;
    shaders.emplace_back(GL_VERTEX_SHADER, "./shaders/shader.vert");
    shaders.emplace_back(GL_FRAGMENT_SHADER, "./shaders/shader.frag");
    ShaderProgram program { shaders };

    if (!program.compile()) {
        std::exit(1);
    }

    program.use();
    glEnable(GL_DEPTH_TEST);

    bool running { true };

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        float rotation = SDL_GetTicks() / 10.0f;

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        program.add_uniform_Matrix4fv(trans, "trans");

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        program.add_uniform_Matrix4fv(view, "view");

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
        program.add_uniform_Matrix4fv(projection, "projection");

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        pyramid.draw();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
