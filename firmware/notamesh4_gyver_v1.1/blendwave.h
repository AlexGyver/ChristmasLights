#ifndef BLENDWARE_H
#define BLENDWARE_H

void blendwave() {
  CRGB clr1;
  CRGB clr2;
  uint8_t speed;
  uint8_t loc1;

  if (KolLed >= 10) {

    speed = beatsin8(6, 0, 255);

    clr1 = blend(CHSV(beatsin8(3, 0, 255), 255, 255), CHSV(beatsin8(4, 0, 255), 255, 255), speed);
    clr2 = blend(CHSV(beatsin8(4, 0, 255), 255, 255), CHSV(beatsin8(3, 0, 255), 255, 255), speed);

#if MAX_LEDS < 255
    loc1 = beatsin8(10, 0, KolLed - 1);
#else
    loc1 = beatsin16(10, 0, KolLed - 1);
#endif

    fill_gradient_RGB(leds, 0, clr2, loc1, clr1);
    fill_gradient_RGB(leds, loc1, clr2, KolLed - 1, clr1);
  }
} // blendwave()


#endif
