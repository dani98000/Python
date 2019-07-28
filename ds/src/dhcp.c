#include <stdint.h> /* uint32_t */
#include <stdlib.h>
#include <assert.h>

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
	int i = 0;
	uint32_t net = IPIpv4ToNum(network_addr);

	assert((net & subnet_mask) == net);

	dhcp_t *dhcp = (dhcp_t *)malloc(sizeof(*dhcp));
	if(NULL == dhcp)
	{
		return NULL;
	}

	while(((0x1 << i) & subnet_mask) == 0)
	{
		++i;
	}

	num_of_bits = i;

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
	uint32_t res;
	uint32_t net = 0X00;/*IPIpv4ToNum(dhcp->network_addr)*/;
	/*printf("net%x\n",net);*/
	uint32_t bro = 0XFF;/*(~(dhcp->subnet_mask) & net);*/
		/*printf("bro%x\n",bro);*/

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

/* undefined behavior for NULL parameter,
user is assumed to have passed ip_req of the correct subnet */
enum status GetAddress(dhcp_t *dhcp, ip_t ip_req, ip_t *ip_res)
{
	assert(dhcp);

	uint32_t network_addr = IPIpv4ToNum(dhcp->network_addr);
	uint32_t wanted_ip = IPIpv4ToNum(ip_req);
	uint32_t data = (wanted_ip ^ network_addr);
	uint32_t given_ip = 0;
	enum status status = OK;

	status = BTInsert(dhcp->ip_pool, data, &given_ip);

	if(ADDR_TAKEN != status || status != E_ALLOC)
	{
		*ip_res = IPNumToIpv4(given_ip | network_addr);
	}

	return status;
}

/* undefined behavior for NULL parameter,
return status: 0 if found and removed IP */
int FreeAddr(dhcp_t *dhcp, ip_t ip_addr)
{
	assert(dhcp);
	uint32_t ip = IPIpv4ToNum(ip_addr);

	return BTRemove(dhcp->ip_pool, ip);
}

/* undefined behavior for NULL parameter */
size_t DHCPCountFree(const dhcp_t *dhcp)
{
	assert(dhcp);

	return(BTCountFree(dhcp->ip_pool));
}
