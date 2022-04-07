#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "includes.h"

bool ft_isdigit(char *s);
void init_data(data *d, char **av);
void generateBombs(data *d);
void generateHints(data *d);
void generateMlx(data *d);
void generateDisplay(data *d);

int kill_program(data *d);
int controller(int button, int x, int y, data *d);
int escape_or_not(int key, data *d);

void printTable(data *d);

#endif