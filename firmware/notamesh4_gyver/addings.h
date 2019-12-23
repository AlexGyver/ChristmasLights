#ifndef ADDINGS_H
#define ADDINGS_H

#if CANDLE_KOL >0
////////////////////////////////////////////////////////////// Свечи
DEFINE_GRADIENT_PALETTE( candle_Pal ) {
  0,   255,  0,  0,   //red
  90,   255, 255, 255, //full white
  180,   255, 255,  0,  //bright yellow
  255,   255, 255, 255
}; //full white

uint8_t PolCandle = 1;  //Положение свечи

void addcandle()
{
  uint16_t poz = PolCandle;
  CRGBPalette16 myPal = candle_Pal;

  if (NUM_LEDS > 5)
  {
    uint8_t kol = NUM_LEDS / 10;   //Количество свечей

    for ( uint8_t x = 0; x < kol; x++)
    {
      leds[ poz ] = ColorFromPalette( myPal, random8(255));
      poz += CANDLE_KOL;
    }
  }
}
#endif

///////////////////////////////////////////////////////////////// Черный фон
void addbackground()
{
#if MAX_LEDS < 255
  uint8_t i;
#else
  uint16_t i;
#endif

  for (i = 0; i < NUM_LEDS ; i++ )
    if (  (leds[i].r < 5) &&
          (leds[i].g < 5) &&
          (leds[i].b < 5) )
      leds[i].b += CRGB(5, 5, 5);

}

////////////////////////////////////////////////////////////////// Блеск
void addglitter( fract8 chanceOfGlitter)
{
  if ( random8() < chanceOfGlitter) {
#if MAX_LEDS < 255
    leds[ random8(NUM_LEDS) ] += CRGB::White;
#else
    leds[ random16(NUM_LEDS) ] += CRGB::White;
#endif
  }
}

////////////////////////////////////////////////////////////////// Бенгальский огонь
void sparkler(uint8_t n)       //Бенгальский огонь
// 0 - нет эффектов
// 1 - Бенгальский огонь
// 2 - 1 яркий светодиод
// 3 - метеорит
// 4 - случайный эффект
{ uint8_t kol = 3;

  if ( KolLed < 10 ) kol = KolLed / 3;
  if (kol >= 2)
  { uint8_t nn = n;
    switch (nn) {
      case 1 :  for ( uint8_t x = 0; x < kol; x++) leds[ KolLed - random8(kol * 2) ] = CRGB::White; break;      //Бенгальский
      case 2 :  leds[KolLed - 1] = CRGB::White; break;                                                          //1 яркий
      case 3 :  leds[KolLed] = CRGB::White; leds[KolLed - 1] = CRGB::Red; leds[KolLed - 2] = CRGB::Violet; break; //Метеорит
    }
  }
}

#endif
