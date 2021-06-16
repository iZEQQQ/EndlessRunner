//
// Created by jgorny on 6/14/21.
//
#ifndef ENDLESSRUNNER_TEXTURE_HPP
#define ENDLESSRUNNER_TEXTURE_HPP

class Texture {
private:
    //The actual hardware texture
    SDL_Texture *mTexture;

    SDL_Renderer *gRenderer;

    SDL_Rect *splitesArr;

    int splitesCount;

    int currentSplite = 0;
    //Image dimensions
    int mWidth;

    int mHeight;

public:
    //Initializes variables konstruktor
    Texture(SDL_Renderer *, const std::string &, SDL_Rect *, int);

    //Deallocates memory
    ~Texture();

    //Renders texture at given point
    void render(int x, int y);

    //Gets image dimensions
    int getWidth();

    int getHeight();

};


#endif //ENDLESSRUNNER_TEXTURE_HPP
