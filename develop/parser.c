#include "cub3d.h"

int	parser(char *input)
{
	if (input == NULL)
		return (0);
	return (1);
}

static int      charcmp(char c1, char c2)
{
        return ((unsigned char)c1 - (unsigned char)c2);
}

int     ft_strncmp(const char *s1, const char *s2, size_t n)
{
        size_t  i;

        i = 0;
        while (i < n && s1[i] && s2[i])
        {
                if (charcmp(s1[i], s2[i]) != 0)
                        return (charcmp(s1[i], s2[i]));
                i++;
        }
        if (i < n)
                return (charcmp(s1[i], s2[i]));
        return (0);
}

int	check_filename(char *file)
{
	size_t len;

        len = ft_strlen(file);
        if (len < 4)
                return (0);
        if (!(len <= 4 || ft_strncmp(file + len - 4, ".cub", 4) || !ft_strncmp(file + len - 5, "/.cub", 5)))
                return (1);
        return (0);

}
