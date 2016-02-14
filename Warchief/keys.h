/******************************************************************************
   Filename: keys.h

     Author: Rob Bateman, modified by David C. Drake (http://davidcdrake.com)

Description: Improves on GLUT's handling of keyboard input.
******************************************************************************/

#ifndef KEYS_H_
#define KEYS_H_

#include <cstdlib>
#include "glut.h"

#define KEY_F1 (GLUT_KEY_F1 + 256)
#define KEY_F2 (GLUT_KEY_F2 + 256)
#define KEY_F3 (GLUT_KEY_F3 + 256)
#define KEY_F4 (GLUT_KEY_F4 + 256)
#define KEY_F5 (GLUT_KEY_F5 + 256)
#define KEY_F6 (GLUT_KEY_F6 + 256)
#define KEY_F7 (GLUT_KEY_F7 + 256)
#define KEY_F8 (GLUT_KEY_F8 + 256)
#define KEY_F9 (GLUT_KEY_F9 + 256)
#define KEY_F10 (GLUT_KEY_F10 + 256)
#define KEY_F11 (GLUT_KEY_F11 + 256)
#define KEY_F12 (GLUT_KEY_F12 + 256)
#define KEY_LEFT (GLUT_KEY_LEFT + 256)
#define KEY_UP (GLUT_KEY_UP + 256)
#define KEY_RIGHT (GLUT_KEY_RIGHT + 256)
#define KEY_DOWN (GLUT_KEY_DOWN + 256)
#define KEY_PAGE_UP (GLUT_KEY_PAGE_UP + 256)
#define KEY_PAGE_DOWN (GLUT_KEY_PAGE_DOWN + 256)
#define KEY_HOME (GLUT_KEY_HOME + 256)
#define KEY_END (GLUT_KEY_END + 256)
#define KEY_INSERT (GLUT_KEY_INSERT + 256)
#define KEY_CONSOLE '`'
#define KEY_TAB 9
#define KEY_BACKSPACE 8
#define KEY_DELETE 127
#define KEY_SPACE ' '
#define KEY_ENTER 13
#define KEY_ESCAPE 27

typedef void (*key_func) (int, int, int);

bool isKeyPressed(int key);
void initKeyboard();
void setKeyboardFunc(key_func);
void setKeyboardUpFunc(key_func);

#endif  // KEYS_H_
