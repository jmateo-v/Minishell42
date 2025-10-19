#include "libft.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	if(!c)
		return(0);
	i = 0;
	while (c[i] != '\0')
	{
		i++;
	}
	return (i);
}
