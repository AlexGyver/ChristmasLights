
//----------------- IR Receiver and Button Command Processing ---------------------------------------------
#if ( IR_ON == 1 || KEY_ON == 1 || USE_BTN == 1)

void SetMode (uint8_t Mode)
{ demorun = 0;
#if CHANGE_ON == 1
  newMode = Mode;
  StepMode = 1;
#if CHANGE_SPARK == 4
  rand_spark = random8(3) + 1;
#endif
#else
  ledMode = Mode;
  meshwait();
  strobe_mode(Mode, 1);                                // Does NOT reset to 0.
#endif
#if CANDLE_KOL >0
  PolCandle = random8(CANDLE_KOL);
#endif
}

void getirl() {                                                   // This is the IR function that gets the value and selects/performs command.

  if (Protocol) {

#if LOG_ON == 1
    Serial.print(F("Command: 0x")); Serial.println(Command, HEX);
#endif

    switch (Command) {

#if IR_Key_Brightness_plus
      case IR_Key_Brightness_plus :   //////////////////////////////////////////////////////////////////////////  Увеличить максимальную яркость
        max_bright = min(max_bright * 2, 255);
        LEDS.setBrightness(max_bright);
#if LOG_ON == 1
        Serial.print(F("Brightness+ ")); Serial.println(max_bright);
#endif
        break;
#endif

#if IR_Key_Brightness_minus
      case IR_Key_Brightness_minus :    /////////////////////////////////////////////////////////////////////////  Уменьшить максимальную яркость
        max_bright = max(max_bright / 2, 1);
        LEDS.setBrightness(max_bright);
#if LOG_ON == 1
        Serial.print(F("Brightness- ")); Serial.println(max_bright);
#endif
        break;
#endif

#if IR_Key_Reset
      case IR_Key_Reset :              ///////////////////////////////////////////////////////////////////////////  Сброс всех настроек
        ledMode = 0; strobe_mode(ledMode, 1); FastLED.show(); bootme();
#if LOG_ON == 1
        Serial.println(F("Reset"));
#endif
        break;
#endif

#if IR_Key_Demo
      case IR_Key_Demo :            /////////////////////////////////////////////////////////////////////////////  Включит демо режим (перебор)
        demorun = 1; meshwait();
#if LOG_ON == 1
        Serial.println(F("Demo On"));
#endif
        break;
#endif

#if IR_Key_Demo_Random
      case IR_Key_Demo_Random :     /////////////////////////////////////////////////////////////////////////////  Включит демо режим (Случайно)
        demorun = 2; meshwait();
#if LOG_ON == 1
        Serial.println(F("Demo Random On"));
#endif
        break;
#endif

#if IR_Key_Demo_MyMode
      case IR_Key_Demo_MyMode :         /////////////////////////////////////////////////////////////////////////////  Включит демо режим из выбранных режимов (перебор)
        demorun = 3; meshwait();
#if LOG_ON == 1
        Serial.println(F("Demo On"));
#endif
        break;
#endif

#if IR_Key_Demo_MyMode_Random
      case IR_Key_Demo_MyMode_Random :     /////////////////////////////////////////////////////////////////////////////  Включит демо режим из выбранных режимов (Случайно)
        demorun = 4; meshwait();
#if LOG_ON == 1
        Serial.println(F("Demo Random On"));
#endif
        break;
#endif

#if IR_Key_Length_Garland_plus
      case IR_Key_Length_Garland_plus : ///////////////////////////////////////////////////////////////////////////  Увеличить количество светодиодов в гирлянде
        demorun = 0; ledMode = 200;
        if (NUM_LEDS < (MAX_LEDS - 1)) NUM_LEDS++;                        //Новое значение
#if IR_ON == 1
#if MAX_LEDS < 255
        EEPROM.write(STRANDLEN, NUM_LEDS);                              //Сохранить в память
#else
        EEPROM.write(STRANDLEN,   (uint16_t)(NUM_LEDS) & 0x00ff);       //Сохранить в память
        EEPROM.write(STRANDLEN + 1, (uint16_t)(NUM_LEDS) >> 8);         //Сохранить в память
#endif
#endif
#if LOG_ON == 1
        Serial.print(F("Length Garland ")); Serial.println(NUM_LEDS);
#endif
        break;
#endif

#if IR_Key_Length_Garland_minus
      case IR_Key_Length_Garland_minus : ///////////////////////////////////////////////////////////////////////////  Уменьшить количество светодиодов в гирлянде
        demorun = 0; ledMode = 200;
        if (NUM_LEDS > 0) NUM_LEDS--;                                     //Новое значение
#if IR_ON == 1
#if MAX_LEDS < 255
        EEPROM.write(STRANDLEN, NUM_LEDS);                              //Сохранить в память
#else
        EEPROM.write(STRANDLEN,   (uint16_t)(NUM_LEDS) & 0x00ff);       //Сохранить в память
        EEPROM.write(STRANDLEN + 1, (uint16_t)(NUM_LEDS) >> 8);         //Сохранить в память
#endif
#endif
#if LOG_ON == 1
        Serial.print(F("Length Garland ")); Serial.println(NUM_LEDS);
#endif
        break;
#endif

#if IR_Key_Rotate
      case IR_Key_Rotate :             ///////////////////////////////////////////////////////////////////////////  Сменить направление движения эффектов
        if (Protocol == 1) {          //отключить повтор
          thisdir = thisdir * -1;
#if LOG_ON == 1
          Serial.println(F("Rotate"));
#endif
        }
        break;
#endif

#if IR_Key_Speed_minus
      case IR_Key_Speed_minus :                ///////////////////////////////////////////////////////////////////////////  Замедлить движение
        if (thisdelay < 1000) thisdelay++;
#if LOG_ON == 1
        Serial.print(F("Speed- ")); Serial.println(thisdelay);
#endif
        break;
#endif

#if IR_Key_Speed_plus
      case IR_Key_Speed_plus :                ///////////////////////////////////////////////////////////////////////////  Ускорить движение
        if (thisdelay > 0) thisdelay--;
#if LOG_ON == 1
        Serial.print(F("Speed+ ")); Serial.println(thisdelay);
#endif
        break;
#endif

#if IR_Key_Glitter
      case IR_Key_Glitter :                ///////////////////////////////////////////////////////////////////////////  Включить/выключить сверкание
        if (Protocol == 1) {          //отключить повтор
          glitter = !glitter;
#if LOG_ON == 1
          Serial.print(F("Glitter ")); Serial.println(glitter);
#endif
        }
        break;
#endif

#if IR_Key_BackGround
      case IR_Key_BackGround :                ///////////////////////////////////////////////////////////////////////////  Включить/выключить заполнение фона
        if (Protocol == 1) {          //отключить повтор
          background = !background;
#if LOG_ON == 1
          Serial.print(F("BackGround ")); Serial.println(background);
#endif
        }
        break;
#endif

#if IR_Key_Candle
      case IR_Key_Candle :                ///////////////////////////////////////////////////////////////////////////  Включить/выключить Свечки
#if CANDLE_KOL >0
        if (Protocol == 1) {          //отключить повтор
          candle = !candle;
          PolCandle = random8(10);
#if LOG_ON == 1
          Serial.print(F("Candle ")); Serial.println(candle);
#endif
        }
#endif
        break;
#endif

#if IR_Key_Previous_mode
      case IR_Key_Previous_mode :          ///////////////////////////////////////////////////////////////////////////  Предыдущий эффект
        if (Protocol == 1) {          //отключить повтор
          if (ledMode > 0)  SetMode(ledMode - 1);
          else            SetMode(maxMode);
#if LOG_ON == 1
          Serial.println(F("Previous mode"));
#endif
        }
        break;
#endif

#if IR_Key_Next_mode
      case IR_Key_Next_mode :              ///////////////////////////////////////////////////////////////////////////  Следующий эффект
        if (Protocol == 1) {          //отключить повтор
          if (ledMode >= (maxMode))  SetMode(0);
          else                      SetMode(ledMode + 1);
#if LOG_ON == 1
          Serial.println(F("Next mode"));
#endif
        }
        break;
#endif

#if IR_Key_SetMode_X0
      case IR_Key_SetMode_X0 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта единицы кнопка 0
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode / 10) * 10;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 0 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_X1
      case IR_Key_SetMode_X1 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта единицы кнопка 1
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode / 10) * 10 + 1;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 1 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_X2
      case IR_Key_SetMode_X2 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта единицы кнопка 2
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode / 10) * 10 + 2;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 2 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_X3
      case IR_Key_SetMode_X3 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта единицы кнопка 3
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode / 10) * 10 + 3;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 3 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_X4
      case IR_Key_SetMode_X4 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта единицы кнопка 4
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode / 10) * 10 + 4;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 4 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_X5
      case IR_Key_SetMode_X5 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта единицы кнопка 5
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode / 10) * 10 + 5;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 5 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_X6
      case IR_Key_SetMode_X6 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта единицы кнопка 6
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode / 10) * 10 + 6;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 6 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_X7
      case IR_Key_SetMode_X7 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта единицы кнопка 7
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode / 10) * 10 + 7;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 7 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_X8
      case IR_Key_SetMode_X8 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта единицы кнопка 8
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode / 10) * 10 + 8;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 8 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_X9
      case IR_Key_SetMode_X9 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта единицы кнопка 9
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode / 10) * 10 + 9;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 9 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_1X
      case IR_Key_SetMode_1X :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта десядки кнопка +10
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode += 10;
          if (IR_New_Mode > maxMode) IR_New_Mode = IR_New_Mode % 10;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press +10 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_0
      case IR_Key_SetMode_0 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта сдвиг + кнопка 0
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode % 10) * 10 + 0;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 0 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_1
      case IR_Key_SetMode_1 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта сдвиг + кнопка 1
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode % 10) * 10 + 1;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 1 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_2
      case IR_Key_SetMode_2 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта сдвиг + кнопка 2
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode % 10) * 10 + 2;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 2 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_3
      case IR_Key_SetMode_3 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта сдвиг + кнопка 3
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode % 10) * 10 + 3;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 3 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_4
      case IR_Key_SetMode_4 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта сдвиг + кнопка 4
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode % 10) * 10 + 4;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 4 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_5
      case IR_Key_SetMode_5 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта сдвиг + кнопка 5
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode % 10) * 10 + 5;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 5 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_6
      case IR_Key_SetMode_6 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта сдвиг + кнопка 6
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode % 10) * 10 + 6;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 6 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_7
      case IR_Key_SetMode_7 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта сдвиг + кнопка 7
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode % 10) * 10 + 7;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 7 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_8
      case IR_Key_SetMode_8 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта сдвиг + кнопка 8
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode % 10) * 10 + 8;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 8 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_SetMode_9
      case IR_Key_SetMode_9 :                /////////////////////////////////////////////////////////////////////////// Набор номера выбор эффекта сдвиг + кнопка 9
        if (Protocol == 1) {          //отключить повтор
          IR_New_Mode = (IR_New_Mode % 10) * 10 + 9;
          IR_Time_Mode = millis();//время последнего нажатия
#if LOG_ON == 1
          Serial.print(F("Press 9 Mode: ")); Serial.println(IR_New_Mode);
#endif
        }
        break;
#endif

#if IR_Key_Mode_0
      case IR_Key_Mode_0 :                ///////////////////////////////////////////////////////////////////////////  Эффект 0
        SetMode (0);   break;
#endif

#if IR_Key_Mode_1
      case IR_Key_Mode_1 :                ///////////////////////////////////////////////////////////////////////////  Эффект 1
        SetMode (1);   break;
#endif

#if IR_Key_Mode_2
      case IR_Key_Mode_2 :                ///////////////////////////////////////////////////////////////////////////  Эффект 2
        SetMode (2);   break;
#endif

#if IR_Key_Mode_3
      case IR_Key_Mode_3 :                ///////////////////////////////////////////////////////////////////////////  Эффект 3
        SetMode (3);   break;
#endif

#if IR_Key_Mode_4
      case IR_Key_Mode_4 :                ///////////////////////////////////////////////////////////////////////////  Эффект 4
        SetMode (4);   break;
#endif

#if IR_Key_Mode_5
      case IR_Key_Mode_5 :                ///////////////////////////////////////////////////////////////////////////  Эффект 5
        SetMode (5);   break;
#endif

#if IR_Key_Mode_6
      case IR_Key_Mode_6 :                ///////////////////////////////////////////////////////////////////////////  Эффект 6
        SetMode (6);   break;
#endif

#if IR_Key_Mode_7
      case IR_Key_Mode_7 :                ///////////////////////////////////////////////////////////////////////////  Эффект 7
        SetMode (7);   break;
#endif

#if IR_Key_Mode_8
      case IR_Key_Mode_8 :                ///////////////////////////////////////////////////////////////////////////  Эффект 8
        SetMode (8);   break;
#endif

#if IR_Key_Mode_9
      case IR_Key_Mode_9 :                ///////////////////////////////////////////////////////////////////////////  Эффект 9
        SetMode (9);   break;
#endif

#if IR_Key_Mode_10
      case IR_Key_Mode_10 :                ///////////////////////////////////////////////////////////////////////////  Эффект 10
        SetMode (10);   break;
#endif

#if IR_Key_Mode_11
      case IR_Key_Mode_11 :                ///////////////////////////////////////////////////////////////////////////  Эффект 11
        SetMode (11);   break;
#endif

#if IR_Key_Mode_12
      case IR_Key_Mode_12 :                ///////////////////////////////////////////////////////////////////////////  Эффект 12
        SetMode (12);   break;
#endif

#if IR_Key_Mode_13
      case IR_Key_Mode_13 :                ///////////////////////////////////////////////////////////////////////////  Эффект 13
        SetMode (13);   break;
#endif

#if IR_Key_Mode_14
      case IR_Key_Mode_14 :                ///////////////////////////////////////////////////////////////////////////  Эффект 14
        SetMode (14);   break;
#endif

#if IR_Key_Mode_15
      case IR_Key_Mode_15 :                ///////////////////////////////////////////////////////////////////////////  Эффект 15
        SetMode (15);   break;
#endif

#if IR_Key_Mode_16
      case IR_Key_Mode_16 :                ///////////////////////////////////////////////////////////////////////////  Эффект 16
        SetMode (16);   break;
#endif

#if IR_Key_Mode_17
      case IR_Key_Mode_17 :                ///////////////////////////////////////////////////////////////////////////  Эффект 17
        SetMode (17);   break;
#endif

#if IR_Key_Mode_18
      case IR_Key_Mode_18 :                ///////////////////////////////////////////////////////////////////////////  Эффект 18
        SetMode (18);   break;
#endif

#if IR_Key_Mode_19
      case IR_Key_Mode_19 :                ///////////////////////////////////////////////////////////////////////////  Эффект 19
        SetMode (19);   break;
#endif

#if IR_Key_Mode_20
      case IR_Key_Mode_20 :                ///////////////////////////////////////////////////////////////////////////  Эффект 20
        SetMode (20);   break;
#endif

#if IR_Key_Mode_21
      case IR_Key_Mode_21 :                ///////////////////////////////////////////////////////////////////////////  Эффект 21
        SetMode (21);   break;
#endif

#if IR_Key_Mode_22
      case IR_Key_Mode_22 :                ///////////////////////////////////////////////////////////////////////////  Эффект 22
        SetMode (22);   break;
#endif

#if IR_Key_Mode_23
      case IR_Key_Mode_23 :                ///////////////////////////////////////////////////////////////////////////  Эффект 23
        SetMode (23);   break;
#endif

#if IR_Key_Mode_24
      case IR_Key_Mode_24 :                ///////////////////////////////////////////////////////////////////////////  Эффект 24
        SetMode (24);   break;
#endif

#if IR_Key_Mode_25
      case IR_Key_Mode_25 :                ///////////////////////////////////////////////////////////////////////////  Эффект 25
        SetMode (25);   break;
#endif

#if IR_Key_Mode_26
      case IR_Key_Mode_26 :                ///////////////////////////////////////////////////////////////////////////  Эффект 26
        SetMode (26);   break;
#endif

#if IR_Key_Mode_27
      case IR_Key_Mode_27 :                ///////////////////////////////////////////////////////////////////////////  Эффект 27
        SetMode (27);   break;
#endif

#if IR_Key_Mode_28
      case IR_Key_Mode_28 :                ///////////////////////////////////////////////////////////////////////////  Эффект 28
        SetMode (28);   break;
#endif

#if IR_Key_Mode_29
      case IR_Key_Mode_29 :                ///////////////////////////////////////////////////////////////////////////  Эффект 29
        SetMode (29);   break;
#endif

#if IR_Key_Mode_30
      case IR_Key_Mode_0 :                ///////////////////////////////////////////////////////////////////////////  Эффект 30
        SetMode (30);   break;
#endif

#if IR_Key_Mode_31
      case IR_Key_Mode_31 :                ///////////////////////////////////////////////////////////////////////////  Эффект 31
        SetMode (31);   break;
#endif

#if IR_Key_Mode_32
      case IR_Key_Mode_32 :                ///////////////////////////////////////////////////////////////////////////  Эффект 32
        SetMode (32);   break;
#endif

#if IR_Key_Mode_33
      case IR_Key_Mode_33 :                ///////////////////////////////////////////////////////////////////////////  Эффект 33
        SetMode (33);   break;
#endif

#if IR_Key_Mode_34
      case IR_Key_Mode_34 :                ///////////////////////////////////////////////////////////////////////////  Эффект 34
        SetMode (34);   break;
#endif

#if IR_Key_Mode_35
      case IR_Key_Mode_35 :                ///////////////////////////////////////////////////////////////////////////  Эффект 35
        SetMode (35);   break;
#endif

#if IR_Key_Mode_36
      case IR_Key_Mode_36 :                ///////////////////////////////////////////////////////////////////////////  Эффект 36
        SetMode (36);   break;
#endif

#if IR_Key_Mode_37
      case IR_Key_Mode_37 :                ///////////////////////////////////////////////////////////////////////////  Эффект 37
        SetMode (37);   break;
#endif

#if IR_Key_Mode_38
      case IR_Key_Mode_38 :                ///////////////////////////////////////////////////////////////////////////  Эффект 38
        SetMode (38);   break;
#endif

#if IR_Key_Mode_39
      case IR_Key_Mode_39 :                ///////////////////////////////////////////////////////////////////////////  Эффект 39
        SetMode (39);   break;
#endif

#if IR_Key_Mode_40
      case IR_Key_Mode_40 :                ///////////////////////////////////////////////////////////////////////////  Эффект 40
        SetMode (40);   break;
#endif

#if IR_Key_Mode_41
      case IR_Key_Mode_41 :                ///////////////////////////////////////////////////////////////////////////  Эффект 41
        SetMode (41);   break;
#endif


#if IR_Key_Save_Mode
      case IR_Key_Save_Mode :              ///////////////////////////////////////////////////////////////////////////  Сохранить эффект как запускающийся первым
        if (Protocol == 1) {          //отключить повтор
#if IR_ON == 1
          EEPROM.write(STARTMODE, ledMode);
#endif
#if LOG_ON == 1
          Serial.println(F("Save Mode"));
#endif
        }
        break;
#endif

#if IR_Key_Delay_minus
      case IR_Key_Delay_minus :            ///////////////////////////////////////////////////////////////////////////  Уменьшить задержку на 100ms
        demorun = 0; ledMode = 201;
        if (meshdelay > 0) meshdelay--;                                   //Новое значение
#if IR_ON == 1
        EEPROM.write(STRANDEL, meshdelay);
#endif
#if LOG_ON == 1
        Serial.print(F("Delay ")); Serial.print(meshdelay * 100); Serial.println(F(" ms"));
#endif
        break;
#endif

#if IR_Key_Delay_plus
      case IR_Key_Delay_plus :            ///////////////////////////////////////////////////////////////////////////  Увеличить задержку на 100ms
        demorun = 0; ledMode = 201;
        if (meshdelay < 100) meshdelay++;                                 //Новое значение
#if IR_ON == 1
        EEPROM.write(STRANDEL, meshdelay);
#endif
#if LOG_ON == 1
        Serial.print(F("Delay ")); Serial.print(meshdelay * 100); Serial.println(F(" ms"));
#endif
        break;
#endif

#if IR_Key_Palette_Stop
      case IR_Key_Palette_Stop :            ///////////////////////////////////////////////////////////////////////////  Остановить перебор Палитр
        palchg = 0;
#if LOG_ON == 1
        Serial.print(F("Palette_Stop ")); Serial.println(gCurrentPaletteNumber);
#endif
        break;
#endif

#if IR_Key_Palette_Previous
      case IR_Key_Palette_Previous :        ///////////////////////////////////////////////////////////////////////////  Установить предыдущую палитру
        if (Protocol == 1) {          //отключить повтор
          palchg = 1;
          if (gCurrentPaletteNumber > 0)  gCurrentPaletteNumber--;
          else                            gCurrentPaletteNumber = gGradientPaletteCount - 1;
          gCurrentPalette = (gGradientPalettes[gCurrentPaletteNumber]);
#if LOG_ON == 1
          Serial.print(F("Palette- ")); Serial.println(gCurrentPaletteNumber);
#endif
        }
        break;
#endif

#if IR_Key_Palette_Next
      case IR_Key_Palette_Next :            ///////////////////////////////////////////////////////////////////////////  Установить следующую палитру
        if (Protocol == 1) {          //отключить повтор
          palchg = 2;
          if (gCurrentPaletteNumber < (gGradientPaletteCount - 1))  gCurrentPaletteNumber++;
          else                                                gCurrentPaletteNumber = 0;
          gCurrentPalette = (gGradientPalettes[gCurrentPaletteNumber]);
#if LOG_ON == 1
          Serial.print(F("Palette+ ")); Serial.println(gCurrentPaletteNumber);
#endif
        }
        break;
#endif

#if IR_Key_Palette_Auto
      case IR_Key_Palette_Auto :            ///////////////////////////////////////////////////////////////////////////  Включить перебор палитр
        palchg = 3;
#if LOG_ON == 1
        Serial.println(F("Continuous palette change"));
#endif
        break;
#endif

#if IR_Key_Solid_Black
      case IR_Key_Solid_Black :            ///////////////////////////////////////////////////////////////////////////  Установить цвет Черный
        demorun = 0; ledMode = 100; palchg = 0;
        solid = CRGB::Black;
#if LOG_ON == 1
        Serial.println(F("Solid_Black"));
#endif
        break;
#endif

#if IR_Key_Solid_Red
      case IR_Key_Solid_Red :            ///////////////////////////////////////////////////////////////////////////  Установить цвет Красный
        demorun = 0; ledMode = 100; palchg = 0;
        solid = CRGB::Red;
#if LOG_ON == 1
        Serial.println(F("Solid_Red"));
#endif
        break;
#endif

#if IR_Key_Solid_Orange
      case IR_Key_Solid_Orange :            ///////////////////////////////////////////////////////////////////////////  Установить цвет Оранжевый
        demorun = 0; ledMode = 100; palchg = 0;
        solid = CRGB::Orange;
#if LOG_ON == 1
        Serial.println(F("Solid_Orange"));
#endif
        break;
#endif

#if IR_Key_Solid_Yellow
      case IR_Key_Solid_Yellow :            ///////////////////////////////////////////////////////////////////////////  Установить цвет Желтый
        demorun = 0; ledMode = 100; palchg = 0;
        solid = CRGB::Yellow;
#if LOG_ON == 1
        Serial.println(F("Solid_Yellow"));
#endif
        break;
#endif

#if IR_Key_Solid_Green
      case IR_Key_Solid_Green :            ///////////////////////////////////////////////////////////////////////////  Установить цвет Зеленый
        demorun = 0; ledMode = 100; palchg = 0;
        solid = CRGB::Green;
#if LOG_ON == 1
        Serial.println(F("Solid_Green"));
#endif
        break;
#endif

#if IR_Key_Solid_SkyBlue
      case IR_Key_Solid_SkyBlue :            ///////////////////////////////////////////////////////////////////////////  Установить цвет Голубой
        demorun = 0; ledMode = 100; palchg = 0;
        solid = CRGB::SkyBlue;
#if LOG_ON == 1
        Serial.println(F("Solid_SkyBlue"));
#endif
        break;
#endif

#if IR_Key_Solid_Blue
      case IR_Key_Solid_Blue :            ///////////////////////////////////////////////////////////////////////////  Установить цвет Синий
        demorun = 0; ledMode = 100; palchg = 0;
        solid = CRGB::Blue;
#if LOG_ON == 1
        Serial.println(F("Solid_Blue"));
#endif
        break;
#endif

#if IR_Key_Solid_Violet
      case IR_Key_Solid_Violet :            ///////////////////////////////////////////////////////////////////////////  Установить цвет Фиолетовый
        demorun = 0; ledMode = 100; palchg = 0;
        solid = CRGB::Violet;
#if LOG_ON == 1
        Serial.println(F("Solid_Violet"));
#endif
        break;
#endif

#if IR_Key_Solid_White
      case IR_Key_Solid_White :            ///////////////////////////////////////////////////////////////////////////  Установить цвет Белый
        demorun = 0; ledMode = 100; palchg = 0;
        solid = CRGB::White;
#if LOG_ON == 1
        Serial.println(F("Solid_White"));
#endif
        break;
#endif

      default:     break;                // We could do something by default

    } // switch Command

    Protocol = 0;                                             // Reset Protocol variable to not read the same value twice.

  } // if Protocol

} // getirl()

void bootme() {                                                 // This is used to reset all the Arduinos so that their millis() counters are all in sync.

  asm volatile("jmp 0");

} // bootme()



void meshwait() {                                                   // After we press a mode key, we need to wait a bit for the sequence to start.

#if LOG_ON == 1
  Serial.print(F("Mesh delay: ")); Serial.print(meshdelay * 100); Serial.println(F("ms delay."));
#endif
  FastLED.delay(meshdelay * 100);                                   // Here's our notamesh wait upon keypress. Oh god I'm so sorry there's a delay statement here. At least it's only used upon mode change keypress.

} // meshwait()


#endif
