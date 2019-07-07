#ifndef CALCULATOR_H
#define CALCULATOR_H

enum status {OK, E_MATH, E_SYNTAX, E_MALLOC};

enum status Calculate(const char *str, double *result);

#endif
