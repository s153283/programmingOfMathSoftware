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


  vector_t *x = malloc_vector(A->n);
  char trans[2] = "T";
  int info=1;
  int rowA=(int)(A->m), colA=(int)(A->n);
  int colb =1, rowb= (int)(b->n);
  dgels_(trans,&rowA,&colA, &colb,A->A[0],&rowA,b->v,&rowb,x->v,&colA, &info);

  double a = 3.0;

  printf("Matrix A:\n");
  print_matrix(A);
  printf("Vector b:\n");
  print_vector(b);
  dscal_(&rowb, &a, b->v, &colb);
  printf("Vector 3* b:\n");
  print_vector(b);

  print_vector(x);
  printf("The solution will be saved as %s\n",argv[3]);

  write_vector(argv[3],b);
  return EXIT_SUCCESS;
}
