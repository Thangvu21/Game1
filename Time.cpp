#include "time.h"

Time ::Time ()
{
    start_time =0 ;
    pause_time = 0;

    is_paused = false ;
    is_started = false;
}
Time ::~Time()
{

}

void Time::start()
{
    is_started = true;
    is_paused = false ;
    start_time = SDL_GetTicks() ;
}

void Time::stop()
{
    is_paused = false ;
    is_started = false;
}
void Time::paused()
{
    if (is_started && is_paused == false )
        {
            is_paused = false;
            pause_time = SDL_GetTicks() - start_time ;
        }
}
void Time :: unpaused()
{
    if (is_paused == true)
        {
            is_paused = false;
            is_started = SDL_GetTicks() - pause_time ;
            pause_time = 0;
        }
}
int Time:: get_ticks() // laays thoi gian
{
    if (is_started == true)
        {
            if (is_paused == true)
                {
                    return pause_time ;
                }
            else
                {
                    return SDL_GetTicks() - start_time;
                }
        }
    return 0 ;
}

bool Time::is_paused_()
{
    return is_paused ;
}
bool Time:: is_started_()
{
    return is_started;
}