#include <stdio.h>
#include "matrix_io.h"
#include "lssolve.h"
#include <math.h>

int main(int argc, char * argv[]) {
  // Initialize varibles
  double length_b = 0;
  double length_Residual = 0;
  char trans = 'T';
  int info=-100;
  int Am, An;
  int colb, rowb;
  int lwork;

  // Check if the number of inputs are Correct.
  if (argc != 4) {
    printf("Invalid number of input. Correct input form:\n");
    printf("./lssolve A.txt b.txt solution.txt\n");
    return -1;
  }

  // Reads the matrix and vectors
  matrix_t *A = read_matrix(argv[1]);
  vector_t *b = read_vector(argv[2]);

  // Find length of b
  for (size_t i = 0; i < b->n; i++) {
    length_b += b->v[i]*b->v[i];
  }
  length_b = sqrt(length_b);

  // Set the variables for the function call
  Am=(int)(A->m);
  An=(int)(A->n);
  colb =1;
  rowb= (int)(b->n);
  lwork = 2*An;

  // Allocate work space for dgels_
  double * work = (double *)malloc(lwork*sizeof(work[0]));
  if (work==NULL) {
    printf("There is not enough memory to allocate work space\n");
    free_vector(b);
    free_matrix(A);
    return -1;
  }

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
  b->n = An;  // only prints the part of b wich is the solution
  write_vector(argv[3],b);

  //free the memory
  free(work);
  free_vector(b);
  free_matrix(A);

  return EXIT_SUCCESS;
}
