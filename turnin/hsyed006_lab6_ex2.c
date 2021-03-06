/*	Author: hsyed006
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 6  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo Link: https://drive.google.com/file/d/1n9QH34Af4tyPenQ9jKMm9LLVE48exEak/view?usp=sharing
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

enum States {init, one, two, three, wait1,  wait2, wait3}  State;
unsigned char tmp  =  0x00;
unsigned char hold = 0x00;
void blinkGame(){
	tmp = ~tmp;
	hold = ~PINA & 0x01;
	//hold = hold & 0x01;
	switch(State){
		case init:
			State = one;		
		break;
	
		case one:
			if(hold){
				State  = wait1;
			}
			else{
				State = two;
			}
		break;
		
		case wait1:
			if(hold){
				State = one;
			}
			else{ State = wait1;}
		break;

		case two:
			if(hold){
                                State  = wait2;
                        }
                        else{
				State = three;
			}
		break;

                case wait2:
                        if(hold){
                                State = one;
                        }
                        else{State = wait2;}
                break;

		case three:
			if(hold){
                                State  = wait3;
                        }
                        else{
				State = one;
			}
		break;
		

                case wait3:
                        if(hold){
                                State = one;
                        }
                        else{ State = wait3;}
                break;


		default:
			State = init;
		break;
	}
	
	switch(State){
		case init:
					
		break;
	
		case one:
			tmp = 0x01;
		break;

		case two:
			tmp = 0x02;
		break;

		case three:
			tmp = 0x04;
		break;

		case wait1:
                        tmp = 0x01;
                break;

                case wait2:
                        tmp = 0x02;
                break;

                case wait3:
                        tmp = 0x04;
                break;

	}
	PORTB = tmp;
}



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
    /* Insert your solution below */
	TimerSet(300);
	TimerOn();
	State = init;
    
	while (1) {
		blinkGame();
		while(!TimerFlag);
		TimerFlag = 0;
    }
    return 1;
}
