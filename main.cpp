#include <iostream>
#include "commonFunction.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Gamemap.h"
#include "Time.h"
#include "Button.h"
#include "SDL_ttf.h"
LTexture gBackgroundTexture; 
LButton gButtons[5];
MainObject test;      // nhân vật chính

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
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()  
{
	//Loading success flag
	bool success = true;

	if( !gBackgroundTexture.loadFromFile( "Image/a.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	gFont = TTF_OpenFont( "lazy.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };
		
		//Load stop prompt texture
		if (!gButtons[0].loadFromRenderedText(gFont,"PLAY",textColor))
		{
			printf( "Unable to render play prompt texture!\n" );
			success = false;
		}
		if(!gButtons[1].loadFromRenderedText(gFont,"PAUSE",textColor))
		{
			printf( "Unable to render pause prompt texture!\n" );
			success = false;
		}
		if(!gButtons[2].loadFromRenderedText(gFont,"UNPAUSED",textColor))
		{
			printf( "Unable to render unpause prompt texture!\n" );
			success = false;
		}
		if(!gButtons[3].loadFromRenderedText(gFont,"RETURN",textColor))
		{
			printf( "Unable to render exit prompt texture!\n" );
			success = false;
		}
		if(!gButtons[4].loadFromRenderedText(gFont,"EXIT",textColor))
		{
			printf( "Unable to render exit prompt texture!\n" );
			success = false;
		}
		gButtons[0].setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2+100,79, 28);
		gButtons[1].setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2+150,79, 28);
		gButtons[2].setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2+150,79, 28);
		gButtons[3].setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2+150,79, 28);
		gButtons[4].setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2+200,79, 28);
	}
	return success;
}

void close()  
{
	//Free loaded images
	gBackgroundTexture.free();
	test.free();
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	TTF_CloseFont( gFont );
	gFont = NULL;
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
		//Load media
		if( !loadMedia() ) 
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			while (true)
			{
				bool quit = false;
				
				SDL_Color textColor = { 0, 0, 0, 255 };
				
				LTimer timer;
				while (!quit)
				{
					while (SDL_PollEvent(&g_event) != 0)
						{
								//User requests quit
							if( g_event.type == SDL_QUIT )
							{
								quit = true;
							}
							//Reset start time on return keypress
							if(gButtons[0].handleEvent(&g_event))
								{
									quit = true;
									// thêm j thì giải phóng ở đây
								}
							if (gButtons[4].handleEvent(&g_event))
								{
									close();
									return 0;
								}
						}
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear( gRenderer );
					gButtons[0].render_();
					gButtons[4].render_();
					SDL_RenderPresent( gRenderer );
				}
			quit = false;
			GameMap game_Map;
			game_Map.LoadText("map/map01.dat");
			game_Map.LoadTiles();
			//Main loop flag
			while( !quit )
			{
				timer.start();
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

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );


				// Render background texture to screen hiện thị ra
				Map map_data = game_Map.GetMap(); // laays du lieu map trong game map
				test.SetMap_X_Y(map_data.start_x,map_data.start_y);
				gBackgroundTexture.render(0,0, nullptr,0,nullptr,SDL_FLIP_NONE);

				test.handleMove(map_data);

				test.Show(test.getRect().x, test.getRect().y );

				// test.handleBullet();
				game_Map.SetMap(map_data);
				game_Map.DrawMap();

				SDL_RenderPresent( gRenderer );
				// int real_time = time_game.get_ticks();
				// int time_one_frame = 1000 / FRAME_PER_SECOND ; //1000ms dc bn  khung hinh
				// if (real_time < time_one_frame)
				// 	{
				// 		int delay_time = time_one_frame - real_time ;
				// 		if (delay_time > 0)
				// 			SDL_Delay(delay_time);
				// 	}
			}
			quit = false;
			while (!quit) // vòng lặp game
			{
				while(SDL_PollEvent( &g_event ) != 0)
					{
					if( g_event.type == SDL_QUIT )
						{
							quit = true;
						}
					//Reset start time on return keypress
					if(gButtons[3].handleEvent(&g_event))
						{
							timer.stop();
							quit = true;
							// thêm j thì giải phóng ở đây
						}
					if (gButtons[4].handleEvent(&g_event))
						{
							close();
							return 0;
						}
					}
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				gButtons[3].render_();
				gButtons[4].render_();
				SDL_RenderPresent( gRenderer );
			}
		}		
	}
		close();
	}
	//Free resources and close SDL
	return 0;
}
