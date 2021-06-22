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

bool collisionDetection(SDL_Rect obstacle, SDL_Rect guy) {
    //The sides of the rectangles
    int leftObstacle, leftGuy;
    int rightObstacle, rightGuy;
    int topObstacle, topGuy;
    int bottomObstacle, bottomGuy;

    //Calculate the sides of rect A
    leftObstacle = obstacle.x;
    rightObstacle = obstacle.x + obstacle.w;
    topObstacle = obstacle.y;
    bottomObstacle = obstacle.y + obstacle.h;

    //Calculate the sides of rect B
    leftGuy = guy.x;
    rightGuy = guy.x + guy.w;
    topGuy = guy.y;
    bottomGuy = guy.y + guy.h;

    //If any of the sides from A are outside of B
    if (bottomObstacle <= topGuy) {
        return false;
    }

    if (topObstacle >= bottomGuy) {
        return false;
    }

    if (rightObstacle <= leftGuy) {
        return false;
    }

    if (leftObstacle >= rightGuy) {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
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
    Texture *currentTexture = obOne;


    milliseconds dt(150);

    steady_clock::time_point current_time = steady_clock::now(); // remember current time

    int baseGuyX = 550;
    int baseGuyY = 189;
    int currentGuyX = 550;
    int currentGuyY = 189;

    int obstacleX = 0;
    int obstacleY = 330;
    int obstacleVelocity = 40;
    int obstacleAcc = 1;
    int frameCounter = 0;
    int freeFrames = 30;

    bool inMotion = false;
    int guyVelocity = 0;
    int jumpStartVelocity = -130;
    int gravity = 75;
    int points = 0;

    SDL_Rect obstacleSize;
    obstacleSize.x = obstacleX;
    obstacleSize.y = obstacleY;
    obstacleSize.w = 31;
    obstacleSize.h = 65;

    SDL_Rect guySize;
    guySize.x = currentGuyX;
    guySize.y = currentGuyY;
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
                            guyVelocity = jumpStartVelocity;
                            inMotion = true;
                        }
                }
            }
        }
        frameCounter++;
        if (frameCounter % freeFrames == 0) {
            obstacleVelocity = obstacleVelocity + obstacleAcc;
            frameCounter = 0;
        }

        obstacleX = obstacleX + obstacleVelocity;
        if (obstacleX >= SCREEN_WIDTH || collisionDetection(obstacleSize, guySize)) {
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
            points = points + 10;
            std::cout << "Points: " << points << std::endl;
            obstacleX = 0;
        } else {
            std::cout << "You Lost" << " Your score: " << points << std::endl;
            game_active = false;
        }

        if (inMotion) {
            currentGuyY = currentGuyY + guyVelocity;
            if (currentGuyY > baseGuyY) {
                currentGuyY = baseGuyY;
                guyVelocity = 0;
                inMotion = false;
            }
            if (inMotion) {
                guyVelocity = guyVelocity + gravity;
            }
        }


        //        Rendering all sprites
        background->render(0, 0);
        floor->render(0, 395);
        guy->render(currentGuyX, currentGuyY);
        currentTexture->render(obstacleX, 330);

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
    IMG_Quit();
    SDL_Quit();
    return 0;
}