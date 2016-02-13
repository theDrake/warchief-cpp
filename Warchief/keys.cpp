/******************************************************************************
   Filename: keys.cpp

     Author: Rob Bateman, modified by David C. Drake (http://davidcdrake.com)

Description: Improves on GLUT's handling of keyboard input.
******************************************************************************/

#include "keys.h"

// State of all keys (to know if multiple keys are pressed at any given time):
bool g_keystates[512] = { false };

// Callback functions:
key_func g_upfunc = 0;
key_func g_downfunc = 0;

void setKeyboardFunc(key_func func) {
  g_downfunc = func;
}

void setKeyboardUpFunc(key_func func) {
  g_upfunc = func;
}

bool isKeyPressed(int key) {
  if (key >= 0 && key < 512) {
    return g_keystates[key];
  }

  return false;
}

void keyUpFunc(unsigned char key,int x,int y) {
  g_keystates[key] = false;
  if (g_upfunc) {
    g_upfunc(key, x, y);
  }
}

void keyDownFunc(unsigned char key, int x, int y) {
  g_keystates[key] = true;
  if (g_downfunc) {
    g_downfunc(key, x, y);
  }
}

void specialKeyUpFunc(int key, int x, int y) {
  g_keystates[key + 256] = false;
  if (g_upfunc) {
    g_upfunc(key + 256, x, y);
  }
}

void specialKeyDownFunc(int key, int x, int y) {
  g_keystates[key + 256] = true;
  if (g_downfunc) {
    g_downfunc(key + 256, x, y);
  }
}

void initKeyboard() {
  glutKeyboardFunc(keyDownFunc);
  glutKeyboardUpFunc(keyUpFunc);
  glutSpecialFunc(specialKeyDownFunc);
  glutSpecialUpFunc(specialKeyUpFunc);
}
