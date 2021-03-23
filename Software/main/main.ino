#include <LiquidCrystal.h>

#define rs 12
#define en 11
#define d4 5
#define d5 4
#define d6 3
#define d7 2

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define BTN_UP A0
#define BTN_DOWN A1
#define BTN_SELECT A2
#define BTN_BACK A3

// Menus
void print_main_menu();
void print_notes_menu();
void print_chords_menu();
void print_songs_menu();

// Notes
void note_A();
void note_As();
void note_B();
void note_C();
void note_Cs();
void note_D();
void note_Ds();
void note_E();
void note_F();
void note_Fs();
void note_G();
void note_Gs();

// Chords
void chord_A();
void chord_C();
void chord_D();
void chord_E();
void chord_G();
void chord_Am();
void chord_Bm();
void chord_Cm();
void chord_Dm();
void chord_Em();
void chord_Gm();

void setup() {
  pinMode(BTN_UP, INPUT);
  pinMode(BTN_DOWN, INPUT);
  pinMode(BTN_SELECT, INPUT);
  pinMode(BTN_BACK, INPUT);
  pinMode(13, OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Hello world");
  delay(1000);
  
  print_main_menu();
}

void loop() {
  // put your main code here, to run repeatedly:
}

void print_main_menu(){
  int i = 0, prev_i = -1;
  int btn_up = 0, btn_down = 0, btn_select = 0;
  int p_btn_up = 0, p_btn_down = 0, p_btn_select = 0;
  lcd.clear();

  while(true){
    if(i != prev_i){
      lcd.clear();
    }

    switch(i){
      case 0:
        if(prev_i == 0) break;
        lcd.print(">Notes");
        lcd.setCursor(0, 1);
        lcd.print(" Chords");
        prev_i = 0;
        delay(100);
        break;
      case 1:
        if(prev_i == 1) break;
        lcd.print(">Chords");
        lcd.setCursor(0, 1);
        lcd.print(" Songs");
        prev_i = 1;
        delay(100);
        break;
      case 2:
        if(prev_i == 2) break;
        lcd.print(" Chords");
        lcd.setCursor(0, 1);
        lcd.print(">Songs");
        prev_i = 2;
        delay(100);
        break;
    }
    btn_up = digitalRead(BTN_UP);
    btn_down = digitalRead(BTN_DOWN);
    btn_select = digitalRead(BTN_SELECT);

    if(btn_up == HIGH && p_btn_up == LOW){
      p_btn_up = HIGH;
      if(i != 0){
        i--;
        lcd.clear();
      }
    }
    else if(btn_down == HIGH && p_btn_down == LOW){
      p_btn_down = HIGH;
      if(i != 2){
        i++;
        lcd.clear();
      }
    }
    else if(btn_select == HIGH && p_btn_select == LOW){
      p_btn_select = HIGH;
      prev_i = 3;

      switch(i){
        case 0: print_notes_menu(); break;
        case 1: print_chords_menu(); break;
        case 2: print_songs_menu(); break;
      }
      
      lcd.clear();
    }
    
    p_btn_up = btn_up;
    p_btn_down = btn_down;
    p_btn_select = btn_select;
  }
}

// Notes
void print_notes_menu(){
  int i = 0, prev_i = -1;
  int btn_up = 0, btn_down = 0, btn_select = 0, btn_back = 0;
  int p_btn_up = 0, p_btn_down = 0, p_btn_select = 1;
  lcd.clear();

  while(true){
    if(i != prev_i){
      lcd.clear();
    }

    switch(i){
      case 0:
        if(prev_i == 0) break;
        lcd.print(">A");
        lcd.setCursor(0, 1);
        lcd.print(" A# (Bb)");
        prev_i = 0;
        delay(100);
        break;
      case 1:
        if(prev_i == 1) break;
        lcd.print(">A# (Bb)");
        lcd.setCursor(0, 1);
        lcd.print(" B");
        prev_i = 1;
        delay(100);
        break;
      case 2:
        if(prev_i == 2) break;
        lcd.print(">B");
        lcd.setCursor(0, 1);
        lcd.print(" C");
        prev_i = 2;
        delay(100);
        break;
      case 3:
        if(prev_i == 3) break;
        lcd.print(">C");
        lcd.setCursor(0, 1);
        lcd.print(" C# (Db)");
        prev_i = 3;
        delay(100);
        break;
      case 4:
        if(prev_i == 4) break;
        lcd.print(">C# (Db)");
        lcd.setCursor(0, 1);
        lcd.print(" D");
        prev_i = 4;
        delay(100);
        break;
      case 5:
        if(prev_i == 5) break;
        lcd.print(">D");
        lcd.setCursor(0, 1);
        lcd.print(" D# (Eb)");
        prev_i = 5;
        delay(100);
        break;
      case 6:
        if(prev_i == 6) break;
        lcd.print(">D# (Eb)");
        lcd.setCursor(0, 1);
        lcd.print(" E");
        prev_i = 6;
        delay(100);
        break;
      case 7:
        if(prev_i == 7) break;
        lcd.print(">E");
        lcd.setCursor(0, 1);
        lcd.print(" F");
        prev_i = 7;
        delay(100);
        break;
      case 8:
        if(prev_i == 8) break;
        lcd.print(">F");
        lcd.setCursor(0, 1);
        lcd.print(" F# (Gb)");
        prev_i = 8;
        delay(100);
        break;
      case 9:
        if(prev_i == 9) break;
        lcd.print(">F# (Gb)");
        lcd.setCursor(0, 1);
        lcd.print(" G");
        prev_i = 9;
        delay(100);
        break;
      case 10:
        if(prev_i == 10) break;
        lcd.print(">G");
        lcd.setCursor(0, 1);
        lcd.print(" G# (Ab)");
        prev_i = 10;
        delay(100);
        break;
      case 11:
        if(prev_i == 11) break;
        lcd.print(" G");
        lcd.setCursor(0, 1);
        lcd.print(">G# (Ab)");
        prev_i = 11;
        delay(100);
        break;
    }

    btn_up = digitalRead(BTN_UP);
    btn_down = digitalRead(BTN_DOWN);
    btn_select = digitalRead(BTN_SELECT);
    btn_back = digitalRead(BTN_BACK);

    if(btn_up == HIGH && p_btn_up == LOW){
      p_btn_up = HIGH;
      if(i != 0){
        i--;
        lcd.clear();
      }
    }
    else if(btn_down == HIGH && p_btn_down == LOW){
      p_btn_down = HIGH;
      if(i != 11){
        i++;
        lcd.clear();
      }
    }
    else if(btn_select == HIGH && p_btn_select == LOW){
      p_btn_select = HIGH;
      prev_i = 3;

      switch(i){
        case 0: note_A(); break;
        case 1: note_As(); break;
        case 2: note_B(); break;
        case 3: note_C(); break;
        case 4: note_Cs(); break;
        case 5: note_D(); break;
        case 6: note_Ds(); break;
        case 7: note_E(); break;
        case 8: note_F(); break;
        case 9: note_Fs(); break;
        case 10: note_G(); break;
        case 11: note_Gs(); break;
      }
      
      lcd.clear();
    }
    else if(btn_back == HIGH){
      return;
    }

    p_btn_up = btn_up;
    p_btn_down = btn_down;
    p_btn_select = btn_select;
  }
}

void note_A() {
  lcd.clear();
  lcd.print("A");
  delay(1000);
}
void note_As() {
  lcd.clear();
  lcd.print("A# (Bb)");
  delay(1000);
}
void note_B() {
  lcd.clear();
  lcd.print("B");
  delay(1000);
}
void note_C() {
  lcd.clear();
  lcd.print("C");
  delay(1000);
}
void note_Cs() {
  lcd.clear();
  lcd.print("C# (Db)");
  delay(1000);
}
void note_D() {
  lcd.clear();
  lcd.print("D");
  delay(1000);
}
void note_Ds() {
  lcd.clear();
  lcd.print("D# (Eb)");
  delay(1000);
}
void note_E() {
  lcd.clear();
  lcd.print("E");
  delay(1000);
}
void note_F() {
  lcd.clear();
  lcd.print("F");
  delay(1000);
}
void note_Fs() {
  lcd.clear();
  lcd.print("F# (Gb)");
  delay(1000);
}
void note_G() {
  lcd.clear();
  lcd.print("G");
  delay(1000);
}
void note_Gs() {
  lcd.clear();
  lcd.print("G# (Ab)");
  delay(1000);
}

// Chords
void print_chords_menu(){
  int i = 0, prev_i = -1;
  int btn_up = 0, btn_down = 0, btn_select = 0, btn_back = 0;
  int p_btn_up = 0, p_btn_down = 0, p_btn_select = 1;
  lcd.clear();

  while(true){
    if(i != prev_i){
      lcd.clear();
    }

    switch(i){
      case 0:
        if(prev_i == 0) break;
        lcd.print(">A Major");
        lcd.setCursor(0, 1);
        lcd.print(" C Major");
        prev_i = 0;
        delay(100);
        break;
      case 1:
        if(prev_i == 1) break;
        lcd.print(">C Major");
        lcd.setCursor(0, 1);
        lcd.print(" D Major");
        prev_i = 1;
        delay(100);
        break;
      case 2:
        if(prev_i == 2) break;
        lcd.print(">D Major");
        lcd.setCursor(0, 1);
        lcd.print(" E Major");
        prev_i = 2;
        delay(100);
        break;
      case 3:
        if(prev_i == 3) break;
        lcd.print(">E Major");
        lcd.setCursor(0, 1);
        lcd.print(" G Major");
        prev_i = 3;
        delay(100);
        break;
      case 4:
        if(prev_i == 4) break;
        lcd.print(">G Major");
        lcd.setCursor(0, 1);
        lcd.print(" A Minor");
        prev_i = 4;
        delay(100);
        break;
      case 5:
        if(prev_i == 5) break;
        lcd.print(">A Minor");
        lcd.setCursor(0, 1);
        lcd.print(" B Minor");
        prev_i = 5;
        delay(100);
        break;
      case 6:
        if(prev_i == 6) break;
        lcd.print(">B Minor");
        lcd.setCursor(0, 1);
        lcd.print(" C Minor");
        prev_i = 6;
        delay(100);
        break;
      case 7:
        if(prev_i == 7) break;
        lcd.print(">C Minor");
        lcd.setCursor(0, 1);
        lcd.print(" D Minor");
        prev_i = 7;
        delay(100);
        break;
      case 8:
        if(prev_i == 8) break;
        lcd.print(">D Minor");
        lcd.setCursor(0, 1);
        lcd.print(" E Minor");
        prev_i = 8;
        delay(100);
        break;
      case 9:
        if(prev_i == 9) break;
        lcd.print(">E Minor");
        lcd.setCursor(0, 1);
        lcd.print(" G Minor");
        prev_i = 9;
        delay(100);
        break;
      case 10:
        if(prev_i == 10) break;
        lcd.print(" E Minor");
        lcd.setCursor(0, 1);
        lcd.print(">G Minor");
        prev_i = 10;
        delay(100);
        break;
    }

    btn_up = digitalRead(BTN_UP);
    btn_down = digitalRead(BTN_DOWN);
    btn_select = digitalRead(BTN_SELECT);
    btn_back = digitalRead(BTN_BACK);

    if(btn_up == HIGH && p_btn_up == LOW){
      p_btn_up = HIGH;
      if(i != 0){
        i--;
        lcd.clear();
      }
    }
    else if(btn_down == HIGH && p_btn_down == LOW){
      p_btn_down = HIGH;
      if(i != 10){
        i++;
        lcd.clear();
      }
    }
    else if(btn_select == HIGH && p_btn_select == LOW){
      p_btn_select = HIGH;
      prev_i = 3;

      switch(i){
        case 0: chord_A(); break;
        case 1: chord_C(); break;
        case 2: chord_D(); break;
        case 3: chord_E(); break;
        case 4: chord_G(); break;
        case 5: chord_Am(); break;
        case 6: chord_Bm(); break;
        case 7: chord_Cm(); break;
        case 8: chord_Dm(); break;
        case 9: chord_Em(); break;
        case 10: chord_Gm(); break;
      }
      
      lcd.clear();
    }
    else if(btn_back == HIGH){
      return;
    }

    p_btn_up = btn_up;
    p_btn_down = btn_down;
    p_btn_select = btn_select;
  }
}

void chord_A() {
  lcd.clear();
  lcd.print("A Major");
  delay(1000);
}

void chord_C() {
  lcd.clear();
  lcd.print("C Major");
  delay(1000);
}

void chord_D() {
  lcd.clear();
  lcd.print("D Major");
  delay(1000);
}

void chord_E() {
  lcd.clear();
  lcd.print("E Major");
  delay(1000);
}

void chord_G() {
  lcd.clear();
  lcd.print("G Major");
  delay(1000);
}

void chord_Am() {
  lcd.clear();
  lcd.print("A Minor");
  delay(1000);
}

void chord_Bm() {
  lcd.clear();
  lcd.print("B Minor");
  delay(1000);
}

void chord_Cm() {
  lcd.clear();
  lcd.print("C Minor");
  delay(1000);
}

void chord_Dm() {
  lcd.clear();
  lcd.print("D Minor");
  delay(1000);
}

void chord_Em() {
  lcd.clear();
  lcd.print("E Minor");
  delay(1000);
}

void chord_Gm() {
  lcd.clear();
  lcd.print("G Minor");
  delay(1000);
}

// Songs
void print_songs_menu(){
  lcd.clear();
  lcd.print("Coming soon!");
  delay(1000);
}
