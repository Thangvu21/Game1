#include "commonFunction.h"
                          
SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;
                    
double degrees = 0 ;
   
SDL_RendererFlip flipType = SDL_FLIP_NONE ;

TTF_Font* gFont = NULL;

// SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

// bool checkCollision (SDL_Rect a , SDL_Rect b)
// {
// 	int left_a, left_b ;
// 	int right_a,right_b;
// 	int top_a , top_b;
// 	int bot_a , bot_b;
// 	// check tu a -> b
// 	left_a = a.x;
// 	left_b = b.x;

// 	right_a = a.x+a.w;
// 	right_b = b.x+b.w;

// 	top_a = a.y;
// 	top_b = b.y;

// 	bot_a = a.y+a.h;
// 	bot_b = b.y+ b.h;

// 	if (top_a >= bot_b) 
// 		{
// 			return false;
// 		}
// 	if ( top_b >= bot_a)
// 		{
// 			return false;
// 		}
// 	if (left_a >= right_b)
// 		{
// 			return false;
// 		}
// 	if ( left_b >= right_a)
// 		{
// 			return false;
// 		}
// 	return true;
//   } 
                            

