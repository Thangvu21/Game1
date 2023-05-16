#include "Knight.h"

Knight :: Knight()
{
    Win = false;
    frame = 0;
    mRect.x = 399*64;
    mRect.y = 3*64;
}
Knight ::~Knight()
{
    free();
}
void Knight ::set_clip()
{
    loadFromFile("Image/Knight.png");
    for (int i = 0; i < NUM_FRAMES; ++i)
    {
        frame_clip_[i].x = i * mWidth / NUM_FRAMES +32;
        frame_clip_[i].y = mHeight/2-8;
        frame_clip_[i].h = mHeight/2+8;
        frame_clip_[i].w = mWidth / NUM_FRAMES -64;
    }
}
void Knight::Show(int x,int y)
{
    set_clip();
    x  = x - map_x_;
    y  = y - map_y_;
    SDL_Rect *currentClip = &frame_clip_[frame / 5];
    mRect.w = frame_clip_[0].w;
    mRect.h = frame_clip_[0].h;
    render(x, y, currentClip , degrees , nullptr ,SDL_FLIP_NONE);
            // Go to next frame
            ++frame;
            // Cycle animation
    if (frame / 5 >= NUM_FRAMES)
        {
            frame = 0;
        }   
}
void Knight::Set_Win(bool a)
{
    Win = a;
}
