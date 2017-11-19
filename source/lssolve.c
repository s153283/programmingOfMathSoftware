#include <stdio.h>
#include "matrix_io.h"
#include "lssolve.h"
#include <math.h>

int main(int argc, char * argv[]) {
  if (argc != 4) {
    printf("Invalid number of input. Correct input form:\n");
    printf("./lssolve A.txt b.txt solution.txt\n");
    return -1;
  }


  matrix_t *A = read_matrix(argv[1]);
  vector_t *b = read_vector(argv[2]);
  double length_b = 0;
  double length_Residual = 0;

  // Find length of b
  for (size_t i = 0; i < b->n; i++) {
    length_b += b->v[i]*b->v[i];
  }
  length_b = sqrt(length_b);

  // Initial for the function
  char trans = 'T';
  int info=-1;
  int Am=(int)(A->m), An=(int)(A->n);
  int colb =1, rowb= (int)(b->n);
  int lwork = 2*An;
  double * work = (double *)malloc(lwork*sizeof(work[0]));

  // call
  dgels_(&trans, // 'T'
         &An,    // M = 3
         &Am,    // N = 10
         &colb, // NRHS = 1
         A->A[0],  // A
         &An,      // LDA= 3
         b->v,     // B
         &rowb,    // LDB = 10
         work,     // double work[6]
         &lwork,   // lwork = 6
         &info    // only for output
      );

  // Find the norm of the residuals
  for (int i = An; i < rowb; i++) {
    length_Residual += b->v[i]*b->v[i];
  }
  length_Residual = sqrt(length_Residual);

  // Print the relative residual norm
  printf("The relative residual norm: %lf\n",length_Residual/length_b);

  // Writes the x* to file
  b->n = An;
  write_vector(argv[3],b);

  //free the memory
  free(work);
  free_vector(b);
  free_matrix(A);

  return EXIT_SUCCESS;
}
