#ifndef POWERSET_H
#define POWERSET_H

#include <stdlib.h>
#include <stdio.h>

typedef struct s_power
{
	int *arr;
	int size;
	int subset[100];
	int sub_size;
	int total_sum;
} t_power;

#endif