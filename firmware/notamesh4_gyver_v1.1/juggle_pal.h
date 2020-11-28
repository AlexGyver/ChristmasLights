#ifndef JUGGLE_PAL_H
#define JUGGLE_PAL_H

/* This is adapted from a routine created by Mark Kriegsman */

/*  Usage - juggle_pal();

    thishue
    thisfade
    numdots
    thisbeat
    thisbright
    thisdiff
*/

uint8_t numdots;

void juggle_pal() {                                           // Several colored dots, weaving in and out of sync with each other
  if (KolLed >= 10) {
    thisindex = 0;                                              // Reset the hue values.
    fadeToBlackBy(leds, KolLed, thisfade);                  //Затухание к черному
    for ( uint8_t i = 0; i < numdots; i++) {
      leds[beatsin16(thisbeat + i + numdots, 0, KolLed - 1)] += ColorFromPalette(gCurrentPalette, thisindex , 255, currentBlending); // Munge the values and pick a colour from the palette
      thisindex += thisdiff;
    }
  }
} // juggle_pal()

#endif
