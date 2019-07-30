/******************************************
*                _____  __     _   ___    *
*               (  _  )(  )   / ) / _ \   *
*    |\---/|     )(_)(  )(__ / _ \_  /   *
*    | ,_, |    (_____)(____)\___/ (_/    *
*     \_`_/-..----.                       *
*  ___/ `   ' ,""+ \                      *
* (__...'   __\    |`.___.';              *
*  (_,...'(_,.`__)/'.....+                *
*                                         *
*             Exersice: IP                *
******************************************/
#include <math.h> /* pow */

#include "ip.h" 

#define OFFSET 1

uint32_t CharToIPv(ip_t IP)
{
	int i = 0;
	uint32_t ip = 0;

	for (; i < IPV; ++i)
	{
		ip += (uint32_t)(IP.ip_addr[i]) * pow(256, (IPV - OFFSET - i)); 
	}
	
	return ip;
}

ip_t IPvToChar(uint32_t biip)
{
	ip_t ip = {0};
	int i = 0;

	for (i = IPV - 1; i >= 0; --i)
	{
		ip.ip_addr[i] = (char)biip;
		biip >>= 8;
	}

	return ip;
}