#ifndef FIRE_H
#define FIRE_H

void fire() {                                         // The fill_rainbow call doesn't support brightness levels
  if (KolLed >= 10) {

#if MAX_LEDS < 255
    uint8_t x = KolLed / 10;                          // Координаты
    uint8_t k1 =    random8(x * 2);         //Жар
    uint8_t k2 =    random8(x * 2) + k1;    //Огонь
    uint8_t k3 = x * 3 + random8(x * 4);    //Пламя
    uint8_t k4 = KolLed - 1;                //Дым
    if ((k4 - k2) < k3) k3 = k4;
    else k3 = k3 + k2;

#else
    uint16_t x = KolLed / 10;
    uint16_t k1 =      random8(x * 2);       //Жар
    uint16_t k2 =      random8(x * 2) + k1;  //Огонь
    uint16_t k3 = x * 3 + random8(x * 4) + k2; //Пламя
    uint16_t k4 = KolLed - 1;                //Дым

#endif

    if ( thisdir == 1) {       //направление
      fill_gradient_RGB(leds, 0,  CRGB::White,  k1,       CRGB::Yellow);            //Градинет
      fill_gradient_RGB(leds, k1, CRGB::Yellow, k2,       CRGB::Red);
      fill_gradient_RGB(leds, k2, CRGB::Red, k3, CRGB::Black);
      if ( k3 < k4)
        fill_gradient_RGB(leds, k3, CRGB::Black, k4, CRGB::Black);
      for (uint8_t y = 0; y < x; y++) leds[random16(k2, KolLed - 1)] = CRGB::Red;

    }
    else
    {
      k1 = KolLed - 1 - k1;                                                       //Поворот
      k2 = KolLed - 1 - k2;
#if MAX_LEDS < 255
      if ((KolLed - 1) < k3) k3 = 0;
      else  k3 = KolLed - 1 - k3;
#else
      k3 = KolLed - 1 - k3;
#endif

      fill_gradient_RGB(leds, k1,  CRGB::White,  k4,       CRGB::Yellow);           //Градиент
      fill_gradient_RGB(leds, k2, CRGB::Yellow, k1,       CRGB::Red);
      fill_gradient_RGB(leds, k3, CRGB::Red, k2, CRGB::Black);
      if ( k3 > 0)
        fill_gradient_RGB(leds, 0, CRGB::Black, k3, CRGB::Black);
      for (uint8_t y = 0; y < x; y++) leds[random16(k2)] = CRGB::Red;

    }
  }

} // fire()

#endif
