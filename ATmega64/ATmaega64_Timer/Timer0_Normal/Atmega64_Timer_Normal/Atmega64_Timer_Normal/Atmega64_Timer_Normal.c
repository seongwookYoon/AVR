/*
 * Atmega64_Timer_Normal.c
 *
 * Created: 2019-08-12 오전 11:36:36
 *  Author: Steve
 */ 

#define F_CPU	14745600UL	//14.7456Mhz

#include <avr/interrupt.h>
#include <avr/io.h>

#define TCNT0_VAL	112	//타이머0 2.5ms마다 인터럽트 발생

volatile unsigned char Tmr0Cnt=0; //타이머0 ISR에서 사용하는 카운트 변수

void timer0_ini(void)
{
	TCCR0 = (1<<CS02)|(1<<CS01);	//Clock Select,256분주
	TIMSK = (1<<TOIE0);				//Timer/Counter0 Overflow Interrupt Enable
	TCNT0 = TCNT0_VAL;				//2.5ms마다 인터럽트 발생
}

//Timer 0 Overflow interrupt
ISR(TIMER0_OVF_vect)
{
	TCNT0 = TCNT0_VAL;	// 오버플로우 인터럽트 발생시 TCNT0는 0으로 초기화됨. 
						// 따라서 목표 주기로 설정된 TCNT값을 셋팅해줘야 됨.
						
	//2.5ms마다 인터럽트 발생
	if(++Tmr0Cnt >= 40) //2.5ms x 40 = 100ms마다 한번씩 PORTB토글 
	{
		Tmr0Cnt=0;
		PORTB ^= (1<<PORTB0); //PORTB 토글
	}	
}

int main(void)
{
	//약 50ms마다 PORTB의 0번핀 출력토글
	DDRB = (1<DDRB0);
	PORTB = (1<<PORTB0);
	
	timer0_ini(); //타이머 0 초기화 함수 호출
	sei();	//전체 인터럽트 허용 (avr/interrupt.h 필요)
		
    while(1)
    {
        //TODO:: Please write your application code 
    }
}