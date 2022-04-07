#include "includes.h"

int main(int ac, char **av) {
	if ((ac != 2 && ac != 3) || !ft_isdigit(av[1]) || !ft_isdigit(av[2]))
		exit(printf("Usage : ./demineur (number of rows & columns > 0) (number of bombs > 0)"));

	data d;
	init_data(&d, av);
	generateBombs(&d);
	generateHints(&d);
	generateMlx(&d);
	generateDisplay(&d);

	mlx_hook(d.win, 17, 0, kill_program, &d);
	mlx_mouse_hook(d.win, controller, &d);
	mlx_key_hook(d.win, escape_or_not, &d);
	mlx_loop(d.mlx_ptr);

	printTable(&d);
}
