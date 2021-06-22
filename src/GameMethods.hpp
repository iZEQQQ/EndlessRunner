//
// Created by jgorny on 6/14/21.
//
#ifndef ENDLESSRUNNER_GAMEMETHODS_H
#define ENDLESSRUNNER_GAMEMETHODS_H


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

    //Calculate the sides of rect obstacle
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

void points(SDL_Renderer *renderer, int points) {
    TTF_Font *lazy = TTF_OpenFont("assets/lazy.ttf", 80);
    SDL_Color black = {0, 0, 0};
    SDL_Surface *surfaceMessage =
            TTF_RenderText_Solid(lazy, (" Your score: " + std::to_string(points)).c_str(), black);
    SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 400; // controls the width of the rect
    Message_rect.h = 100;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}


#endif //ENDLESSRUNNER_GAMEMETHODS_H
