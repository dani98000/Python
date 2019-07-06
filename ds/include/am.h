#ifndef _AM_H
#define _AM_H

typedef int (*handler_func)(double num1, double num2);

int AMCreate(char *str);
void OpTableInit();
void AMDestroy();
void AMPushNum(double num);
int AMPushOp(char op);
int AMPushEOS();

#endif
