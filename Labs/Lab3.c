//Example ATmega2560 Project
//File: ATmega2560Project.c
//An example file for second year mechatronics project

//include this .c file's header file
#include "Controller.h"

//static function prototypes, functions only called in this file

int main2(void)
{
    //interrupt setup
    cli();
    DDRD &= ~(2<<DD0) //INT0 input mode
    EICRA |= (1<<ISC01)
    EICRA &= ~(1<<ISC00) //INT0 falling edge trigger
    EIMSK |= (1<<INT5) //INT0 enable
    sei();
  
  while(1)//main loop
  {
   
  }
 
  return(1);
}
//end main 

ISR(INT0_vect)
{
    uint32_t currentTime = milliseconds_now();
    static unit32_t previousTime = 0;

    if ((currentTime - previousTime) > DEBOUNCE_PERIOD)
    {
        PORTA ^= (1<<PA1);
        previousTime = currentTime;
    }
}