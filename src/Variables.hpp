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


