#ifndef _ANALOG_KEYS_H
#define _ANALOG_KEYS_H

#define _PIN_KEY  A3
#ifndef PIN_KEY
#define PIN_KEY _PIN_KEY
#endif

//Зачения смотреть в протоколе после строки Analog Key
#define KEY_0         10          // Значение соответствующее нажатой 0 кнопке
// если значение меньше KEY_DELTA, то кнопка не используется
#define KEY_1         70          // Значение соответствующее нажатой 1 кнопке
// если значение меньше KEY_DELTA, то кнопка не используется
#define KEY_2         140         // Значение соответствующее нажатой 2 кнопке
// если значение меньше KEY_DELTA, то кнопка не используется
#define KEY_3         280         // Значение соответствующее нажатой 3 кнопке
// если значение меньше KEY_DELTA, то кнопка не используется
#define KEY_4         360         // Значение соответствующее нажатой 4 кнопке
// если значение меньше KEY_DELTA, то кнопка не используется
#define KEY_5         520         // Значение соответствующее нажатой 5 кнопке
// если значение меньше KEY_DELTA, то кнопка не используется
#define KEY_6         700         // Значение соответствующее нажатой 6 кнопке
// если значение меньше KEY_DELTA, то кнопка не используется
#define KEY_7         900         // Значение соответствующее нажатой 7 кнопке
// если значение меньше KEY_DELTA, то кнопка не используется
#define KEY_DELTA     5           // погрешность значения кнопки, тоесть от -KEY_DELTA до +KEY_DELTA

typedef struct {
  int input;          // Последнее нажатие кнопки 
  int input_new;      // только что пришедшее нажатие кнопки
  bool bounce;        // для антидребезга
  uint32_t key_time;  // время последнего нажатия
} Analog_Keys_t;

void analog_keys_setup() {
  pinMode(PIN_KEY, INPUT);
}

void analog_keys_tick(Analog_Keys_t *analog_keys, uint8_t *protocol, uint32_t *command) {
  analog_keys->input_new = analogRead(PIN_KEY);                                           //прочитаем аналоговые кнопки
  if ((((analog_keys->input - KEY_DELTA) > analog_keys->input_new) ||                     //Пришло новое значение отличное от прошлого
          ((analog_keys->input + KEY_DELTA) < analog_keys->input_new)) &&
        !analog_keys->bounce) {                                                       // и еще ничего не приходило
    analog_keys->bounce = 1;                                                          //Начинаем обрабатывать
    analog_keys->key_time = millis();                                                     //Запомним время
  }
  else if (analog_keys->bounce &&                                                     //Обрабатываем нажатия
             ((millis() - analog_keys->key_time) >= 50)) {                                //Закончилось время дребезга
    analog_keys->bounce = 0;                                                          //Больше не обрабатываем
    analog_keys->input = analog_keys->input_new;
#if LOG_ON == 1
    Serial.print(F("Analog Key: "));
    Serial.println(analog_keys->input);
#endif

#if KEY_0 >= KEY_DELTA
    if  (((KEY_0 - KEY_DELTA) < analog_keys->input) &&
          ((KEY_0 + KEY_DELTA) > analog_keys->input))  {                       //Нашли нажатую кнопку KEY_0
      *protocol = 1;
      *command = KEY_0;
    }
#endif
#if KEY_1 >= KEY_DELTA
    if  (((KEY_1 - KEY_DELTA) < analog_keys->input) &&
          ((KEY_1 + KEY_DELTA) > analog_keys->input))  {                       //Нашли нажатую кнопку KEY_1
      *protocol = 1;
      *command = KEY_1;
    }
#endif
#if KEY_2 >= KEY_DELTA
    if (((KEY_2 - KEY_DELTA) < analog_keys->input) &&
          ((KEY_2 + KEY_DELTA) > analog_keys->input)) {                       //Нашли нажатую кнопку KEY_2
      *protocol = 1;
      *command = KEY_2;
    }
#endif
#if KEY_3 >= KEY_DELTA
    if (((KEY_3 - KEY_DELTA) < analog_keys->input) &&
          ((KEY_3 + KEY_DELTA) > analog_keys->input)) {                       //Нашли нажатую кнопку KEY_3
      *protocol = 1;
      *command = KEY_3;
    }
#endif
#if KEY_4 >= KEY_DELTA
    if (((KEY_4 - KEY_DELTA) < analog_keys->input) &&
          ((KEY_4 + KEY_DELTA) > analog_keys->input)) {                       //Нашли нажатую кнопку KEY_4
      *protocol = 1;
      *command = KEY_4;
    }
#endif
#if KEY_5 >= KEY_DELTA
    if (((KEY_5 - KEY_DELTA) < analog_keys->input) &&
          ((KEY_5 + KEY_DELTA) > analog_keys->input)) {                       //Нашли нажатую кнопку KEY_5
      *protocol = 1;
      *command = KEY_5;
    }
#endif
#if KEY_6 >= KEY_DELTA
    if (((KEY_6 - KEY_DELTA) < analog_keys->input) &&
          ((KEY_6 + KEY_DELTA) > analog_keys->input)) {                       //Нашли нажатую кнопку KEY_6
      *protocol = 1;
      *command = KEY_6;
    }
#endif
#if KEY_7 >= KEY_DELTA
    if (((KEY_7 - KEY_DELTA) < analog_keys->input) &&
          ((KEY_7 + KEY_DELTA) > analog_keys->input)) {                       //Нашли нажатую кнопку KEY_7
      *protocol = 1;
      *command = KEY_7;
    }
#endif
  }
}

#endif
