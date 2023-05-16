#pragma once

#include <SDL.h>
#include "SDL_image.h"
#include <stdio.h>
#include <string>
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <fstream>
#include <iostream>
#include <vector>

//Screen dimension constants
const int SCREEN_WIDTH = 1280; // chiều dài cửa sổ
const int SCREEN_HEIGHT = 640;
     
// const int LEVEL_WIDTH = 1200;
// const int LEVEL_HEIGHT = 653; // chiều dài nền
const int FRAME_PER_SECOND = 50 ; // fps

const int NUM_FRAMES = 5;

const int NUM_FRAMES_1 = 8;

const int NUM_FRAMES_2 = 3;
                  
const int NUM_FRAMES_3 = 6;
//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

extern TTF_Font* gFont ;

static SDL_Event  g_event ; //Event handler

extern double degrees ;
          
extern SDL_RendererFlip flipType  ; // flip cho nhân vật

extern SDL_RendererFlip flipType_EX;

bool checkCollision (SDL_Rect a , SDL_Rect b);

#define MONEY 4

struct Input
{
	int A_input;
	int D_input;
	int S_input;
	int W_input;
	int C_input;
	int V_input;
};

// extern LTexture gTileTexture;

#define TILE_SIZE 64  // kích thước 1 mắt xích
#define MAX_MAP_X 400 // kích thước map chiều X  
#define MAX_MAP_Y 10  
#define BLANK_TILE 0 // khog duoc load hih anh
struct Map  // là đối tượng dữ liệu cho  map 
{
	// vị trí của ô map  như là vị trí phần tử trong mảng 2 chiều nhưng vị trí chính xác
	int start_x ; // vi tri bat dau cua khung hinh
	int start_y ; 

	int max_x_ ;	//vij tris  toi da cua map theo x
	int max_y_ ;  // tuong tu voi y

	int tile [MAX_MAP_Y][MAX_MAP_X]; // mảng 2 chiều chứa map
	const char *file_name_ ;
};


