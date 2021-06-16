//
// Created by jgorny on 6/14/21.
//
#ifndef ENDLESSRUNNER_GAMEMETHODS_H
#define ENDLESSRUNNER_GAMEMETHODS_H


//bool loadMedia() {
//    //Loading success flag
//    bool success = true;
//
//    //Load sprite sheet texture
//    if (!gSpriteSheetTexture.loadFromFile("tn.png")) {
//        printf("Failed to load walking animation texture!\n");
//        success = false;
//    } else {
//        //Set sprite clips
//        gSpriteClips[0].x = 0;
//        gSpriteClips[0].y = 0;
//        gSpriteClips[0].w = 64;
//        gSpriteClips[0].h = 205;
//
//        gSpriteClips[1].x = 64;
//        gSpriteClips[1].y = 0;
//        gSpriteClips[1].w = 64;
//        gSpriteClips[1].h = 205;
//
//        gSpriteClips[2].x = 128;
//        gSpriteClips[2].y = 0;
//        gSpriteClips[2].w = 64;
//        gSpriteClips[2].h = 205;
//
//        gSpriteClips[3].x = 196;
//        gSpriteClips[3].y = 0;
//        gSpriteClips[3].w = 64;
//        gSpriteClips[3].h = 205;
//    }
//
//    return success;
//}

//
//void close() {
//    //Free loaded images
//    delete gSpriteSheetTexture;
//
////    SDL_FreeSurface( gPNGSurface );
////    gPNGSurface = NULL;
//
//    //Destroy window
//    SDL_DestroyRenderer(gRenderer);
//    SDL_DestroyWindow(gWindow);
//    gWindow = NULL;
//    gRenderer = NULL;
//
//    //Quit SDL subsystems
//    IMG_Quit();
//    SDL_Quit();
//}




#endif //ENDLESSRUNNER_GAMEMETHODS_H
