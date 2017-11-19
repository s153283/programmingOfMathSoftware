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

  char trans[2] = "T";

  dgels_(trans,            /* 'N' or 'T'             */
      &(A->m),             /* rows in A              */
      &(A->n),             /* cols in A              */
      &(b->n),             /* cols in B              */
      A->A,                /* array A                */
      const int * lda,     /* leading dimension of A */
      b->v,                /* array B                */
      const int * ldb,     /* leading dimension of B */
      double * work,       /* workspace array        */
      int * lwork,         /* workspace size         */
      int * info           /* status code            */
  )


  printf("Matrix A:\n");
  print_matrix(A);
  printf("Vector b:\n");
  print_vector(b);

  printf("The solution will be saved as %s\n",argv[3]);

  write_vector(argv[3],b);
  return EXIT_SUCCESS;
}
