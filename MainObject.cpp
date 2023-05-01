#include "MainObject.h"
#include "Bullet.h"
#include <vector>

#define GRAVITY_SPEED 1 // trọng lực r ơi
#define MAX_FALL_SPEED 4 // max speed 
#define MAX_JUMP 4
#define MAX_SPEED 10      // tốc độ tối đa
#define PLAYER_SPEED 8    // tốc độ nhân vật
MainObject ::MainObject()
{
    frame = 0; // đang ở ảnh nào trong chuỗi

    x_val_ = 0; // vận tốc
    y_val_ = 0;

    map_x_ = 0;
    map_y_ = 0;

    mRect.x = 100;
    mRect.y = 100;
    status_ = FALL;
    on_ground = false;
    move = true;
}
MainObject ::~MainObject()
{
    free();
}
                                   
void MainObject ::set_clip()
{
    for (int i = 0; i < NUM_FRAMES; ++i)
    {
        frame_clip_[i].x = i * mWidth / NUM_FRAMES +32;
        frame_clip_[i].y = mHeight/2-8;
        frame_clip_[i].h = mHeight/2+8;
        frame_clip_[i].w = mWidth / NUM_FRAMES -64;
    }
}
void MainObject ::set_clip_1()
{
    for (int i = 0; i < NUM_FRAMES_1; ++i)
    {
        frame_clip_1[i].x = i * mWidth / NUM_FRAMES_1 +32;
        frame_clip_1[i].y = mHeight/2-8;
        frame_clip_1[i].h = mHeight/2+8;
        frame_clip_1[i].w = mWidth / NUM_FRAMES_1 -64;
    }
}
void MainObject ::set_clip_2()
{
    for (int i = 0; i < NUM_FRAMES_2; ++i)
    {
        frame_clip_2[i].x = i * mWidth / NUM_FRAMES_2+32;
        frame_clip_2[i].y = mHeight/2-8;
        frame_clip_2[i].h = mHeight/2+8;
        frame_clip_2[i].w = mWidth / NUM_FRAMES_2-64;
    }
}
void MainObject ::set_clip_3()
{
    for (int i = 0; i < NUM_FRAMES_3; ++i)
    {
        frame_clip_3[i].x = i * mWidth / NUM_FRAMES_3+32;
        frame_clip_3[i].y = mHeight/2-8;
        frame_clip_3[i].h = mHeight/2+8;
        frame_clip_3[i].w = mWidth / NUM_FRAMES_3 -64;
    }
}

void MainObject ::set_clip_Jump_Fall()
{
        frame_clip_Jump.x = 2 * mWidth / NUM_FRAMES_1 +32;
        frame_clip_Jump.y = mHeight *5/16;
        frame_clip_Jump.h = mHeight/2+8;
        frame_clip_Jump.w = mWidth / NUM_FRAMES_1 -64;
    for (int i= 3; i<6 ; i++)
        {
            frame_clip_Fall[i-3].x = i * mWidth / NUM_FRAMES_1 +32;
            frame_clip_Fall[i-3].y = mHeight *5/16;
            frame_clip_Fall[i-3].h = mHeight/2+8;
            frame_clip_Fall[i-3].w = mWidth / NUM_FRAMES_1 -64;
        }
    frame_clip_Fall[3].x = 6 * mWidth / NUM_FRAMES_1 +32;
    frame_clip_Fall[3].y = mHeight/2-8;
    frame_clip_Fall[3].h = mHeight/2+8;
    frame_clip_Fall[3].w = mWidth / NUM_FRAMES_1 -64;
}
void MainObject :: set_clip_4()
{
    for (int i = 0; i < 10; ++i)
    {
        frame_clip_4[i].x = i * mWidth / 10;
        frame_clip_4[i].y = mHeight/2-8;
        frame_clip_4[i].h = mHeight/2+8;
        frame_clip_4[i].w = mWidth / 10;
    }
}

void MainObject:: set_Bullet()
{
    // tao ra skill

        Bullet * Main_bullet = new Bullet;
        Main_bullet->loadFromFile ("Image/Bullet.png");
        Main_bullet->set_IsMove(true);
        mList_Bullet_.push_back(Main_bullet);
}

void MainObject:: handleBullet()
{
    for (int i=0; i< mList_Bullet_.size(); i++)
        {
            Bullet * skill = mList_Bullet_.at(i);
            if (skill != NULL)
                {
                    if (skill->get_IsMove() == true)
                        {
                            skill->HandleMove();
                            skill->render(mRect.x + mRect.w,mRect.y+ mRect.h/2 , nullptr ,0 ,nullptr ,SDL_FLIP_NONE);
                        }
                    else
                        {
                            mList_Bullet_.erase(mList_Bullet_.begin());
                            if (skill != NULL)
                                {
                                    delete skill;
                                    skill = NULL;
                                }
                        }
                }
        }
}
    
void MainObject ::handleEvent(SDL_Event events)
{
    if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_d:
        {
            // đang bấm phím phải
            if (status1_ == LEFT )
                {
                    flipType = SDL_FLIP_NONE;
                    status1_ = RIGHT ;
                }
            else if (status1_ == RIGHT )
                {
                    flipType = SDL_FLIP_NONE;
                }
            input_type.D_input = 1;
            move = true;
        }
         
        break;
        default:
            break;
        }
    }
    else if (events.type == SDL_KEYUP && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_d:
            {
                input_type.D_input = 0;
            }
        break;
        default:
            break;
        }
    }
    //s
    if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_s:
            {
                input_type.S_input = 1;
                move = true;
            }
            break;
        default:
            break;
        }
    }
    else if (events.type == SDL_KEYUP && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_s:
            {
                input_type.S_input = 0;
            }
            break;
        default:
            break;
        }
    }
    // a
    if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_a:
                {
                            // đang bấm phím phải
                            if (status1_ == RIGHT)
                                {
                                    flipType = SDL_FLIP_HORIZONTAL;
                                    status1_ = LEFT;
                                }
                            else if (status1_ == LEFT)
                                {
                                    flipType = SDL_FLIP_HORIZONTAL;
                                }
                            input_type.A_input = 1;
                            move = true;
                }        
            break;
        default:
            break;
        }
    }
    else if (events.type == SDL_KEYUP && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_a:
            {
                input_type.A_input = 0;
            }   
            break;
        default:
            break;
        }
    }
    //w
    if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_w:
            {
                input_type.W_input = 1;
                move = true;
            }      
            break;
        default:
            break;
        }
    }
    else if (events.type == SDL_KEYUP && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_w:
            {
                input_type.W_input = 0;
            }    
            break;
        default:
            break;
        }
    }
    // run
    // if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    // {
    //     switch (events.key.keysym.sym)
    //     {
    //         case SDLK_s:{
    //         if (on_ground )
    //             {
    //                 status_ = RUN;
    //             }
    //         else 
    //             {
    //                 status_ = FALL;
    //             }
    //         }
    //         break;
    //     default:
    //         break;
    //     }
    // }
    // else if (events.type == SDL_KEYUP && events.key.repeat == 0)
    // {
    //     switch (events.key.keysym.sym)
    //     {
    //         case SDLK_s: // RUN  
    //             {
    //                 if (on_ground == true)
    //                     {
    //                         status_=STAND;
    //                     }
    //                 else
    //                     {
    //                         status_ = FALL;
    //                     }
    //             }
    //     break;
    //     default:
    //         break;
    //     }
    // }

    // walk  right
    // if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    // {
    //     switch (events.key.keysym.sym)
    //     {
    //         case SDLK_a:
    //             {
    //                 // đang bấm phím phải
    //                 if (status1_ == RIGHT)
    //                     {
    //                         flipType = SDL_FLIP_HORIZONTAL;
    //                         status1_ = LEFT;
    //                     }
    //                 else if (status1_ == LEFT)
    //                     {
    //                         flipType = SDL_FLIP_HORIZONTAL;
    //                     }
    //                 if (on_ground == false)
    //                     {
    //                         status_ = JUMP;
    //                     }
    //                 else 
    //                     {
    //                         on_ground = WALK;
    //                     }
    //             }
    //     break;
    //     default:
    //         break;
    //     }
    // }
    // else if (events.type == SDL_KEYUP && events.key.repeat == 0)
    // {
    //     switch (events.key.keysym.sym)
    //     {
    //         case SDLK_a: 
    //             {
    //                 if (on_ground)   
    //                     {
    //                         status_=STAND;
    //                     }
    //                 else
    //                     status_ = FALL;
    //             }
    //     break;
    //     default:
    //         break;
    //     }
    // }

    // ATTACK - 0
    if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_c:
            {
                status_ = ATTACK;
            }
            break;
        default:
            break;
        }
    }
    else if (events.type == SDL_KEYUP && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_c: 
        {
            status_=STAND;
        }
        break;
        default:
            break;
        }
    }
    
    // JUMP
    // if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    // {
    //     switch (events.key.keysym.sym)
    //     {
    //     case SDLK_w:
    //     {
    //         // đang bấm phím phải
    //         status_ = JUMP;
    //     }
    //     break;
    //     default:
    //         break;
    //     }
    // }
    // else if (events.type == SDL_KEYUP && events.key.repeat == 0)
    // {
    //     switch (events.key.keysym.sym)
    //     {
    //     case SDLK_w:
    //     {
    //         status_=FALL;
    //     }
    //     break;
    //     default:
    //         break;
    //     }
    // }
    // ATTACK_1
    if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_v:
            {
                status_ = ATTACK1;
            }
            break;
        default:
            break;
        }
    }
    else if (events.type == SDL_KEYUP && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_v: 
        {
            status_=STAND;
        }
        break;
        default:
            break;
        }
    }
    // ATTACK_2
    if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_b:
            {
                status_ = ATTACK2;
            }
            break;
        default:
            break;
        }
    }
    else if (events.type == SDL_KEYUP && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_b: 
        {
            status_=STAND;
        }
        break;
        default:
            break;
        }
    }
    // ATTACK_4
    if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_n:
            {
                status_ = ATTACK3;
            }
            break;
        default:
            break;
        }
    }
    else if (events.type == SDL_KEYUP && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_n: 
        {
            status_=STAND;
        }
        break;
        default:
            break;
        }
    }
}
// move
void MainObject::handleMove(Map & map_data_)
{           
    x_val_ = 0;
    // y_val_  = GRAVITY_SPEED;

        
    if (status1_==RIGHT)
    {
        // if (status_ == WALK )  bản cũ
        //     {
        //         x_val_ = 2;
        //     }
        // if (status_ == RUN )
        //     {
        //         x_val_ = 4;
        //     }
        // if (status_ == JUMP && on_ground == true)
        //     {
        //         y_val_ = -3;
        //     }
        // if ( status_ == FALL )
        //     {
        //         y_val_ = 3;
        //     }
        if (on_ground ==  true &&  input_type.D_input == 1)
            {
                status_ = WALK;
                x_val_ = 2;
            }
        else if (on_ground ==  true  && input_type.S_input == 1)
            {
                status_ = RUN;
                x_val_ = 4;
            }
        else if (on_ground == true && move == false) //đang đứng yên
            {
                status_ = STAND;
            }
        else if (on_ground == false && move == true && input_type.W_input == 0  ) // đang rơi
            {
                status_ = FALL;
                y_val_  = 4; 
            }
            
        // else if (on_ground == false &&  input_type.W_input == 1) // nhảy lên bị chạm chướng ngại vật
        //     {
        //         // có thể rơi hoặc đứng yên nếu giữ  phím w
        //         status_ = JUMP;
              //     }
        else if (input_type.W_input== 1 )
            {  
                if (input_type.D_input == 1 )
                        {                    
                            x_val_ = 2;
                        }
                y_val_ = -3;
                status_ = JUMP;
                on_ground = false;
            }
    }
    else if (status1_ == LEFT)
    {
        // if (status_ == WALK )
        //     {
        //         // if (on_ground == false)
        //         //     {
        //         //         status_ = FALL ;
        //         //     }
        //         // else
        //         //     {
        //             x_val_ = -2;
        //     }
        // if (status_ == RUN )
        //     {
        //         // if (on_ground == false)
        //         //     {
        //         //         status_ = FALL ;
        //         //     }
        //         // else
        //         //     {
        //                 x_val_ = -4;
        //     }
        // if (status_ == JUMP && on_ground == true)
        //     {
        //         y_val_ = -3;
        //     }
        // if (status_ == FALL)
        //     {
        //         y_val_ = 3;
        //     }
        if (on_ground ==  true && input_type.A_input == 1)
            {
                status_ = WALK;
                x_val_ = -2;
            }
        else if (on_ground ==  true && input_type.S_input == 1)
            {
                status_ = RUN;
                 x_val_ = -4;
            }
        else if (on_ground == true && move == false) //đang đứng yên
            {
                status_ = STAND;
            }            
        else if (on_ground == false  && move== true && input_type.W_input == 0 ) // đang rơi
            {
                status_ = FALL;
                y_val_  = 4; 
            }
        else if (input_type.W_input== 1 )
            {  
                if (input_type.A_input == 1 )
                        {                    
                            x_val_ = -2;
                        }
                    y_val_ = -3;
                    status_ = JUMP;
                    on_ground = false;
            }
        
    }
    if (input_type.W_input == 0 && input_type.A_input== 0 && input_type.D_input == 0 && input_type.S_input == 0)
            {
                move=false;
            }
    if ( status_ == RUN || status_ == WALK || status_ == STAND)
            {
                if (on_ground == false)
                    {
                        status_ = FALL;
                        y_val_ = 4;
                    }
            } 
    checkMap(map_data_);
    SetCamera_Entity_Map(map_data_);
}
     
void MainObject ::SetCamera_Entity_Map(Map & map_data_ )
{
    map_data_.start_x = mRect.x - (SCREEN_WIDTH /2 );
    if ( map_data_.start_x < 0 )
        {
            map_data_.start_x = 0;
        }
    else if (map_data_.start_x + SCREEN_WIDTH >= map_data_.max_x_ )
        {
            map_data_.start_x = map_data_.max_x_ - SCREEN_WIDTH;
        }

    map_data_.start_y = mRect.y -( SCREEN_HEIGHT /2 );
    if ( map_data_.start_y < 0 )
        {
            map_data_.start_y = 0;
        }
    else if (map_data_.start_y + SCREEN_HEIGHT >= map_data_.max_y_ )
        {
            map_data_.start_y = map_data_.max_y_ - SCREEN_HEIGHT;
        }
}
// render
void MainObject ::Show(int x, int y )  
{
    x = mRect.x - map_x_;
    y = mRect.y - map_y_;
    if (status_==STAND)
        {
            loadFromFile("Image/Stand.png");
            set_clip();
            SDL_Rect *currentClip = &frame_clip_[frame / 5];
            mRect.w = frame_clip_[0].w;
            mRect.h = frame_clip_[0].h;
            render(x, y, currentClip , degrees , nullptr ,flipType);
            // Go to next frame
            ++frame;

            // Cycle animation
             if (frame / 5 >= NUM_FRAMES)
                {
                    frame = 0;
                }   
        } 
    else if (status_== WALK) 
        {
            loadFromFile("Image/Walk.png");
            set_clip_1();
            SDL_Rect *currentClip = &frame_clip_1[frame / 4];
            mRect.w = frame_clip_1[0].w;
            mRect.h = frame_clip_1[0].h;
            render(x, y, currentClip , degrees , nullptr ,flipType);
            // Go to next frame
            ++frame;

            // Cycle animation
             if (frame / 4 >= NUM_FRAMES)
                {
                    frame = 0;
                }   
            
        }
    else if (status_== RUN) 
        {
            loadFromFile("Image/Run.png")  ;  
            set_clip_1();
            SDL_Rect *currentClip = &frame_clip_1[frame / 4];
            mRect.w = frame_clip_1[0].w;
            mRect.h = frame_clip_1[0].h;
            render(x, y, currentClip , degrees , nullptr ,flipType);
            // Go to next frame
            ++frame;

            // Cycle animation
             if (frame / 4 >= NUM_FRAMES)
                {
                    frame = 0;
                }   
        }
    else if (status_ == JUMP ) 
        {
            loadFromFile("Image/Jump.png");
            set_clip_Jump_Fall();
            SDL_Rect *currentClip = &frame_clip_Jump;
            mRect.w = frame_clip_Jump.w;
            mRect.h = frame_clip_Jump.h;
            render(x, y, currentClip , degrees , nullptr ,flipType);
            // Go to next frame 
        }
    else if (status_== FALL) 
        {
            loadFromFile("Image/Jump.png");
            set_clip_Jump_Fall();
            SDL_Rect *currentClip = &frame_clip_Fall[frame / 4];
            mRect.w = frame_clip_Fall[0].w;
            mRect.h = frame_clip_Fall[0].h;
            render(x, y, currentClip , degrees , nullptr ,flipType);
            // Go to next frame
            ++frame;
            // Cycle animation
             if (frame / 4 >= 4)
                {
                    frame = 0;
                }   
        }
    else if (status_ == ATTACK ) 
        {
            loadFromFile ("Image/Attack_1.png") ;
            set_clip_3();
            // set_Bullet();
            SDL_Rect *currentClip = &frame_clip_3[frame / 6];
            mRect.w = frame_clip_3[0].w;
            mRect.h = frame_clip_3[0].h;
            render(x, y, currentClip , degrees , nullptr ,flipType);
            // Go to next frame
            ++frame;

            // Cycle animation
             if (frame / 6 >= NUM_FRAMES_3)
                {
                    frame = 0;
                }   
        }
    else if (status_ == ATTACK1 ) 
        {
            loadFromFile ("Image/Attack_2.png") ;
            set_clip_2();
            SDL_Rect *currentClip = &frame_clip_2[frame / 3];
            mRect.w = frame_clip_2[0].w;
            mRect.h = frame_clip_2[0].h;
            render(x, y, currentClip , degrees , nullptr ,flipType);
            // Go to next frame
            ++frame;

            // Cycle animation
             if (frame / 3 >= NUM_FRAMES_2)
                {
                    frame = 0;
                }     
        }
    else if (status_ == ATTACK2 ) 
        {
            loadFromFile ("Image/Attack_3.png") ;
            set_clip_2();
            SDL_Rect *currentClip = &frame_clip_2[frame / 3];
            render(x, y, currentClip , degrees , nullptr ,flipType);
            // Go to next frame
            ++frame;

            // Cycle animation
             if (frame / 3 >= NUM_FRAMES_2)
                {
                    frame = 0;
                } 
            // handleBullet();  
        }
    else if (status_ == ATTACK3 ) 
        {
            loadFromFile ("Image/Attack_4.png") ;
            set_clip_4();
            SDL_Rect *currentClip = &frame_clip_4[frame / 10];
            mRect.w = frame_clip_4[0].w;
            mRect.h = frame_clip_4[0].h;
            render(x, y, currentClip , degrees , nullptr ,flipType);
            // Go to next frame
            ++frame;

            // Cycle animation
             if (frame / 10 >= 10)
                {
                    frame = 0;
                }   
        }
    // Render current frame
    // set_clip();
      
}

// void MainObject :: setCamera(SDL_Rect & camera)
// { 
//     // Center MainObject over the camera
//     camera.x = (mRect.x + mRect.w /2 ) - SCREEN_WIDTH/2  ; 
//     camera.y = (mRect.y + mRect.h /2 ) - SCREEN_HEIGHT/2 ;
//     // keep camera in bounds
//     if (camera.x < 0)
//     {
//         camera.x =0;
//     }
//     if (camera.y < 0)
//     {
//         camera.y = 0;
//     }
//     if (camera.x > LEVEL_WIDTH - camera.w)
//     {
//         camera.x =LEVEL_WIDTH - camera.w;
//     }
//     if (camera.y > LEVEL_HEIGHT - camera.h)
//     {
//         camera.y = LEVEL_HEIGHT - camera.h;
//     }
// }
void MainObject::checkMap(Map & map_data_)
{
    int x1 = 0; // điểm đầu
    int x2 = 0; // điểm kết thúc của check
    int x3 = 0;
    int x4 = 0;

    int y1 = 0;
    int y2 = 0;
    
    // check theo x 
    int height_min = TILE_SIZE;
    x1 = (mRect.x + x_val_ )/TILE_SIZE ; // vị trí tại ô bao nhiêu theo chiều x
    x2 = (mRect.x  + mRect.w   + x_val_ -1 )/TILE_SIZE ; 

    y1 = ( mRect.y  ) / TILE_SIZE; // theo chiều y
    y2 = ( mRect.y+ TILE_SIZE -1 )/ TILE_SIZE ; // -1 sai số

    //   x1y1 .......... x2y1
    //    . . . . . . .. . .
    //  ..... .. . . . . .  .
    // . . . . .  . . . . . .
    //  x1y2 ... ........x2y2

    if ( x1 >= 0 && x2 < MAX_MAP_X  && y1 >=0  && y2 <MAX_MAP_Y)
    {
        if (x_val_ > 0)
            {
                if (y_val_ == 0)
                    {
                        if (map_data_.tile[y2+1][x1] == BLANK_TILE && map_data_.tile[y2+1][x2] == BLANK_TILE  )
                            {
                                on_ground = false;
                            }
                    }
                if (map_data_.tile[y1][x2] != BLANK_TILE || map_data_.tile[y2][x2] != BLANK_TILE  ) // oo ko duowc load hinh anh
                    {
                        mRect.x = x2 * TILE_SIZE  ; // neeu va cham tru di 1luong la chieu nganh cua nhan vat
                        mRect.x -=  mRect.w +1 ;
                        x_val_ = 0;
                    }
            }
           
        if (x_val_ < 0)
            {
                if (y_val_ == 0)
                    {
                        if (map_data_.tile[y2+1][x1] == BLANK_TILE && map_data_.tile[y2+1][x2] == BLANK_TILE  )
                            {
                                on_ground = false;
                            }
                    }
                if (map_data_.tile[y1][x1] != BLANK_TILE || map_data_.tile[y2][x1] != BLANK_TILE  )
                    {
                        mRect.x = (x1+1)*TILE_SIZE;
                        x_val_ = 0;
                    }
                
            }
    }

    mRect.x += x_val_;

    // check theo chieu y /check o chu ko phai check theo chinh xac tung vi tri
    int width_min = TILE_SIZE ; 
    x1 = ( mRect.x ) / TILE_SIZE;  

    x2 = (mRect.x + mRect.w ) / TILE_SIZE;

    // x3 = (mRect.x+mRect.w + x_val_)/TILE_SIZE;

    // x4 = (mRect.x+mRect.w - x_val_)/TILE_SIZE;

    y1 = (mRect.y +y_val_) / TILE_SIZE;

    y2 = (mRect.y + y_val_ + mRect.h -1)/TILE_SIZE;

    if ( x1 >= 0 && x2 < MAX_MAP_X  && y1 >=0  && y2 <MAX_MAP_Y)
    {
        if (y_val_ > 0 ) // ddang roi
                {
                    if (map_data_.tile[y2][x1] != BLANK_TILE || map_data_.tile[y2][x2] != BLANK_TILE) // 
                        {
                            mRect.y = y2*TILE_SIZE ;
                            mRect.y -= (mRect.h +1 );
                            y_val_ = 0;
                            on_ground = true;
                        }
                }
            
            else if ( y_val_ < 0 )  // danh nhay
                {
                    if (map_data_.tile[y1][x1] != BLANK_TILE || map_data_.tile[y1][x2] != BLANK_TILE )
                        {
                            mRect.y = (y1+1)*TILE_SIZE ; 
                            y_val_ = 0;
                            on_ground = false;
                        }
                }
    }
    mRect.y += y_val_;

    if (mRect.x < 0 )
        {
            mRect.x = 0 ;
        }
    else if ( mRect.x +mRect.w > map_data_.max_x_ )
        {
            mRect.x = map_data_.max_x_ - mRect.w -1; 
        }

}
int MainObject ::GetWidth()
{
    return mWidth;
}
int MainObject ::GetHeight()
{
    return mHeight;
}