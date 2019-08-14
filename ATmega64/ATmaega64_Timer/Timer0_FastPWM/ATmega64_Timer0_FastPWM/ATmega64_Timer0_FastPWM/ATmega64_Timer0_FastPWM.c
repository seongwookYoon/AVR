/*
 * ATmega64_Timer0_FastPWM.c
 *
 * Created: 2019-08-13 오후 4:42:45
 *  Author: Steve
 */ 

#define F_CPU 14745600UL //14.7456Mhz, UL은 Unsgined Long 자료형을 의미함
#include <avr/io.h>

//Fast PWM모드 설정
void timer0_ini(void)
{
	TCCR0 = (1<<WGM01)|(1<<WGM00)|(1<<COM01)|(1<<CS02)|(1<<CS01); //Fast PWM모드, OC0핀 비반전 출력 사용,256분주		
	OCR0 = 128;			//Duty 50%
	//OCR0 = 25;			//Duty 10%
	DDRB = (1<<DDRB4); //OC0핀 출력 설정
}

int main(void)
{
	timer0_ini(); //타이머 0 초기화 함수 호출
	 
    while(1)
    {
        //TODO:: Please write your application code 
    }
}