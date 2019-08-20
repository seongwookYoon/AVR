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
void USART_putString(unsigned char *str)
{
	while(*str)
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

//UART1 Rx 인터럽트 서비스 루틴
ISR(USART1_RX_vect)
{
	
}



int main(void)

{

	USART_ini(MYUBRR);            //UART초기화 함수 호출

	unsigned char data = 0x5A;    //UART 송신 데이터

	while(1)

	{

		//TODO:: Please write your application code

		_delay_ms(20);         //20ms 지연시간

		USART_Transmit(data);  // UART#1 1Byte 전송함수

	}

	return 0;

}