#ifndef KNIGHT_H_
#define KNIGHT_H_
#include "commonFunction.h"
#include "BaseObject.h"

class Knight : public LTexture
{
    public :
    Knight();

    ~Knight();

    void set_clip();

    SDL_Rect getRect() const { return mRect; }
    
    void Show(int x , int y);

    void Set_Win(bool a) ;
    
    bool Get_Win() const {return Win; }

    void SetMap_X_Y ( const int map_x , const int map_y) 
        {
                map_x_ = map_x;
                map_y_ = map_y;
        }

    private :
    int frame;

    SDL_Rect mRect;
    
    SDL_Rect frame_clip_ [5] ; // Knight
    
    bool Win;
    
    int map_x_ ; // check vi tri ban do theo nhan vat

    int map_y_ ;
       
};

#endif