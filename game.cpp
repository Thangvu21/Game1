#include <iostream>
#include "commonFunction.h"
#include "BaseObject.h"
#include "MainObject.h"
#include <fstream>
LTexture gBackgroundTexture;
       
MainObject test;      
                 
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading khởi tạo PNG
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()  //Tile* tiles[]
{
	//Loading success flag
	bool success = true;

	if( !gBackgroundTexture.loadFromFile( "Image//image.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	return success;
}
 
void close()
{

	// for( int i = 0; i < TOTAL_TILES; ++i )
	// {
	// 	 if( tiles[ i ] != NULL )
	// 	 {
	// 		delete tiles[ i ];
	// 		tiles[ i ] = NULL;
	// 	 }
	// }
	//Free loaded images
	gBackgroundTexture.free();
	test.free();
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		// Tile* tileSet[ TOTAL_TILES ];
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	

			//Main loop flag
			SDL_Rect camera = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };

			bool quit = false;
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( & g_event ) != 0 )
				{
					//User requests quit
					if( g_event.type == SDL_QUIT )
					{
						quit = true;
					}
					test.handleEvent(g_event);
				}

				test.handleMove();

				test.setCamera(camera);

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				// Render background texture to screen hiện thị ra
				gBackgroundTexture.render(0,0, &camera,0,nullptr,SDL_FLIP_NONE);
				
				test.Show(test.getRect().x, test.getRect().y ,camera);
				
				SDL_RenderPresent( gRenderer );
			}
		}
		close();
	}

	//Free resources and close SDL
	
	return 0;
}
