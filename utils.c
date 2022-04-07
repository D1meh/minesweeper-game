#include "includes.h"

bool ft_isdigit(char *s) {
	int i = 0;
	while (s[i]) {
		if (s[i] < '0' || s[i] > '9')
			return false;
		i++;
	}
	return true;
}

void init_data(data *d, char **av) {
	d->can_i_play = true;
	d->rows = atoi(av[1]);
	d->bombs = atoi(av[2]);
	d->flags = atoi(av[2]);
	
	d->table = calloc(d->rows, sizeof(Case*));
	for (int i = 0; i < d->rows; i++) {
		d->table[i] = calloc(d->rows, sizeof(Case));
		for (int j = 0; j < d->rows; j++) {
			d->table[i][j].value = 0;
			d->table[i][j].is_flagged = false;
			d->table[i][j].is_opened = false;
		}
	}
}

void generateBombs(data *d) {
	srand(time(NULL));
	int bombs = d->bombs;

	while (bombs) {
		int i = rand() % d->rows;
		int j = rand() % d->rows;
		if (d->table[i][j].value != -1) {
			d->table[i][j].value = -1;
			bombs--;
		}
	}
}

void generateHints(data *d) {
	int i = 0, j = 0, count = 0;

	while (i < d->rows) {

		j = 0;
		while (j < d->rows) {

			if (d->table[i][j].value == -1) {
				j++;
				continue ;
			}

			count = 0;
			if (i > 0 && d->table[i-1][j].value == -1)
				count++;
			if (i < d->rows-1 && d->table[i+1][j].value == -1)
				count++;
			if (j > 0 && d->table[i][j-1].value == -1)
				count++;
			if (j < d->rows-1 && d->table[i][j+1].value == -1)
				count++;
			if (i > 0 && j > 0 && d->table[i-1][j-1].value == -1)
				count++;
			if (i > 0 && j < d->rows-1 && d->table[i-1][j+1].value == -1)
				count++;
			if (i < d->rows-1 && j > 0 && d->table[i+1][j-1].value == -1)
				count++;
			if (i < d->rows-1 && j < d->rows-1 && d->table[i+1][j+1].value == -1)
				count++;
			
			d->table[i][j].value = count;
			j++;
		}
		i++;
	}
}

void generateMlx(data *d) {
	int height, width;

	d->mlx_ptr = mlx_init();

	d->closed = mlx_xpm_file_to_image(d->mlx_ptr, (char*)"./images/closed.xpm", &width, &height);
	d->op_1 = mlx_xpm_file_to_image(d->mlx_ptr, (char*)"./images/1.xpm", &width, &height);
	d->op_2 = mlx_xpm_file_to_image(d->mlx_ptr, (char*)"./images/2.xpm", &width, &height);
	d->op_3 = mlx_xpm_file_to_image(d->mlx_ptr, (char*)"./images/3.xpm", &width, &height);
	d->op_4 = mlx_xpm_file_to_image(d->mlx_ptr, (char*)"./images/4.xpm", &width, &height);
	d->op_5 = mlx_xpm_file_to_image(d->mlx_ptr, (char*)"./images/5.xpm", &width, &height);
	d->op_6 = mlx_xpm_file_to_image(d->mlx_ptr, (char*)"./images/6.xpm", &width, &height);
	d->op_7 = mlx_xpm_file_to_image(d->mlx_ptr, (char*)"./images/7.xpm", &width, &height);
	d->op_8 = mlx_xpm_file_to_image(d->mlx_ptr, (char*)"./images/8.xpm", &width, &height);
	d->flagged = mlx_xpm_file_to_image(d->mlx_ptr, (char*)"./images/flagged.xpm", &width, &height);
	d->opened = mlx_xpm_file_to_image(d->mlx_ptr, (char*)"./images/opened.xpm", &width, &height);
	d->bombed = mlx_xpm_file_to_image(d->mlx_ptr, (char*)"./images/bomb.xpm", &width, &height);

	d->win = mlx_new_window(d->mlx_ptr, d->rows * SIZE, d->rows * SIZE + 30, (char*)"demineur");
	
}

void generateDisplay(data *d) {
	int i = 0, j = 0;

	while (i < d->rows) {

		j = 0;
		while (j < d->rows) {

			if (d->table[i][j].is_opened == false && d->table[i][j].is_flagged == false)
				mlx_put_image_to_window(d->mlx_ptr, d->win, d->closed, SIZE*j, SIZE*i);
			else if (d->table[i][j].is_flagged == true)
				mlx_put_image_to_window(d->mlx_ptr, d->win, d->flagged, SIZE*j, SIZE*i);
			else if (d->table[i][j].value == -1)
				mlx_put_image_to_window(d->mlx_ptr, d->win, d->bombed, SIZE*j+5, SIZE*i+5);
			else if (d->table[i][j].value == 0)
				mlx_put_image_to_window(d->mlx_ptr, d->win, d->opened, SIZE*j, SIZE*i);
			else if (d->table[i][j].value == 1)
				mlx_put_image_to_window(d->mlx_ptr, d->win, d->op_1, SIZE*j, SIZE*i);
			else if (d->table[i][j].value == 2)
				mlx_put_image_to_window(d->mlx_ptr, d->win, d->op_2, SIZE*j, SIZE*i);
			else if (d->table[i][j].value == 3)
				mlx_put_image_to_window(d->mlx_ptr, d->win, d->op_3, SIZE*j, SIZE*i);
			else if (d->table[i][j].value == 4)
				mlx_put_image_to_window(d->mlx_ptr, d->win, d->op_4, SIZE*j, SIZE*i);
			else if (d->table[i][j].value == 5)
				mlx_put_image_to_window(d->mlx_ptr, d->win, d->op_5, SIZE*j, SIZE*i);
			else if (d->table[i][j].value == 6)
				mlx_put_image_to_window(d->mlx_ptr, d->win, d->op_6, SIZE*j, SIZE*i);
			else if (d->table[i][j].value == 7)
				mlx_put_image_to_window(d->mlx_ptr, d->win, d->op_7, SIZE*j, SIZE*i);
			else if (d->table[i][j].value == 8)
				mlx_put_image_to_window(d->mlx_ptr, d->win, d->op_8, SIZE*j, SIZE*i);

			j++;
		}
		i++;
	}
}

void printTable(data *d) {
	for (int i = 0; i < d->rows; i++) {
		for (int j = 0; j < d->rows; j++) {
			if (d->table[i][j].value != -1)
				printf(" ");
			printf("%d", d->table[i][j].value);
		}
		printf("\n");
	}
}