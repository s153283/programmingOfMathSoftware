#include <stdio.h>
#include "matrix_io.h"
#include "lssolve.h"

int main(int argc, char * argv[]) {
  if (argc != 4) {
    printf("Invalid number of input. Correct input form:\n");
    printf("./lssolve A.txt b.txt solution.txt\n");
    return -1;
  }

  matrix_t *A = read_matrix(argv[1]);
  vector_t *b = read_vector(argv[2]);



  printf("Matrix A:\n");
  print_matrix(A);
  printf("Vector b:\n");
  print_vector(b);

  printf("The solution will be saved as %s\n",argv[3]);

  write_vector(argv[3],b);
  return EXIT_SUCCESS;
}
