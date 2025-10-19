#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*sweeper;

	sweeper = (unsigned char *)s;
	while (n > 0)
	{
		if (*sweeper == (unsigned char)c)
			return ((void *)sweeper);
		sweeper++;
		n--;
	}
	return (NULL);
}
