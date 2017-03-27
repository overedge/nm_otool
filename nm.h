#ifndef __FT_NM__
# define __FT_NM__

# include "libft/includes/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct	s_env {
	int		ac;
	char	**av;
}				t_env;
#endif
