#include <stdio.h>
#include "algebra.h"

int main() {
  // Matrix* m = create_matrix(3, 3);
  // matrix_print(m);

  // MatrixElement el = matrix_get_reference_at(m, 0, 0);

  // if (el != NULL) {
  //   *el = 3;
  // } else {
  //   printf("NULL!");
  // }

  // matrix_print(m);

  // if (1 == matrix_is_diagonal(m)) {
  //   printf("Matriz diagonal!");
  // } else {
  //   printf("Matriz nao diagonal!");
  // }

  Matrix m = {
    .rows = 3,
    .cols = 3,
    .data = (int[]) {1,2,3,0,4,5,0,0,6}
  };

  matrix_print(&m);

  return 0;
}
