#ifndef ONE_SIN_PAL_H
#define ONE_SIN_PAL_H


/* There's lots of values to play with here, as well as selecting your own palettes

*/


/*
   Usage - one_sin_pal();

   allfreq - What is the frequency
   bgbri - The background brightness
   bgclr - The background colour
   startindex  - What foreground colour are we starting with?
   thisbright - How bright is it?
   thiscutoff - If the brightness is lower than this, then brightness=0
   thisinc - incrementer to change the starting colour after each pass
   thisindex - rotating colours down the strip counter
   thisphase - the counter used in conjunction with the frequency to move down the strip
   thisrot - How quickly to rotate those colours down the strip
   thisspeed  - How fast does it whip down the strand
   thisdir - Direction.
*/


void one_sin_pal() {

  startindex += thisinc;
  thisindex = startindex;
  thisphase += thisdir;                                                                       // You can change direction and speed individually.

#if MAX_LEDS < 255
  uint8_t k;
#else
  uint16_t k;
#endif
  if (KolLed >= 10) {
    for (k = 0; k < KolLed; k++) {                                                         // For each of the LED's in the strand, set a brightness based on a wave as follows:
      int thisbright = qsubd(cubicwave8((k * allfreq) + thisphase), thiscutoff);                // qsub sets a minimum value called thiscutoff. If < thiscutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
      leds[k] = CHSV(bgclr, 255, bgbri);                                                        // First set a background colour, but fully saturated.
      leds[k] += ColorFromPalette(gCurrentPalette, thisindex + k * thisinc, thisbright, currentBlending);
      thisindex += thisrot;
    }
  }
} // one_sin()


#endif
