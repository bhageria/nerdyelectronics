/*! \  line_follow 
 *
 * @author      Ashwini Kodlimath
 * @date       2020/03/31
 *
  
 *
 * \subsection Motors Connections:
 * Direction Pins of Motors are connected to the ATmega328P microcontroller.			<br>
 *		 Motors Pin	  	Microcontroller Pin      										<br>
 *			  RB  	--> 	PD7															<br>
 *			  RF  	--> 	PD6															<br>
 *			  LF  	--> 	PD2															<br>
 *			  LB 	--> 	PD4															<br>
 *
 * PWM or Enable Pins of Motors of the ATmega328P microcontroller.						<br>
 *		   PWM Pin	  		Micro controller Pin										<br>
 *		  Left Motor  	--> 	PD3														<br>
 *		  Right Motor  	--> 	PD5														<br>
 * 
 * \subsection Macro_Definitions
 * Macros for Motor Control:															<br>
 *		motors_dir_ddr_reg			:	DDRD											<br>
 *		motors_dir_port_reg			:	PORTD											<br>
 *		motors_RB_pin				:	PD7												<br>
 *		motors_RF_pin				:	PD6												<br>
 *		motors_LF_pin				:	PD2												<br>
 *		motors_LB_pin				:	PD4												<br>
 *		motors_pwm_ddr_reg			:	DDRD											<br>
 *		motors_pwm_port_reg			:	PORTD											<br>
 *		motors_pwm_R_pin			:	PD5												<br>
 *		motors_pwm_L_pin			:	PD3												<br>
 *
 * Macros for 3 Line Sensors:															<br>
 *		left_center_wl_ddr_reg		:	DDRB											<br>
 *		left_center_wl_port_reg		:	PORTB											<br>
 *		left_center_wl_pin_reg		:	PINB											<br>
 *		right_wl_ddr_reg			:	DDRC											<br>
 *		right_wl_port_reg			:	PORTC											<br>
 *		right_wl_pin_reg			:	PINC											<br>
 *		left_wl_sensor_pin			:	PB3												<br>
 *		center_wl_sensor_pin		:	PB4												<br>
 *		right_wl_sensor_pin			:	PC0												<br>
 *
 * Macros for Timer / Counter 0 and 2 registers:										<br>
 *		OCR0B_reg					:	OCR0B											<br>
 *		TCCR0A_reg					:	TCCR0A											<br>
 *		TCCR0B_reg					:	TCCR0B											<br>
 *		OCR2B_reg					:	OCR2B											<br>
 *		TCCR2A_reg					:	TCCR2A											<br>
 *		TCCR2B_reg					:	TCCR2B											<br>
 *		COMB1_bit					:	COM2B1											<br>
 *		COMB0_bit					:	COM2B0											<br>
 *		WGM2_bit					:	WGM22											<br>
 *		WGM1_bit					:	WGM21											<br>
 *		WGM0_bit					:	WGM20											<br>
 *		CS2_bit						:	CS22											<br>
 *		CS1_bit						:	CS21											<br>
 *		CS0_bit						:	CS20											<br>
 */

//---------------------------------- HEADER FILES --------------------------------------------------
#include "week4_simulation.h"					// Header file that contains macro definitions essential for ATmega328P
#include <util/delay.h>							// Standard AVR Delay Library
#include <stdbool.h>


//---------------------------------- GLOBAL VARIABLES --------------------------------------------------

unsigned char left_sensor   = 0;				///< Left line sensor pin value
unsigned char center_sensor = 0;				///< Center line sensor pin value
unsigned char right_sensor	= 0;				///< Right line sensor pin value

bool left_status   = false;						///< False (F) if Left sensor is on white surface, True (T) if on black line
bool center_status = false;						///< False (F) if Center sensor is on white surface, True (T) if on black line
bool right_status  = false;						///< False (F) if Right sensor is on white surface, True (T) if on black line

  

//---------------------------------- FUNCTION DEFINITIONS --------------------------------------------------

/**
 * @brief      Function to configure pins of 3 line sensors
 */
void line_sensors_pin_config(void)
{
	// Make **ONLY** three white line sensor pins as input and activate internal pull-up resistor
	
	left_center_wl_ddr_reg &= ~((1<< left_wl_sensor_pin)|(1<<center_wl_sensor_pin)) ;
	left_center_wl_port_reg |= ((1<< left_wl_sensor_pin)|(1<<center_wl_sensor_pin));
	
	right_wl_ddr_reg &= ~(1 << right_wl_sensor_pin);
	right_wl_port_reg |= (1 << right_wl_sensor_pin);
}

/**
 * @brief      Function to configure direction pins of motor
 */
void motors_pin_config(void)
{
	// Make **ONLY** Direction pins of motors as output and initially set them to LOW to stop motors
	
	motors_dir_ddr_reg |= ((1<<motors_LB_pin)|(1<<motors_LF_pin)|(1<<motors_RB_pin)|(1<<motors_RF_pin));		// motor pins as output
	motors_dir_port_reg &= ~((1<<motors_LB_pin)|(1<<motors_LF_pin)|(1<<motors_RB_pin)|(1<<motors_RF_pin));		// stop motors initially
}

/**
 * @brief      Function to configure left and right channel pins of motor
 */
void pwm_pin_config(void)
{
	// Make **ONLY** PWM or Enable pins of motors as output and initially set them to HIGH to enable motors
	
	motors_pwm_ddr_reg |= ((1<<motors_pwm_L_pin)|(1<<motors_pwm_R_pin));	// left and right channel pin as output
	motors_pwm_port_reg |= ((1<<motors_pwm_L_pin)|(1<<motors_pwm_R_pin));	// enable left and right channel
}

/**
 * @brief      Function to make robot move forward.
 */
void motors_move_forward(void)
{
	motors_dir_port_reg &= ~((1<<motors_LF_pin)|(1<<motors_LB_pin)|(1<<motors_RF_pin)|(1<<motors_RB_pin)) ;	// Make LF, LB, RF, RB LOW
	motors_dir_port_reg |= ((1<<motors_LF_pin)|(1<<motors_RF_pin)) ;	// Make LF and RF HIGH
}

/**
 * @brief      Function to make robot move backward.
 */
void motors_move_backward(void)
{
	motors_dir_port_reg  &= ~((1<<motors_LF_pin)|(1<<motors_LB_pin)|(1<<motors_RF_pin)|(1<<motors_RB_pin));	// Make LF, LB, RF, RB LOW
	motors_dir_port_reg |= ((1<<motors_LB_pin)|(1<<motors_RB_pin)) ;	// Make LB and RB HIGH
}
/**
 * @brief      Function to make Turtle rotate left.
 */
void left (void) //Left wheel backward, Right wheel forward
{
  	motors_dir_port_reg &=  ~( (1 << motors_RB_pin) | (1 << motors_LF_pin) );	// Make LF and RB LOW
	motors_dir_port_reg |= (1 << motors_RF_pin) | (1 << motors_LB_pin) ;		// Make LB and RF HIGH
}

/**
 * @brief      Function to make Turtle rotate right.
 */
void right (void) //Left wheel forward, Right wheel backward
{
  	motors_dir_port_reg &=  ~( (1 << motors_LB_pin) | (1 << motors_RF_pin) );	// Make LB and RF LOW
	motors_dir_port_reg |= (1 << motors_LF_pin) | (1 << motors_RB_pin) ;		// Make LF and RB HIGH
}

/**
 * @brief      Function to make Turtle rotate soft left.
 */
void soft_left (void) //Left wheel stationary, Right wheel forward
{
	motors_dir_port_reg &=  ~( (1 << motors_LB_pin) | (1 << motors_RF_pin) | (1 << motors_LF_pin));	// Make LF, LB and RF LOW
	motors_dir_port_reg |= (1 << motors_RF_pin) ;	// Make RF HIGH
}

/**
 * @brief      Function to make Turtle rotate soft right.
 */
void soft_right (void) //Left wheel forward, Right wheel is stationary
{
 	motors_dir_port_reg &=  ~( (1 << motors_LB_pin) | (1 << motors_RF_pin) | (1 << motors_RB_pin));	// Make LB, RF and RB LOW
	motors_dir_port_reg |= (1 << motors_LF_pin) ;	// Make LF HIGH
}

/**
 * @brief      Function to make Turtle rotate backward left.
 */
void soft_left_2 (void) //Left wheel backward, right wheel stationary
{
 	motors_dir_port_reg &=  ~( (1 << motors_LF_pin) | (1 << motors_RF_pin) | (1 << motors_RB_pin));	// Make LF, RF and RB LOW
	motors_dir_port_reg |= (1 << motors_LB_pin) ;	// Make LB HIGH
}

/**
 * @brief      Function to make Turtle rotate backward right.
 */
void soft_right_2 (void) //Left wheel stationary, Right wheel backward
{
	motors_dir_port_reg &=  ~( (1 << motors_LF_pin) | (1 << motors_RF_pin) | (1 << motors_LB_pin));	// Make LF, RF and LB LOW
	motors_dir_port_reg |= (1 << motors_RB_pin) ;	// Make RB HIGH
}

/**
 * @brief      Function to make Turtle stop.
 */
void stop (void)
{
  	motors_dir_port_reg &=  ~( (1 << motors_LF_pin) | (1 << motors_RF_pin) | (1 << motors_LB_pin) | (1 << motors_RB_pin));	// Make LF, RF, LB and RB LOW
}

/**
 * @brief      Function to initialize Timer 0 and 2 in 8-bit Fast PWM mode for speed control of motors.
 */
void timer_pwm_init(void)
{
	// Make values in both Output Compare Registers as 0 
	OCR0B_reg = 0x00;
	OCR2B_reg = 0x00;
	
	// Configure Compare Output Mode bits to select Clear on Compare setting in TCCRnA register
	
	// For Timer 0
	TCCR0A_reg = (TCCR0A_reg  | (1<<COMB1_bit)) & ~((1<<COMB0_bit)) ;
	
	// For Timer 2
	TCCR2A_reg = (TCCR2A_reg  | (1<<COMB1_bit)) & ~((1<<COMB0_bit));
	
	// Configure Waveform Generation Mode bits for 8-bit Fast PWM in TCCRnA and TCCRnB register
	
	// For Timer 0
	TCCR0A_reg = (TCCR0A_reg | ((1<<WGM0_bit)| (1<<WGM1_bit)));
	TCCR0B_reg = (TCCR0B_reg  & ~(1<<WGM2_bit));
	// For Timer 2
	TCCR2A_reg = (TCCR2A_reg | ((1<<WGM0_bit)| (1<<WGM1_bit)));
	TCCR2B_reg = (TCCR2B_reg  & ~(1<<WGM2_bit));
	
	// Configure Clock Select bits to choose prescalar division factor of 64
	
	// For Timer 0
	TCCR0B_reg = (TCCR0B_reg| ((1<<CS0_bit)|(1<<CS1_bit))) & ~(1<<CS2_bit);
	
	// For Timer 2
	TCCR2B_reg = (TCCR2B_reg| (1<<CS2_bit)) & ~((1<<CS0_bit)|(1<<CS1_bit));
}

/**
 * @brief      Function to control the speed of both the motors of robot.
 *
 * @param[in]  left_motor_pwm   Left motor speed 0 to 255
 * @param[in]  right_motor_pwm  Right motor speed 0 to 255
 */
void set_duty_cycle(unsigned char left_motor_pwm, unsigned char right_motor_pwm)
{
	OCR2B_reg = left_motor_pwm;
	OCR0B_reg = right_motor_pwm;
}

/**
 * @brief      Function to make update left_status, center_status and right_status variables by reading the 3 line sensors.
 */
void read_line_sensor(void)
{
	// Update the left_sensor, center_sensor and right_sensor variables
	// by reading the corresponding sensor pin from PIN register
	left_sensor   = (left_center_wl_pin_reg & (1<<left_wl_sensor_pin)) == (1<<left_wl_sensor_pin) ? 1:0;
	center_sensor = (left_center_wl_pin_reg & (1<<center_wl_sensor_pin))== (1<<center_wl_sensor_pin) ? 1:0;
	right_sensor  = (right_wl_pin_reg	   & (1<<right_wl_sensor_pin)) == (1<<right_wl_sensor_pin) ? 1:0;
	
	// Update the boolean type left_status, center_status and right_status variables based on
	// the data of left_sensor, center_sensor and right_sensor variables to either true (T) or false (F)
	// true (T) = if the sensor is on black line
	// false (F) = if the sensor is on white surface
	left_status   = left_sensor==1 ? true :false ;
	center_status = center_sensor==1 ? true :false;
	right_status  = right_sensor==1 ? true :false;
}
/*void read_line_sensor_B_W_B (void)			//Sensor update for traversal on White line on Black Background
{											// Same as above but Exact opposite condition
	// Update the left_sensor, center_sensor and right_sensor variables
	// by reading the corresponding sensor pin from PIN register
	left_sensor   = (left_center_wl_pin_reg & (1<<left_wl_sensor_pin)) == (1<<left_wl_sensor_pin) ? 1:0;
	center_sensor = (left_center_wl_pin_reg & (1<<center_wl_sensor_pin))== (1<<center_wl_sensor_pin) ? 1:0;
	right_sensor  = (right_wl_pin_reg	   & (1<<right_wl_sensor_pin)) == (1<<right_wl_sensor_pin) ? 1:0;
	
	// Update the boolean type left_status, center_status and right_status variables based on
	// the data of left_sensor, center_sensor and right_sensor variables to either true (T) or false (F)
	// true (T) = if the sensor is on white line
	// false (F) = if the sensor is on black surface
	left_status   = left_sensor==0 ? true :false ;
	center_status = center_sensor==0 ? true :false;		//sensor gives high on black surface,
	right_status  = right_sensor==0 ? true :false;		//So if high give false
}*/
/**
 * @brief      Function to execute the logic for path planning and line following making the robot traverse on a black line on white background

/*void reach_to_goal(void)
{
		    while(1){
			     motors_move_forward();
			     read_line_sensor();
			     if(!left_status && center_status && !right_status)		//0,1,0
			     {
				     motors_move_forward();
				     set_duty_cycle(200,200);
				     _delay_ms(100);
				     
			     }
			     if(left_status && !center_status && !right_status)		//1,0,0
			     {
				     soft_left();
				     set_duty_cycle(0,200);
				     _delay_ms(50);
				     
			     }
			     if(left_status && center_status && !right_status)		//1,1,0
			     {
				     soft_left();
				     set_duty_cycle(0,200);
				     _delay_ms(50);
				     
			     }
			     if(!left_status && !center_status && right_status)		//0,0,1
			     {
				     soft_right();
				     set_duty_cycle(200,0);
				     _delay_ms(50);
				     
			     }
			     
			     if(!left_status && center_status && right_status)		//0,1,1
			     {
				     soft_right();
				     set_duty_cycle(200,0);
				     _delay_ms(50);
				     
			     }
			     if (!left_status && !center_status && !right_status)	//0,0,0
			     {
				     motors_move_backward();
				     set_duty_cycle(100,100);
				     _delay_ms(5);
				     //stop();
				     
			     }
				if(left_status && center_status && right_status)		//1,1,1
				{
				    stop();
				}
		}
}*/
 
 
 
void B_W_B (void)	//Code for traversal on White line on Black Background
{
	  while(1){
		  motors_move_forward();
		  read_line_sensor();
		  if(left_status && !center_status && right_status)		//0,1,0
		  {
			  motors_move_forward();
			  set_duty_cycle(200,200);
			  _delay_ms(100);
			  
		  }
		  if(!left_status && center_status && right_status)		//1,0,0
		  {
			  soft_left();
			  set_duty_cycle(0,200);
			  _delay_ms(50);
			  
		  }
		  if(!left_status && !center_status && right_status)		//1,1,0
		  {
			  soft_left();
			  set_duty_cycle(0,200);
			  _delay_ms(50);
			  
		  }
		  if(left_status && center_status && !right_status)		//0,0,1
		  {
			  soft_right();
			  set_duty_cycle(200,0);
			  _delay_ms(50);
			  
		  }
		  
		  if(left_status && !center_status && !right_status)		//0,1,1
		  {
			-  soft_right();
			  set_duty_cycle(200,0);
			  _delay_ms(50);
			  
		  }
		  if (left_status && center_status && right_status)		//0,0,0
		  {
			  motors_move_backward();
			  set_duty_cycle(100,100);
			  _delay_ms(5);
			  //stop();
			  
		  }
		  if(!left_status && !center_status && !right_status)		//1,1,1
		  {
			  stop();
		  }
	  }
}

//---------------------------------- MAIN ----------------------------------------------------------------
/**
 * @brief      Main function
 *
 * @details    First initializes 3 line sensors, motors and timers for 8-bit Fast PWM mode	  
 *
 * @return     0
 */
int main(void)
{
	line_sensors_pin_config();			// Initialize 3 line sensor pins
	motors_pin_config();				// Initialize direction pins of motors
	pwm_pin_config();				// Initialize left and right channel pins of motors
	timer_pwm_init();				// Initialize Timer 0 and 2 for PWM
	
	 
	 B_W_B();					//follow white line
	
	//reach_to_goal();				//  follow black line
	
	
    //while (1);
}
//---------------------------------- END ------------------------------------------------------------------
