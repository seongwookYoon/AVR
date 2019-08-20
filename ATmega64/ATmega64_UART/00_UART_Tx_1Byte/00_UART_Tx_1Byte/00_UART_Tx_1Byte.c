/*
 * _00_UART_Tx_1Byte.c
 *
 * Created: 2019-08-20 오전 10:42:16
 *  Author: Steve
 */ 

#define F_CPU	14745600UL	// Clock Speed
#define BAUD	38400		//Target Baud
#define MYUBRR	F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#define FEATURE_USART1_PRINTF

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
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	/* Set frame format: 8data, 2stop bit */
	UCSR1C = (1<<USBS1)|(3<<UCSZ10);
}


int main(void)
{
	USART_ini(MYUBRR);			//UART초기화 함수 호출
	unsigned char data = 0x5A;	//UART 송신 데이터 
	while(1)
	{	
		//TODO:: Please write your application code	
		_delay_ms(20);			// 20ms 지연시간
		USART_Transmit(data);	// UART#1 1Byte 전송함수		
	}
	return 0;
}