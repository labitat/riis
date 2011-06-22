#include <util/delay.h>

#include <arduino/pins.h>
#include <arduino/timer0.h>
#include <arduino/timer1.h>
#include <arduino/timer2.h>

#define LOW 32
#define HIGH 128

static uint8_t exp[256] = {
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   1,   1,   1,   1,   1,
	1,   1,   1,   1,   1,   1,   1,   1,
	1,   1,   1,   1,   1,   1,   1,   1,
	2,   2,   2,   2,   2,   2,   2,   2,
	2,   3,   3,   3,   3,   3,   3,   4,
	4,   4,   4,   4,   5,   5,   5,   5,
	6,   6,   6,   7,   7,   7,   8,   8,
	9,   9,  10,  10,  11,  11,  12,  13,
	13,  14,  15,  16,  17,  18,  18,  20,
	21,  22,  23,  24,  26,  27,  28,  30,
	32,  33,  35,  37,  39,  41,  44,  46,
	48,  51,  54,  57,  60,  63,  67,  71,
	74,  79,  83,  87,  92,  97, 103, 108,
	114, 121, 127, 134, 142, 149, 157, 166,
	175, 185, 195, 206, 217, 229, 242, 255,
	242, 229, 217, 206, 195, 185, 175, 166,
	157, 149, 142, 134, 127, 121, 114, 108,
	103,  97,  92,  87,  83,  79,  74,  71,
	67,  63,  60,  57,  54,  51,  48,  46,
	44,  41,  39,  37,  35,  33,  32,  30,
	28,  27,  26,  24,  23,  22,  21,  20,
	18,  18,  17,  16,  15,  14,  13,  13,
	12,  11,  11,  10,  10,   9,   9,   8,
	8,   7,   7,   7,   6,   6,   6,   5,
	5,   5,   5,   4,   4,   4,   4,   4,
	3,   3,   3,   3,   3,   3,   2,   2,
	2,   2,   2,   2,   2,   2,   2,   1,
	1,   1,   1,   1,   1,   1,   1,   1,
	1,   1,   1,   1,   1,   1,   1,   1,
	1,   1,   1,   1,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0
};

/*
 * lave:
 * 5  -> R
 * 6  -> G
 * 3  -> B
 *
 * høje:
 * 9  -> R
 * 10 -> G
 * 11 -> B
 */

int __attribute__((noreturn))
main()
{
	uint8_t pin5  = 0;
	uint8_t pin6  = 85;
	uint8_t pin3  = 171;
	uint8_t pin9  = 0;
	uint8_t pin10 = 85;
	uint8_t pin11 = 171;

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
		pin10++;
		pin11++;

		pin3++;
		pin5++;
		pin6++;

		timer0_compare_a_set(exp[pin5]);
		timer0_compare_b_set(exp[pin6]);
		timer1_compare_a_set(exp[pin9]);
		timer1_compare_b_set(exp[pin10]);
		timer2_compare_a_set(exp[pin11]);
		timer2_compare_b_set(exp[pin3]);


		pin2_toggle();
		pin13_toggle();

		_delay_ms(20);
	}
}
