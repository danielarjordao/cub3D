# include "../../includes/cub3d.h"

int	msg_error(t_error err, int ret)
{
	ft_printf(2, "Error\n");
	if (err == W_NBR_ARGS)
		ft_printf(2, "Wrong number of arguments\n");
	else if (err == W_EXTENSION)
		ft_printf(2, "Wrong file extension\n");
	return (ret);
}
