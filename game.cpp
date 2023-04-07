
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 639;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables khoi tao
		LTexture();
 
		//Deallocates memory phân bố bộ nhớ
		~LTexture();

		//Loads image at specified path tải ảnh từ đường dẫn
		bool loadFromFile( std::string path );

		//Deallocates texture phân bố kết cấu
		void free();

		//Renders texture at given point kết suất kết cấu tại điểm nhất định
		void render( int x, int y, SDL_Rect* clip = NULL );


		//Gets image dimensions nhận kích thước ảnh
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture  kết cấu phần cứng thực tế
		SDL_Texture* mTexture;

		//Image dimensions kích thước ảnh
		int mWidth;
		int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL 
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer kết 
SDL_Renderer* gRenderer = NULL;

const int WALKING_ANIMATION_FRAMES = 8;
SDL_Rect Walk_clips[WALKING_ANIMATION_FRAMES]; // chuỗi ảnh cho đi bộ 
const int RUN_ANIMATION_FRAMES = 8;
SDL_Rect Run_clips[RUN_ANIMATION_FRAMES];	// chuỗi cho chạy
const int JUMP_ANIMATION_FRAMES = 8;
SDL_Rect Jump_clips[JUMP_ANIMATION_FRAMES]; // chuỗi cho  nhảy lên
//Scene textures kết cấu ảnh
LTexture WalkTexture;
LTexture RunTexture;
LTexture gBackgroundTexture;
LTexture JumpTexture;


LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image  colorkey trước khi tạo kết cấu mới
		 SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions lấy kích thước ảnh
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
  
	//Return success
 	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render( int x, int y, SDL_Rect* clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}
int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

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
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
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

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load Foo' texture
	//Load background texture
	if( !gBackgroundTexture.loadFromFile( "bgr.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	if( !WalkTexture.loadFromFile( "Walk.png" ) )
	{
		printf( "Failed to load Walk' texture image!\n" );
		success = false;
	}
	else
	{
		Walk_clips[0].x =0;
		Walk_clips[0].y =60;
		Walk_clips[0].w =128;
		Walk_clips[0].h =64;

		Walk_clips[1].x =128;
		Walk_clips[1].y =60;
		Walk_clips[1].w =128;
		Walk_clips[1].h =70;

		Walk_clips[2].x =256;
		Walk_clips[2].y =60;
		Walk_clips[2].w =128;
		Walk_clips[2].h =70;

		Walk_clips[3].x =384;
		Walk_clips[3].y =60;
		Walk_clips[3].w =128;
		Walk_clips[3].h =70;

		Walk_clips[4].x =512;
		Walk_clips[4].y =60;
		Walk_clips[4].w =128;
		Walk_clips[4].h =70;

		Walk_clips[5].x =640;
		Walk_clips[5].y =60;
		Walk_clips[5].w =128;
		Walk_clips[5].h =70;

		Walk_clips[6].x =768;
		Walk_clips[6].y =60;
		Walk_clips[6].w =128;
		Walk_clips[6].h =70;

		Walk_clips[7].x =896;
		Walk_clips[7].y =60;
		Walk_clips[7].w =128;
		Walk_clips[7].h =70;
	}
	if( !RunTexture.loadFromFile( "Run.png" ) )
	{
		printf( "Failed to load Run' texture image!\n" );
		success = false;
	}
	else
	{
		Run_clips[0].x =0;
		Run_clips[0].y =60;
		Run_clips[0].w =128;
		Run_clips[0].h =64;

		Run_clips[1].x =128;
		Run_clips[1].y =60;
		Run_clips[1].w =128;
		Run_clips[1].h =70;

		Run_clips[2].x =256;
		Run_clips[2].y =60;
		Run_clips[2].w =128;
		Run_clips[2].h =70;

		Run_clips[3].x =384;
		Run_clips[3].y =60;
		Run_clips[3].w =128;
		Run_clips[3].h =70;

		Run_clips[4].x =512;
		Run_clips[4].y =60;
		Run_clips[4].w =128;
		Run_clips[4].h =70;

		Run_clips[5].x =640;
		Run_clips[5].y =60;
		Run_clips[5].w =128;
		Run_clips[5].h =70;

		Run_clips[6].x =768;
		Run_clips[6].y =60;
		Run_clips[6].w =128;
		Run_clips[6].h =70;

		Run_clips[7].x =896;
		Run_clips[7].y =60;
		Run_clips[7].w =128;
		Run_clips[7].h =70;
	}
	if( !JumpTexture.loadFromFile( "Jump.png" ) )
	{
		printf( "Failed to load Jump' texture image!\n" );
		success = false;
	}
	else
	{
		Jump_clips[0].x =0;
		Jump_clips[0].y =40;
		Jump_clips[0].w =128;
		Jump_clips[0].h =84;

		Jump_clips[1].x =128;
		Jump_clips[1].y =40;
		Jump_clips[1].w =128;
		Jump_clips[1].h =84;

		Jump_clips[2].x =256;
		Jump_clips[2].y =40;
		Jump_clips[2].w =128;
		Jump_clips[2].h =84;

		Jump_clips[3].x =384;
		Jump_clips[3].y =40;
		Jump_clips[3].w =128;
		Jump_clips[3].h =84;

		Jump_clips[4].x =512;
		Jump_clips[4].y =40;
		Jump_clips[4].w =128;
		Jump_clips[4].h =84;

		Jump_clips[5].x =640;
		Jump_clips[5].y =40;
		Jump_clips[5].w =128;
		Jump_clips[5].h =84;

		Jump_clips[6].x =768;
		Jump_clips[6].y =40;
		Jump_clips[6].w =128;
		Jump_clips[6].h =84;

		Jump_clips[7].x =896;
		Jump_clips[7].y =40;
		Jump_clips[7].w =128;
		Jump_clips[7].h =84;
	}
	return success;
}

void close()
{
	//Free loaded images
	WalkTexture.free();
	gBackgroundTexture.free();
	RunTexture.free();
	JumpTexture.free();
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
	//Start up SDL and create window
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
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			//Current animation frame
			int frame_Walk = 0;
			int frame_Run = 0;
			int frame_Jump = 0;
			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render background texture to screen hiện thị ra
				gBackgroundTexture.render( 0, 0, nullptr );

				SDL_Rect * CurrentClip2 = &Run_clips[frame_Run/16];
				SDL_Rect * CurrentClip = &Walk_clips[frame_Walk /16];
				SDL_Rect * CurrentClip3 = &Jump_clips[frame_Jump/16];
				WalkTexture.render(30,480 ,CurrentClip);
				RunTexture.render (120,480,CurrentClip2);
				JumpTexture.render( 500, 440, CurrentClip3);
				frame_Walk ++;
				frame_Run ++;
				frame_Jump ++;
				if (frame_Walk /8 > WALKING_ANIMATION_FRAMES)
					{
						frame_Walk =0 ;
					}
				if (frame_Run /8 > RUN_ANIMATION_FRAMES)
					{
						frame_Run =0 ;
					}
				if (frame_Jump /8 > JUMP_ANIMATION_FRAMES)
					{
						frame_Jump =0 ;
					}
				// Update screen cập nhật màn hình
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}