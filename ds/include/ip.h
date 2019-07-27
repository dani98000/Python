#ifndef OL69_IP_H
#define OL69_IP_H

#include <stdint.h> /* uint32_t */

#include "dhcp.h" /* ip_t */

ip_t IPNumToIpv4(uint32_t ip_num);

uint32_t IPIpv4ToNum(ip_t ip);

#endif /* OL69_IP_H */
