#include "Explosion.h"
Explosion :: Explosion()
{
    velocity_x = 2;
    veloxity_y = 0;
    frame_Explosion = 0;
    mRect.x = 0;
    mRect.y = 0;
    on_ground = false;
    frame_Explosion = 0;
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
void Explosion ::set_Position(const int& x,const int& y)
{
    mRect.x  = x*64;
    mRect.y  = y*64;
}
void Explosion ::set_clip_Explosion()
{
    loadFromFile("Image/explosion.png");
    for (int i=0; i<5; i++)
		{
			for (int j=0; j<5; j++)
				{
					clip_Explosion[i*5+j].x = i*64;
					clip_Explosion[i*5+j].y	= j*64;
					clip_Explosion[i*5+j].w = mWidth/5;
					clip_Explosion[i*5+j].h = mHeight/5;
				}
		}
}
void Explosion ::show_Explosion()
{
    set_clip_Explosion();
    int x = mRect.x - map_x;
    int y = mRect.y - map_y;
    SDL_Rect * Current_fame = & clip_Explosion[frame_Explosion/10];
    mRect.w = clip_Explosion[0].w;
    mRect.h = clip_Explosion[0].h;
    render(x,y,Current_fame,0,nullptr,SDL_FLIP_NONE);
    frame_Explosion ++;
    if (frame_Explosion/10 >=25)
		{
			frame_Explosion = 0;
		}
}
void Explosion::move_Explosion(Map & map_data)
{
    if (velocity_x > 0)
        {
            Explosion_status = RIGHT;
        }
    else if (velocity_x < 0)
        {
            Explosion_status = LEFT;
        }
    
    if (check_map(map_data) ==false )
        {
            velocity_x = -velocity_x ;
            mRect.x +=velocity_x;
        }
    else
        {
            mRect.x +=velocity_x;
        }
}
bool Explosion::check_map(Map & map_data_)
{
    bool check = true;
    int x1 = 0; // điểm đầu
    int x2 = 0; // điểm kết thúc của check

    int y1 = 0;
    int y2 = 0;
    
    // check theo x 
    int height_min = TILE_SIZE;
    x1 = (mRect.x + velocity_x )/TILE_SIZE ; // vị trí tại ô bao nhiêu theo chiều x
    x2 = (mRect.x  + mRect.w   + velocity_x -1 )/TILE_SIZE ; 

    y1 = ( mRect.y  ) / TILE_SIZE; // theo chiều y
    y2 = ( mRect.y+ TILE_SIZE -1 )/ TILE_SIZE ; // -1 sai số

    //   x1y1 .......... x2y1
    //    . . . . . . .. . .
    //  ..... .. . . . . .  .
    // . . . . .  . . . . . .
    //  x1y2 ... ........x2y2

    if ( x1 >= 0 && x2 < MAX_MAP_X  && y1 >=0  && y2 <MAX_MAP_Y)
    {
        if (velocity_x > 0)
            {
                if (veloxity_y == 0)
                    {
                        if (map_data_.tile[y2+1][x1] == BLANK_TILE && map_data_.tile[y2+1][x2] == BLANK_TILE  )
                            {
                                on_ground = false;
                                check = false;
                            }
                    }
                if (map_data_.tile[y1][x2] != BLANK_TILE || map_data_.tile[y2][x2] != BLANK_TILE  ) // oo ko duowc load hinh anh
                    {
                        mRect.x = x2 * TILE_SIZE  ; // neeu va cham tru di 1luong la chieu nganh cua nhan vat
                        mRect.x -=  mRect.w +1 ;
                        check = false;
                    }
            }
           
        else if (velocity_x < 0)
            {
                if (veloxity_y == 0)
                    {
                        if (map_data_.tile[y2+1][x1] == BLANK_TILE && map_data_.tile[y2+1][x2] == BLANK_TILE  )
                            {
                                on_ground = false;
                                check = false;
                                
                            }
                    }
                if (map_data_.tile[y1][x1] != BLANK_TILE || map_data_.tile[y2][x1] != BLANK_TILE  )
                    {
                        mRect.x = (x1+1)*TILE_SIZE;
                        check = false;
                    }
                
            }
    }

    // mRect.x += velocity_x;

    // check theo chieu y /check o chu ko phai check theo chinh xac tung vi tri
    int width_min = TILE_SIZE ; 
    x1 = ( mRect.x ) / TILE_SIZE;  

    x2 = (mRect.x + mRect.w ) / TILE_SIZE;

    y1 = (mRect.y +veloxity_y) / TILE_SIZE;

    y2 = (mRect.y + veloxity_y + mRect.h -1)/TILE_SIZE;

    if ( x1 >= 0 && x2 < MAX_MAP_X  && y1 >=0  && y2 <MAX_MAP_Y)
    {
        if (veloxity_y > 0 ) // ddang roi
                {
                    if (map_data_.tile[y2][x1] != BLANK_TILE || map_data_.tile[y2][x2] != BLANK_TILE) // 
                        {
                            mRect.y = y2*TILE_SIZE ;
                            mRect.y -= (mRect.h +1 );
                            veloxity_y = 0;
                            on_ground = true;
                        }
                }
            
            else if ( veloxity_y < 0 )  // danh nhay
                {
                    if (map_data_.tile[y1][x1] != BLANK_TILE || map_data_.tile[y1][x2] != BLANK_TILE )
                        {
                            mRect.y = (y1+1)*TILE_SIZE ; 
                            veloxity_y = 0;
                            on_ground = false;
                        }
                }
    }
    mRect.y += veloxity_y;

    if (mRect.x < 0 )
        {
            mRect.x = 0 ;
        }
    else if ( mRect.x +mRect.w > map_data_.max_x_ )
        {
            mRect.x = map_data_.max_x_ - mRect.w -1; 
        }

    if ( mRect.y >map_data_.max_y_ )
        {
            check = false;
        }
    return check;
}

