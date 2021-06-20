#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <thread>
#include <tuple>
#include <vector>
#include "Variables.hpp"
#include "Texture.hpp"
#include "GameMethods.hpp"


// check for errors
#define errcheck(e)                                                            \
  {                                                                            \
    if (e) {                                                                   \
      cout << SDL_GetError() << endl;                                          \
      SDL_Quit();                                                              \
      return -1;                                                               \
    }                                                                          \
  }

//na kazda metode kolejna taka metoda
Texture *guySprite(SDL_Renderer *renderer) {
    SDL_Rect *gSpriteClips = new SDL_Rect[4];

    gSpriteClips[0].x = 0;
    gSpriteClips[0].y = 0;
    gSpriteClips[0].w = 64;
    gSpriteClips[0].h = 205;

    gSpriteClips[1].x = 64;
    gSpriteClips[1].y = 0;
    gSpriteClips[1].w = 64;
    gSpriteClips[1].h = 205;

    gSpriteClips[2].x = 128;
    gSpriteClips[2].y = 0;
    gSpriteClips[2].w = 64;
    gSpriteClips[2].h = 205;

    gSpriteClips[3].x = 196;
    gSpriteClips[3].y = 0;
    gSpriteClips[3].w = 64;
    gSpriteClips[3].h = 205;


    Texture *texture = new Texture(renderer, "assets/tn.png", gSpriteClips, 4);
    return texture;
}


Texture *obstacleOneSprite(SDL_Renderer *renderer) {
    SDL_Rect *gSpriteClips = new SDL_Rect[1];


    gSpriteClips[0].x = 0;
    gSpriteClips[0].y = 0;
    gSpriteClips[0].w = 31;
    gSpriteClips[0].h = 65;


    Texture *texture = new Texture(renderer, "assets/obstacle1.png", gSpriteClips, 1);
    return texture;
}

Texture *obstacleTwoSprite(SDL_Renderer *renderer) {
    SDL_Rect *gSpriteClips = new SDL_Rect[1];


    gSpriteClips[0].x = 0;
    gSpriteClips[0].y = 0;
    gSpriteClips[0].w = 31;
    gSpriteClips[0].h = 65;


    Texture *texture = new Texture(renderer, "assets/obstacle2.png", gSpriteClips, 1);
    return texture;
}

Texture *obstacleThreeSprite(SDL_Renderer *renderer) {
    SDL_Rect *gSpriteClips = new SDL_Rect[1];

    gSpriteClips[0].x = 0;
    gSpriteClips[0].y = 0;
    gSpriteClips[0].w = 31;
    gSpriteClips[0].h = 65;


    Texture *texture = new Texture(renderer, "assets/obstacle3.png", gSpriteClips, 1);
    return texture;
}

Texture *backgroundSprite(SDL_Renderer *renderer) {
    SDL_Rect *gSpriteClips = new SDL_Rect[1];

    gSpriteClips[0].x = 0;
    gSpriteClips[0].y = 0;
    gSpriteClips[0].w = 692;
    gSpriteClips[0].h = 559;


    Texture *texture = new Texture(renderer, "assets/background.png", gSpriteClips, 1);
    return texture;
}

Texture *floorSprite(SDL_Renderer *renderer) {
    SDL_Rect *gSpriteClips = new SDL_Rect[1];

    gSpriteClips[0].x = 0;
    gSpriteClips[0].y = 0;
    gSpriteClips[0].w = 692;
    gSpriteClips[0].h = 288;


    Texture *texture = new Texture(renderer, "assets/floor.png", gSpriteClips, 1);
    return texture;
}


void renderRunner() {
    //Walking animation
    const int WALKING_ANIMATION_FRAMES = 4;
    SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
//    Texture gSpriteSheetTexture;
}

int main(int, char **) {
    using namespace std;
    using namespace std::chrono;

    errcheck(SDL_Init(SDL_INIT_VIDEO) != 0);
    errcheck(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG);


    SDL_Window *window = SDL_CreateWindow(
            "iZEQ the Endless Runner", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    errcheck(window == nullptr);

    SDL_Renderer *renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED); // SDL_RENDERER_PRESENTVSYNC
    errcheck(renderer == nullptr);


    Texture *floor = floorSprite(renderer);
    Texture *background = backgroundSprite(renderer);
    Texture *guy = guySprite(renderer);
    Texture *obOne = obstacleOneSprite(renderer);
    Texture *obTwo = obstacleTwoSprite(renderer);
    Texture *obThree = obstacleThreeSprite(renderer);


    milliseconds dt(150);

    steady_clock::time_point current_time = steady_clock::now(); // remember current time
    for (bool game_active = true; game_active;) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) { // check if there are some events
            if (event.type == SDL_QUIT) {
                game_active = false;
            }
        }

        background->render(0, 0);
        floor->render(0, 395);
        guy->render(550, 189);
        obOne->render(140, 330);
        obTwo->render(250, 330);
        obThree->render(70, 330);


        //Update the surface
        SDL_UpdateWindowSurface(window);
        SDL_RenderPresent(renderer); // draw frame to screen

        this_thread::sleep_until(current_time = current_time + dt);
    }

    guy->~Texture();
    obOne->~Texture();
    obThree->~Texture();
    obTwo->~Texture();
    floor->~Texture();
    background->~Texture();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}