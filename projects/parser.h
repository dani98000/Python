#ifndef _PARS_H
#define _PARS_H

#include "am.h"

enum status
{
	OK = 0,
	E_MATH,
	E_SYNTAX,
	E_MALLOC
};

void TransTableInit();
int Calculate(char *str, double *result);

#endif
