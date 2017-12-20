#include <avr/io.h>
#include <util/delay.h>
#define GREEN 0
#define RED 2
#define BUZZER 4
uint8_t get_Enable();
uint8_t get_Buzzer();
uint8_t get_Light();
void set_output(uint8_t, uint8_t);
int main()
{
    //PB0,2,4 OUTPUT //0Green 2Red 4Buzzer
    //PB1,3,5 INPUT  //1Enable 3Noise 5Light
    DDRB = 0b00010101;
    _delay_ms(2000);
    do
    {
        set_output(RED,0);
        set_output(GREEN,0);
        set_output(BUZZER,0);
    }
    while(get_Enable() == 0); //wait for ready
    while(1)
    {
        if(get_Light() == 0)
        {
            set_output(RED,0);
            set_output(GREEN,1);
        }
        else
        {
            set_output(RED,1);
            set_output(GREEN,0);
        }
        if(get_Buzzer() == 0)
        {
            set_output(BUZZER,0);
        }
        else
        {
            set_output(BUZZER,1);
        }
    }
}
uint8_t get_Enable()
{
    return (PINB & (1<<1));
}
uint8_t get_Buzzer()
{
    return (PINB & (1<<3));
}
uint8_t get_Light()
{
    return (PINB & (1<<5));
}
void set_output(uint8_t pin,uint8_t state)
{
	if(state)
    {
	    PORTB |= (1<<pin);
    }
	else
    {
	    PORTB &= ~(1<<pin);
    }	
}