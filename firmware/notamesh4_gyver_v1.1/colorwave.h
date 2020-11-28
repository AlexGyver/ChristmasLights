#ifndef COLORWAVE_H
#define COLORWAVE_H

// ColorWavesWithPalettes
// Animated shifting color waves, with several cross-fading color palettes.
// by Mark Kriegsman, August 2015
//
// Color palettes courtesy of cpt-city and its contributors:
//   http://soliton.vm.bytemark.co.uk/pub/cpt-city/
//
// Color palettes converted for FastLED using "PaletteKnife" v1:
//   http://fastled.io/tools/paletteknife/
//


// This function draws color waves with an ever-changing,
// widely-varying set of parameters, using a color palette.


void colorwaves()
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
#if MAX_LEDS < 255
  uint8_t i;
#else
  uint16_t i;
#endif

  if (KolLed >= 10) {
    uint8_t brightdepth = beatsin88( 341, 96, 224);
    uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
    uint8_t msmultiplier = beatsin88(147, 23, 60);

    uint16_t hue16 = sHue16;//gHue * 256;
    uint16_t hueinc16 = beatsin88(113, 300, 1500);

    uint16_t ms = millis();
    uint16_t deltams = ms - sLastMillis ;
    sLastMillis  = ms;
    sPseudotime += deltams * msmultiplier;
    sHue16 += deltams * beatsin88( 400, 5, 9);
    uint16_t brightnesstheta16 = sPseudotime;

    for ( i = 0 ; i < KolLed; i++) {
      hue16 += hueinc16;
      uint8_t hue8 = hue16 / 256;
      uint16_t h16_128 = hue16 >> 7;
      if ( h16_128 & 0x100) {
        hue8 = 255 - (h16_128 >> 1);
      } else {
        hue8 = h16_128 >> 1;
      }

      brightnesstheta16  += brightnessthetainc16;
      uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

      uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
      uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
      bri8 += (255 - brightdepth);

      uint8_t index = hue8;
      //index = triwave8( index);
      index = scale8( index, 240);

      CRGB newcolor = ColorFromPalette(gCurrentPalette, index, bri8);
      if ( thisdir == 1)        //направление
        nblend( leds[(KolLed - 1) - i], newcolor, 128);
      else
        nblend( leds[i], newcolor, 128);

    }
  }

}

#endif
