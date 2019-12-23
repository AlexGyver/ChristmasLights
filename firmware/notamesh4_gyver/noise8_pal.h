#ifndef NOISE8_PAL_H
#define NOISE8_PAL_H

/* This is adapted from a routine created by Mark Kriegsman */

/*  Usage - noise8();

*/

uint16_t dist = 12345;         // A random number for our noise generator.
uint8_t scale = 30;          // Wouldn't recommend changing this on the fly, or the animation will be really blocky.

void noise8_pal() {

#if MAX_LEDS < 255
  uint8_t i;
#else
  uint16_t i;
#endif
  if (KolLed >= 10) {
    for ( i = 0; i < KolLed; i++) {                                     // Just ONE loop to fill up the LED array as all of the pixels change.
      uint8_t index = inoise8(i * scale, dist + i * scale) % 255;            // Get a value from the noise function. I'm using both x and y axis.
      leds[i] = ColorFromPalette(gCurrentPalette, index, 255, currentBlending);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
    }
    dist += beatsin8(10, 1, 4) * thisdir;                                            // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.
  }                                                                                  // In some sketches, I've used millis() instead of an incremented counter. Works a treat.
} // noise8_pal()

#endif
