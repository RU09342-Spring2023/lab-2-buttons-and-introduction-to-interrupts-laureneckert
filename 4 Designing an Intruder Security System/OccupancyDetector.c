/*
 * OccupancyDetector.c
 *
 *  Created on: Jan 30, 2023
 *      Author: russty
 *      Lauren Eckert
 */



#define ARMED_STATE 0
#define WARNING_STATE 1
#define ALERT_STATE 2

int main(void){
// Initialization

    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    // Setting Directions of Pins
    P1DIR |= BIT0;              // Configure P1.0 to an Output - green LED
    P6DIR |= BIT6;              // Configure P6.6 to an Output - red LED
    P2DIR &= ~BIT3;             // Configure P2.3 to an Input  - button 1 (temp sensor)
    P4DIR &= ~BIT1;             // Configure P4.1 to an Input - button 2 (reset)

    // Configuring Pullup Resistors per MSP430FR2355 Family User Guide
    /*
     *   PXDIR | PXREN | PXOUT | I/O Configuration
     *     0       0       X     Input
     *     0       1       0     Input with Pull Down Resistor
     *     0       1       1     Input With Pull Up Resistor
     *     1       X       X     Output
     */

     P2REN |= BIT3;               // Enable Resistor on P2.3
     P2OUT |= BIT3;               // Configure Resistor on P2.3 to be Pullup

     P4REN |= BIT1;               // Enable Resistor on P4.1
     P4OUT |= BIT1;               // Configure Resistor on P4.1 to be Pullup

//green + red LED
     // Configure GPIO
     P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
     P1DIR |= BIT0;                          // Set P1.0 to output direction

     P6OUT &= ~BIT6;                         //same thing as above but with the other LED (green)
     P6DIR |= BIT6;

//timer

//button 2.3 (temp sensor)
     P2IES &= ~BIT3;                         // P2.3 Low --> High edge //sensor says there is a person
     P2IE |= BIT3;                           // P2.3 interrupt enabled

                                             //need interrupt for high to low edge //sensor says person left

//button 4.1 (reset)
     P4IES &= ~BIT1;                         // P4.1 Low --> High edge //reset button is pressed
     P4IE |= BIT1;                           // P4.1 interrupt enabled



}

char state = ARMED_STATE; //initialize to armed

while(1)
{
  switch (state) {
    case ARMED_STATE:
    {
      //red LED off

      // blink green LED every 3 seconds

      //if the sensor returns a 1, indicating person is in the room, move into the WARNING_STATE
      // state = WARNING_STATE


    }
    case WARNING_STATE:
    {
      //green LED off

      //red LED blinks every 1 sec, 500 ms on then 500 ms off

      //start timer at 0

      //if timer reaches 10 seconds AND sensor is still 1, move to ALERT_STATE

    }
    case ALERT_STATE:
    {
        //red LED on

        //if button pressed, move to ARMED_STATE
    }
  }
}



