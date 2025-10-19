#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*sweeper;
	const unsigned char	*buffer;

	sweeper = (unsigned char *)dest;
	buffer = (const unsigned char *)src;
	while (n > 0)
	{
		*sweeper = *buffer;
		sweeper++;
		buffer++;
		n--;
	}
	return (dest);
}
