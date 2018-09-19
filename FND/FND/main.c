#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/delay.h>

uint8_t number[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
//uint8_t fndselect[] = {0x01, 0x02, 0x04, 0x08};

void displayFND(uint8_t position, uint8_t number);
void displaynumber(int count);

volatile uint8_t timercounter0 = 0;
volatile unsigned int counter=0;

ISR(TIMER0_OVF_vect)
{
	if(timercounter0%4 == 0)
	displayFND(0, counter%10);
	else if(timercounter0%4 == 1)
	displayFND(1, counter%100/10);
	else if(timercounter0%4 == 2)
	displayFND(2, counter%1000/100);
	else if(timercounter0%4 == 3)
	displayFND(3, counter/1000);
	
	timercounter0++;
	if(timercounter0 >= 200)
	{
		timercounter0 =0;
	}
}

int main(void)
{
	int count =0, count2=0;
	
	DDRC = 0xff;
	DDRF = 0xff;
	
	TCCR0 |= (1 << CS02) | (0 << CS01) | (0 << CS00) ;
	TIMSK |= (1 << TOIE0);
	
	sei();
	
	while (1)
	{
		_delay_ms(100);
		_delay_ms(100);
		counter++;
	}
}

void displayFND(uint8_t position, uint8_t number)
{
	uint8_t num[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
	uint8_t fndselect[] = {0x01, 0x02, 0x04, 0x08};
	PORTC = PORTC|0x0f;
	PORTC &= ~fndselect[position];
	PORTF=num[number];
}

void displaynumber(int count)
{
	displayFND(0, count%10);
	_delay_ms(1);
	displayFND(1, count%100/10);
	_delay_ms(1);
	displayFND(2, count%1000/100);
	_delay_ms(1);
	displayFND(3, count/1000);
	_delay_ms(1);
}