/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pudry <pudry@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:50:15 by pudry             #+#    #+#             */
/*   Updated: 2024/08/27 10:50:15 by pudry            ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <errno.h>
#include <signal.h>
#include "libft.h"
#include <net/if.h>
#include <netinet/ip.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <netinet/if_ether.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <net/if_arp.h>




#define RESET   "\033[0m"
#define RESETN  "\033[0m\n"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"
#define ORANGE  "\033[38;5;208m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"      
#define WHITE   "\033[37m"
#define	HBLUE	"\033[48;5;17m"
#define HRED	"\033[41m"
#define BOLD	"\033[1m"
#define NOBOLD	"\033[0m"
#define DEBUG printf("\033[31m %s, %d, %s", __FILE__, __LINE__, "\033[0m\n");

extern int socketfd;

void			ft_parsing(int argc, char **argv);
void 			ft_exit(char *str, int icode);
void       		ft_exit_fd(char *str, int icode, int fd);
void			ft_free_array(char **a);
void			sig_handler(int sig);

unsigned int	get_interfaces(const char *srcip, const char *dstip);

void    		readpacket(const char *str_srcip, const char *str_dstip);

void			ft_malcolm(char *srcip, char *srcmac, char *dstip, char *dstmac, const int interface);