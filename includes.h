#ifndef INCLUDES_H
#define INCLUDES_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include <time.h>

#define SIZE 40

typedef enum BOOL {
	false,
	true,
} bool;

typedef struct Case {

	int value;
	bool is_opened;
	bool is_flagged;

} Case;

typedef struct Data {
	int bombs;
	int rows;
	int flags;
	bool can_i_play;
	
	Case **table;

	void *mlx_ptr;
	void *win;

	void *closed;
	void *opened;
	void *flagged;
	void *bombed;
	void *op_1;
	void *op_2;
	void *op_3;
	void *op_4;
	void *op_5;
	void *op_6;
	void *op_7;
	void *op_8;

} data;

#include "functions.h"

#endif