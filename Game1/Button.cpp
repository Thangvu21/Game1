#include "Button.h"
LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrent_Status = BUTTON_MOUSE_OUT;
}

void LButton::setPosition( int x, int y,int w,int h )
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.w = w;
	mPosition.h = h;
}

bool LButton::handleEvent( SDL_Event* e )
{
	
	//If mouse event happened
	if(  e->type == SDL_MOUSEBUTTONDOWN  )
	{
		bool inside = true;
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x +mPosition.w )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + mPosition.h )
		{
			inside = false;
		}
		if (inside )
			{
				return true;
			}
			
	}
	return false;
}
	
void LButton::render_()
{
	//Show current button sprite
	render( mPosition.x, mPosition.y,nullptr,0,nullptr,SDL_FLIP_NONE );
}