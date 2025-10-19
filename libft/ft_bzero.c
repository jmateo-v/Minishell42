#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*sweeper;

	sweeper = (unsigned char *)s;
	while (n > 0)
	{
		*sweeper = 0;
		sweeper++;
		n--;
	}
}
