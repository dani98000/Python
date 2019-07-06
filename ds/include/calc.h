#ifndef _AM_H
#define _AM_H



int AMCreate(char *str);
void OpTableInit();
void AMDestroy();
void AMPushNum(double num);
int AMPushOp(char op);
double AMPushEOS();

#endif
