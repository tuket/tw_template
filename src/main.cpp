#include <stdio.h>
#include <SDL.h>
#include <glad/glad.h>
#include <tgl/init.hpp>
#include <tgl/render_target.hpp>

SDL_Window* window = nullptr;
SDL_GLContext glContext;
bool gameLoopRunning = true;

constexpr int INIT_WINDOW_WIDTH = 800;
constexpr int INIT_WINDOW_HEIGHT = 600;

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return -1;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    window = SDL_CreateWindow("title",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
    glContext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glContext);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    if(gladLoadGL() == 0) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return -1;
    }
    tgl::viewport(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);
    tgl::scissor(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);

    while(gameLoopRunning)
    {
        static SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                gameLoopRunning = false;
                break;
            }
        }

        tgl::clearColor(0, 0.1f, 0.1f, 0.f);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}