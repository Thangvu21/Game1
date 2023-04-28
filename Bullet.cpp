#include "Bullet.h"

Bullet :: Bullet ()
{
    val_x = 0;
    is_move_ = false;
}
Bullet :: ~Bullet()
{

} 
void Bullet :: HandleMove () 
{
    mBullet.x += val_x ;
    if ( mBullet.x + mBullet.w >  SCREEN_WIDTH  ) // checl va cham voi map
        {
            is_move_ = false;
        }
}

