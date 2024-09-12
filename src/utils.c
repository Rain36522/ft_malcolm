
#include "ft_malcolm.h"

void	sig_handler(int sig)
{
	if (sig == 2)
        ft_exit_fd("User exit !", 1, socketfd);
}

void ft_exit(char *str, int icode)
{
	char	buffer[200];
	if (icode > 0)
		sprintf(buffer, "%s%s%s", RED, str, RESETN);
	else
		sprintf(buffer, "%s%s%s", GREEN, str, RESETN);
	ft_putstr_fd(buffer, 2);
	exit(icode);
}

void ft_exit_fd(char *str, int icode, int fd)
{
	char	buffer[200];

	if (fd > 0)
		close(fd);
	if (icode > 0)
		sprintf(buffer, "%s%s%s", RED, str, RESETN);
	else
		sprintf(buffer, "%s%s%s", GREEN, str, RESETN);
	ft_putstr_fd(buffer, 2);
	exit(icode);
}


void	ft_free_array(char **a)
{
	for (int i = 0; a[i]; i ++)
		free(a[i]);
	free(a);
}