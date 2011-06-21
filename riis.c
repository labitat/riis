#include <util/delay.h>

#include <arduino/pins.h>
#include <arduino/timer0.h>
#include <arduino/timer1.h>
#include <arduino/timer2.h>

#define LOW 32
#define HIGH 128

static uint8_t fib[] = { 0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233 };

#define FIB_MAX (sizeof(fib))

int __attribute__((noreturn))
main()
{
	uint8_t pin5  = 0;
	uint8_t pin6  = 1;
	uint8_t pin9  = 2;
	uint8_t pin10 = 3;
	uint8_t pin11 = 4;
	uint8_t pin3  = 5;

	pinA0_mode_input();
	pinA1_mode_input();
	pinA2_mode_input();
	pinA3_mode_input();
	pinA4_mode_input();
	pinA5_mode_input();

	pin2_mode_output();
	pin13_mode_output();

	pin3_mode_output();

	/* set up timer0 */
	timer0_mode_fastpwm();
	timer0_compare_a_set(0);
	timer0_compare_b_set(0);
	timer0_clock_d256();
	pin5_mode_output();
	pin6_mode_output();
	timer0_pin5_clear();
	timer0_pin6_clear();

	/* set up timer1 */
	timer1_mode_fastpwm_8bit();
	timer1_compare_a_set(0);
	timer1_compare_b_set(0);
	timer1_clock_d256();
	pin9_mode_output();
	pin10_mode_output();
	timer1_pin9_clear();
	timer1_pin10_clear();

	/* set up timer2 */
	timer2_mode_fastpwm();
	timer2_compare_a_set(0);
	timer2_compare_b_set(0);
	timer2_clock_d256();
	pin11_mode_output();
	pin3_mode_output();
	timer2_pin11_clear();
	timer2_pin3_clear();


	while (1) {
		while (pinA0_is_high() ||
		       pinA1_is_high() ||
		       pinA2_is_high() ||
		       pinA3_is_high() ||
		       pinA4_is_high() ||
		       pinA5_is_high());

		pin9++;
		if (pin9 >= FIB_MAX) {
			pin9 = 0;

			pin10++;
			if (pin10 >= FIB_MAX) {
				pin10 = 0;

				pin11++;
				if (pin11 >= FIB_MAX)
					pin11 = 0;
			}
		}

		pin5++;
		if (pin5 >= FIB_MAX)
			pin5 = 0;

		pin6++;
		if (pin6 >= FIB_MAX)
			pin6 = 0;

		pin3++;
		if (pin3 >= FIB_MAX)
			pin3 = 0;

		timer0_compare_a_set(fib[pin5]);
		timer0_compare_b_set(fib[pin6]);
		timer1_compare_a_set(fib[pin9]);
		timer1_compare_b_set(fib[pin10]);
		timer2_compare_a_set(fib[pin11]);
		timer2_compare_b_set(fib[pin3]);


		pin2_toggle();
		pin13_toggle();

		_delay_ms(200);
	}
}
