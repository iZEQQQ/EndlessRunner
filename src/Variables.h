#include "LTextureClass.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The window renderer
SDL_Renderer *gRenderer = NULL;

//Scene sprites
//SDL_Rect gSpriteClips[4];
LTexture *gSpriteSheetTexture;
