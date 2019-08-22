/*
 * ATmega64_UART_Printf.c
 *
 * Created: 2019-08-22 오후 12:04:23
 *  Author: Steve
 */ 

#define F_CPU 14745600UL     // Clock Speed
#define BAUD   38400          //TargetBaud
#define MYUBRR F_CPU/16/BAUD-1

#define FEATURE_DEBUG_UART1_PRINTF	//Feature.h로 관리

#include <stdio.h>
#include <avr/io.h>

//1Byte 송신 함수
void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR1A & (1<<UDRE1)) )
	;

	/* Put data into buffer, sends the data */
	UDR1 = data;
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
	#ifdef FEATURE_DEBUG_UART1_PRINTF
		static FILE OUTPUT_device = FDEV_SETUP_STREAM(USART_Transmit,NULL, _FDEV_SETUP_WRITE);
		static FILE INPUT_device = FDEV_SETUP_STREAM(NULL,USART_Receive, _FDEV_SETUP_WRITE);
		stdout	= &OUTPUT_device;
		stdin	= &INPUT_device;
	#endif
	
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
	unsigned char Arr[]="Hello World";
	unsigned char Val = 150;
	
	USART_ini(MYUBRR);
	
	printf("String: %s\r\n",Arr);
	printf("Val: %d\r\n",Val);
    while(1)
    {
        //TODO:: Please write your application code 
    }
}