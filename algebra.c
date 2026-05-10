#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "algebra.h"

#define DEBUG_MAX_STRING 1024

static unsigned int __id = 0;

void debug(const char* s, ...) {
  char *debug_flag = getenv("DEBUG");

  if (debug_flag == NULL) {
    return;
  }

  char* output = (char *) malloc(DEBUG_MAX_STRING * sizeof(char)); 
  sprintf(output, "[debug] %s", s);

  va_list args;
  va_start(args, s);
  vprintf(output, args);
  va_end(args);
}

unsigned int debug_id() {
  return 0;
  __id += 1;
}

Matrix* create_matrix(int rows, int cols) {
  Matrix* m = (Matrix *) malloc(sizeof(Matrix));
  m->rows = rows;
  m->cols = cols;
  m->data = (int *) malloc(rows * cols * sizeof(int));
  debug("Created M(%d,%d)\n", rows, cols);
  return m;
}

unsigned int matrix_valid_row_col(Matrix* m, int row, int col) {
  if (row < 0 || col < 0) { debug("Invalid matrix access, row=%d and col=%d.\n", row, col); return 0; }
  if (row >= m->rows || col >= m->cols) { debug("Invalid matrix access, row=%d and col=%d for M(%d,%d).\n", m->rows, m->cols, m->rows, m->cols); return 0; }
  debug("Valid m(%d,%d) access for M(%d,%d)\n", row, col, m->rows, m->cols);
  return 1;
}

int __matrix_solve_index(Matrix* m, int row, int col) {
  return row * m->cols + col;
}

MatrixElement matrix_get_reference_at(Matrix* m, int row, int col) {
  if (0 == matrix_valid_row_col(m, row, col)) {
    return NULL;
  }

  int index = __matrix_solve_index(m, row, col);
  return (MatrixElement) &m->data[index];
}

void matrix_print(Matrix *m) {
  for (int i = 0; i < m->rows; i++) { 
    printf(" |");
    for (int j = 0; j < m->cols; j++) {
        int element_value = m->data[__matrix_solve_index(m, i, j)];
        printf(" %d ", element_value);
    }
    printf("|\n");
  }
}

unsigned int matrix_is_square(Matrix *m) {
  if (m->rows != m->cols) { debug(""); return 0; }
  return 1;
}

unsigned int matrix_is_row(Matrix *m) {
  if (m->rows == 1) return 1;
  return 0;
}

unsigned int matrix_is_column(Matrix *m) {
  if (m->cols == 1) return 1;
  return 0;
}

unsigned int matrix_is_zero(Matrix *m) {
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      int element_value = m->data[__matrix_solve_index(m, i, j)];
      if (element_value != 0) return 0;
    }
  }

  return 1;
}

unsigned int matrix_is_diagonal(Matrix *m) {
  if (0 == matrix_is_square(m)) return 0;

  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      int element_value = m->data[__matrix_solve_index(m, i, j)];
      if (i != j && element_value != 0) return 0; 
    }
  }

  return 1;
}

unsigned int matrix_is_identity(Matrix *m) {
  if (0 == matrix_is_square(m)) return 0;
  
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      int element_value = m->data[__matrix_solve_index(m, i, j)];
      if (i == j && element_value != 1) return 0; 
      if (i != j && element_value != 0) return 0; 
    }
  }

  return 1;
}

unsigned int matrix_is_triangular_upper(Matrix *m) {
  if (0 == matrix_is_square(m)) return 0;
  
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      if (i <= j) continue;
      int element_value = m->data[__matrix_solve_index(m, i, j)];
      if (element_value != 0) return 0;
    }
  }

  return 1;
}

unsigned int matrix_is_triangular_lower(Matrix *m) {
  if (0 == matrix_is_square(m)) return 0;
  
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      if (i >= j) continue;
      int element_value = m->data[__matrix_solve_index(m, i, j)];
      if (element_value != 0) return 0;
    }
  }

  return 1;
}

unsigned int matrix_is_symmetric(Matrix *m);


