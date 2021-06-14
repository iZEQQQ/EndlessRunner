//
// Created by jgorny on 6/14/21.
//
#ifndef ENDLESSRUNNER_LTEXTURECLASS_H
#define ENDLESSRUNNER_LTEXTURECLASS_H

class LTexture {
private:
    //The actual hardware texture
    SDL_Texture *mTexture;

    SDL_Renderer *gRenderer;

    //Image dimensions
    int mWidth;
    int mHeight;

public:
    //Initializes variables konstruktor
    LTexture(SDL_Renderer *, const std::string&);

    //Deallocates memory
    ~LTexture();

    //Renders texture at given point
    void render(int x, int y, SDL_Rect *clip = NULL);

    //Gets image dimensions
    int getWidth();

    int getHeight();

};

void LTexture::render(int x, int y, SDL_Rect *clip) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    //Set clip rendering dimensions
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}


LTexture::LTexture(SDL_Renderer *renderer, const std::string& path) {
    gRenderer = renderer;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
}


LTexture::~LTexture() {
    SDL_DestroyRenderer(gRenderer);
}



#endif //ENDLESSRUNNER_LTEXTURECLASS_H
