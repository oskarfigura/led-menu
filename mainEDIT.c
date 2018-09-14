/*
 * main.c
 *
 *  Created on: 25 Jan 2013
 *      Author: osa1313 projekt team
 */
 
//Bazgroly (nie patrzec na komentarze hehe)
//Klawiszem jeden wybieramy menu od 1 do 8 a diody sygnalizuja na ktorym obecnie sie znajdujemy
//Jezeli klawisz zostanie nacisniety wiecej razy niz jest pozycji menu, diody zostana zgaszone oraz wartosc i wyzerowana
//aby umozliwic ponowny wybor menu.
//Klawisz 2 sluzy do zatwierdzenia menu ktore wybralismy oraz aby zostala wykonana petla switch (efekty)
//Pliki naglowkowe
#include <avr/io.h>
#include <util/delay.h>
 
//Makrodefinicje klawiszy oraz mkara sprawdzajace stan niski na nich
#define KEY_PIN1 (1<<PD0)
#define KEY_DOWN1 !(PIND & KEY_PIN1)
 
#define KEY_PIN2 (1<<PD1)
#define KEY_DOWN2 !(PIND & KEY_PIN2)
 
//Petla glowna main
int main(void) {
//Inicjalizacje
        DDRC = 0xFF;            //PORTC jako wyjscie
        PORTC = 0xFF;           //PORTC wylaczony poprzez wstawienie jedynek
 
        DDRA = 0xFF;            //PORTA jako wyjscie
        PORTA = 0xFF;           //PORTA wylaczony poprzez wstawienie jedynek
 
        DDRD &= ~( KEY_PIN1 | KEY_PIN2 );               //Wejscia PD0 oraz PD1
        PORTD |= KEY_PIN1 | KEY_PIN2;                   //Podciagniecie klawiszy pod VCC (wewnetrzny rezystor)
 
        int8_t i = 0;                     //Deklaracja zmiennej iteracyjnej (i) o wartosci 0
 
        while ( 1 )                        //Petla nieskonczona
        {
 
                if ( KEY_DOWN1 )           //Klawisz 1 nacisniety ?
                {
                        _delay_ms ( 80 );  //Drgania stykow
                        if ( KEY_DOWN1 ) {
                                PORTC &= ~( 1 << i );               //Zapalaj diody pokazujac jaka wartosc ma zmienna i
                                _delay_ms ( 250 );
                                ++i;                                    //Zwiekszaj wartosc i o jeden za kazdym wykonaniem petli
 
                                if ( i == 9 )                                //Jezeli klawisz zostanie nacisniety wiecej razy niz mamy pozycjy menu, wtedy zacznij odliczac ponownie
                                                {
                                        i = 0;
                                        PORTC = 0xFF;           //Wylacz diody sygnalizujac ze zadne menu nie wybrane
                                }
                        }
                }
 
                if ( KEY_DOWN2 )                           //Kiedy klawisz 2 nacisniety przejdz do petli switch i zapal odpowiednia diode w zaleznosci od wartosci zmiennej i
                {
                        _delay_ms ( 80 );
                        if ( KEY_DOWN2 ) {
 
//**************Efekt 1****************************
                                if ( i == 1 ) {
                                        int8_t x = 0;                                     //Deklaracja zmiennej i
                                        for ( x = 0; x <= 7; x++ )                     //i jest rowne 0, rob dopoki i bedzie mniejsze od 7 lub rowne 7, za kadym obiegiem zwieksz wartosc i o 1
                                                        {
                                                PORTA &= ~( 1 << x );               //Taka jaka wartosc i taki pin portu C zostanie wlaczony
                                                _delay_ms ( 100 );                //Odczekaj 100ms
 
                                        }
 
                                        for ( x = 7; x >= 0; x-- )                     //i jest rowne 7, rob dopoki i bedzie wieksze od zero lub jemu rowne, zmniejszaj wartosc i o 1 za kazdym obiegiem
                                                        {
                                                PORTA |= ( 1 << x );                //Pin portu C wylaczany po kolei
                                                _delay_ms ( 100 );                //Odczekaj 100ms
                                        }
                                }
 
//*******************Efekt 2**********************
 
                                if ( i == 2 ) {
                                        int8_t p, l;
                                        for ( p = 7, l = 0; p >= 4 && l <= 3; l++, p-- )          //Zapalaj LEDy pokolei az spotkaja sie na srodku (----> <----)
                                                        {
                                                PORTA &= ~( 1 << l | 1 << p );
                                                _delay_ms ( 100 );
                                        }
 
                                        if ( p == 4 && l == 3 )                                                        //Jezeli petla for sie wykonala oraz  p i l przyjely takie wartosci, wykonaj petle for
                                                        {
                                                for ( p = 4, l = 3; p <= 7 && l >= 0; p++, l-- )           //Gas LEDy lecz do tylu czyli od srodka na boki (<---- ---->)
                                                                {
                                                        PORTA |= ( 1 << l | 1 << p );
                                                        _delay_ms ( 100 );
                                                }
                                        }
                                }
 
//******************************Efekt 3*****************************
 
                                if ( i == 3 ) {
                                        int8_t i;                               //Zmienna nie jest widoczna przez inne funkcje niz ta
 
                                        for ( i = 0; i <= 7; i++ )             //Zapalaj kolejne diody, tylda ~ powoduje ze tylko jedna dioda jest zapalona (prace w negatywie)
                                                        {
                                                PORTA = ~( 1 << i );                //Usuniecie tyldy ~ spowoduje prace w negatywie czyli wszytkie LEDy zapalone a jedna sie tylko gasi
                                                _delay_ms ( 100 );
                                        }
 
                                        for ( i = 7; i >= 0; i-- )             //Kiedy ostatnia dioda zostanie zapalona wroc do poczatku
                                                        {
                                                PORTA = ~( 1 << i );
                                                _delay_ms ( 100 );
                                        }
                                        PORTA |= 0xFF;
                        }
 
//**********************************Efekt 4***************************
 
                                if ( i == 4 ) {
                                        int8_t n, p;
 
                                        for ( n = 0; n <= 7; n = n + 2 ) {
                                                PORTA &= ~( 1 << n );
                                                _delay_ms ( 300 );
                                        }
                                        for ( p = 7; p >= 0; p = p - 2 ) {
                                                PORTA &= ~( 1 << p );
                                                _delay_ms ( 300 );
                                        }
                                        PORTA = 0xFF;
                                        _delay_ms ( 300 );
                                }
 
//********************************Efekt 5********************************************
 
                                if ( i == 5 ) {
                                        int8_t p, l;
 
                                        for ( p = 7, l = 0; p >= 4 && l <= 3; l++, p-- )          //Zapalaj LEDy pokolei az spotkaja sie na srodku (----> <----)
                                                        {
                                                PORTA = ~( 1 << l | 1 << p );
                                                _delay_ms ( 100 );
                                        }
                                        if ( p == 4 && l == 3 )                                                      //Jezeli petla for sie wykonala oraz  p i l przyjely takie wartosci, wykonaj petle for
                                                        {
                                                for ( p = 4, l = 3; p <= 7 && l >= 0; p++, l-- )           //Gas LEDy lecz do tylu czyli od srodka na boki (<---- ---->)
                                                                {
                                                        PORTA = ~( 1 << l | 1 << p );
                                                        _delay_ms ( 100 );
                                                }
                                        }
                                        PORTA |= 0xFF;
                                }
 
//********************************Efekt 6********************************************
 
                                if ( i == 6 ) {
                                        PORTA &= ~0xFF;
                                        _delay_ms ( 300 );
                                        PORTA |= 0xFF;
                                        _delay_ms ( 300 );
                                }
 
//********************************Efekt 7********************************************
 
                                if ( i == 7 ) PORTA &= ~0xFF;
 
//********************************Efekt 8********************************************
 
                                if ( i == 8 ) PORTA |= 0xFF;
 
                        }
                }
        }
}
 
