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

  // Reading the txt-files and printing the files
  matrix_t *A = read_matrix(argv[1]);
  vector_t *b = read_vector(argv[2]);
  double length_b = 0;
  double length_Residual = 0;
  print_vector(b);
  print_matrix(A);
  printf("A is a %dx%d matrix\n",(int)A->m,(int)A->n);
  printf("b is a %d vector\n",(int)b->n);

  // testing A and b
  if (A->m != b->n) {
    printf("Dimension of A.m is not equal to dimension of b.n\n");
    free_vector(b);
    free_matrix(A);
    return -1;
  }
  printf("Dimension of A.m and b.n fits\n");

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
  printf("printing output from dgels\n");    
  print_vector(b);
  printf("The info number is %d\n",info);

  // Checking output
  if (info < 0) {
    printf("the %d-th argument had an illegal value\n",info);
    free(work);
    free_vector(b);
    free_matrix(A);
    return -1;
  }

  // Find the norm of the residuals
  for (int i = An; i < rowb; i++) {
    length_Residual += b->v[i]*b->v[i];
  }
  length_Residual = sqrt(length_Residual);

  // Print the relative residual norm
  printf("length of b: %lf\n",length_b);
  printf("The residual norm: %lf\n",length_Residual);
  printf("The relative residual norm: %lf\n",length_Residual/length_b);

  // Writes the x* to file
  b->n = An;
  write_vector(argv[3],b);
  vector_t *x = read_vector(argv[3]);
  printf("Testing that the file is safed and checking if it is correct\n");
  print_vector(x);

  //free the memory
  free(work);
  free_vector(b);
  free_matrix(A);
  free_vector(x);

  return EXIT_SUCCESS;
}
