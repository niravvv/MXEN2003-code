//Example ATmega2560 Project
//File: ATmega2560Project.c
//An example file for second year mechatronics project

//include this .c file's header file
#include "Controller.h"
#define DEBOUNCE_PERIOD 100

//static function prototypes, functions only called in this file
volatile uint16_t btn_press = 0;

int main(void)
{

  char lcd_string[33]={0};

  milliseconds_init();
  adc_init();
  lcd_init();

  _delay_ms(20);
  uint16_t variableToPrint;
  uint16_t temp;

  //interrupt setup
    cli();
    DDRE &= ~(2<<PE3); //INT0 input mode
    EICRB |= (1<<ISC51);
    EICRB &= ~(1<<ISC50); //INT0 falling edge trigger
    EIMSK |= (1<<INT5); //INT0 enable
    sei();

while(1)
{
    variableToPrint = adc_read(0);
    variableToPrint = 2631.6/(variableToPrint) - 1.1092;
    lcd_clrscr();
    lcd_home();
    sprintf(lcd_string, " %u" , variableToPrint);
    lcd_puts(lcd_string);

  if (btn_press == 1){
    _delay_ms(1000);
    btn_press = 0;
  }
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
      btn_press = 1;
      previousTime = currentTime;
    }
}