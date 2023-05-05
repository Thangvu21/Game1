#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "commonFunction.h"
#include "BaseObject.h"
#include "time.h"

class Explosion : public LTexture
{
    public :
    Explosion();
    ~Explosion();
    
    void set_clip_Explosion();
    
    void show_Explosion();
    
    SDL_Rect get_Rect() {return mExplosion_rect ;};
    
    int Get_Width();
    int Get_Height();
    
    void set_Position(int x,int y);
    
    private:
    
    int velocity_x;
    int acceleration_x ;
    
    SDL_Rect clip_Explosion[25];
    
    int frame_Explosion;
    
    SDL_Rect mExplosion_rect;

};

#endif
