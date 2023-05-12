#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "commonFunction.h"
#include "BaseObject.h"
#include "Gamemap.h"

class Explosion : public LTexture
{
    public :
    enum Status_EX
    {
        LEFT,
        RIGHT
    };
    Explosion();
    ~Explosion();
    
    void set_clip_Explosion();
    
    void show_Explosion();

    void move_Explosion(Map & map_data);

    bool check_map(Map & map_data);
    
    SDL_Rect get_Rect() {return mRect ;};
    
    int Get_Width();
    int Get_Height();
    
    void set_Position(const int& x,const int& y);
    
    void SetMap_X_Y ( const int map_x_ , const int map_y_) 
        {
                map_x = map_x_;
                map_y = map_y_;
        }
    private:
    
    int map_x;
    int map_y;
    
    bool on_ground;
    
    int velocity_x;
    int veloxity_y;
    
    SDL_Rect clip_Explosion[25];
    
    int frame_Explosion;
    
    SDL_Rect mRect;
    
    Status_EX Explosion_status;


};

#endif
