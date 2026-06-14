#ifndef Pins_Arduino_h
#define Pins_Arduino_h

/*
 * pins_arduino.h - AT90S8535 pin mapping for Arduino
 *
 * AT90S8535 Pin Layout (PDIP-40 / TQFP-44)
 *
 *   Port A (PA0-PA7): Digital 0-7   / ADC0-ADC7 (analog input)
 *   Port B (PB0-PB7): Digital 8-15  / SPI (PB4=SS, PB5=MOSI, PB6=MISO, PB7=SCK)
 *   Port C (PC0-PC7): Digital 16-23 / General purpose
 *   Port D (PD0-PD7): Digital 24-31 / UART (PD0=RXD, PD1=TXD), INT0/INT1, Timer
 *
 * NOTE: AT90S8535 is a Classic AVR (avr3 architecture).
 *       Some newer AVR features (e.g., TWI) are NOT available.
 *       Timer0 is 8-bit, Timer1 is 16-bit, Timer2 is 8-bit (async capable).
 */

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS    32
#define NUM_ANALOG_INPUTS   8

// analogInputToDigitalPin: Port A = Digital 0-7
#define analogInputToDigitalPin(p) ((p < 8) ? (p) : -1)

// PWM対応ピン (Timer1 OC1A=PD5, OC1B=PD4 / Timer2 OC2=PD7)
#define digitalPinHasPWM(p) \
    ((p) == 29 || (p) == 28 || (p) == 31)
//   PD5=29     PD4=28      PD7=31

// SPI
static const uint8_t SS   = 12;  // PB4
static const uint8_t MOSI = 13;  // PB5
static const uint8_t MISO = 14;  // PB6
static const uint8_t SCK  = 15;  // PB7

// UART
#define PIN_SERIAL_RX  24   // PD0
#define PIN_SERIAL_TX  25   // PD1

// Analog pins (PA0-PA7 = A0-A7)
static const uint8_t A0 = 0;
static const uint8_t A1 = 1;
static const uint8_t A2 = 2;
static const uint8_t A3 = 3;
static const uint8_t A4 = 4;
static const uint8_t A5 = 5;
static const uint8_t A6 = 6;
static const uint8_t A7 = 7;

/*
 * digitalPinToPCICR / digitalPinToPCIMSK:
 * AT90S8535 does NOT support Pin Change Interrupts.
 * Only INT0 (PD2=26) and INT1 (PD3=27) are available.
 */
#define digitalPinToInterrupt(p) \
    ((p) == 26 ? 0 : ((p) == 27 ? 1 : NOT_AN_INTERRUPT))
//   PD2=INT0            PD3=INT1

/*
 * Pin to Port/DDR/PIN mapping
 * Order: PA0-PA7, PB0-PB7, PC0-PC7, PD0-PD7
 */

#define PA 1
#define PB 2
#define PC 3
#define PD 4

// Port registers
#define PORT_PA PORTA
#define PORT_PB PORTB
#define PORT_PC PORTC
#define PORT_PD PORTD

// digitalPinToPort
const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
    PA, PA, PA, PA, PA, PA, PA, PA,  //  0- 7: PA0-PA7
    PB, PB, PB, PB, PB, PB, PB, PB,  //  8-15: PB0-PB7
    PC, PC, PC, PC, PC, PC, PC, PC,  // 16-23: PC0-PC7
    PD, PD, PD, PD, PD, PD, PD, PD, // 24-31: PD0-PD7
};

// digitalPinToBitMask
const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
    _BV(0), _BV(1), _BV(2), _BV(3), _BV(4), _BV(5), _BV(6), _BV(7),  // PA
    _BV(0), _BV(1), _BV(2), _BV(3), _BV(4), _BV(5), _BV(6), _BV(7),  // PB
    _BV(0), _BV(1), _BV(2), _BV(3), _BV(4), _BV(5), _BV(6), _BV(7),  // PC
    _BV(0), _BV(1), _BV(2), _BV(3), _BV(4), _BV(5), _BV(6), _BV(7),  // PD
};

// digitalPinToTimer
//   Timer1 OC1B = PD4 (pin28), OC1A = PD5 (pin29)
//   Timer2 OC2  = PD7 (pin31)
const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
    NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER,  //  0- 3
    NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER,  //  4- 7
    NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER,  //  8-11
    NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER,  // 12-15
    NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER,  // 16-19
    NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER,  // 20-23
    NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER, NOT_ON_TIMER,  // 24-27
    TIMER1B,      TIMER1A,      NOT_ON_TIMER, TIMER2,        // 28-31 (PD4,PD5,PD6,PD7)
};

#ifdef ARDUINO_MAIN

// Port to IO register mapping
const uint16_t PROGMEM port_to_mode_PGM[] = {
    NOT_A_PORT,
    (uint16_t) &DDRA,   // PA
    (uint16_t) &DDRB,   // PB
    (uint16_t) &DDRC,   // PC
    (uint16_t) &DDRD,   // PD
};

const uint16_t PROGMEM port_to_input_PGM[] = {
    NOT_A_PORT,
    (uint16_t) &PINA,
    (uint16_t) &PINB,
    (uint16_t) &PINC,
    (uint16_t) &PIND,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
    NOT_A_PORT,
    (uint16_t) &PORTA,
    (uint16_t) &PORTB,
    (uint16_t) &PORTC,
    (uint16_t) &PORTD,
};

#endif // ARDUINO_MAIN

#endif // Pins_Arduino_h
