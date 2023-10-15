#include <Keyboard.h>
#include <Mouse.h>

char state = 0;
int KMap[256] = {0 , };

void setup() {
  Serial.begin(9600);
  Mouse.begin();
  Keyboard.begin();

  KMap['\\'] = '\\';
  // Escape and function keys
  for(int i = 1;i <= 9; i++)
    KMap[i + '0'] = KEY_F1 + i - 1;
  KMap['A'] = KEY_F10;
  KMap['B'] = KEY_F11;
  KMap['C'] = KEY_F12;
  KMap['D'] = KEY_F13;
  KMap['E'] = KEY_F14;
  KMap['F'] = KEY_F15;

  // Keyboard modifiers
  KMap['z'] = KEY_LEFT_CTRL;
  KMap['x'] = KEY_LEFT_ALT;
  KMap['c'] = KEY_LEFT_SHIFT;
  KMap['v'] = KEY_LEFT_GUI;
  KMap['a'] = KEY_RIGHT_CTRL;
  KMap['s'] = KEY_RIGHT_ALT;
  KMap['d'] = KEY_RIGHT_SHIFT;
  KMap['f'] = KEY_RIGHT_GUI;

  // Special keys
  KMap['t'] = KEY_TAB;
  KMap['r'] = KEY_RETURN;
  KMap['m'] = KEY_MENU;
  KMap['p'] = KEY_CAPS_LOCK;
  KMap['e'] = KEY_BACKSPACE;

  // Arrow Keys
  KMap['i'] = KEY_UP_ARROW;
  KMap['j'] = KEY_LEFT_ARROW;
  KMap['k'] = KEY_DOWN_ARROW;
  KMap['l'] = KEY_RIGHT_ARROW;

  // bghnoquwyGHIJKLMNOPQRSTUVWXYZ
}

void loop() {
  if(!Serial.available()) return;
  char data = Serial.read();

  if(data == '\n' || data == ';') {
    if(state == 1) Keyboard.releaseAll();
    state = 0;
  } else if(state == 0) { // Command Selecter
    if(data == 'z') // Keyboard.press then Release All (1, 2)
      state = 1;
    else if(data == 'x') // Keyboard.write (3)
      state = 3;
    else if(data == 'c') // Keybaord.press (4, 5)
      state = 4;
    else if(data == 'v') // Keyboard.Release (6, 7)
      state = 6;
    else if(data == 'b') // Keyboard.ReleaseAll
      Keyboard.releaseAll();
    else if(data == 'a') // Mouse.Click (8)
      state = 8;
    else if(data == 's') // Mouse.Press (9)
      state = 9;
    else if(data == 'd') // Mouse.Release (10)
      state = 10;
  }
  else if (state == 1 || state == 4) {
    if(data != '\\') Keyboard.press(data);
    else state = 2;
  } else if (state == 2 || state == 5) {
    if(KMap[data] != 0)
      Keyboard.press(KMap[data]);
    state = state - 1;
  } else if (state == 3)
    Keyboard.write(data);
  else if (state == 6) {
    if(data != '\\') Keyboard.release(data);
    else state = 7;
  } else if (state == 7) {
    if(KMap[data] != 0)
      Keyboard.release(KMap[data]);
    state = state - 1;
  } else if (state == 8) {
    if(data == '1') Mouse.click(MOUSE_LEFT);
    else if (data == '2') Mouse.click(MOUSE_MIDDLE);
    else if (data == '3') Mouse.click(MOUSE_RIGHT);
  } else if (state == 9) {
    if(data == '1') Mouse.press(MOUSE_LEFT);
    else if (data == '2') Mouse.press(MOUSE_MIDDLE);
    else if (data == '3') Mouse.press(MOUSE_RIGHT);
  } else if (state == 10) {
    if(data == '1') Mouse.release(MOUSE_LEFT);
    else if (data == '2') Mouse.release(MOUSE_MIDDLE);
    else if (data == '3') Mouse.release(MOUSE_RIGHT);
  }
}
