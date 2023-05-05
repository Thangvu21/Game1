#ifndef TIME_H_
#define TIME_H_

#include "commonFunction.h"

class Time // quan ly time
{
public:
    Time();
    ~Time();

    void start() ;

    void stop () ;

    void paused() ;
       
    void unpaused() ;
  
    int get_ticks();

    bool is_started_ ();

    bool is_paused_ () ;

private:
    //The clock time when the timer started
    int start_time ; 
    //The ticks stored when the timer was paused
    int pause_time ;

    //The timer status
    bool is_paused ;
    bool is_started ;
};

#endif