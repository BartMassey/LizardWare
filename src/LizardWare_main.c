//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB1_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
// $[Generated Includes]
// [Generated Includes]$

#ifndef NO_LIZARD
#include <LizardWare_synth.h>
ring_t lizard_ring;
#endif

SI_SBIT(LED0, SFR_P1, 2);
SI_SBIT(LED1, SFR_P1, 3);
SI_SBIT(SPEAKER0, SFR_P0, 2);
SI_SBIT(SPEAKER1, SFR_P0, 3);
SI_SBIT(TC0, SFR_P1, 0);
SI_SBIT(TC1, SFR_P1, 1);

/* All periods must be smaller than this. */
#define SPIN_PERIOD 0xffffff

/* How long to wait for the touch timer. Read halfway through. */
#define TOUCH_PERIOD 0x1fff

/* One on-off cycle for the LED. */
#define LED_PERIOD 0x7fff

/* One on-off cycle for the speaker. */
#define SPEAKER_PERIOD 0x1fff
/* Speaker base frequency */
#define SPEAKER_FREQ 0x1f
/* The on length of the on-off cycle. */
#define SPEAKER_ON_TIME (SPEAKER_PERIOD >> 1)


//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main (void)
{
	uint32_t spincounter = 0;
	int speaking = 0;

	// Call hardware initialization routine
	enter_DefaultMode_from_RESET();

	while (1) {
		uint32_t speaker_enable;
		// $[Generated Run-time code]
		// [Generated Run-time code]$

#ifdef TOUCH_ME
		uint32_t touch_cycle = spincounter & TOUCH_PERIOD;
		if (touch_cycle == 0) {
			TC0 = 0;
			TC1 = 0;
		} else if (touch_cycle == (TOUCH_PERIOD >> 1)) {
			TC0 = 1;
			TC1 = 0;
			if(TC0){
				LED0 = 1;
			} else {
				LED0 = 0;
			}
			TC0 = 0;
			TC1 = 1;
			if(TC1){
				LED1 = 1;
			} else {
				LED1 = 0;
			}
		}
#else
		uint32_t led_timer = spincounter & LED_PERIOD;
		if (led_timer == 0) {
			LED0 = 0;
			LED1 = 1;
		} else if(led_timer == (LED_PERIOD >> 1)) {
			LED0 = 1;
			LED1 = 0;
		}
#endif

		speaker_enable =
		  (spincounter & SPEAKER_PERIOD) < SPEAKER_ON_TIME;
		if (speaker_enable) {
			int left;
#ifndef NO_LIZARD
			sample_t v;
			if (!speaking)
				lizard_synth_init_ring(&lizard_ring);
			if ((spincounter & SPEAKER_FREQ) == 0) {
				v = lizard_synth(&lizard_ring);
				left = v < 0;
			}
#else
			uint32_t cycle = spincounter & SPEAKER_FREQ;
			left = cycle < (SPEAKER_FREQ >> 1);
#endif
			if (left) {
				SPEAKER0 = 1;
				SPEAKER1 = 0;
			} else {
				SPEAKER0 = 0;
				SPEAKER1 = 1;
			}
			speaking = 1;
		} else {
			SPEAKER0 = 0;
			SPEAKER1 = 0;
			speaking = 0;
		}

		spincounter = (spincounter + 1) & SPIN_PERIOD;
	}
}
