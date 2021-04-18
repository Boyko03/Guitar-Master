#include <Wire.h>                  // Include Wire library (required for I2C devices)
#include <LiquidCrystal_I2C.h>     // Include LiquidCrystal_I2C library 

#define p1 2
#define p2 3
#define p3 4
#define p4 5
#define p5 6
#define p6 7
#define p7 8
#define p8 9
#define p9 10
#define p10 11
#define p11 12
#define p12 13

#define BTN_UP A0
#define BTN_DOWN A1
#define BTN_SELECT A2
#define BTN_BACK A3

#define MAIN_MENU_COUNT 4
#define NOTES_COUNT 12
#define CHORDS_COUNT 11

#define SNAKE_LENGTH 9

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows

uint8_t btn_up = 0, btn_down = 0, btn_select = 0, btn_back = 0;
uint8_t main_menu = 1, sub_menu = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(BTN_UP, INPUT);
  pinMode(BTN_DOWN, INPUT);
  pinMode(BTN_SELECT, INPUT);
  pinMode(BTN_BACK, INPUT);

  lcd.init();                        // Initialize I2C LCD module
 
  lcd.backlight();                   // Turn backlight ON
 
  lcd.setCursor(0, 0);               // Go to column 0, row 0
  lcd.print("GUITAR MASTER");
  lcd.setCursor(0, 1);               // Go to column 0, row 1
  lcd.print("  Boyko Georgiev");

  show_demo();

  delay(500);

  show_menu();

  while(true) {
    on_up();
    on_down();
    on_select();
    on_back();
  
    show_action();
    init_leds();
  }
}

void on_up() {
  if(digitalRead(BTN_UP) == HIGH && btn_up == LOW){
    btn_up = HIGH;
    btn_down = LOW;
    btn_select = LOW;
    btn_back = LOW;

    if (sub_menu == 0) {
      main_menu--;
      if (main_menu < 1) {
        main_menu = MAIN_MENU_COUNT;
      }
    } else {
      switch(main_menu) {
        case 1: // notes
          sub_menu--;
          if (sub_menu < 1) {
            sub_menu = NOTES_COUNT;
          }
          break;
        case 2: // chords
          sub_menu--;
          if (sub_menu < 1) {
            sub_menu = CHORDS_COUNT;
          }
          break;
        case 3: break;
        case 4: break;
      }
    }

  } else if (digitalRead(BTN_UP) == LOW && btn_up == HIGH) {
    btn_up = LOW;

    show_menu();
  }
}

void on_down() {
  if(digitalRead(BTN_DOWN) == HIGH && btn_down == LOW){
    btn_up = LOW;
    btn_down = HIGH;
    btn_select = LOW;
    btn_back = LOW;

    if (sub_menu == 0) {
      main_menu++;
      if (main_menu > MAIN_MENU_COUNT) {
        main_menu = 1;
      }
    } else {
      switch(main_menu) {
        case 1: // notes
          sub_menu++;
          if (sub_menu > NOTES_COUNT) {
            sub_menu = 1;
          }
          break;
        case 2: // chords
          sub_menu++;
          if (sub_menu > CHORDS_COUNT) {
            sub_menu = 1;
          }
          break;
        case 3: break;
        case 4: break;
      }
    }
  
  } else if (digitalRead(BTN_DOWN) == LOW && btn_down == HIGH) {
    btn_down = LOW;

    show_menu();
  }
}

void on_select() {
  if(digitalRead(BTN_SELECT) == HIGH && btn_select == LOW){
    btn_up = LOW;
    btn_down = LOW;
    btn_select = HIGH;
    btn_back = LOW;

    if ((main_menu == 1 || main_menu == 2) && sub_menu == 0) {
      sub_menu = 1;
    } else if (main_menu == 3) {
      show_songs();
    } else if (main_menu == 4) {
      lcd.clear();
      lcd.print("    ::DEMO::");
      show_demo();
    }

  } else if (digitalRead(BTN_SELECT) == LOW && btn_select == HIGH) {
    btn_select = LOW;

    show_menu();
  }
}

void on_back() {
  if(digitalRead(BTN_BACK) == HIGH && btn_back == LOW){
    btn_up = LOW;
    btn_down = LOW;
    btn_select = LOW;
    btn_back = HIGH;

    if (sub_menu == 0) {
      main_menu--;
      if (main_menu < 1) {
        main_menu = MAIN_MENU_COUNT;
      }
    } else {
      sub_menu = 0;
    }

  } else if (digitalRead(BTN_BACK) == LOW && btn_back == HIGH) {
    btn_back = LOW;

    show_menu();
  }
}

void show_menu() {
  lcd.clear();

  switch(main_menu) {
    case 1: // notes
      switch(sub_menu) {
        case 0:
          lcd.print(">Notes");
          lcd.setCursor(0, 1);
          lcd.print(" Chords");
          break;
        case 1:
          lcd.print(">Do");
          lcd.setCursor(0, 1);
          lcd.print(" Do# (Re b)");
          break;
        case 2:
          lcd.print(">Do# (Re b)");
          lcd.setCursor(0, 1);
          lcd.print(" Re");
          break;
        case 3:
          lcd.print(">Re");
          lcd.setCursor(0, 1);
          lcd.print(" Re# (Mi b)");
          break;
        case 4:
          lcd.print(">Re# (Mi b)");
          lcd.setCursor(0, 1);
          lcd.print(" Mi");
          break;
        case 5:
          lcd.print(">Mi");
          lcd.setCursor(0, 1);
          lcd.print(" Fa");
          break;
        case 6:
          lcd.print(">Fa");
          lcd.setCursor(0, 1);
          lcd.print(" Fa# (Sol b)");
          break;
        case 7:
          lcd.print(">Fa# (Sol b)");
          lcd.setCursor(0, 1);
          lcd.print(" Sol");
          break;
        case 8:
          lcd.print(">Sol");
          lcd.setCursor(0, 1);
          lcd.print(" Sol# (La b)");
          break;
        case 9:
          lcd.print(">Sol# (La b)");
          lcd.setCursor(0, 1);
          lcd.print(" La");
          break;
        case 10:
          lcd.print(">La");
          lcd.setCursor(0, 1);
          lcd.print(" La# (Si b)");
          break;
        case 11:
          lcd.print(">La# (Si b)");
          lcd.setCursor(0, 1);
          lcd.print(" Si");
          break;
        case 12:
          lcd.print(" La# (Si b)");
          lcd.setCursor(0, 1);
          lcd.print(">Si");
          break;
      }
      break;
    case 2:
      switch(sub_menu) {
        case 0:
          lcd.print(">Chords");
          lcd.setCursor(0, 1);
          lcd.print(" Songs");
          break;
        case 1:
          lcd.print(">La Major");
          lcd.setCursor(0, 1);
          lcd.print(" Do Major");
          break;
        case 2:
          lcd.print(">Do Major");
          lcd.setCursor(0, 1);
          lcd.print(" Re Major");
          break;
        case 3:
          lcd.print(">Re Major");
          lcd.setCursor(0, 1);
          lcd.print(" Mi Major");
          break;
        case 4:
          lcd.print(">Mi Major");
          lcd.setCursor(0, 1);
          lcd.print(" Sol Major");
          break;
        case 5:
          lcd.print(">Sol Major");
          lcd.setCursor(0, 1);
          lcd.print(" La Minor");
          break;
        case 6:
          lcd.print(">La Minor");
          lcd.setCursor(0, 1);
          lcd.print(" Si Minor");
          break;
        case 7:
          lcd.print(">Si Minor");
          lcd.setCursor(0, 1);
          lcd.print(" Do Minor");
          break;
        case 8:
          lcd.print(">Do Minor");
          lcd.setCursor(0, 1);
          lcd.print(" Re Minor");
          break;
        case 9:
          lcd.print(">Re Minor");
          lcd.setCursor(0, 1);
          lcd.print(" Mi Minor");
          break;
        case 10:
          lcd.print(">Mi Minor");
          lcd.setCursor(0, 1);
          lcd.print(" Sol Minor");
          break;
        case 11:
          lcd.print(" Mi Minor");
          lcd.setCursor(0, 1);
          lcd.print(">Sol Minor");
          break;
      }
      break;
    case 3:
      lcd.clear();
      lcd.print(">Songs");
      lcd.setCursor(0, 1);
      lcd.print(" Demo");
      break;
    case 4:
      lcd.clear();
      lcd.print(" Songs");
      lcd.setCursor(0, 1);
      lcd.print(">Demo");
      break;
  }

}

void show_demo() {
  draw_snake();
  delay(200);
  col_by_col();
}

void draw_snake() {
  const char snake_leds[11][12][2] = {
    {
      {p1, p12}, {p1, p10}, {p1, p8}, {p1, p6}, {p1, p4}, {p1, p2},
      {p3, p2}, {p2, p4}, {p2, p6}, {p2, p8}, {p2, p10}, {p2, p12},
    },
    {
      {p3, p12}, {p3, p10}, {p3, p8}, {p3, p6}, {p3, p4}, {p4, p2},
      {p5, p2}, {p5, p4}, {p4, p6}, {p4, p8}, {p4, p10}, {p4, p12},
    },
    {
      {p5, p12}, {p5, p10}, {p5, p8}, {p5, p6}, {p6, p4}, {p6, p2},
      {p7, p2}, {p7, p4}, {p7, p6}, {p6, p8}, {p6, p10}, {p6, p12},
    },
    {
      {p7, p12}, {p7, p10}, {p7, p8}, {p8, p6}, {p8, p4}, {p8, p2},
      {p9, p2}, {p9, p4}, {p9, p6}, {p9, p8}, {p8, p10}, {p8, p12},
    },
    {
      {p9, p12}, {p9, p10}, {p10, p8}, {p10, p6}, {p10, p4}, {p10, p2},
      {p11, p2}, {p11, p4}, {p11, p6}, {p11, p8}, {p11, p10}, {p10, p12},
    },
    {
      {p11, p12}, {p12, p10}, {p12, p8}, {p12, p6}, {p12, p4}, {p12, p2},
      {p2, p1}, {p1, p3}, {p1, p5}, {p1, p7}, {p1, p9}, {p1, p11},
    },
    {
      {p2, p11}, {p2, p9}, {p2, p7}, {p2, p5}, {p2, p3}, {p3, p1},
      {p4, p1}, {p4, p3}, {p3, p5}, {p3, p7}, {p3, p9}, {p3, p11},
    },
    {
      {p4, p11}, {p4, p9}, {p4, p7}, {p4, p5}, {p5, p3}, {p5, p1},
      {p6, p1}, {p6, p3}, {p6, p5}, {p5, p7}, {p5, p9}, {p5, p11},
    },
    {
      {p6, p11}, {p6, p9}, {p6, p7}, {p7, p5}, {p7, p3}, {p7, p1},
      {p8, p1}, {p8, p3}, {p8, p5}, {p8, p7}, {p7, p9}, {p7, p11},
    },
    {
      {p8, p11}, {p8, p9}, {p9, p7}, {p9, p5}, {p9, p3}, {p9, p1},
      {p10, p1}, {p10, p3}, {p10, p5}, {p10, p7}, {p10, p9}, {p9, p11},
    },
    {
      {p10, p11}, {p11, p9}, {p11, p7}, {p11, p5}, {p11, p3}, {p11, p1},
      {p12, p1}, {p12, p3}, {p12, p5}, {p12, p7}, {p12, p9}, {p12, p11},
    }
  };

  char snake[SNAKE_LENGTH + 1][2] = {NULL};

  for (char i = 0; i < 11; i++) {
    for (char j = 0; j < 12; j++) {
      for(char k = 1; k < SNAKE_LENGTH; k++) {
        snake[k - 1][0] = snake[k][0];
        snake[k - 1][1] = snake[k][1];
      }
      
      snake[SNAKE_LENGTH - 1][0] = snake_leds[i][j][0];
      snake[SNAKE_LENGTH - 1][1] = snake_leds[i][j][1];

      print_snake(snake);
    }
  }

  for (char i = 0; i < SNAKE_LENGTH; i++) {
    for (char j = 1; j < SNAKE_LENGTH; j++) {
      snake[j - 1][0] = snake[j][0];
      snake[j - 1][1] = snake[j][1];
    }

    snake[SNAKE_LENGTH - 1][0] = NULL;
    snake[SNAKE_LENGTH - 1][1] = NULL;

    print_snake(snake);
  }
}

void print_snake(char snake[SNAKE_LENGTH][2]) {
  for(char t = 0; t < 80; t++){
    for(char i = 0; i < SNAKE_LENGTH; i++){
      if(snake[i][0] != NULL){
        init_leds();
        light(snake[i]);
      }
    }
  }
  init_leds();
}

void col_by_col() {
  const char snake_leds[11][12][2] = {
    {
      {p1, p12}, {p1, p10}, {p1, p8}, {p1, p6}, {p1, p4}, {p1, p2},
      {p3, p2}, {p2, p4}, {p2, p6}, {p2, p8}, {p2, p10}, {p2, p12},
    },
    {
      {p3, p12}, {p3, p10}, {p3, p8}, {p3, p6}, {p3, p4}, {p4, p2},
      {p5, p2}, {p5, p4}, {p4, p6}, {p4, p8}, {p4, p10}, {p4, p12},
    },
    {
      {p5, p12}, {p5, p10}, {p5, p8}, {p5, p6}, {p6, p4}, {p6, p2},
      {p7, p2}, {p7, p4}, {p7, p6}, {p6, p8}, {p6, p10}, {p6, p12},
    },
    {
      {p7, p12}, {p7, p10}, {p7, p8}, {p8, p6}, {p8, p4}, {p8, p2},
      {p9, p2}, {p9, p4}, {p9, p6}, {p9, p8}, {p8, p10}, {p8, p12},
    },
    {
      {p9, p12}, {p9, p10}, {p10, p8}, {p10, p6}, {p10, p4}, {p10, p2},
      {p11, p2}, {p11, p4}, {p11, p6}, {p11, p8}, {p11, p10}, {p10, p12},
    },
    {
      {p11, p12}, {p12, p10}, {p12, p8}, {p12, p6}, {p12, p4}, {p12, p2},
      {p2, p1}, {p1, p3}, {p1, p5}, {p1, p7}, {p1, p9}, {p1, p11},
    },
    {
      {p2, p11}, {p2, p9}, {p2, p7}, {p2, p5}, {p2, p3}, {p3, p1},
      {p4, p1}, {p4, p3}, {p3, p5}, {p3, p7}, {p3, p9}, {p3, p11},
    },
    {
      {p4, p11}, {p4, p9}, {p4, p7}, {p4, p5}, {p5, p3}, {p5, p1},
      {p6, p1}, {p6, p3}, {p6, p5}, {p5, p7}, {p5, p9}, {p5, p11},
    },
    {
      {p6, p11}, {p6, p9}, {p6, p7}, {p7, p5}, {p7, p3}, {p7, p1},
      {p8, p1}, {p8, p3}, {p8, p5}, {p8, p7}, {p7, p9}, {p7, p11},
    },
    {
      {p8, p11}, {p8, p9}, {p9, p7}, {p9, p5}, {p9, p3}, {p9, p1},
      {p10, p1}, {p10, p3}, {p10, p5}, {p10, p7}, {p10, p9}, {p9, p11},
    },
    {
      {p10, p11}, {p11, p9}, {p11, p7}, {p11, p5}, {p11, p3}, {p11, p1},
      {p12, p1}, {p12, p3}, {p12, p5}, {p12, p7}, {p12, p9}, {p12, p11},
    }
  };

  for (char i = 10; i >= 0; i--) {
    for (byte t = 0; t < 200; t++) {
      for (char j = 11; j > 5; j--) {
        init_leds();
        light(snake_leds[i][j]);
      }
    }
    init_leds();

    for (byte t = 0; t < 200; t++) {
      for (char j = 5; j >= 0; j--) {
        init_leds();
        light(snake_leds[i][j]);
      }
    }
    init_leds();
  }
}

void init_leds() {
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  pinMode(p3, INPUT);
  pinMode(p4, INPUT);
  pinMode(p5, INPUT);
  pinMode(p6, INPUT);
  pinMode(p7, INPUT);
  pinMode(p8, INPUT);
  pinMode(p9, INPUT);
  pinMode(p10, INPUT);
  pinMode(p11, INPUT);
  pinMode(p12, INPUT);
}

void light(char pins[2]){
  pinMode(pins[0], OUTPUT);
  digitalWrite(pins[0], HIGH);

  pinMode(pins[1], OUTPUT);
  digitalWrite(pins[1], LOW);
}

void show_songs() {
  lcd.clear();
  lcd.print("  Coming soon");
  delay(2000);
}

void show_action() {
  switch(main_menu) {
    case 1: // notes
      switch(sub_menu) {
        case 1: note_Do(); break;
        case 2: note_DoD(); break;
        case 3: note_Re(); break;
        case 4: note_ReD(); break;
        case 5: note_Mi(); break;
        case 6: note_Fa(); break;
        case 7: note_FaD(); break;
        case 8: note_Sol(); break;
        case 9: note_SolD(); break;
        case 10: note_La(); break;
        case 11: note_LaD(); break;
        case 12: note_Si(); break;
      }
      break;
    case 2: // chords
      switch(sub_menu) {
        case 1: chord_La(); break;
        case 2: chord_Do(); break;
        case 3: chord_Re(); break;
        case 4: chord_Mi(); break;
        case 5: chord_Sol(); break;
        case 6: chord_LaM(); break;
        case 7: chord_SiM(); break;
        case 8: chord_DoM(); break;
        case 9: chord_ReM(); break;
        case 10: chord_MiM(); break;
        case 11: chord_SolM(); break;
      }
      break;
  }
}

// Notes
void note_Do() {
  char Do[11][2] = {      // C
    {p10, p2},
    {p11, p1},
    {p5, p4},
    {p6, p3},
    {p12, p6},
    {p6, p8},
    {p8, p7},
    {p2, p10},
    {p3, p9},
    {p9, p12},
    {p10, p11}
  };

  for (char i = 0; i < 11; i++) {
    init_leds();
    light(Do[i]);
  }
}
void note_DoD() {
  char DoD[9][2] = {      // Cs
    {p11, p2},
    {p6, p4},
    {p7, p3},
    {p1, p5},
    {p7, p8},
    {p9, p7},
    {p3, p10},
    {p4, p9},
    {p10, p12}
  };

  for (char i = 0; i < 9; i++) {
    init_leds();
    light(DoD[i]);
  }
}
void note_Re() {
  char Re[10][2] = {      // D
    {p12, p2},
    {p7, p4},
    {p8, p3},
    {p1, p6},
    {p2, p5},
    {p9, p8},
    {p10, p7},
    {p4, p10},
    {p5, p9},
    {p11, p12}
  };

  for (char i = 0; i < 10; i++) {
    init_leds();
    light(Re[i]);
  }
}
void note_ReD() {
  char ReD[10][2] = {
    {p2, p1},
    {p8, p4},
    {p9, p3},
    {p2, p6},
    {p3, p5},
    {p10, p8},
    {p11, p7},
    {p5, p10},
    {p6, p9},
    {p1, p11}
  };

  for (char i = 0; i < 10; i++) {
    init_leds();
    light(ReD[i]);
  }
}
void note_Mi() {
  char Mi[11][2] = {
    {p1, p2},
    {p3, p1},
    {p9, p4},
    {p10, p3},
    {p3, p6},
    {p4, p5},
    {p11, p8},
    {p6, p10},
    {p7, p9},
    {p1, p12},
    {p2, p11}
  };

  for (char i = 0; i < 11; i++) {
    init_leds();
    light(Mi[i]);
  }
}
void note_Fa() {
  char Fa[11][2] = {
    {p3, p2},
    {p4, p1},
    {p10, p4},
    {p11, p3},
    {p4, p6},
    {p6, p5},
    {p12, p8},
    {p7, p10},
    {p8, p9},
    {p2, p12},
    {p3, p11}
  };

  for (char i = 0; i < 11; i++) {
    init_leds();
    light(Fa[i]);
  }
}
void note_FaD() {
  char FaD[10][2] = {
    {p4, p2},
    {p5, p1},
    {p11, p4},
    {p5, p6},
    {p7, p5},
    {p1, p7},
    {p8, p10},
    {p10, p9},
    {p3, p12},
    {p4, p11}
  };

  for (char i = 0; i < 10; i++) {
    init_leds();
    light(FaD[i]);
  }
}
void note_Sol() {
  char Sol[11][2] = {
    {p5, p2},
    {p6, p1},
    {p12, p4},
    {p7, p6},
    {p8, p5},
    {p1, p8},
    {p2, p7},
    {p9, p10},
    {p11, p9},
    {p4, p12},
    {p5, p11}
  };

  for (char i = 0; i < 11; i++) {
    init_leds();
    light(Sol[i]);
  }
}
void note_SolD() {
  char SolD[10][2] = {
    {p6, p2},
    {p7, p1},
    {p1, p3},
    {p8, p6},
    {p9, p5},
    {p2, p8},
    {p3, p7},
    {p11, p10},
    {p5, p12},
    {p6, p11}
  };

  for (char i = 0; i < 10; i++) {
    init_leds();
    light(SolD[i]);
  }
}
void note_La() {
  char La[11][2] = {
    {p7, p2},
    {p8, p1},
    {p1, p4},
    {p2, p3},
    {p9, p6},
    {p10, p5},
    {p3, p8},
    {p4, p7},
    {p12, p10},
    {p6, p12},
    {p7, p11}
  };

  for (char i = 0; i < 11; i++) {
    init_leds();
    light(La[i]);
  }
}
void note_LaD() {
  char LaD[11][2] = {
    {p8, p2},
    {p9, p1},
    {p2, p4},
    {p4, p3},
    {p10, p6},
    {p11, p5},
    {p4, p8},
    {p5, p7},
    {p1, p9},
    {p7, p12},
    {p8, p11}
  };

  for (char i = 0; i < 11; i++) {
    init_leds();
    light(LaD[i]);
  }
}
void note_Si() {
  char Si[11][2] = {
    {p9, p2},
    {p10, p1},
    {p3, p4},
    {p5, p3},
    {p11, p6},
    {p5, p8},
    {p6, p7},
    {p1, p10},
    {p2, p9},
    {p8, p12},
    {p9, p11}
  };

  for (char i = 0; i < 11; i++) {
    init_leds();
    light(Si[i]);
  }
}

// Chords
void chord_La() {
  const uint8_t La[13][2] = {    // A
    {p1, p12},
    {p1, p10},
    {p1, p8},
    {p1, p6},
    {p1, p4},
    {p3, p10},
    {p3, p8},
    {p3, p6},
    {p12, p11},
    {p12, p9},
    {p12, p7},
    {p12, p5},
    {p12, p3}
  };

  for (uint8_t j = 0; j < 13; j++) {
    init_leds();
    light(La[j]);
  }
}
void chord_Do() {
  const uint8_t Do[13][2] = {    // C
    {p1, p12},
    {p1, p10},
    {p1, p8},
    {p1, p6},
    {p1, p4},
    {p2, p10},
    {p3, p6},
    {p5, p4},
    {p12, p11},
    {p12, p9},
    {p12, p7},
    {p12, p5},
    {p12, p3}
  };

  for (uint8_t j = 0; j < 13; j++) {
    init_leds();
    light(Do[j]);
  }
}
void chord_Re() {
  const uint8_t Re[11][2] = {    // D
    {p1, p12},
    {p1, p10},
    {p1, p8},
    {p1, p6},
    {p3, p12},
    {p3, p8},
    {p4, p10},
    {p12, p11},
    {p12, p9},
    {p12, p7},
    {p12, p5}
  };

  for (uint8_t j = 0; j < 11; j++) {
    init_leds();
    light(Re[j]);
  }
}
void chord_Mi() {
  const uint8_t Mi[15][2] = {    // E
    {p1, p12},
    {p1, p10},
    {p1, p8},
    {p1, p6},
    {p1, p4},
    {p1, p2},
    {p2, p8},
    {p3, p6},
    {p3, p4},
    {p12, p11},
    {p12, p9},
    {p12, p7},
    {p12, p5},
    {p12, p3},
    {p12, p1}
  };

  for (uint8_t j = 0; j < 15; j++) {
    init_leds();
    light(Mi[j]);
  }
}
void chord_Sol() {
  const uint8_t Sol[15][2] = {   // G
    {p1, p12},
    {p1, p10},
    {p1, p8},
    {p1, p6},
    {p1, p4},
    {p1, p2},
    {p3, p4},
    {p4, p12},
    {p5, p2},
    {p12, p11},
    {p12, p9},
    {p12, p7},
    {p12, p5},
    {p12, p3},
    {p12, p1}
  };

  for (uint8_t j = 0; j < 15; j++) {
    init_leds();
    light(Sol[j]);
  }
}
void chord_LaM() {
  const uint8_t LaM[13][2] = {   // Am
    {p1, p12},
    {p1, p10},
    {p1, p8},
    {p1, p6},
    {p1, p4},
    {p2, p10},
    {p3, p8},
    {p3, p6},
    {p12, p11},
    {p12, p9},
    {p12, p7},
    {p12, p5},
    {p12, p3}
  };

  for (uint8_t j = 0; j < 13; j++) {
    init_leds();
    light(LaM[j]);
  }
}
void chord_SiM() {
  const uint8_t SiM[18][2] = {   // Bm
    {p1, p12},
    {p1, p10},
    {p1, p8},
    {p1, p6},
    {p1, p4},
    {p3, p12},
    {p3, p10},
    {p3, p8},
    {p3, p6},
    {p3, p4},
    {p4, p10},
    {p5, p8},
    {p5, p6},
    {p12, p11},
    {p12, p9},
    {p12, p7},
    {p12, p5},
    {p12, p3}
  };

  for (uint8_t j = 0; j < 18; j++) {
    init_leds();
    light(SiM[j]);
  }
}
void chord_DoM() {
  const uint8_t DoM[18][2] = {   // Cm
    {p1, p12},
    {p1, p10},
    {p1, p8},
    {p1, p6},
    {p1, p4},
    {p4, p12},
    {p4, p10},
    {p4, p8},
    {p4, p6},
    {p5, p4},
    {p5, p10},
    {p6, p8},
    {p7, p6},
    {p12, p11},
    {p12, p9},
    {p12, p7},
    {p12, p5},
    {p12, p3}
  };

  for (uint8_t j = 0; j < 18; j++) {
    init_leds();
    light(DoM[j]);
  }
}
void chord_ReM() {
  const uint8_t ReM[11][2] = {   // Dm
    {p1, p12},
    {p1, p10},
    {p1, p8},
    {p1, p6},
    {p2, p12},
    {p3, p8},
    {p4, p10},
    {p12, p11},
    {p12, p9},
    {p12, p7},
    {p12, p5}
  };
  
  for (uint8_t j = 0; j < 11; j++) {
    init_leds();
    light(ReM[j]);
  }
}
void chord_MiM() {
  const uint8_t MiM[14][2] = {   // Em
    {p1, p12},
    {p1, p10},
    {p1, p8},
    {p1, p6},
    {p1, p4},
    {p1, p2},
    {p3, p6},
    {p3, p4},
    {p12, p11},
    {p12, p9},
    {p12, p7},
    {p12, p5},
    {p12, p3},
    {p12, p1}
  };

  for (uint8_t j = 0; j < 14; j++) {
    init_leds();
    light(MiM[j]);
  }
}
void chord_SolM() {
  const uint8_t SolM[20][2] = {  // Gm
    {p1, p12},
    {p1, p10},
    {p1, p8},
    {p1, p6},
    {p1, p4},
    {p1, p2},
    {p4, p12},
    {p4, p10},
    {p4, p8},
    {p4, p6},
    {p5, p4},
    {p5, p2},
    {p7, p6},
    {p7, p4},
    {p12, p11},
    {p12, p9},
    {p12, p7},
    {p12, p5},
    {p12, p3},
    {p12, p1}
  };

  for (uint8_t j = 0; j < 20; j++) {
    init_leds();
    light(SolM[j]);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
}
