#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init(unsigned int);
void USART_Transmit(unsigned char);
unsigned char USART_Receive(void);

int main(void)
{
    USART_Init(MYUBRR);
    DDRB = 0xFF;

    while(1)
    {
        unsigned char c = USART_Receive();
        if (c == 'w')
        {
            PORTB = 0x00;
            PORTB |= (1<<PORTB2);
        }  
        else if (c == 's')
        {
            PORTB = 0x00;
            PORTB |= (1<<PORTB1);
        }    
        else if (c == 'd')
        {
            PORTB = 0x00;
            PORTB |= (1<<PORTB0);
        }  
        else if (c == 'a')
        {
            PORTB = 0x00;
            PORTB |= (1<<PORTB3);
        }
        else
            PORTB = 0x00;
    }

    return 0;
}


void USART_Init(unsigned int ubrr)
{
    /* Set Baud Rate */
    UBRR0H = (unsigned char) (ubrr>>8);
    UBRR0L = (unsigned char) ubrr;

    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);

    /* Set frame format: 8 data, 2 stop bit */
    UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

void USART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while ( !(UCSR0A & (1<<UDRE0)) )
    ;

    /* Put data into buffer, sends the data */
    UDR0 = data;
}

unsigned char USART_Receive(void)
{
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) )
    ;

    /* Get and return received data from buffer */
    return UDR0;
}