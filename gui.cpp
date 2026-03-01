#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>
#include <switch.h>

class MinecraftLauncher {
public:
    bool init() {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) return false;
        
        // La Switch a une résolution de 1280x720 en mode portable et docké (720p interne)
        window = SDL_CreateWindow("JavaSwitch", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        IMG_Init(IMG_INIT_PNG);
        return true;
    }

    void renderMenu() {
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // Fond gris foncé style launcher
        SDL_RenderClear(renderer);

        // Ici, on chargerait l'image du bouton "PLAY" officiel
        // drawImage(btn_play_tex, 500, 600); 

        SDL_RenderPresent(renderer);
    }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};
