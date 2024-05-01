//Example ATmega2560 Project
//File: ATmega2560Project.c
//An example file for second year mechatronics project

//include this .c file's header file
#include "Controller.h"

//static function prototypes, functions only called in this file

int main2(void)
{
  DDRC = 0xFF;//put PORTC into output mode
  DDRA = 0;// put PORTA into input
  PORTA = 0;
  PORTA |= (1<<PA0); // enabling pullup PA0
  PORTC = 0; 

  uint16_t adcInput = 0; 
  
  while(1)//main loop
  {
    if(!(PINA & (1<<PA0)))// PA0 low / / button pressed
    {
        adcInput = adc_read(1);
        adcInput = adcInput/128;
        PORTC |= adcInput;
    }
    else{
        adcInput = adc_read(0);
        adcInput = adcInput/128;
        PORTC |= adcInput;
    }
  }
 
  return(1);
}
//end main 