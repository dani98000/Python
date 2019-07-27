

/*typedef struct
{
	unsigned char ip_addr[IPV];
} ip_t;*/
#include "ip.h"

ip_t IPNumToIpv4(uint32_t ip_num)
{
	ip_t ip;
	ip ==={  
		{
			(char)(ip_num >> 24),
			(char)((ip_num << 8) >> 24),
			(char)((ip_num << 16) >> 24),
			(char)((ip_num << 24) >> 24)
		};
	};


	return ip;
}

uint32_t IPIpv4ToNum(ip_t ip)
{
	uint32_t ip_num = 0;

	ip_num |= ((uint32_t)ip.ip_addr[0]) << 24;
	ip_num |= ((uint32_t)ip.ip_addr[1]) << 16;
	ip_num |= ((uint32_t)ip.ip_addr[2]) << 8;
	ip_num |= ((uint32_t)ip.ip_addr[3]);

	return ip_num;
}
