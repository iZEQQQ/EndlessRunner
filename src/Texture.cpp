//
// Created by jgorny on 6/14/21.
//
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <vector>
#include "Texture.hpp"

void Texture::render(int x, int y) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x,
                           y,
                           spritesArr[currentSprite].w,
                           spritesArr[currentSprite].h};

    SDL_RenderCopy(gRenderer, mTexture, &spritesArr[currentSprite], &renderQuad);
    currentSprite = (currentSprite + 1) % spritesCount;
}


Texture::Texture(SDL_Renderer *renderer, const std::string &path, SDL_Rect *sprites, int count) {
    gRenderer = renderer;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        std::cout<<IMG_GetError()<<std::endl;
    }
    mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    spritesArr = sprites;
    spritesCount = count;
}


Texture::~Texture() {
    SDL_DestroyTexture(mTexture);
    delete spritesArr;
}


