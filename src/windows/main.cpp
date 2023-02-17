#include <thread>

#include "SDL.h"

#define _ENABLE_LUNA_LOGGER_
#include "luna.hpp"

const u32 SCREEN_WIDTH = 800;
const u32 SCREEN_HEIGHT = 600;

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Luna", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    luna::Program program(SCREEN_WIDTH, SCREEN_HEIGHT);

    while (true) {
        SDL_Event ev;

        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_QUIT: {
                    return 1;
                }
                case SDL_MOUSEBUTTONDOWN: {   
                    luna::Event event;
                    event.touchEvent = luna::TouchEvent{ luna::EventType::TOUCH_EVENT, ev.button.x, ev.button.y };
                    luna::EventManager::pushEvent(event);
                    break;
                }
                case SDL_MOUSEBUTTONUP: {   
                    luna::Event event;
                    event.touchReleaseEvent = luna::TouchRreleaseEvent{ luna::EventType::TOUCH_RELEASE_EVENT, ev.button.x, ev.button.y };
                    luna::EventManager::pushEvent(event);
                    break;
                }
                case SDL_MOUSEMOTION: {
                    luna::Event event;
                    event.touchMotionEvent = luna::TouchMotionEvent{ luna::EventType::TOUCH_MOTION_EVENT, ev.button.x, ev.button.y };
                    luna::EventManager::pushEvent(event);
                    break;
                }
            }
        }

        SDL_RenderClear(renderer);
        
        SDL_Rect window_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

        void *pixels_dst;
        int pitch;
        SDL_LockTexture(texture, &window_rect, &pixels_dst, &pitch);

        auto begin = std::chrono::high_resolution_clock::now();                                                                                                                                     
        
        {
            program.Update();
            program.Render((u32*) pixels_dst);

            auto end = std::chrono::high_resolution_clock::now();                                                                
            double durationMs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / 1000000.0; 

            if(durationMs < 16.0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(16 - (u32)durationMs));
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        double loopDurationMs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count(); 
        luna::LUNA_LOG("[INFO][SDL] Last render took: " + std::to_string(loopDurationMs / 1000000.0) + "ms \n");

        SDL_UnlockTexture(texture);

        SDL_RenderCopy(renderer, texture, &window_rect, &window_rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

  return 0;
}