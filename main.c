#include "SHELL.H"
/**
* main - main function
* Description:- using the main function
* @av: arguments vector
* @ac: arguments count
*
* Return: 0 on success,1 on error
*/
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int g = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (g)
			: "r" (g));

	if (ac == 2)
	{
		g = open(av[1], O_RDONLY);
		if (g == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				puts(av[0]);
				puts(": 0: Can't open ");
				puts(av[1]);
				putchar('\n');
				putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readg = g;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
