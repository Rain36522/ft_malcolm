
#include "ft_malcolm.h"

static int ft_check_arp_data(unsigned char *buffer, const char *strsrcip, uint32_t srcip, const char *strdstip, uint32_t dstip)
{
    struct ether_arp    *arp;
    struct ethhdr       *eth;
    char                ipa[20];
    char                ipb[20];

    eth = (struct ethhdr *) buffer;
    if (ntohs(eth->h_proto) != ETH_P_ARP)
        return (0);
    arp = (struct ether_arp *)(buffer + sizeof(struct ethhdr));
    if (ntohs(arp->ea_hdr.ar_op) != ARPOP_REQUEST)
        return (0);
    if (ft_memcmp(arp->arp_tpa, &dstip, sizeof(struct in_addr)) == 0)
    {
        if (ft_memcmp(arp->arp_spa, &srcip, sizeof(struct in_addr)) == 0)
        {
            printf("%sARP request from %s, asking for %s%s", GREEN, strdstip, strsrcip, RESETN);
            return (1);
        }
    }
    inet_ntop(AF_INET, arp->arp_tpa, ipa, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, arp->arp_spa, ipb, INET_ADDRSTRLEN);
    printf("%sARP request from %s, asking for %s%s", BLUE, ipa, ipb, RESETN);
    return (0);
}

void    readpacket(const char *str_srcip, const char *str_dstip)
{
    ssize_t         readvalue;
    unsigned char   buffer[65536];
    struct sockaddr saddr;
    socklen_t       saddr_len;
    uint32_t        srcip;
    uint32_t        dstip;

    inet_pton(AF_INET, str_srcip, &srcip);
    inet_pton(AF_INET, str_dstip, &dstip);

    saddr_len = sizeof(saddr);
    while (1)
    {
        readvalue = recvfrom(socketfd, buffer, sizeof(buffer), 0, &saddr, &saddr_len);
        if (readvalue < 0)
            ft_exit_fd("Error while reading packets!", 1, socketfd);
        if (ft_check_arp_data(buffer, str_srcip, srcip, str_dstip, dstip))
            break;
    }
}

