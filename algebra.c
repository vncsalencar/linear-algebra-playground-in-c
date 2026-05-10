#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "algebra.h"

#define DEBUG_MAX_STRING 1024
#define MATRIX_SOLVE_INDEX(m, row, col) ((row) * (m)->cols + (col))

static unsigned int __id = 0;

void debug(Matrix *m, const char* s, ...) {
  char *debug_flag = getenv("DEBUG");

  if (debug_flag == NULL) {
    return;
  }

  char* output = (char *) malloc(DEBUG_MAX_STRING * sizeof(char)); 

  if (m->_id != NULL) {
    sprintf(output, "[id@%d] %s", *m->_id, s);
  } else {
    sprintf(output, "[id@unknown] %s", s);
  }

  va_list args;
  va_start(args, s);
  vprintf(output, args);
  va_end(args);
}

int* debug_id() {
  __id += 1;
  int* id = (int *) malloc(sizeof(int));
  *id = __id - 1;
  return id;
}

Matrix* create_matrix(int rows, int cols) {
  Matrix* m = (Matrix *) malloc(sizeof(Matrix));
  m->_id = debug_id();
  m->rows = rows;
  m->cols = cols;
  m->data = (int *) malloc(rows * cols * sizeof(int));
  debug(m, "Created M(%d,%d)\n", rows, cols);
  return m;
}

Matrix* create_matrix_init(int rows, int cols, int length, int data[]) {
  Matrix* m = (Matrix *) malloc(sizeof(Matrix));
  m->_id = debug_id();
  m->rows = rows;
  m->cols = cols;
  m->data = data;
  debug(m, "Created M(%d,%d) with init data @%p\n", rows, cols, data);
  return m;
}

unsigned int matrix_valid_row_col(Matrix* m, int row, int col) {
  if (row < 0 || col < 0) {
    debug(m, "Invalid matrix access, row=%d and col=%d.\n", row, col);
    return 0;
  }

  if (row >= m->rows || col >= m->cols) {
    debug(m, "Invalid matrix access, row=%d and col=%d for M(%d,%d).\n", m->rows, m->cols, m->rows, m->cols);
    return 0;
  }

  debug(m, "Valid m(%d,%d) access for M(%d,%d)\n", row, col, m->rows, m->cols);

  return 1;
}

int __matrix_solve_index(Matrix* m, int row, int col) {
  int index = MATRIX_SOLVE_INDEX(m, row, col);
  debug(m, "Solved m(%d,%d) to flat index %d.\n", row, col, index);
  return index;
}

MatrixElement matrix_get_reference_at(Matrix* m, int row, int col) {
  if (0 == matrix_valid_row_col(m, row, col)) {
    return NULL;
  }

  int index = MATRIX_SOLVE_INDEX(m, row, col);
  debug(m, "Returning reference to m(%d,%d) at index %d.\n", row, col, index);
  return (MatrixElement) &m->data[index];
}

void matrix_print(Matrix *m) {
  debug(m, "Printing matrix M(%d,%d).\n", m->rows, m->cols);
  for (int i = 0; i < m->rows; i++) { 
    printf(" |");
    for (int j = 0; j < m->cols; j++) {
        int element_value = m->data[MATRIX_SOLVE_INDEX(m, i, j)];
        printf(" %d ", element_value);
    }
    printf("|\n");
  }
}

unsigned int matrix_is_square(Matrix *m) {
  if (m->rows != m->cols) {
    debug(m, "Matrix M(%d,%d) is not square.\n", m->rows, m->cols);
    return 0;
  }
  debug(m, "Matrix M(%d,%d) is square.\n", m->rows, m->cols);
  return 1;
}

unsigned int matrix_is_row(Matrix *m) {
  if (m->rows == 1) {
    debug(m, "Matrix M(%d,%d) is a row matrix.\n", m->rows, m->cols);
    return 1;
  }
  debug(m, "Matrix M(%d,%d) is not a row matrix.\n", m->rows, m->cols);
  return 0;
}

unsigned int matrix_is_column(Matrix *m) {
  if (m->cols == 1) {
    debug(m, "Matrix M(%d,%d) is a column matrix.\n", m->rows, m->cols);
    return 1;
  }
  debug(m, "Matrix M(%d,%d) is not a column matrix.\n", m->rows, m->cols);
  return 0;
}

unsigned int matrix_is_zero(Matrix *m) {
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      int element_value = m->data[MATRIX_SOLVE_INDEX(m, i, j)];
      if (element_value != 0) {
        debug(m, "Matrix M(%d,%d) is not zero because m(%d,%d)=%d.\n", m->rows, m->cols, i, j, element_value);
        return 0;
      }
    }
  }

  debug(m, "Matrix M(%d,%d) is a zero matrix.\n", m->rows, m->cols);
  return 1;
}

unsigned int matrix_is_diagonal(Matrix *m) {
  if (0 == matrix_is_square(m)) return 0;

  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      int element_value = m->data[MATRIX_SOLVE_INDEX(m, i, j)];
      if (i != j && element_value != 0) {
        debug(m, "Matrix M(%d,%d) is not diagonal because m(%d,%d)=%d.\n", m->rows, m->cols, i, j, element_value);
        return 0;
      }
    }
  }

  debug(m, "Matrix M(%d,%d) is diagonal.\n", m->rows, m->cols);
  return 1;
}

unsigned int matrix_is_identity(Matrix *m) {
  if (0 == matrix_is_square(m)) return 0;
  
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      int element_value = m->data[MATRIX_SOLVE_INDEX(m, i, j)];
      if (i == j && element_value != 1) {
        debug(m, "Matrix M(%d,%d) is not identity because diagonal m(%d,%d)=%d.\n", m->rows, m->cols, i, j, element_value);
        return 0;
      }
      if (i != j && element_value != 0) {
        debug(m, "Matrix M(%d,%d) is not identity because off-diagonal m(%d,%d)=%d.\n", m->rows, m->cols, i, j, element_value);
        return 0;
      }
    }
  }

  debug(m, "Matrix M(%d,%d) is identity.\n", m->rows, m->cols);
  return 1;
}

unsigned int matrix_is_triangular_upper(Matrix *m) {
  if (0 == matrix_is_square(m)) return 0;
  
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      if (i <= j) continue;
      int element_value = m->data[MATRIX_SOLVE_INDEX(m, i, j)];
      if (element_value != 0) {
        debug(m, "Matrix M(%d,%d) is not upper triangular because m(%d,%d)=%d.\n", m->rows, m->cols, i, j, element_value);
        return 0;
      }
    }
  }

  debug(m, "Matrix M(%d,%d) is upper triangular.\n", m->rows, m->cols);
  return 1;
}

unsigned int matrix_is_triangular_lower(Matrix *m) {
  if (0 == matrix_is_square(m)) return 0;
  
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      if (i >= j) continue;
      int element_value = m->data[MATRIX_SOLVE_INDEX(m, i, j)];
      if (element_value != 0) {
        debug(m, "Matrix M(%d,%d) is not lower triangular because m(%d,%d)=%d.\n", m->rows, m->cols, i, j, element_value);
        return 0;
      }
    }
  }

  debug(m, "Matrix M(%d,%d) is lower triangular.\n", m->rows, m->cols);
  return 1;
}

unsigned int matrix_is_symmetric(Matrix *m) {
  if (0 == matrix_is_square(m)) {
    return 0;
  }
  
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      if (i == j) continue;
      int element_value_ij = m->data[MATRIX_SOLVE_INDEX(m, i, j)];
      int element_value_ji = m->data[MATRIX_SOLVE_INDEX(m, j, i)];

      if (element_value_ij != element_value_ji) {
        debug(m, "Matrix M(%d,%d) is not symmetric because m(%d,%d)=%d and m(%d,%d)=%d.\n", m->rows, m->cols, i, j, element_value_ij, j, i, element_value_ji);
        return 0;
      }
    }
  }

  debug(m, "Matrix M(%d,%d) is symmetric.\n", m->rows, m->cols);
  return 1;
}

unsigned int matrix_equals(Matrix* a, Matrix* b) {
  if (a->rows != b->rows || a->cols != b->cols) {
    debug(a, "Not equal to %d because a(%d,%d) != b(%d,%d).\n", a->rows, a->cols, b->rows, b->cols);
    return 0;
  }
  
  for (int i = 0; i < a->rows; i++) {
    for (int j = 0; j < a->cols; j++) {
      int element_a = a->data[MATRIX_SOLVE_INDEX(a, i, j)];
      int element_b = b->data[MATRIX_SOLVE_INDEX(b, i, j)];
      if (element_a != element_b) return 0;
    }
  }

  debug(a, "a@%d is equal to b@%d!", a->_id, b->_id);
  return 0;
}


// if (a->cols != b->rows) {
//   debug(a, "Can't mutiply by %d because cols=%d.\n", b->_id, a->cols);
//   debug(b, "Can't mutiply by %d because rows=%d.\n", a->_id, b->cols);
//   return 0;
// }

Matrix* matrix_add(Matrix* a, Matrix* b);
Matrix* matrix_subtract(Matrix* a, Matrix* b);
Matrix* matrix_scalar_multiplication(Matrix* m, int scalar);
Matrix* matrix_product(Matrix* a, Matrix* b);
