#ifndef BaseObject_h_
#define BaseObject_h_
#include "commonFunction.h"

// Texture wrapper class
class LTexture
{
public:
	// Initializes variables
	LTexture();

	// Deallocates memory
	~LTexture();

	// Loads image at specified path
	bool loadFromFile(std::string path);

	#if defined(SDL_TTF_MAJOR_VERSION)
	//Creates image from font string
	bool loadFromRenderedText( TTF_Font* gFont, std::string textureText, SDL_Color textColor );
	#endif

	// Deallocates texture
	void free();

	//Set color modulation
	void setColor( Uint8 red, Uint8 green, Uint8 blue );

	//Set blending
	void setBlendMode( SDL_BlendMode blending );

	//Set alpha modulation
	void setAlpha( Uint8 alpha );

	// Renders texture at given point
	void render(int x, int y, SDL_Rect *clip , double angle, SDL_Point* center, SDL_RendererFlip flip );

	// Gets image dimensions
	int getWidth();
	int getHeight();

protected:
	// The actual hardware texture
	SDL_Texture *mTexture;

	// Image dimensions
	int mWidth;
	int mHeight;
};

#endif