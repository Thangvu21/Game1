#include "Explosion.h"
Explosion :: Explosion()
{
    velocity_x = 0;
    acceleration_x = 0;
    frame_Explosion = 0;
    mExplosion_rect.x = 0;
    mExplosion_rect.y = 0;
}
Explosion :: ~Explosion()
{
    free();
}
int Explosion :: Get_Height()
{
    return mHeight;
}
int Explosion :: Get_Width()
{
    return mWidth;
}
void Explosion ::set_Position(int x,int y)
{
    mExplosion_rect.x  = x;
    mExplosion_rect.y  = y;
}
void Explosion ::set_clip_Explosion()
{
    for (int i=0; i<5; i++)
		{
			for (int j=0; j<5; j++)
				{
					clip_Explosion[i*5+j].x = i*100;
					clip_Explosion[i*5+j].y	= j*100;
					clip_Explosion[i*5+j].w = mWidth/5;
					clip_Explosion[i*5+j].h = mHeight/5;
				}
		}
}
void Explosion ::show_Explosion()
{
    loadFromFile("Image/explosion.png");
    set_clip_Explosion();
    SDL_Rect * Current_fame = & clip_Explosion[frame_Explosion/10];
    mExplosion_rect.w = clip_Explosion[0].w;
    mExplosion_rect.h = clip_Explosion[0].h;
    render(mExplosion_rect.x,mExplosion_rect.y,clip_Explosion,0,nullptr,SDL_FLIP_NONE);
    frame_Explosion ++;
    if (frame_Explosion/10 >=25)
		{
			frame_Explosion = 0;
		}
}
