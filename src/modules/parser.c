#include "modules.h"

int file_obj_parser(char *file_name, model_data *data) {
  memory_free(data);
  data->polygonals_arr = NULL;
  data->polygonals_count = 0;
  data->vertices_arr = NULL;
  data->vertices_count = 0;
  int exit_status = ERROR;

  if (file_name != NULL) {
    FILE *file = fopen(file_name, "r");
    if (file) {
      count_vertices_and_polygonals(file, data);
      if (memory_alloc(data) == OK) {
        fseek(file, 0, SEEK_SET);
        exit_status = parse_vertices_and_polygonals(file, data);
      }
      fclose(file);
    }
  }

  return exit_status;
}

void count_vertices_and_polygonals(FILE *file, model_data *data) {
  char *buff_str = NULL;
  size_t size = 0;
  while (getline(&buff_str, &size, file) != EOF) {
    if (strncmp(buff_str, "v ", 2) == 0) {
      data->vertices_count++;
    } else if (strncmp(buff_str, "f ", 2) == 0) {
      data->polygonals_count++;
    }
  }

  if (buff_str) free(buff_str);
}

int memory_alloc(model_data *data) {
  int exit_status = OK;
  if (data->vertices_count)
    data->vertices_arr = calloc(data->vertices_count * 3, sizeof(double));
  if (data->polygonals_count)
    data->polygonals_arr = calloc(data->polygonals_count * 16, sizeof(int));
  if (!data->polygonals_arr || !data->vertices_arr) exit_status = ERROR;
  return exit_status;
}

void memory_free(model_data *data) {
  if (data != NULL) {
    if (data->vertices_arr != NULL) {
      free(data->vertices_arr);
      data->vertices_arr = NULL;
    }
    if (data->polygonals_arr != NULL) {
      free(data->polygonals_arr);
      data->polygonals_arr = NULL;
    }
  }
}

int parse_vertices_and_polygonals(FILE *file, model_data *data) {
  int exit_status = OK;
  char *buff_str = NULL;
  char *token = NULL;
  double x, y, z;
  int v, v1, v1_flag = 0;
  size_t ln = 0, v_indx = 0, f_indx = 0;

  while (getline(&buff_str, &ln, file) != EOF && exit_status == OK) {
    if (strncmp(buff_str, "v ", 2) == 0) {
      if (sscanf(buff_str, "v %lf %lf %lf", &x, &y, &z) == 3) {
        data->vertices_arr[v_indx++] = x;
        data->vertices_arr[v_indx++] = y;
        data->vertices_arr[v_indx++] = z;
      } else {
        exit_status = ERROR;
        break;
      }
    } else if (strncmp(buff_str, "f ", 2) == 0) {
      token = strtok(buff_str + 2, " ");
      while (token && !exit_status && strcmp(token, "\n")) {
        if (sscanf(token, "%d", &v) == 1 && v > 0 &&
            (unsigned int)v <= data->vertices_count) {
          v -= 1;
          if (!v1_flag) {
            v1 = v;
            v1_flag = 1;
          } else
            data->polygonals_arr[f_indx++] = v;
          data->polygonals_arr[f_indx++] = v;
        } else
          exit_status = ERROR;
        token = strtok(NULL, " ");
      }
      data->polygonals_arr[f_indx++] = v1;
      v1_flag = 0;
    }
  }

  if (buff_str) free(buff_str);

  return exit_status;
}