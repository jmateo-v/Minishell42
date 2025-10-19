#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*finder;

	finder = NULL;
	while (*str != '\0')
	{
		if (*str == (char)c)
			finder = str;
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return ((char *)finder);
}
