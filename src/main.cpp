#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

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


int main(int, char **) {
    using namespace std;
    using namespace std::chrono;

    errcheck(SDL_Init(SDL_INIT_VIDEO) != 0);
    errcheck(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG);
    errcheck(TTF_Init() != 0);


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
    Texture *currentTexture = obOne;

    milliseconds dt(150);

    steady_clock::time_point current_time = steady_clock::now(); // remember current time

    SDL_Rect obstacleSize;
    obstacleSize.x = 0;
    obstacleSize.y = 330;
    obstacleSize.w = 31;
    obstacleSize.h = 65;

    SDL_Rect guySize;
    guySize.x = 550;
    guySize.y = 189;
    guySize.w = 64;
    guySize.h = 205;


    for (bool game_active = true; game_active;) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) { // check if there are some events
            if (event.type == SDL_QUIT) {
                game_active = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        if (inMotion == false) {
                            guyVelocity = JUMP_START_VELOCITY;
                            inMotion = true;
                        }
                }
            }
        }
        frameCounter++;
        if (frameCounter % FREE_FRAMES == 0) {
            obstacleVelocity = obstacleVelocity + OBSTACLE_ACC;
            frameCounter = 0;
        }

        obstacleSize.x = obstacleSize.x + obstacleVelocity;
        if (obstacleSize.x >= SCREEN_WIDTH) {
            int number = rand() % 3;
            switch (number) {
                case 0:
                    currentTexture = obOne;
                    break;
                case 1:
                    currentTexture = obTwo;
                    break;
                case 2:
                    currentTexture = obThree;
                    break;
            }
            currentPoints = currentPoints + 10;
            obstacleSize.x = 0;
        }

        if (inMotion) {
            guySize.y = guySize.y + guyVelocity;
            if (guySize.y > BASE_GUY_Y) {
                guySize.y = BASE_GUY_Y;
                guyVelocity = 0;
                inMotion = false;
            }
            if (inMotion) {
                guyVelocity = guyVelocity + GRAVITY;
            }
        }
        if (collisionDetection(obstacleSize, guySize)) {
            std::cout << "Game over" << " Your score: " << currentPoints << std::endl;
            game_active = false;
        }

        //        Rendering all sprites
        background->render(0, 0);
        floor->render(0, 395);
        guy->render(guySize.x, guySize.y);
        points(renderer, currentPoints);
        currentTexture->render(obstacleSize.x, 330);


        //Update the surface
        SDL_UpdateWindowSurface(window);
        SDL_RenderPresent(renderer); // draw frame to screen

        this_thread::sleep_until(current_time = current_time + dt);
    }

//    destroying all sprites and freeing memory
    guy->~Texture();
    obOne->~Texture();
    obThree->~Texture();
    obTwo->~Texture();
    floor->~Texture();
    background->~Texture();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}