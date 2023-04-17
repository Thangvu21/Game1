#include "MainObject.h"
   
#define GRAVITY_SPEED 4 // trọng lực rơi
#define MAX_JUMP 4
#define MAX_SPEED 10      // tốc độ tối đa
#define PLAYER_SPEED 8    // tốc độ nhân vật
MainObject ::MainObject()
{
    frame = 0; // đang ở ảnh nào trong chuỗi

    x_val_ = 0; // vận tốc
    y_val_ = 0;

    mRect.x = 100;
    mRect.y = 100;
    status_ = STAND;
}
MainObject ::~MainObject()
{
    free();
}

void MainObject ::set_clip()
{
    for (int i = 0; i < NUM_FRAMES; ++i)
    {
        frame_clip_[i].x = i * mWidth / NUM_FRAMES;
        frame_clip_[i].y = mHeight/2-8;
        frame_clip_[i].h = mHeight/2+8;
        frame_clip_[i].w = mWidth / NUM_FRAMES;
    }
}
void MainObject ::set_clip_1()
{
    for (int i = 0; i < NUM_FRAMES_1; ++i)
    {
        frame_clip_1[i].x = i * mWidth / NUM_FRAMES_1;
        frame_clip_1[i].y = mHeight/2-8;
        frame_clip_1[i].h = mHeight/2+8;
        frame_clip_1[i].w = mWidth / NUM_FRAMES_1;
    }
}
void MainObject ::set_clip_2()
{
    for (int i = 0; i < NUM_FRAMES_2; ++i)
    {
        frame_clip_2[i].x = i * mWidth / NUM_FRAMES_2;
        frame_clip_2[i].y = mHeight/2-8;
        frame_clip_2[i].h = mHeight/2+8;
        frame_clip_2[i].w = mWidth / NUM_FRAMES_2;
    }
}
void MainObject ::set_clip_3()
{
    for (int i = 0; i < NUM_FRAMES_3; ++i)
    {
        frame_clip_3[i].x = i * mWidth / NUM_FRAMES_3;
        frame_clip_3[i].y = mHeight/2-8;
        frame_clip_3[i].h = mHeight/2+8;
        frame_clip_3[i].w = mWidth / NUM_FRAMES_3;
    }
}

void MainObject ::set_clip_Jump_Fall()
{
        frame_clip_Jump.x = 2 * mWidth / NUM_FRAMES_1;
        frame_clip_Jump.y = mHeight *5/16;
        frame_clip_Jump.h = mHeight/2+8;
        frame_clip_Jump.w = mWidth / NUM_FRAMES_1;
    for (int i= 3; i<6 ; i++)
        {
            frame_clip_Fall[i-3].x = i * mWidth / NUM_FRAMES_1;
            frame_clip_Fall[i-3].y = mHeight *5/16;
            frame_clip_Fall[i-3].h = mHeight/2+8;
            frame_clip_Fall[i-3].w = mWidth / NUM_FRAMES_1;
        }
    frame_clip_Fall[3].x = 6 * mWidth / NUM_FRAMES_1;
    frame_clip_Fall[3].y = mHeight/2-8;
    frame_clip_Fall[3].h = mHeight/2+8;
    frame_clip_Fall[3].w = mWidth / NUM_FRAMES_1;
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
            if (status_ == WALK_LEFT)
                {
                    degrees += 360 ;
                    // flipType = SDL_FLIP_VERTICAL;
                }
            status_ = WALK_RIGHT;
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
            status_=STAND;
        }
        break;
        default:
            break;
        }
    }
    // run
    if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_s:
            {
                status_ = RUN;
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
            case SDLK_s: // RUN  
        {
            status_=STAND;
        }
        break;
        default:
            break;
        }
    }
    // walk  right
    if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_a:
        {
            // đang bấm phím phải
            if (status_ == WALK_RIGHT)
                {
                    degrees -= 360;
                    // flipType = SDL_FLIP_VERTICAL;
                }
            status_ = WALK_LEFT;
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
            status_=STAND;
        }
        break;
        default:
            break;
        }
    }
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
    if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_w:
        {
            // đang bấm phím phải
            status_ = JUMP;
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
            status_=FALL;
        }
        break;
        default:
            break;
        }
    }
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
}

void MainObject::handleMove()
{
    if (mRect.x>=SCREEN_WIDTH) 
        {
            mRect.x =0;
        }
    if (mRect.y >= SCREEN_HEIGHT) 
        {
            mRect.y =0;
        }

    if (status_==WALK_RIGHT)
    {
        mRect.x+=4;
    }
    if (status_ == RUN)
    {
        mRect.x+=8;
    }
    if (status_ == WALK_LEFT)
    {
        mRect.x-=4;
    }
    if (status_==STAND)
    {
        
    }
    if (status_==JUMP)
    {
        mRect.y -= 4 ;
        status_ == FALL;
    }
    if (status_==FALL)
    {
        mRect.y += 4 ;
        status_ == STAND;
    }
}

void MainObject ::Show(int x, int y)
{
    if (status_==STAND)
        {
            loadFromFile("Image/Stand.png");
            set_clip();
            SDL_Rect *currentClip = &frame_clip_[frame / 5];
            render(x, y, currentClip , degrees , nullptr ,flipType);
            // Go to next frame
            ++frame;

            // Cycle animation
             if (frame / 5 >= NUM_FRAMES)
                {
                    frame = 0;
                }   
        } 
    else if (status_== WALK_LEFT || status_ == WALK_RIGHT) 
        {
            loadFromFile("Image/Walk.png");
            set_clip_1();
            SDL_Rect *currentClip = &frame_clip_1[frame / 4];
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
            render(x, y, currentClip , degrees , nullptr ,flipType);
            // Go to next frame 
        }
    else if (status_== FALL) 
        {
            loadFromFile("Image/Jump.png");
            set_clip_Jump_Fall();
            SDL_Rect *currentClip = &frame_clip_Fall[frame / 4];
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
            SDL_Rect *currentClip = &frame_clip_3[frame / 6];
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
        }
    // Render current frame
    // set_clip();
    
}
int MainObject ::GetWidth()
{
    return mWidth;
}
int MainObject ::GetHeight()
{
    return mHeight;
}