/* Copyright © 2015 Bart Massey */
/* "Lizard Noise" differential synthesizer
 * C.f. http://github.com/BartMassey/diffsynth */
/* [This program is licensed under the "MIT License"]
   Please see the file COPYING in the source
   distribution of this software for license terms. */

#define LIZARD_RING_SIZE 32

typedef int8_t sample_t;

typedef struct ring {
    sample_t ring_vs[LIZARD_RING_SIZE];
    uint8_t ring_nvs;
    uint8_t ring_ptr;
} ring_t;

extern sample_t lizard_synth(ring_t *ring);
extern void lizard_synth_init_ring(ring_t *ring);
