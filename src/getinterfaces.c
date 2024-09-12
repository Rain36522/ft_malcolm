
#include "ft_malcolm.h"

static int ft_ip_in_network(const uint32_t srcip, const uint32_t destip, const uint32_t ipnetwork, const uint32_t netmask)
{
	return (((srcip & netmask) == (ipnetwork & netmask)) && ((destip & netmask) == (ipnetwork & netmask)));
}


unsigned int get_interfaces(const char *srcip, const char *dstip)
{
	struct ifaddrs      *ifp;
	struct ifaddrs      *ptr;
	uint32_t            binsrcip = (uint32_t)inet_addr(srcip);
	uint32_t            bindstip = (uint32_t)inet_addr(dstip);
	struct sockaddr_in  *adr;
	struct sockaddr_in  *netmask;
	unsigned int		return_value;

	if (getifaddrs(&ifp) < 0)
		ft_exit("Error while getting interfaces", 1);
	printf("GENERATE INTERFACES\n");
	ptr = ifp;
	while (ifp)
	{
		if (ifp->ifa_addr->sa_family == AF_INET) 
		{
			adr = (struct sockaddr_in *)ifp->ifa_addr;
			netmask = (struct sockaddr_in *)ifp->ifa_netmask;
			if (ft_ip_in_network(binsrcip, bindstip, (uint32_t)adr->sin_addr.s_addr, (uint32_t)netmask->sin_addr.s_addr))
				break;
		}
		ifp = ifp->ifa_next;
	}
	if (!ifp)
	{
		freeifaddrs(ptr);
		return (0);
	}
	DEBUG
	return_value = if_nametoindex(ifp->ifa_name);
	printf("%sFound interface : %s%s%s", BLUE, BOLD, ifp->ifa_name, RESETN);
	freeifaddrs(ptr);
	return (return_value);
}