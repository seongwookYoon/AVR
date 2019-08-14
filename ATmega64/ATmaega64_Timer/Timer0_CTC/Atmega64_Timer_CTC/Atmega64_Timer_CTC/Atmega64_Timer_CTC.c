
#define F_CPU 14745600UL //14.7456Mhz, UL은 Unsgined Long 자료형을 의미함

#include <avr/interrupt.h> //sei()함수가 정의되있음
#include <avr/io.h>

volatile unsigned char Tmr0Cnt=0; //타이머0 ISR에서 사용하는 카운트 변수

//2.5ms마다 인터럽트 발생
void timer0_ini(void)
{
	TCCR0 = (1<<WGM01)|(1<<CS02)|(1<<CS01); //Clock Select,256분주
	TIMSK = (1<<OCIE0);						//Timer/Counter0 Output Compare Match Interrupt Enable
	OCR0 = 71;								//TCNT0와 비교되는 값, Top 값
}

ISR(TIMER0_COMP_vect)
{
	//2.5ms마다 인터럽트 발생
	if(++Tmr0Cnt >= 40) //2.5ms x 40 = 100ms마다 한번씩 PORTB토글
	{
		Tmr0Cnt=0;
		PORTB ^= (1<<PORTB0); //PORTB 토글
	}
	
}
int main(void)
{
	//100ms마다 PORTB의 0번핀 출력토글
	DDRB = (1<DDRB0);
	PORTB = (1<<PORTB0);
	
	timer0_ini(); //타이머 0 초기화 함수 호출
	sei(); //전체 인터럽트 허용 (avr/interrupt.h 필요)
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}