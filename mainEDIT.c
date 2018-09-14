/*
 *  main.c
 *
 *  Created on: 25 Jan 2013
 *  Author: Oskar Figura
 *  (MENU_KEY_PIN & MENU_KEY_DOWN) is used to choose menu options from 1 to 8 LEDs signal which option you are currently on
 *  (SELECT_KEY_PIN & SELECT_KEY_DOWN) is used to confirm selection of a chosen option from the menu which starts the appropriate effect
 */
 
//Includes
#include<avr/io.h>
#include<util/delay.h>
 
//Macros for buttons and for checking if they are in low state
#define MENU_KEY_PIN (1<<PD0)
#define MENU_KEY_DOWN !(PIND & MENU_KEY_PIN)
 
#define SELECT_KEY_PIN (1<<PD1)
#define SELECT_KEY_DOWN !(PIND & SELECT_KEY_PIN)
 
int main(void)
{
    //Initialization
    DDRC = 0xFF;    //PORTC output
    PORTC = 0xFF;   //PORTC off by inserting 1's

    DDRA = 0xFF;    //PORTA output
    PORTA = 0xFF;   //PORTA off by inserting 1's

    DDRD &= ~( MENU_KEY_PIN | SELECT_KEY_PIN );   //Inputs PD0 and PD1
    PORTD |= MENU_KEY_PIN | SELECT_KEY_PIN;  //Connect buttons to VCC (internal resistor)

    int8_t i=0;  //Declare variable used for loops

    while(1)                        
    {
        //Move to next menu option
        if(MENU_KEY_DOWN)           
        {
            _delay_ms(80);  //Accounting for potential changes in button state caused by it's internal components

            if(MENU_KEY_DOWN)
            {
                PORTC &= ~(1<<i);  //Turn LEDs ON showing value of i
                _delay_ms (250);
                ++i;                                    

                //Menu overflow loopback to start
                if(i==9)
                {
                    i=0;
                    PORTC = 0xFF;  //LEDs OFF signal no active menu option          
                }
            }
        }
 
        //Menu option selected
        if(SELECT_KEY_DOWN)                          
        {
            _delay_ms(80); //Accounting for potential changes in button state caused by it's internal components
            
            if(SELECT_KEY_DOWN)
            {
                if ( i == 1 ) {
                    int8_t x = 0;    

                    for(x=0; x<=7; x++)                     
                    {
                        PORTA &= ~(1<<x); //Turn on PORTC number x 
                        _delay_ms (100);               
                    }

                    for(x=7; x>=0; x--)                     
                    {
                        PORTA |= (1<<x);  //Turn off PORTC number x
                        _delay_ms (100);  
                    }
                }

                if ( i == 2 ) {
                    int8_t p,l;

                    //Turn LEDs ON until they meet in middle (----> <----)
                    for( p=7, l=0; p>=4 && l<=3; l++, p--)          
                    {
                        PORTA &= ~( 1<<l | 1<<p );
                        _delay_ms (100);
                    }

                    if(p==4 && l==3);                                                       
                    {
                        //Turn LEDs OFF (<---- ---->)
                        for(p=4, l=3; p<=7 && l>=0; p++, l--)           
                        {
                            PORTA |= ( 1<<l | 1<<p );
                            _delay_ms (100);
                        }
                    }
                }

                if ( i == 3 ) {
                    int8_t i; 

                    //Turn LEDs on ~ causes one LED to be ON, removing it will invert the result (all LEDs on one off) 
                    for(i=0; i<=7; i++)             
                    {
                        PORTA = ~(1<<i);             
                        _delay_ms (100);
                    }

                    for(i=7; i>=0; i--)             
                    {
                        PORTA = ~(1<<i);
                        _delay_ms (100);
                    }
                    PORTA |= 0xFF;
                }

                if ( i == 4 ) {
                    int8_t n,p;

                    for(n=0; n<=7; n=n+2)
                    {
                        PORTA &= ~(1<<n);
                        _delay_ms (300);
                    }

                    for(p=7; p>=0; p=p-2)
                    {
                        PORTA &= ~(1<<p);
                        _delay_ms (300);
                    }

                    PORTA = 0xFF;
                    _delay_ms (300);
                }

                if ( i == 5 ) {
                    int8_t p,l;

                    for( p=7, l=0; p>=4 && l<=3; l++, p--)          
                    {
                        PORTA = ~( 1<<l | 1<<p );
                        _delay_ms (100);
                    }

                    if(p==4 && l==3);                                                       
                    {
                        for(p=4, l=3; p<=7 && l>=0; p++, l--) 
                        {
                            PORTA = ~( 1<<l | 1<<p );
                            _delay_ms (100);
                        }
                    }
                    PORTA |= 0xFF;
                }

                if ( i == 6 ) {
                    PORTA &= ~0xFF;
                    _delay_ms(300);
                    PORTA |= 0xFF;
                    _delay_ms (300);
                }

                if ( i == 7 ) {
                    PORTA &= ~0xFF;
                }

                if ( i == 8 ) {
                    PORTA |= 0xFF;
                }
            }
        }
    }
}
 
