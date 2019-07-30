/******************************************
*                _____  __     _   ___    *
*               (  _  )(  )   / ) / _ \   *
*    |\---/|     )(_)(  )(__ / _ \\_  /   *
*    | ,_, |    (_____)(____)\___/ (_/    *
*     \_`_/-..----.                       *
*  ___/ `   ' ,""+ \                      *
* (__...'   __\    |`.___.';              *
*  (_,...'(_,.`__)/'.....+                *
*                                         *
*             Exercise: DHCP              *
******************************************/
#ifndef OL69_IP_H
#define OL69_IP_H

#include <stdint.h> /* uint32_t */

#define IPV (4) /* implementation of 4 byte IP address space */

typedef struct
{
	unsigned char ip_addr[IPV];
} ip_t;

/* converts struct ip to uint32 type */
uint32_t CharToIPv(ip_t IP);

/* converts from uint32_t to struct ip */
ip_t IPvToChar(uint32_t IP);

#endif /* OL69_IP_H */
