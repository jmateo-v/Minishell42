#include <stdio.h>
#include "minishell.h"

int	main(int argc, char **argv)
{
	char **matches;
	int i;
	if (argc != 2)
	{
		printf("Uso: %s <patron_wildcard>\n", argv[0]);
		return 1;
	}
	matches = expand_wildcards(argv[1]);
	if (!matches)
	{
		printf("No hay coincidencias o error de memoria.\n");
		return 1;
	}
	i = 0;
	while (matches[i])
	{
		printf("%s ", matches[i]);
		i++;
	}
	printf("\n");
	free_wildcard_matches(matches);
	return 0;
}
