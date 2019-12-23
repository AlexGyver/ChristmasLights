#ifndef CANDLES_H
#define CANDLES_H

void candles() {
  if (KolLed >= 10) {

#if MAX_LEDS < 255
    uint8_t x;
#else
    uint16_t x;
#endif

    for (x = 0; x < KolLed; x++)
    {
#if CANDLE_40 == 1
      //Вариант  efimova1969
      uint8_t flicker = random8(1, 80);
      leds[x] = CRGB(255 - flicker * 2, 150 - flicker, flicker / 2);
#else
      uint8_t flicker = random8(1, 15);
      leds[x] = CRGB(255 - flicker * 2, 63 - flicker, flicker / 2);
#endif
    }
  }
} // candles()

#endif
