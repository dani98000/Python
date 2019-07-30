/*******************************************
 **         Author: Mishel Liberman       **
 **         Reviewer: Sasha Limarev       **
 **         Date: 29.07.19                **
 *******************************************/

#include <stdlib.h> /* calloc */
#include <assert.h> /* assert */
#include <math.h> /* pow */

#include "dhcp.h" 

#define OFFSET 1
#define BITS 32

struct dhcp
{
	trie_t *ip_pool;
	ip_t network_addr;
	uint32_t subnet_mask;
};

static enum dhcp_status Init(dhcp_t *dhcp)
{
	int status = OK;

	status = TrieInsert(dhcp->ip_pool, 0x0);

	if (OK == status)
	{
		status = TrieInsert(dhcp->ip_pool, 0xFFFFFFFF);
		if (OK == status)
		{
			return OK;
		}
		else if (M_FAIL == status)
		{
			return E_ALLOC;
		}

		return NO_FREE_ADDR;
	}
	else if (M_FAIL == status)
	{
		return 	E_ALLOC;
	}

	return NO_FREE_ADDR;
}

dhcp_t *DHCPCreate(ip_t network_addr, uint32_t subnet_mask)
{
	uint32_t num_of_bits = 0, i = 0;
	dhcp_t *dhcp = malloc(sizeof(*dhcp));
	if (NULL == dhcp)
	{
		return NULL;
	}

	assert(subnet_mask < 0xFFFFFFFF);

	for (; i < 32; ++i)
	{
		if ((subnet_mask >> i & 0x1) == 1)
		{
			break;
		}

		++num_of_bits;
	}

	dhcp->ip_pool = TrieCreate(num_of_bits);
	if (!dhcp->ip_pool)
	{
		free(dhcp);
		dhcp = NULL;

		return NULL;
	}

	if (OK != Init(dhcp))
	{
		TrieDestroy(dhcp->ip_pool);
		dhcp->ip_pool = NULL;
		free(dhcp);
		dhcp = NULL;

		return NULL;
	}

	dhcp->network_addr = network_addr;
	dhcp->subnet_mask = subnet_mask;

	return dhcp;
}

void DHCPDestroy(dhcp_t *dhcp)
{
	assert(dhcp);

	TrieDestroy(dhcp->ip_pool);
	dhcp->ip_pool = NULL;
	free(dhcp);
	dhcp = NULL;
}

static int IsAskingForAnyIP(ip_t ip_req)
{
	return 0 == CharToIPv(ip_req);
}

enum dhcp_status GetAddress(dhcp_t *dhcp, ip_t ip_req, ip_t *ip_res)
{
	int status = 0;
	uint32_t new_ip = 0;

	assert(dhcp);

	new_ip = CharToIPv(ip_req) & ~dhcp->subnet_mask;

	if (IsAskingForAnyIP(ip_req))
	{
		new_ip = TrieNextFreeIp(dhcp->ip_pool);

		status = TrieInsert(dhcp->ip_pool, new_ip);

		if (FAILURE == status)
		{
			return NO_FREE_ADDR;
		}
		else if (M_FAIL == status)
		{
			return E_ALLOC;
		}
		*ip_res = IPvToChar((CharToIPv(dhcp->network_addr) | new_ip));

		return ADDR_TAKEN;
	}

	status = TrieInsert(dhcp->ip_pool, new_ip);

	if (FAILURE == status)
	{
		new_ip = TrieNextFreeIp(dhcp->ip_pool);
		status = TrieInsert(dhcp->ip_pool, new_ip);

		if (FAILURE == status)
		{
			return NO_FREE_ADDR;
		}
		else if (M_FAIL == status)
		{
			return E_ALLOC;
		}

		*ip_res = IPvToChar((CharToIPv(dhcp->network_addr) | new_ip));

		return ADDR_TAKEN;
	}
	else if (M_FAIL == status)
	{
		return E_ALLOC;
	}

	*ip_res = IPvToChar((CharToIPv(dhcp->network_addr) | new_ip)); 

	return OK;
}

int FreeAddr(dhcp_t *dhcp, ip_t ip_addr)
{
	assert(dhcp);

	if ((CharToIPv(ip_addr) | dhcp->subnet_mask) == dhcp->subnet_mask)
	{
		return FAILURE;
	}

	return TrieRemove(dhcp->ip_pool, CharToIPv(ip_addr));
}

size_t DHCPCountFree(const dhcp_t *dhcp)
{
	assert(dhcp);

	return pow(2, TrieNumOfBits(dhcp->ip_pool)) - TrieCount(dhcp->ip_pool);
}
