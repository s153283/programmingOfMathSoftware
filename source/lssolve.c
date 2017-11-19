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
  int lwork = 6;
  double work[lwork];
  int info=-10;
  int Am=(int)(A->m), An=(int)(A->n);
  int colb =1, rowb= (int)(b->n);
  printf("A:\n");
  print_matrix(A);
  printf("Vector b:\n");
  print_vector(b);
  printf("Am: %d  , An: %d\n",Am,An);
  printf("n of b %ld\n", (b->n));
  dgels_(trans // 'T'
        ,&An    // M = 3
        ,&Am    // N = 10
        ,&colb // NRHS = 1
        ,A->A[0]  // A
        ,&An      // LDA= 3
        ,b->v     // B
        ,&rowb    // LDB = 10
        ,work     // double work[6]
        ,&lwork   // lwork = 6
        ,&info    // only for output
      );
  printf("n of b %ld\n", (b->n));
  printf("The char is %c\n",*trans);
  printf("Info is %d\n",info );

  printf("Solution:\n");
  print_vector(b);

  printf("The solution will be saved as %s\n",argv[3]);

  write_vector(argv[3],b);
  return EXIT_SUCCESS;
}
