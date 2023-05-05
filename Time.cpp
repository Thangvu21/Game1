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

    //Get the current clock time
    start_time = SDL_GetTicks() ;
    pause_time = 0;
}

void Time::stop()
{
    is_paused = false ;
    is_started = false;

    //Clear tick variables
    start_time = 0;
    pause_time = 0;
}
void Time::paused()
{
    if (is_started && is_paused == false )
        {
            is_paused = true;
            //Calculate the paused ticks
            pause_time = SDL_GetTicks() - start_time ;
            start_time = 0;
        }
}
void Time :: unpaused()
{
    if (is_paused == true && is_started == true)
        {
            is_paused = false;
            //Reset the starting ticks
            is_started = SDL_GetTicks() - pause_time ;
            //Reset the paused ticks
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