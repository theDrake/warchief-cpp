/*******************************************************************************
   Filename: keys.cc

     Author: Rob Bateman, modified by David C. Drake (https://davidcdrake.com)

Description: Improves on GLUT's handling of keyboard input.
*******************************************************************************/

#include "keys.h"

bool g_key_states[512] = { false };

key_function g_key_up_function = 0;
key_function g_key_down_function = 0;

void SetKeyboardFunc(key_function func) {
  g_key_down_function = func;
}

void SetKeyboardUpFunc(key_function func) {
  g_key_up_function = func;
}

bool IsKeyPressed(int key) {
  if (key >= 0 && key < 512) {
    return g_key_states[key];
  }

  return false;
}

void KeyUpFunc(unsigned char key,int x,int y) {
  g_key_states[key] = false;
  if (g_key_up_function) {
    g_key_up_function(key, x, y);
  }
}

void KeyDownFunc(unsigned char key, int x, int y) {
  g_key_states[key] = true;
  if (g_key_down_function) {
    g_key_down_function(key, x, y);
  }
}

void SpecialKeyUpFunc(int key, int x, int y) {
  g_key_states[key + 256] = false;
  if (g_key_up_function) {
    g_key_up_function(key + 256, x, y);
  }
}

void SpecialKeyDownFunc(int key, int x, int y) {
  g_key_states[key + 256] = true;
  if (g_key_down_function) {
    g_key_down_function(key + 256, x, y);
  }
}

void InitKeyboard() {
  glutKeyboardFunc(KeyDownFunc);
  glutKeyboardUpFunc(KeyUpFunc);
  glutSpecialFunc(SpecialKeyDownFunc);
  glutSpecialUpFunc(SpecialKeyUpFunc);
}
