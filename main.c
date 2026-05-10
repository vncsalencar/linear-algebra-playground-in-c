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
    ._id = debug_id(),
    .rows = 3,
    .cols = 3,
    .data = (int[]) {1,4,5,4,2,6,5,6,3}
  };

  matrix_print(&m);
  matrix_equals(&m, &m);

  Matrix* n = create_matrix_init(3, 3, 3 * 3, (int[]) {1,4,5,4,2,6,5,6,3});
  matrix_is_identity(n);

  return 0;
}
