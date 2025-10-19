#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	i = 0;
	dest_len = 0;
	src_len = ft_strlen(src);
	while (dest_len < n && dest[dest_len])
		dest_len++;
	if (dest_len == n)
		return (n + src_len);
	while ((dest_len + i + 1) < n && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (dest_len + i < n)
		dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
