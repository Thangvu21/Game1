#ifndef BUTTON_H_
#define BUTTON_H

#include "commonFunction.h"
#include "BaseObject.h"

class LButton : public LTexture
{
	public:
        enum Status_Button
        {
            BUTTON_MOUSE_OUT,
            BUTTON_MOUSE_MOTION
        };

		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y ,int w,int h );

		//Handles mouse event
		bool handleEvent( SDL_Event* e );
	
		//Shows button sprite
		void render_();

	private:
		//Top left position
		SDL_Rect mPosition;

		//Currently used global sprite
		Status_Button mCurrent_Status;
};
#endif