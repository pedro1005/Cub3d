#include "cub3d.h"
#include <sys/time.h>

void	ft_sleep(unsigned int mlseconds)
{
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&current, NULL);
		if (((current.tv_sec - start.tv_sec) * 1000
				+ (current.tv_usec - start.tv_usec) / 1000) >= mlseconds)
			break ;
	}
}
