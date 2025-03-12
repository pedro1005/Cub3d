#include "cub3d.h"

int	ft_clean(char *str)
{
	int	i;
	int	j;
	int	is_nwl;

	i = 0;
	j = 0;
	is_nwl = 0;
	while (str[i])
	{
		if (is_nwl)
			str[j++] = str[i];
		if (str[i] == '\n')
			is_nwl = 1;
		str[i] = '\0';
		i++;
	}
	return (is_nwl);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		v;
	char	*str_to_return;

	i = 0;
	v = 0;
	str_to_return = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str_to_return)
		return (NULL);
	while (s1 && s1[v])
		str_to_return[i++] = s1[v++];
	v = 0;
	while (s2 && s2[v])
	{
		str_to_return[i] = s2[v++];
		if (str_to_return[i++] == '\n')
			break ;
	}
	str_to_return[i] = '\0';
	free (s1);
	return (str_to_return);
}

char	*get_next_line(int fd)
{
	static char	files_array[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || FOPEN_MAX < fd)
		return (NULL);
	line = NULL; 
	while (files_array[fd][0] || read(fd, files_array[fd], BUFFER_SIZE) > 0)
	{
		line = ft_strjoin(line, files_array[fd]);
		if (ft_strlen(files_array[fd]) == 0)
			return (line);
		if (ft_clean(files_array[fd]) == 1)
			break ;
		if (read(fd, files_array[fd], BUFFER_SIZE) < 0)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}
