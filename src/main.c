#include "ft_malcolm.h"

int socketfd;

void ft_print_help()
{
	printf("This program is for doing an attack man in the middle!\n");
	printf("For executing the programme you need to use this commande:\n");
	printf("%s./ft_malcolm source_ip source_mac dest_ip dest_mac\n", BOLD);
	printf("./ft_malcolm xxx.xxx.xxx.xxx xx:xx:xx:xx:xx:xx xxx.xxx.xxx.xxx xx:xx:xx:xx:xx:xx\n%s", RESETN);
	exit(0);
}

void    setup_signal()
{
    struct sigaction sa;

    sa.sa_handler = sig_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1)
        ft_exit("Error setting up signal handler!", 1);
}


int	main(int arc, char **arv)
{
	int indexinterface;

	if (arc == 2 && !ft_strcmp(arv[1], "--help"))
		ft_print_help();
	else if (getuid() != 0)
		ft_exit("The programme must be run as root! Try ./ft_malcolm --help", 13);
	ft_parsing(arc, arv);
	indexinterface = get_interfaces(arv[1], arv[3]);
	if (!indexinterface)
		ft_exit("No interface match with the ip address!\n", 1);
    setup_signal();
	ft_malcolm(arv[1], arv[2], arv[3], arv[4], indexinterface);
	return (0);
}