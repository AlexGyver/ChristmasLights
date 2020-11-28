#ifndef COMMANDS_H
#define COMMANDS_H

//здесь находятся команды обрабатываемые скетчем
//формат такой
// #define IR_Key_XXXX   YYYYY
// где IR_Key_XXXX - код команды, это лучше не менять
//     YYYYY -Код клавиши пульта или аналоговой клавиатуры
//            Если кнопка не используется, то тогда надо либо поставить код 0, либо закоментировать строку
//                Например #define IR_Key_XXXX   0xff4ab5
//                или так  #define IR_Key_XXXX   KEY_0

// кнопка на пульте
#define IR_Key_Brightness_plus              0xff4ab5  // N/P                    // Увеличить максимальную яркость 
#define IR_Key_Brightness_minus             0xff6a95  // Repeat                 // Уменьшить максимальную яркость 
#define IR_Key_Reset                        0xffca35  // Power                  // Сброс всех настроек и перезагрузка 
#define IR_Key_Demo                         0xfffa05  // Open                   // Включит демо режим (перебор) 
#define IR_Key_Demo_Random                  0xffda25  // Prog                   // Включит демо режим (Случайно) 
#define IR_Key_Demo_MyMode                  0xff5aa5  // A-B                   // Включит демо режим (перебор) 
#define IR_Key_Demo_MyMode_Random           0xff7a85  // RAN                   // Включит демо режим (Случайно) 

#define IR_Key_Length_Garland_plus          0xFF8A75  // L/R                    // Увеличить количество светодиодов в гирлянде 
#define IR_Key_Length_Garland_minus         0xFFAA55  // Slow                   // Уменьшить количество светодиодов в гирлянде
#define IR_Key_Rotate                       0xff08f7  // Setup                  // Сменить направление движения эффектов
#define IR_Key_Speed_minus                  0xfff807  // vol -                  // Замедлить движение
#define IR_Key_Speed_plus                   0xff3ac5  // vol +                  // Ускорить движение

#define IR_Key_Glitter                      0xFFC837  // Subtitle               // Включить/выключить сверкание
#define IR_Key_BackGround                   0xFFE817  // Time                   // Включить/выключить заполнение фона
#define IR_Key_Candle                       0xFFD827  // PDVD                   // Включить/выключить свечки

#define IR_Key_Previous_mode                0xff50af  // Down                   // Предыдущий эффект. Отключает демонстрационный режим
#define IR_Key_Next_mode                    0xff28d7  // Up                     // Следующий эффект. Отключает демонстрационный режим

//Вариант выбора используя кнопки 0-9 и +10  кнопками 0-9 меняются только единицы числа, а кнопкой +10 увеличиваются десятки числа
#define IR_Key_SetMode_X0                   0                                   // Набор номера выбор эффекта единицы кнопка 0
#define IR_Key_SetMode_X1                   0                                   // Набор номера выбор эффекта единицы кнопка 1
#define IR_Key_SetMode_X2                   0                                   // Набор номера выбор эффекта единицы кнопка 2
#define IR_Key_SetMode_X3                   0                                   // Набор номера выбор эффекта единицы кнопка 3
#define IR_Key_SetMode_X4                   0                                   // Набор номера выбор эффекта единицы кнопка 4
#define IR_Key_SetMode_X5                   0                                   // Набор номера выбор эффекта единицы кнопка 5
#define IR_Key_SetMode_X6                   0                                   // Набор номера выбор эффекта единицы кнопка 6
#define IR_Key_SetMode_X7                   0                                   // Набор номера выбор эффекта единицы кнопка 7
#define IR_Key_SetMode_X8                   0                                   // Набор номера выбор эффекта единицы кнопка 8
#define IR_Key_SetMode_X9                   0                                   // Набор номера выбор эффекта единицы кнопка 9
#define IR_Key_SetMode_1X                   0                                   // Набор номера выбор эффекта десядки кнопка +10

//Вариант выбора используя кнопки 0-9  кнопками 0-9 число сдвигается на разряд и добавляется единица, соответствующая номеру кнопки
#define IR_Key_SetMode_0                    0xFF20DF  //0                       // Набор номера выбор эффекта сдвиг + кнопка 0
#define IR_Key_SetMode_1                    0xFFC03F  //1                       // Набор номера выбор эффекта сдвиг + кнопка 1
#define IR_Key_SetMode_2                    0xFFE01F  //2                       // Набор номера выбор эффекта сдвиг + кнопка 2
#define IR_Key_SetMode_3                    0xFFD02F  //3                       // Набор номера выбор эффекта сдвиг + кнопка 3
#define IR_Key_SetMode_4                    0xFFF00F  //4                       // Набор номера выбор эффекта сдвиг + кнопка 4
#define IR_Key_SetMode_5                    0xFF02FD  //5                       // Набор номера выбор эффекта сдвиг + кнопка 5
#define IR_Key_SetMode_6                    0xFF22DD  //6                       // Набор номера выбор эффекта сдвиг + кнопка 6
#define IR_Key_SetMode_7                    0xFF12ED  //7                       // Набор номера выбор эффекта сдвиг + кнопка 7
#define IR_Key_SetMode_8                    0xFF32CD  //8                       // Набор номера выбор эффекта сдвиг + кнопка 8
#define IR_Key_SetMode_9                    0xFF00FF  //9                       // Набор номера выбор эффекта сдвиг + кнопка 9

#define IR_Key_Mode_0                       0                                   //  Эффект 0
#define IR_Key_Mode_1                       0                                   //  Эффект 1
#define IR_Key_Mode_2                       0                                   //  Эффект 2
#define IR_Key_Mode_3                       0                                   //  Эффект 3
#define IR_Key_Mode_4                       0                                   //  Эффект 4
#define IR_Key_Mode_5                       0                                   //  Эффект 5
#define IR_Key_Mode_6                       0                                   //  Эффект 6
#define IR_Key_Mode_7                       0                                   //  Эффект 7
#define IR_Key_Mode_8                       0                                   //  Эффект 8
#define IR_Key_Mode_9                       0                                   //  Эффект 9
#define IR_Key_Mode_10                      0                                    //  Эффект 10
#define IR_Key_Mode_11                      0                                    //  Эффект 11
#define IR_Key_Mode_12                      0                                    //  Эффект 12
#define IR_Key_Mode_13                      0                                    //  Эффект 13
#define IR_Key_Mode_14                      0                                    //  Эффект 14
#define IR_Key_Mode_15                      0                                    //  Эффект 15
#define IR_Key_Mode_16                      0                                    //  Эффект 16
#define IR_Key_Mode_17                      0                                    //  Эффект 17
#define IR_Key_Mode_18                      0                                    //  Эффект 18
#define IR_Key_Mode_19                      0                                    //  Эффект 19
#define IR_Key_Mode_20                      0                                    //  Эффект 20
#define IR_Key_Mode_21                      0                                    //  Эффект 21
#define IR_Key_Mode_22                      0                                    //  Эффект 22
#define IR_Key_Mode_23                      0                                    //  Эффект 23
#define IR_Key_Mode_24                      0                                    //  Эффект 24
#define IR_Key_Mode_25                      0                                    //  Эффект 25
#define IR_Key_Mode_26                      0                                    //  Эффект 26
#define IR_Key_Mode_27                      0                                    //  Эффект 27
#define IR_Key_Mode_28                      0                                    //  Эффект 28
#define IR_Key_Mode_29                      0                                    //  Эффект 29
#define IR_Key_Mode_30                      0                                    //  Эффект 30
#define IR_Key_Mode_31                      0                                    //  Эффект 31
#define IR_Key_Mode_32                      0                                    //  Эффект 32
#define IR_Key_Mode_33                      0                                    //  Эффект 33
#define IR_Key_Mode_34                      0                                    //  Эффект 34
#define IR_Key_Mode_35                      0                                    //  Эффект 35
#define IR_Key_Mode_36                      0                                    //  Эффект 36
#define IR_Key_Mode_37                      0                                    //  Эффект 37
#define IR_Key_Mode_38                      0                                    //  Эффект 38
#define IR_Key_Mode_39                      KEY_0                                //  Эффект 39
#define IR_Key_Mode_40                      0                                    //  Эффект 40
#define IR_Key_Mode_41                      0                                    //  Эффект 40

#define IR_Key_Save_Mode                    0xFF30CF  // Clear                  // Сохранить эффект как запускающийся первым
#define IR_Key_Delay_minus                  0xFF9A65  // Resume                 // Уменьшить задержку на 100ms (используя белые светодиоды)
#define IR_Key_Delay_plus                   0xFFBA45  // Step                   // Увеличить задержку на 100ms (используя белые светодиоды)

#define IR_Key_Palette_Stop                 0xff8877  // Menu                   // Остановка вращения палитры        Остановить перебор Палитр
#define IR_Key_Palette_Previous             0xff9867  // <-                     // Выберите предыдущую палитру       Установить предыдущую палитру
#define IR_Key_Palette_Next                 0xff18e7  // ->                     // Выберите следующую палитру        Установить следующую палитру
#define IR_Key_Palette_Auto                 0xffa857  // Enter                  // Включить поворот палитры          Продолжить автоматический перебор палитр

#define IR_Key_Solid_Black                  0xFF48B7  // <<                     //  Установить цвет Черный  (Выключает гирлянду, Например перед тем как сказать елочка зажгись на детском утреннике)
#define IR_Key_Solid_Red                    0xFF6897  // >>                     //  Установить цвет Красный
#define IR_Key_Solid_Orange                 0xFF58A7  // |<<                    //  Установить цвет Оранжевый
#define IR_Key_Solid_Yellow                 0xFF7887  // >>|                    //  Установить цвет Желтый
#define IR_Key_Solid_Green                  0xFF42BD  // |>                     //  Установить цвет Зеленый
#define IR_Key_Solid_SkyBlue                0xFF629D  // ||                     //  Установить цвет Голубой
#define IR_Key_Solid_Blue                   0xFF52AD  // []                     //  Установить цвет Синий
#define IR_Key_Solid_Violet                 0xFF728D  // ><                     //  Установить цвет Фиолетовый
#define IR_Key_Solid_White                  0xFFB847  // Zoom                   //  Установить цвет Белый

#endif
