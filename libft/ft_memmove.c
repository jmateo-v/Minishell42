#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*sweeper;
	const unsigned char	*buffer;

	sweeper = (unsigned char *)dest;
	buffer = (const unsigned char *)src;
	if (sweeper + n <= buffer || buffer + n <= sweeper)
	{
		while (n > 0)
		{
			*sweeper = *buffer;
			sweeper++;
			buffer++;
			n--;
		}
	}
	else
	{
		while (n > 0)
		{
			n--;
			*(sweeper + n) = *(buffer + n);
		}
	}
	return (dest);
}
