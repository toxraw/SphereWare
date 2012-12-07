#ifndef __BRITE_H__ 
#define __BRITE_H__ 

#include <avr/io.h>
#include <util/delay.h>

// Defines for direct port access
#define CLKPORT PORTC
#define ENAPORT PORTC
#define LATPORT PORTE
#define DATPORT PORTF
#define CLKREG DDRC 
#define ENAREG DDRC
#define LATREG DDRE
#define DATREG DDRF
#define CLKPIN  7 
#define ENAPIN 	6 
#define LATPIN 	6 
#define DATPIN 	7 

// Variables for communication
unsigned long LED_CommandPacket;
int LED_CommandMode;
int LED_BlueCommand;
int LED_RedCommand;
int LED_GreenCommand;

// Define number of ShiftBrite modules
#define NumLEDs 1

void LED_Init(void);
void LED_SendPacket(void);
void LED_Latch(void);
void WriteLEDArray(int LEDChannels[NumLEDs][3]);

// Example loop to cycle all LEDs through primary colors
void LED_TestLoop(void);

#endif// __BRITE_H__ 
