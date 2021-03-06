/*! \mainpage Header File: week4_simulation.h (generic for both CA_1 and CA_2)
 *
 * @author     e-Yantra Team
 * @date       2020/03/31
 */


#ifndef WEEK4_SIMULATION_H_
#define WEEK4_SIMULATION_H_


//---------------------------------- HEADER FILES --------------------------------------------------
#include <avr/io.h>							// Standard AVR IO Library
#include <avr/interrupt.h>					// Standard AVR Interrupt Library


//---------------------------------- MACRO DEFINITIONS ---------------------------------------------

// Definitions for ATmega328P micro-controller in sample projects in Proteus 8 Demonstration software

#if defined(__AVR_ATmega328P__)

#define		F_CPU								16000000

//---------------------------------- INPUT / OUTPUT PERIPHERALS -----------------------------------------------------

// LCD pin definitions
#define		lcd_data_ddr_reg					DDRD		///< Data Direction Register for PORTD
#define		lcd_control_ddr_reg					DDRB		///< Data Direction Register for PORTB

#define		lcd_data_port_reg					PORTD		///< Port Register for PORTD
#define		lcd_control_port_reg				PORTB		///< Port Register for PORTB

#define		RS_pin								PB0			///< PORTB Pin 0 ( IO8 )
#define		RW_pin								PB2			///< PORTB Pin 2 ( IO10 )
#define		EN_pin								PB1			///< PORTB Pin 1 ( IO9 )

#define		DB7_pin								PD7			///< PORTD Pin 7 ( IO7 )
#define		DB6_pin								PD6			///< PORTD Pin 6 ( IO6 )
#define		DB5_pin								PD5			///< PORTD Pin 5 ( IO5 )
#define		DB4_pin								PD4			///< PORTD Pin 4 ( IO4 )

// Motor direction pin definitions
#define 	motors_dir_ddr_reg					DDRD		///< Data Direction Register for PORTD
#define 	motors_dir_port_reg					PORTD		///< Port Register for PORTD
#define 	motors_RB_pin						PD7			///< PORTD Pin 7 ( IO7 )
#define 	motors_RF_pin						PD6			///< PORTD Pin 6 ( IO6 )
#define 	motors_LF_pin						PD2			///< PORTD Pin 2 ( IO2 )
#define 	motors_LB_pin						PD4			///< PORTD Pin 4 ( IO4 )

// Motor enable pin definitions
#define 	motors_pwm_ddr_reg					DDRD		///< Data Direction Register for PORTD
#define 	motors_pwm_port_reg					PORTD		///< Port Register for PORTD
#define 	motors_pwm_R_pin					PD5			///< PORTD Pin 5 ( IO5 / OC0B )
#define 	motors_pwm_L_pin					PD3			///< PORTD Pin 3 ( IO3 / OC2B )

// 3 Line sensor pin definitions
#define		left_center_wl_ddr_reg				DDRB		///< Data Direction Register for PORTB
#define		left_center_wl_port_reg				PORTB		///< Port Register for PORTB
#define		left_center_wl_pin_reg				PINB		///< Pin Register for PORTB
#define		right_wl_ddr_reg					DDRC		///< Data Direction Register for PORTC
#define		right_wl_port_reg					PORTC		///< Port Register for PORTC
#define		right_wl_pin_reg					PINC		///< Pin Register for PORTC
#define		left_wl_sensor_pin					PB3			///< PORTB Pin 3 ( IO11 )
#define		center_wl_sensor_pin				PB4			///< PORTB Pin 4 ( IO12 )
#define		right_wl_sensor_pin					PC0			///< PORTC Pin 0 ( AD0 )

//---------------------------------- INTERNAL REGISTERS -----------------------------------------------------

// Timer / Counter 2 registers
#define		TCCR2A_reg							TCCR2A		///< Timer / Counter Control Register 2A
#define		TCCR2B_reg							TCCR2B		///< Timer / Counter Control Register 2B
#define		TCNT2_reg							TCNT2		///< Timer / Counter 2 register
#define		OCR2A_reg							OCR2A		///< Output Compare Register 2 A
#define		OCR2B_reg							OCR2B		///< Output Compare Register 2 B
#define		TIMSK2_reg							TIMSK2		///< Timer / Counter Interrupt Mask register 2
#define		TIFR2_reg							TIFR2		///< Timer / Counter Interrupt Flag register 2

// Timer / Counter 0 registers
#define		TCCR0A_reg							TCCR0A		///< Timer / Counter Control Register 0A
#define		TCCR0B_reg							TCCR0B		///< Timer / Counter Control Register 0B
#define		TCNT0_reg							TCNT0		///< Timer / Counter 0 register
#define		OCR0A_reg							OCR0A		///< Output Compare Register 0 A
#define		OCR0B_reg							OCR0B		///< Output Compare Register 0 B
#define		TIMSK0_reg							TIMSK0		///< Timer / Counter Interrupt Mask register 0
#define		TIFR0_reg							TIFR0		///< Timer / Counter Interrupt Flag register 0

// Bits of TCCRnA register ( Timer / Counter 'n' Control Register A, where n = 0, 1, 2 )
#define		COMA1_bit							COM2A1		///< 7	( Compare Output Mode bit 1 for Channel A )
#define		COMA0_bit							COM2A0		///< 6	( Compare Output Mode bit 0 for Channel A )
#define		COMB1_bit							COM2B1		///< 5	( Compare Output Mode bit 1 for Channel B )
#define		COMB0_bit							COM2B0		///< 4	( Compare Output Mode bit 0 for Channel B )
#define		WGM1_bit							WGM21		///< 1	( Waveform Generation Mode bit 1 )
#define		WGM0_bit							WGM20		///< 0	( Waveform Generation Mode bit 0 )

// Bits of TCCRnB register ( Timer / Counter 'n' Control Register B, where n = 0, 1, 2 )
#define		WGM2_bit							WGM22		///< 3	( Waveform Generation Mode bit 2 )
#define		CS2_bit								CS22		///< 2	( Clock Select bit 2 )
#define		CS1_bit								CS21		///< 1	( Clock Select bit 1 )
#define		CS0_bit								CS20		///< 0	( Clock Select bit 0 )

#endif

#endif /* WEEK4_SIMULATION_H_ */