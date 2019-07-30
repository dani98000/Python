/******************************************
*                _____  __     _   ___    *
*               (  _  )(  )   / ) / _ \   *
*    |\---/|     )(_)(  )(__ / _ \\_  /   *
*    | ,_, |    (_____)(____)\___/ (_/    *
*     \_`_/-..----.                       *
*  ___/ `   ' ,""+ \                      *
* (__...'   __\    |`.___.';              *
*  (_,...'(_,.`__)/'.....+                *
*            *********************        *
*            -Exersice: DHCP  	  		  *
*			 -Name: Daniel Maizel         *
*			 -Reviewer: Roi 	          *
******************************************/
#include <stdint.h> /* uint32_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "dhcp.h"
#include "bt.h"
#include "ip.h"

struct dhcp
{
	bt_t *ip_pool;
	ip_t network_addr;
	uint32_t subnet_mask;
};

static enum status PoolInit(dhcp_t *dhcp);

dhcp_t *DHCPCreate(ip_t network_addr, uint32_t subnet_mask)
{
	int num_of_bits = 0;
	uint32_t net = IPIpv4ToNum(network_addr);
	dhcp_t *dhcp = NULL;

	assert((net & subnet_mask) == net);

	dhcp = (dhcp_t *)malloc(sizeof(*dhcp));
	if(NULL == dhcp)
	{
		return NULL;
	}

	while(((0x1 << num_of_bits) & subnet_mask) == 0)
	{
		++num_of_bits;
	}

	dhcp->ip_pool = BTCreate(num_of_bits);
	if(NULL == dhcp->ip_pool)
	{
		free(dhcp);
		dhcp = NULL;

		return NULL;
	}

	dhcp->network_addr = network_addr;
	dhcp->subnet_mask = subnet_mask;

	if (PoolInit(dhcp) != OK)
	{
		 DHCPDestroy(dhcp);

		 return NULL;
	}

	return dhcp;
}

static enum status PoolInit(dhcp_t *dhcp)
{
	uint32_t net = 0X0;
	uint32_t bro = ~0X0;		

	enum status status = OK;

	status = BTInsert(dhcp->ip_pool, bro, &bro);
	if(status!=OK)
	{
		return status;
	}

	status = BTInsert(dhcp->ip_pool, net, &net);
	if(status!=OK)
	{
		return status;
	}

	return OK;
}

/* undefined behavior for NULL parameter */
void DHCPDestroy(dhcp_t *dhcp)
{
	assert(dhcp);

	BTDestroy(dhcp->ip_pool);
	dhcp->ip_pool = NULL;

	free(dhcp);
	dhcp = NULL;
}

enum status GetAddress(dhcp_t *dhcp, ip_t ip_req, ip_t *ip_res)
{
	uint32_t network_addr = 0;
	uint32_t data = 0;
	uint32_t given_ip = 0;
	uint32_t wanted_ip = IPIpv4ToNum(ip_req);

	enum status status = OK;

	assert(dhcp);

	network_addr = IPIpv4ToNum(dhcp->network_addr);
	data = (wanted_ip ^ network_addr);

	status = BTInsert(dhcp->ip_pool, data, &given_ip);

	if(NO_FREE_ADDR != status || status != E_ALLOC)
	{
		*ip_res = IPNumToIpv4(given_ip | network_addr);
	}

	return status;
}

int FreeAddr(dhcp_t *dhcp, ip_t ip_addr)
{
	uint32_t ip = IPIpv4ToNum(ip_addr);
	
	assert(dhcp);

	return BTRemove(dhcp->ip_pool, ip);
}

size_t DHCPCountFree(const dhcp_t *dhcp)
{
	assert(dhcp);

	return(BTCountFree(dhcp->ip_pool));
}
