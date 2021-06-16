//
// Created by jgorny on 6/14/21.
//
#include "Texture.hpp"

void Texture::render(int x, int y) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, splitesArr[currentSplite].w, splitesArr[currentSplite].h};
    //Set clip rendering dimensions
//    if (clip != NULL) {
//        renderQuad.w = clip->w;
//        renderQuad.h = clip->h;
//    }
//
//    //Render to screen
    SDL_RenderCopy(gRenderer, mTexture, &splitesArr[currentSplite], &renderQuad);
    currentSplite = (currentSplite + 1) % splitesCount;
}


Texture::Texture(SDL_Renderer *renderer, const std::string &path, SDL_Rect *splices, int count) {
    gRenderer = renderer;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    splitesArr = splices;
    splitesCount = count;
}


Texture::~Texture() {
    SDL_DestroyTexture(mTexture);
}


