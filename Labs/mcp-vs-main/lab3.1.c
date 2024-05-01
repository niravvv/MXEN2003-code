//Example ATmega2560 Project
//File: ATmega2560Project.c
//An example file for second year mechatronics project

//include this .c file's header file
#include "Controller.h"
#define DEBOUNCE_PERIOD 100

//static function prototypes, functions only called in this file

int main(void)
{
  milliseconds_init();

    //DDRA |= (1<<PA0);
    DDRA = 0xFF;//put PORTA into output mode
    PORTA = 0;

    //interrupt setup
    cli();
    DDRE &= ~(2<<PE3); //INT0 input mode
    EICRB |= (1<<ISC51);
    EICRB &= ~(1<<ISC50); //INT0 falling edge trigger
    EIMSK |= (1<<INT5); //INT0 enable
    sei();
  
  while(1)//main loop
  {
  }
  return(1);
}
//end main 

ISR(INT5_vect)
{
    uint32_t currentTime = milliseconds_now();
    static uint32_t previousTime = 0;

    if ((currentTime - previousTime) > DEBOUNCE_PERIOD)
    {
        PORTA ^= (1<<PA0);
        previousTime = currentTime;
    }
}