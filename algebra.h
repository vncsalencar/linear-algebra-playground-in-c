#ifndef ALGEBRA_H
#define ALGEBRA_H

typedef struct {
  int* _id;
  int rows;
  int cols;
  int* data;
} Matrix;

typedef int* MatrixElement;

void debug(const char* s, ...);
unsigned int debug_id();
Matrix* create_matrix(int rows, int cols);
unsigned int matrix_valid_row_col(Matrix* m, int row, int col);
int __matrix_solve_index(Matrix* m, int row, int col);
MatrixElement matrix_get_reference_at(Matrix* m, int row, int col);
void matrix_print(Matrix *m);
unsigned int matrix_is_square(Matrix *m);
unsigned int matrix_is_row(Matrix *m);
unsigned int matrix_is_column(Matrix *m);
unsigned int matrix_is_zero(Matrix *m);
unsigned int matrix_is_diagonal(Matrix *m);
unsigned int matrix_is_identity(Matrix *m);
unsigned int matrix_is_triangular_upper(Matrix *m);
unsigned int matrix_is_triangular_lower(Matrix *m);
unsigned int matrix_is_symmetric(Matrix *m);

#endif
