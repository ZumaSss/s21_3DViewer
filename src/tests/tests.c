#include <check.h>

#include "../modules/modules.h"

#define EPS 1e-06

START_TEST(parser_1) {
  model_data d = {0};
  char filename[] = "obj_files/xxx.obj";
  int res = file_obj_parser(filename, &d);
  ck_assert_int_eq(res, ERROR);
  memory_free(&d);
}
END_TEST

START_TEST(parser_2) {
  model_data d = {0};
  char *filename = NULL;
  int res = file_obj_parser(filename, &d);
  ck_assert_int_eq(res, ERROR);
  memory_free(&d);
}
END_TEST

START_TEST(parser_3) {
  model_data d = {0};
  char filename[] = "tests/error.obj";
  int res = file_obj_parser(filename, &d);
  ck_assert_int_eq(res, ERROR);
  memory_free(&d);
}
END_TEST

START_TEST(parser_4) {
  model_data d = {0};
  char filename[] = "tests/error1.obj";
  int res = file_obj_parser(filename, &d);
  ck_assert_int_eq(res, ERROR);
  memory_free(&d);
}
END_TEST

START_TEST(parser_5) {
  model_data d = {0};
  char filename[] = "tests/cube1.obj";
  int res = file_obj_parser(filename, &d);
  ck_assert_int_eq(res, OK);
  memory_free(&d);
}
END_TEST

START_TEST(transformation_1) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      -0.500000, -0.683013, -0.183013, -0.500000, -0.183013,
      0.683013,  -0.500000, 0.183013,  -0.683013, -0.500000,
      0.683013,  0.183013,  0.500000,  -0.683013, -0.183013,
      0.500000,  -0.183013, 0.683013,  0.500000,  0.183013,
      -0.683013, 0.500000,  0.683013,  0.183013,  -0.500000};
  file_obj_parser(filename, &d);
  rotate_X(&d, 30);

  // int j = 0;
  // while (j < (int)d.vertices_count * 3) {
  //   printf("%lf, ", d.vertices_arr[j++]);
  // }

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

START_TEST(transformation_2) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      -0.500000, -0.183013, -0.683013, -0.500000, -0.683013, 0.183013,
      -0.500000, 0.683013,  -0.183013, -0.500000, 0.183013,  0.683013,
      0.500000,  -0.183013, -0.683013, 0.500000,  -0.683013, 0.183013,
      0.500000,  0.683013,  -0.183013, 0.500000,  0.183013,  0.683013};
  file_obj_parser(filename, &d);
  rotate_X(&d, -30);

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);
  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

START_TEST(transformation_3) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      -0.500000, 0.640856,  0.298836, -0.500000, 0.298836,  -0.640856,
      -0.500000, -0.298836, 0.640856, -0.500000, -0.640856, -0.298836,
      0.500000,  0.640856,  0.298836, 0.500000,  0.298836,  -0.640856,
      0.500000,  -0.298836, 0.640856, 0.500000,  -0.640856, -0.298836};
  file_obj_parser(filename, &d);
  rotate_X(&d, 2000000);

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);
  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

START_TEST(transformation_4) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      -0.683013, -0.500000, -0.183013, -0.183013, -0.500000, 0.683013,
      -0.683013, 0.500000,  -0.183013, -0.183013, 0.500000,  0.683013,
      0.183013,  -0.500000, -0.683013, 0.683013,  -0.500000, 0.183013,
      0.183013,  0.500000,  -0.683013, 0.683013,  0.500000,  0.183013};
  file_obj_parser(filename, &d);
  rotate_Y(&d, 30);

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

START_TEST(transformation_5) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      -0.183013, -0.500000, -0.683013, -0.683013, -0.500000, 0.183013,
      -0.183013, 0.500000,  -0.683013, -0.683013, 0.500000,  0.183013,
      0.683013,  -0.500000, -0.183013, 0.183013,  -0.500000, 0.683013,
      0.683013,  0.500000,  -0.183013, 0.183013,  0.500000,  0.683013};
  file_obj_parser(filename, &d);
  rotate_Y(&d, -30);

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

START_TEST(transformation_6) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      0.640856,  -0.500000, 0.298836, 0.298836,  -0.500000, -0.640856,
      0.640856,  0.500000,  0.298836, 0.298836,  0.500000,  -0.640856,
      -0.298836, -0.500000, 0.640856, -0.640856, -0.500000, -0.298836,
      -0.298836, 0.500000,  0.640856, -0.640856, 0.500000,  -0.298836};
  file_obj_parser(filename, &d);
  rotate_Y(&d, 2000000);

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

START_TEST(transformation_7) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      -0.683013, -0.183013, -0.500000, -0.683013, -0.183013, 0.500000,
      -0.183013, 0.683013,  -0.500000, -0.183013, 0.683013,  0.500000,
      0.183013,  -0.683013, -0.500000, 0.183013,  -0.683013, 0.500000,
      0.683013,  0.183013,  -0.500000, 0.683013,  0.183013,  0.500000};
  file_obj_parser(filename, &d);
  rotate_Z(&d, 30);

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

START_TEST(transformation_8) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      -0.183013, -0.683013, -0.500000, -0.183013, -0.683013, 0.500000,
      -0.683013, 0.183013,  -0.500000, -0.683013, 0.183013,  0.500000,
      0.683013,  -0.183013, -0.500000, 0.683013,  -0.183013, 0.500000,
      0.183013,  0.683013,  -0.500000, 0.183013,  0.683013,  0.500000};
  file_obj_parser(filename, &d);
  rotate_Z(&d, -30);

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

START_TEST(transformation_9) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      0.640856,  0.298836,  -0.500000, 0.640856,  0.298836,  0.500000,
      0.298836,  -0.640856, -0.500000, 0.298836,  -0.640856, 0.500000,
      -0.298836, 0.640856,  -0.500000, -0.298836, 0.640856,  0.500000,
      -0.640856, -0.298836, -0.500000, -0.640856, -0.298836, 0.500000};
  file_obj_parser(filename, &d);
  rotate_Z(&d, 2000000);

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

START_TEST(transformation_10) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      -1.500000, -1.500000, -1.500000, -1.500000, -1.500000, 1.500000,
      -1.500000, 1.500000,  -1.500000, -1.500000, 1.500000,  1.500000,
      1.500000,  -1.500000, -1.500000, 1.500000,  -1.500000, 1.500000,
      1.500000,  1.500000,  -1.500000, 1.500000,  1.500000,  1.500000};
  file_obj_parser(filename, &d);
  scale(&d, 3);

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

START_TEST(transformation_11) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      -0.150000,      -0.150000,      -0.150000,      -0.150000,
      -0.150000,      0.150000,       -0.150000,      0.150000,
      -0.150000,      -0.150000,      0.150000,       0.150000,
      0.150000,       -0.150000,      -0.150000,      0.150000,
      -0.150000,      0.150000,       0.150000,       0.150000,
      -0.150000,      0.150000,       0.150000,       0.150000,
      -166666.500000, -166666.500000, -166666.500000, -166666.500000,
      -166666.500000, 166666.500000,  -166666.500000, 166666.500000,
      -166666.500000, -166666.500000, 166666.500000,  166666.500000,
      166666.500000,  -166666.500000, -166666.500000, 166666.500000,
      -166666.500000, 166666.500000,  166666.500000,  166666.500000,
      -166666.500000, 166666.500000,  166666.500000,  166666.500000};
  file_obj_parser(filename, &d);
  scale(&d, 0.3);

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

START_TEST(transformation_12) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      -166666.500000, -166666.500000, -166666.500000, -166666.500000,
      -166666.500000, 166666.500000,  -166666.500000, 166666.500000,
      -166666.500000, -166666.500000, 166666.500000,  166666.500000,
      166666.500000,  -166666.500000, -166666.500000, 166666.500000,
      -166666.500000, 166666.500000,  166666.500000,  166666.500000,
      -166666.500000, 166666.500000,  166666.500000,  166666.500000};

  file_obj_parser(filename, &d);
  scale(&d, 333333);

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

START_TEST(transformation_13) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      -1.000000, -0.500000, -0.500000, -1.000000, -0.500000, 0.500000,
      -1.000000, 0.500000,  -0.500000, -1.000000, 0.500000,  0.500000,
      0.000000,  -0.500000, -0.500000, 0.000000,  -0.500000, 0.500000,
      0.000000,  0.500000,  -0.500000, 0.000000,  0.500000,  0.500000,
      -0.500000, -2.000000, -0.500000, -0.500000, -2.000000, 0.500000,
      -0.500000, -1.000000, -0.500000, -0.500000, -1.000000, 0.500000,
      0.500000,  -2.000000, -0.500000, 0.500000,  -2.000000, 0.500000,
      0.500000,  -1.000000, -0.500000, 0.500000,  -1.000000, 0.500000};
  file_obj_parser(filename, &d);
  move_X(&d, -0.5);

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

START_TEST(transformation_14) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      -0.500000, -2.000000, -0.500000, -0.500000, -2.000000, 0.500000,
      -0.500000, -1.000000, -0.500000, -0.500000, -1.000000, 0.500000,
      0.500000,  -2.000000, -0.500000, 0.500000,  -2.000000, 0.500000,
      0.500000,  -1.000000, -0.500000, 0.500000,  -1.000000, 0.500000};
  file_obj_parser(filename, &d);
  move_Y(&d, -1.5);

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

START_TEST(transformation_15) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      -0.500000, -0.500000, 0.000000,  -0.500000, -0.500000, 1.000000,
      -0.500000, 0.500000,  0.000000,  -0.500000, 0.500000,  1.000000,
      0.500000,  -0.500000, 0.000000,  0.500000,  -0.500000, 1.000000,
      0.500000,  0.500000,  0.000000,  0.500000,  0.500000,  1.000000,
      -0.500000, -3.500000, -0.500000, -0.500000, -3.500000, 0.500000,
      -0.500000, -2.500000, -0.500000, -0.500000, -2.500000, 0.500000,
      0.500000,  -3.500000, -0.500000, 0.500000,  -3.500000, 0.500000,
      0.500000,  -2.500000, -0.500000, 0.500000,  -2.500000, 0.500000};
  file_obj_parser(filename, &d);
  move_Z(&d, 0.5);

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

START_TEST(transformation_16) {
  model_data d = {0};
  char filename[] = "tests/cube.obj";
  double vertices_arr[] = {
      -0.500000, -3.500000, -0.500000, -0.500000, -3.500000, 0.500000,
      -0.500000, -2.500000, -0.500000, -0.500000, -2.500000, 0.500000,
      0.500000,  -3.500000, -0.500000, 0.500000,  -3.500000, 0.500000,
      0.500000,  -2.500000, -0.500000, 0.500000,  -2.500000, 0.500000};
  file_obj_parser(filename, &d);
  move_Y(&d, -3);

  ck_assert_int_eq(d.polygonals_count, 12);
  ck_assert_int_eq(d.vertices_count, 8);

  int i = 0;
  while (i < (int)d.vertices_count * 3) {
    ck_assert_double_eq_tol(d.vertices_arr[i], vertices_arr[i], EPS);
    i++;
  }
  memory_free(&d);
}
END_TEST

Suite *

three_d_viever(void) {
  Suite *suite = suite_create("3DViewerV1.0");
  TCase *parsing = tcase_create("parsing");
  TCase *affine = tcase_create("affine");

  tcase_add_test(parsing, parser_1);
  tcase_add_test(parsing, parser_2);
  tcase_add_test(parsing, parser_3);
  tcase_add_test(parsing, parser_4);
  tcase_add_test(parsing, parser_5);
  tcase_add_test(affine, transformation_1);
  tcase_add_test(affine, transformation_2);
  tcase_add_test(affine, transformation_3);
  tcase_add_test(affine, transformation_4);
  tcase_add_test(affine, transformation_5);
  tcase_add_test(affine, transformation_6);
  tcase_add_test(affine, transformation_7);
  tcase_add_test(affine, transformation_8);
  tcase_add_test(affine, transformation_9);
  tcase_add_test(affine, transformation_10);
  tcase_add_test(affine, transformation_11);
  tcase_add_test(affine, transformation_12);
  tcase_add_test(affine, transformation_13);
  tcase_add_test(affine, transformation_14);
  tcase_add_test(affine, transformation_15);
  tcase_add_test(affine, transformation_16);

  suite_add_tcase(suite, parsing);
  suite_add_tcase(suite, affine);

  return suite;
}

int main(void) {
  int count_failed;
  Suite *s = three_d_viever();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (count_failed == 0) ? 0 : 1;
}