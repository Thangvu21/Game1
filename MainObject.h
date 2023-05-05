#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include<vector>
#include "commonFunction.h"
#include "BaseObject.h"
#include "Gamemap.h"
#include "Bullet.h"
// Nhật vật chính
class MainObject : public LTexture
{
public:
    enum Status_Main
    {
        WALK, // đi bộ
        RUN, // chạy
        JUMP, // bật nhảy
        STAND,  // dứng
        FALL,  // rơi tự do 
        ATTACK,
        ATTACK1,
        ATTACK2,
        ATTACK3
    };
    enum Status_Main1
    {
        RIGHT ,
        LEFT  
    };
    
    MainObject();

    ~MainObject();

    void Show(int x, int y); // show theo dạng frame

    void handleEvent(SDL_Event events); // xử lý sự kiện

    void set_clip(); // tạo mảng các ảnh của animation đứng và rơi xuống

    void set_clip_1(); // chạy và đi bộ 

    void set_clip_2(); // attack2,3 và Jump

    void set_clip_3(); 

    void set_clip_Jump_Fall();

    void set_clip_4(); // attack 4

    void set_Bullet(); // tao ra danj

    void handleBullet();

    // void setCamera (SDL_Rect & camera); //Centers the camera over the dot

    SDL_Rect getRect() const { return mRect; }
    
    int GetWidth();

    int GetHeight();

    std:: vector<Bullet*> Get_list_Bullet () const {return mList_Bullet_;};

    void handleMove(Map & map_data_);
    
    void checkMap(Map & map_data);

    void SetCamera_Entity_Map(Map & map_data );

    void SetMap_X_Y ( const int map_x , const int map_y) 
        {
                map_x_ = map_x;
                map_y_ = map_y;
        }

private:

    int x_val_;
    int y_val_; // vận tốc theo phương ..

    SDL_Rect frame_clip_1 [8] ; // lưu mảng đi và chạy

    SDL_Rect frame_clip_[5]; // mảng lưu số ảnh động stand v

    SDL_Rect frame_clip_2 [3] ;// mảng lưu ảnh tung chiêu 2 vaf 3 

    SDL_Rect frame_clip_3 [6] ; // attack

    SDL_Rect frame_clip_4 [10]; // attack 4

    SDL_Rect frame_clip_Jump ; //Jump

    SDL_Rect frame_clip_Fall [4]; //FALL

    int frame; // lưu đang ở frame nào trong 8 frame

    Status_Main status_; // trạng thái hiện tại của nhân vật

    Status_Main1 status1_ ; // bên trái / phải

    SDL_Rect mRect;

    std:: vector<Bullet* > mList_Bullet_;

    bool on_ground;

    bool move ;

    int map_x_ ; // check vi tri ban do theo nhan vat

    int map_y_ ;

    Input input_type ;

};

#endif