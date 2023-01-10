#include "libft.h"

int	ft_export_isalnum(const char *s)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(s))
	{
		if ((!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && \
					s[i] != '_' && s[i] != '=' && s[i] != '+'))
			return (0);
		if (s[i] == '+' && s[i + 1] != '=')
			return (0);
		if (s[i] == '+' && s[i + 1] == '=' && !s[i + 2])
			return (0);
		i++;
	}
	return (1);
}
