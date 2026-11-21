#include <glad/gl.h>
#include <SDL3/SDL.h>
#include <print>

struct Vertex {
    float x, y, z;
    float r, g, b;
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

    SDL_Window* window = SDL_CreateWindow(
        "Donut",
        1200,
        800,
        SDL_WINDOW_OPENGL
    );

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
    
    bool running{true};

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}