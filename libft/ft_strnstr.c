#include "libft.h"

char	*ft_strnstr(const char *haystk, const char *ndl, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*ndl)
		return ((char *)haystk);
	while (haystk[i] != '\0' && i < len)
	{
		j = 0;
		while (haystk[i + j] == ndl[j] && (i + j) < len)
		{
			j++;
			if (ndl[j] == '\0')
				return ((char *)(haystk + i));
		}
		i++;
	}
	return (NULL);
}
