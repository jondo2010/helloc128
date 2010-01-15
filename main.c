//
//	main.c
//	Blink an LED on the AT90CAN128 microcontroller to verify operation.
//
//	University of Manitoba Society of Automotive Engineers (UMSAE)
//	Formula 2010
//
//	Michael Jean <michael.jean@shaw.ca>
//

#include <avr/interrupt.h>
#include <avr/io.h>

//
//	Timer 0 interrupt service routine.
//
//	Count to one second, then toggle the LED.
//

ISR(TIMER0_COMP_vect)
{
	static uint16_t ticks = 0;

	if (++ticks > 1000)
	{
		PORTE ^= _BV (PE4);
		ticks = 0;
	}
}

//
//	Configure the GPIO ports.
//
//	Port:Pin	Direction	Function
//	========	=========	========
//	PE4			Output		LED supply pin
//

void
setup_ports (void)
{
	DDRE = _BV (PE4);
}

//
//	Configure the on-board timers.
//
//	Timer	Frequency	Function
//	=====	=========	========
//	0		1 kHz		Toggle LED after one second
//

void
setup_timers (void)
{
	TCCR0A = _BV (WGM01) | _BV (CS01) | _BV (CS00);
	TIMSK0 = _BV (OCIE0A);
	OCR0A =	 250;
}

//
//	Main entry point of the microcontroller.
//

int
main(void)
{
	setup_ports ();
	setup_timers ();

	sei ();

	for (;;)
		;

    return 0;
}
