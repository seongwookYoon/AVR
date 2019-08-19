/*
 * ATmega64_Timer_PCPWM.c
 *
 * Created: 2019-08-19 오전 9:53:23
 *  Author: Steve
 */ 


#define F_CPU 14745600UL //14.7456Mhz, UL은 Unsgined Long 자료형을 의미함
#include <avr/io.h>

//PC PWM, OC0핀 비반전 출력
void timer0_ini(void)
{
	TCCR0 = (1<<WGM00)|(1<<COM01)|(1<<CS02)|(1<<CS01);	//PWM, Phase Correct, Clock Select,256분주
														//Clear OC0 on Compare Match when up-counting. 
														//Set OC0 on Compare Match when downcounting.
	//OCR0 = 128;		//Duty 50%
	OCR0 = 25;			//Duty 10%
	DDRB = (1<<DDRB4);	//OC0핀 출력 설정
}

int main(void)
{	
	timer0_ini(); //타이머 0 초기화 함수 호출	
	while(1)
	{
		//TODO:: Please write your application code
	}
}