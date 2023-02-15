#include "SDL.h" 

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Luna", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 800, 600);

    while (true) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: {
                return 1;
            } break;

            }
        }
        SDL_RenderClear(renderer);
        
        SDL_Rect window_rect = {0, 0, 800, 600};

        void *pixels_dst;
        int pitch;
        SDL_LockTexture(texture, &window_rect, &pixels_dst, &pitch);

        for(int i = 0; i < 90000; ++i) {
            ((uint32_t*) pixels_dst)[i] = 0xFFFFFFFF;
        }

        SDL_UnlockTexture(texture);

        SDL_RenderCopy(renderer, texture, &window_rect, &window_rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

  return 0;
}