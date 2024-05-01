//Example ATmega2560 Project
//File: ATmega2560Project.c
//An example file for second year mechatronics project

//include this .c file's header file
#include "Controller.h"

//static function prototypes, functions only called in this file

int main(void)
{
  TCCR1A = (1<<COM1A1)|(1<<COM1B1);
  TCCR1B = (1<<WGM13)|(1<<CS11);
  // TCNT1 = 0;
  ICR1 = 20000;
  DDRB |= (1<<PB5)|(1<<PB6);
  uint16_t compValueV = 10000;
  uint16_t compValueH = 10000;
  OCR1A = compValueV;
  OCR1B = compValueH;
  adc_init();
  uint32_t joystickADC = 0;

  while(1)
  {
    //Vertical
    joystickADC = adc_read(0);
    compValueV = (joystickADC*(uint32_t)1000/1023) + 1000;
    OCR1A = compValueV;
    //Horizontal
    joystickADC = adc_read(1);
    compValueH = (joystickADC*(uint32_t)1000/1023) + 1000;
    OCR1B = compValueH;
  }
  
  
  

  return(1);
}//end main 