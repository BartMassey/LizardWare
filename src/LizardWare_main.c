
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB1_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
// $[Generated Includes]
// [Generated Includes]$
SI_SBIT(LED0, SFR_P1, 2);
SI_SBIT(LED1, SFR_P1, 3);
SI_SBIT(SPEAKER0, SFR_P0, 2);
SI_SBIT(SPEAKER1, SFR_P0, 3);

SI_SBIT(TC0, SFR_P1, 0);
SI_SBIT(TC1, SFR_P1, 1);
#define TOUCH_PERIOD 0x1fff

#define LED_PERIOD 0x7fff
#define SPEAKER_PERIOD 0x1f
#define SPEAKER_ENABLE_PERIOD 0x1fff
#define SPEAKER_ON_TIME 800


//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main (void)
{
	uint32_t spincounter = 0;

	// Call hardware initialization routine
	enter_DefaultMode_from_RESET();

	while (1) {
		uint32_t speaker_enable;
        // $[Generated Run-time code]
        // [Generated Run-time code]$
		uint32_t touch_cycle = spincounter & TOUCH_PERIOD;
    	if (touch_cycle == 0) {
    		TC0 = 0;
    		TC1 = 0;

    	} else if (touch_cycle == (TOUCH_PERIOD >> 1)) {
    		TC0 = 1;
    		TC1 = 1;
    		if(TC0){
    			LED0 = 1;
  //  			LED1 = 0;
    		} else {
    			LED0 = 0;
//        		LED1 = 1;
    		}
    		if(TC1){
 //   			LED0 = 1;
    			LED1 = 1;
    		} else {
//    			LED0 = 0;
    			LED1 = 0;
    		}
    	}
//	    spincounter = spincounter & LED_PERIOD;
//        if (spincounter == 0) {
//		    LED0 = 0;
//		    LED1 = 1;
//        } else if(spincounter == (LED_PERIOD >> 1)) {
//    	    LED0 = 1;
//    	    LED1 = 0;
//        }
       speaker_enable = (spincounter & SPEAKER_ENABLE_PERIOD) < SPEAKER_ON_TIME;
        if (speaker_enable) {
            uint32_t cycle = spincounter & SPEAKER_PERIOD;
        	if (cycle == 0) {
        		SPEAKER0 = 0;
       		SPEAKER1 = 1;
        	} else if (cycle == (SPEAKER_PERIOD >> 1)) {
        		SPEAKER0 = 1;
        		SPEAKER1 = 0;
        	}
        } else {
        	SPEAKER0 = 0;
        	SPEAKER0 = 0;
        }
    	spincounter++;
	}
}
