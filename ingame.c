#include "includes.h"

void open_zero(data *d, int i, int j) {
	if (d->table[i][j].value == 0 && d->table[i][j].is_opened == false) {
		d->table[i][j].is_opened = true;
		if (i > 0) {
			open_zero(d, i-1, j);
			d->table[i-1][j].is_opened = true;
		}
		if (j > 0) {
			open_zero(d, i, j-1);
			d->table[i][j-1].is_opened = true;
		}
		if (i < d->rows-1) {
			open_zero(d, i+1, j);
			d->table[i+1][j].is_opened = true;
		}
		if (j < d->rows-1) {
			open_zero(d, i, j+1);
			d->table[i][j+1].is_opened = true;
		}
	}
}

void open_bombs(data *d) {

	int i = 0;
	int j = 0;
	while (i < d->rows) {
		j = 0;
		while (j < d->rows) {
			if (d->table[i][j].value == -1)
				d->table[i][j].is_opened = true;
			j++;
		}
		i++;
	}
}

void check_for_win(data *d) {

	for (int i = 0; i < d->rows; i++) {
		for (int j = 0; j < d->rows; j++) {
			if (d->table[i][j].value != -1 && !d->table[i][j].is_opened)
				return ;
		}
	}
	mlx_string_put(d->mlx_ptr, d->win, 10, d->rows*SIZE, 255255255, "gg jgl diff");
	d->can_i_play = false;
}

int escape_or_not(int key, data *d) {
	if (key == 53)
		kill_program(d);
	return 0;
}

int kill_program(data *d) {
	int i = 0;
	while (i < d->rows) {
		free(d->table[i]);
		i++;
	}
	free(d->table);
	mlx_destroy_window(d->mlx_ptr, d->win);
	exit(0);
}

void left_click(data *d, int x, int y) {
	int i = y/SIZE, j = x/SIZE;

	if (d->table[i][j].is_opened == false && d->table[i][j].is_flagged == false) {

		if (d->table[i][j].value == 0)
			open_zero(d, i, j);
		else if (d->table[i][j].value == -1) {
			open_bombs(d);
			generateDisplay(d);
			mlx_string_put(d->mlx_ptr, d->win, 10, d->rows*SIZE, 255255255, "t'es eclate frr");
			d->can_i_play = false;
		} else
			d->table[i][j].is_opened = true;

		check_for_win(d);
		generateDisplay(d);
	}
}

void right_click(data *d, int x, int y) {
	int i = y/SIZE, j = x/SIZE;

	if (d->table[i][j].is_opened == false) {
		if (d->table[i][j].is_flagged)
			d->table[i][j].is_flagged = false;
		else {
			d->table[i][j].is_flagged = true;
		}
		generateDisplay(d);
	}
}

int controller(int button, int x, int y, data *d) { // 1 = clic gauche, 2 = clic droit
	if (!d->can_i_play)
		return 0;
	
	if (button == 1)
		left_click(d, x, y);
	else if (button == 2)
		right_click(d, x, y);
	return 0;
}