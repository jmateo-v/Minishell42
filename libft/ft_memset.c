#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*sweeper;

	sweeper = (unsigned char *)s;
	while (n > 0)
	{
		*sweeper = (unsigned char)c;
		sweeper++;
		n--;
	}
	return (s);
}
