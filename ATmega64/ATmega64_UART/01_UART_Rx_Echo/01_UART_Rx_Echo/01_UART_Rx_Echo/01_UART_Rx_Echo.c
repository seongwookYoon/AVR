/*
 * _01_UART_Rx_Echo.c
 *
 * Created: 2019-08-20 오전 11:34:02
 *  Author: Steve
 */ 

#define F_CPU  14745600UL     // Clock Speed
#define BAUD   38400          //TargetBaud
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define MAX_RX_NUM	3	//최대 수신 바이트 수
//===========================================================================
//                         STRUCT
//===========================================================================

//유아트 수신 구조체
typedef struct uart1_rx_struct
{
	volatile unsigned char rcvFlag;	//수신 완료 플래그
	volatile unsigned char rcvCnt;  //수신 횟수 카운터 
	unsigned char rcvBuff[MAX_RX_NUM]; //수신 데이터 저장용 버퍼
	
}uart1_rx_type;
//===========================================================================
//                          GLOBAL VARIABLES
//===========================================================================
uart1_rx_type com1;	//유아트 수신 구조체 변수

//===========================================================================
//                          GLOBAL FUNCTIONS
//===========================================================================

//1Byte 송신 함수
void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR1A & (1<<UDRE1)) )
	;
	/* Put data into buffer, sends the data */
	UDR1 = data;
}

//nByte 송신 함수
/*void USART_putString(unsigned char *str)
{
	while(*str)
	{
		USART_Transmit(*str);
		str++;
	}
}*/
void USART_putString(unsigned char *str, unsigned char len)
{
	for(int i=0; i< len; i++)
	{
		USART_Transmit(*str);
		str++;
	}
}

// 1Byte 수신 함수
unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR1A & (1<<RXC1)) )
	;

	/* Get and return received data from buffer */
	return UDR1;
}

//UART 초기화 함수
void USART_ini( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR1H = (unsigned char)(ubrr>>8);
	UBRR1L = (unsigned char)ubrr;

	/* Enable receiver and transmitter */
	/* RX Complete Interrupt Enable */
	UCSR1B =(1<<RXCIE1)|(1<<RXEN1)|(1<<TXEN1);

	/* Set frame format: 8data, 2stop bit */
	UCSR1C = (1<<USBS1)|(3<<UCSZ10);
}

ISR(USART1_RX_vect)
{	
	com1.rcvBuff[com1.rcvCnt++] = UDR1; //수신 데이터 버퍼에 저장
	
	if(com1.rcvCnt == MAX_RX_NUM) //현재 수신된 데이터 수와 최대 수신 바이트 수 비교
	{
		com1.rcvFlag = 1;	//수신 완료 플래그 설정
		com1.rcvCnt=0;		//수신 데이터 카운트 초기화
	}
}

int main(void)
{	
	USART_ini(MYUBRR);  //UART초기화 함수 호출
	sei();				//인터럽트 허용

	while(1)
	{
		//TODO:: Please write your application code
		if(com1.rcvFlag == 1)
		{
			USART_putString(com1.rcvBuff,MAX_RX_NUM);	//수신된 데이터 유아트 전송 (Echo)
			com1.rcvFlag =0;	//유아트 수신 플래그 클리어
		}
	}
	return 0;
}