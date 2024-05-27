#ifndef MODULES_H
#define MODULES_H

#ifndef __cplusplus
#define _GNU_SOURCE
#endif

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14159265358979323846264338327950288

typedef struct data {
  unsigned int vertices_count;
  double *vertices_arr;
  unsigned int polygonals_count;
  int *polygonals_arr;
} model_data;

enum exit_status { OK, ERROR };

#ifdef __cplusplus
extern "C" {
#endif

/*PARSER*/

int file_obj_parser(char *file_name, model_data *data);
int memory_alloc(model_data *data);
void memory_free(model_data *data);
void count_vertices_and_polygonals(FILE *file, model_data *data);
int parse_vertices_and_polygonals(FILE *file, model_data *data);

/*AFFINE TRANSFORMATIONS*/

void move_X(model_data *data, const double dx);
void move_Y(model_data *data, const double dy);
void move_Z(model_data *data, const double dz);
void scale(model_data *data, const double d);
void rotate_X(model_data *data, double angle);
void rotate_Y(model_data *data, double angle);
void rotate_Z(model_data *data, double angle);
#ifdef __cplusplus
}
#endif

#endif  // MODULES_H
