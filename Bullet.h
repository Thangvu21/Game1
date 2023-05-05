#ifndef BULLET_H_
#define BULLET_H_

#include "BaseObject.h"
#include "commonFunction.h"
// ban ra chieu 1 quang ngan thoi
class Bullet : public LTexture {
public:
    Bullet ();
    ~Bullet() ;

    int getBullet_X () { return val_x ;}; // van toc bay cua dan

    void set_IsMove(bool isMove) { is_move_ = isMove ;};

    bool get_IsMove() { return is_move_ ;};  // check con di chuyen ko

    void HandleMove(); // tao speed cho skill

    SDL_Rect getBullet()  { return mBullet; };
    

private:
    int val_x = 3 ;
                     // giới hạn v đạn bắn
    bool is_move_ ;

    SDL_Rect mBullet ;
};

#endif