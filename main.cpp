#include <iostream>
#include "commonFunction.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Gamemap.h"
#include "Time.h"
#include "Button.h"
#include "SDL_ttf.h"
#include "Explosion.h"
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
	gFont = TTF_OpenFont( "menu/GameName.ttf", 28 );
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


std:: vector<Explosion *> Make_Explosion_List()
	{
		std:: vector<Explosion*> List_Explosion;
		Explosion * p_EX =  new Explosion;
			if (p_EX != NULL)
				{
					p_EX->set_clip_Explosion();
					p_EX->set_Position(14,6);
					List_Explosion.push_back(p_EX);
				}
		Explosion * p_EX_1 =  new Explosion;
			if (p_EX_1 != NULL)
				{
					p_EX_1->set_clip_Explosion();
					p_EX_1->set_Position(108,6);
					List_Explosion.push_back(p_EX_1);
				}
		Explosion * p_EX_2 =  new Explosion;
			if (p_EX_2 != NULL)
				{
					p_EX_2->set_clip_Explosion();
					p_EX_2->set_Position(250,6);
					List_Explosion.push_back(p_EX_2);
				}
		Explosion * p_EX_3 =  new Explosion;
			if (p_EX_3 != NULL)
				{
					p_EX_3->set_clip_Explosion();
					p_EX_3->set_Position(70,5);
					List_Explosion.push_back(p_EX_3);
				}
		Explosion * p_EX_4 =  new Explosion;
			if (p_EX_4 != NULL)
				{
					p_EX_4->set_clip_Explosion();
					p_EX_4->set_Position(390,6);
					List_Explosion.push_back(p_EX_4);
				}
		Explosion * p_EX_5 = new Explosion;
			if (p_EX_5 != NULL)
				{
					p_EX_5->set_clip_Explosion();
					p_EX_5->set_Position(120,6);
					List_Explosion.push_back(p_EX_5);
				}
		return List_Explosion;
	}
void close_ (std::vector<Explosion*> List_Explosion)
	{
		for (int i = 0; i< int(List_Explosion.size()); i++)
			{
				Explosion * p_EX = List_Explosion[i];
					if (p_EX != NULL)
						{
							p_EX->free();
						}	
			}
	}
void close()  
{
	//Free loaded images
	gBackgroundTexture.free();
	test.free();	
	// test_.free();
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
				int frame =0;
				LTimer timer;
				while (!quit)
				{
					while (SDL_PollEvent(&g_event) != 0)
						{
								//User requests quit
							if( g_event.type == SDL_QUIT )
							{
								close();
								return 0;
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
			Map map_data = game_Map.GetMap(); // laays du lieu map trong game map
			Map EX = game_Map.GetMap();
			std::vector<Explosion*> L_Explosion = Make_Explosion_List();
			
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
						test.free();
						close_(L_Explosion);
						return 0;
					}
					test.handleEvent(g_event);
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				// Render background texture to screen hiện thị ra
				
				test.SetMap_X_Y(map_data.start_x,map_data.start_y);
				gBackgroundTexture.render(0,0, nullptr,0,nullptr,SDL_FLIP_NONE);

				test.handleMove(map_data);

				test.Show(test.getRect().x, test.getRect().y );

				// test.handleBullet();
				game_Map.SetMap(map_data);
				game_Map.DrawMap();
				for (int i = 0; i< int(L_Explosion.size()); i++)
					{
						Explosion * p_EX = L_Explosion[i];
						if (p_EX != NULL)
							{
								p_EX->SetMap_X_Y(map_data.start_x,map_data.start_y);
								p_EX->move_Explosion(map_data);
								p_EX->show_Explosion();
							}
						else 
							{
								std::cout<<"need fixx"<<std::endl;
							}
						SDL_Rect rect_player = test.getRect(); // laays ra cua main
						SDL_Rect rect_EX = p_EX->get_Rect(); // lay cua EX
						bool check_end  = checkCollision(rect_player,rect_EX);
						if (check_end == true)
							{
								quit = true;
							}
					}
				
				if ( test.checkMap(map_data) == false)
					{
						quit = true;
					}
				SDL_RenderPresent( gRenderer );
				int real_time = timer.getTicks();
				int time_one_frame = 1000 / FRAME_PER_SECOND ; //1000ms dc bn  khung hinh
				if (real_time < time_one_frame)
					{
						int delay_time = time_one_frame - real_time ;
						if (delay_time > 0)
							SDL_Delay(delay_time);
					}
			}
			quit = false;
			while (!quit) // vòng lặp game
			{
				while(SDL_PollEvent( &g_event ) != 0)
					{
					if( g_event.type == SDL_QUIT )
						{
							test.free();
							close_(L_Explosion); // giair phongs booj nhows
							return 0;
						}
					//Reset start time on return keypress
					if(gButtons[3].handleEvent(&g_event))
						{
							timer.stop();
							test.Set_x_y(100,100);
							
							test.Set_status(4);
							test.Set_status1(0);
							quit = true;

							// thêm j thì giải phóng ở đây
						}
					if (gButtons[4].handleEvent(&g_event))
						{
							test.free();
							close_(L_Explosion); // giair phongs booj nhows
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
