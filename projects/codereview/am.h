#ifndef AM_H
#define AM_H

#include <stdlib.h>
#include "calculator.h"

enum status AMCreate(size_t len);
void AMDestroy();
enum status PushOp(char op);
enum status PusnNum(double num);
enum status EOS();
enum status Parentheses(char op);

#endif
