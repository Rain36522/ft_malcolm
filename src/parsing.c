
#include "ft_malcolm.h"


static void	ft_check_mac_char(char  *mac, int pos)
{
	for (int i = 0; mac[i]; i ++)
	{
		mac[i] = ft_toupper((int)mac[i]);
		if (((i + 1) % 3 == 0 && mac[i] != ':') || ((i + 1) % 3 && mac[i] == ':'))
		{
			if (pos == 1)
				ft_exit("The char \":\" is at the wrong position or is missing in the source mac address!", 1);
			else
				ft_exit("The char \":\" is at the wrong position or is missing in the dest mac address!", 1);
		}

		else if (!ft_strchr("0123456789ABCDEF:", mac[i]))
		{
			if (pos == 1)
				ft_exit("Unknow char on source mac address!", 1);
			else
				ft_exit("Unknow char on dest mac address!", 1);
		}
	}
	printf(GREEN);
	if (pos == 1)
		printf("Source mac address is valide!");
	else
		printf("Target mac address is valide!");
	printf(RESETN);
}



static void	ft_check_mac(char *mac, int pos)
{
	if (ft_strlen(mac) != 17)
	{
		if (pos == 1)
			ft_exit("Wrong len for source mac address!", 1);
		else
			ft_exit("Wrong len for dest mac address!", 1);
	}
	ft_check_mac_char(mac, pos);
}

static void	ft_check_ip_char(char *ip, int pos)
{
	int	j = 0;
	int	k = 0;
	int	wrong_pos = 0;

	if (ip[0] == '.' || ip[ft_strlen(ip) - 1] =='.')
		wrong_pos = 1;

	for (size_t i = 0; i < ft_strlen(ip) && !wrong_pos; i ++)
	{
		if (ip[i] == '.')
		{
			k ++;
			if (j == 0 || j > 3)
				wrong_pos = 1;
			j = 0;
		}
		else if (!ft_isdigit(ip[i]))
		{
			if (pos == 1)
				ft_exit("Wrong character in source ip address!", 1);
			else
				ft_exit("Wrong character in dest ip address!", 1);
		}
		else
			j++;
	}
	if (wrong_pos || j > 3 || k != 3)
	{
		if (pos == 1)
			ft_exit("Wrong quantity or position for \".\"in source ip address!", 1);
		else
			ft_exit("Wrong quantity or position for \".\"in dest ip address!", 1);

	}
}

static void	ft_check_ip(char *ip, int pos)
{
	if (ft_strlen(ip) < 7 || ft_strlen(ip) > 15)
	{
		if (pos == 1)
			ft_exit("Wrong len for source ip address!", 1);
		else
			ft_exit("Wrong len for dest ip address!", 1);
	}
	ft_check_ip_char(ip, pos);
}

static void	ft_get_ip(char *ip, int pos)
{
	char	**a;
	int		itmp;
	int		ierror = 0;

	if (!(a = ft_split(ip, '.')))
		ft_exit("Error alocating memory", 12);
	for (size_t i = 0; a[i] && !ierror; i ++)
	{
		if ((itmp = ft_atoi(a[i])) > 255)
			ierror = 1;
	}
	ft_free_array(a);
	if (ierror)
	{
		if (pos == 1)
			ft_exit("Source ip address as a to big value!", 1);
		else
			ft_exit("Dest ip address as a to big value!", 1);
	}
}

void	ft_parsing(int argc, char **argv)
{
	if (argc != 5)
		ft_exit("Wrong argument number, try \033[34m./ft_malcolm --help", 1);	
	ft_check_mac(argv[2], 1);
	ft_check_mac(argv[4], 2);
	ft_check_ip(argv[1], 1);
	ft_check_ip(argv[3], 2);
	ft_get_ip(argv[1], 1);
	printf("%sSource ip address is valide!%s", GREEN, RESETN);
	ft_get_ip(argv[3], 2);
	printf("%sTarget ip address is valide!%s", GREEN, RESETN);
}