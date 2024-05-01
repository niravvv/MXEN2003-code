//Example ATmega2560 Project
//File: ATmega2560Project.c
//An example file for second year mechatronics project

//include this .c file's header file
#include "Controller.h"
#define DEBOUNCE_PERIOD 100

//static function prototypes, functions only called in this file
volatile uint16_t btn_reset = 0;
volatile uint16_t timer_btn = 1; //if its 1 then timer is running, if its 0 then timer is stopped
volatile uint16_t t = 0;
//static function prototypes, functions only called in this file

int main(void)
{
  cli();
  TCCR1A = 0;
  TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS11);
  TCNT1 = 0;
  ICR1 = 1999;
  TIMSK1 = (1<<ICIE1);

  DDRE &= ~(2<<PE3); //INT0 input mode
  EICRB |= (1<<ISC51)|(1<<ISC41);
  EICRB &= ~(1<<ISC50)|~(1<<ISC40); //INT0 falling edge trigger
  EIMSK |= (1<<INT5)|(1<<INT4); //INT0 enable
  sei();

  char lcd_string[33]={0};

  milliseconds_init();
  adc_init();
  lcd_init();

  _delay_ms(20);
  uint16_t sec =0;
  uint16_t min =0;
  

  while(1)
  {

    if(t>999)
    {
      sec += 1;
      t=0;
    }

    if(sec>59)
    {
      sec = 0;
      min += 1;
    }

    lcd_clrscr();
    lcd_home();
    sprintf(lcd_string, " %2u:%2u:%3u" , min, sec, t);
    lcd_puts(lcd_string);
    _delay_ms(50);

    if (btn_reset == 1)
    {
      _delay_ms(100);
      btn_reset = 0;
      t=0;
      sec=0;
      min=0;
    }
  
  }

  return(1);
}//end main 

ISR(INT5_vect)
{
    uint32_t currentTime = milliseconds_now();
    static uint32_t previousTime = 0;

    if ((currentTime - previousTime) > DEBOUNCE_PERIOD)
    {
      btn_reset = 1;
      previousTime = currentTime;
    }
}

ISR(TIMER1_CAPT_vect)
{
 if (timer_btn == 1)
 {
    t += 1;
 }
}

ISR(INT4_vect)
{
    uint32_t currentTime = milliseconds_now();
    static uint32_t previousTime = 0;

    if ((currentTime - previousTime) > DEBOUNCE_PERIOD && timer_btn == 1)
    {
      timer_btn = 0;
      previousTime = currentTime;
    }
    else if((currentTime - previousTime) > DEBOUNCE_PERIOD && timer_btn == 0)
    {
      timer_btn = 1;
      previousTime = currentTime;
    }
}