#include "Texture.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int BASE_GUY_Y = 189;
int obstacleVelocity = 40;
const int OBSTACLE_ACC = 1;
int frameCounter = 0;
const int FREE_FRAMES = 30;

bool inMotion = false;
int guyVelocity = 0;
const int JUMP_START_VELOCITY = -130;
const int GRAVITY = 75;
int currentPoints = 0;


////The window we'll be rendering to
//SDL_Window *gWindow = NULL;
//
////The window renderer
//SDL_Renderer *gRenderer = NULL;

//Scene sprites
//SDL_Rect gSpriteClips[4];
//Texture *gSpriteSheetTexture;

//Loads individual image
//SDL_Surface* loadSurface( std::string path );

//Current displayed PNG image
//SDL_Surface* gPNGSurface = NULL;

//The surface contained by the window
//SDL_Surface* gScreenSurface = NULL;