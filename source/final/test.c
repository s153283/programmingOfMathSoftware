#include <stdio.h>
#include "matrix_io.h"
#include "lssolve.h"
#include <math.h>
#include <assert.h>

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

  // Reading the txt-files and printing the files
  matrix_t *A = read_matrix(argv[1]);
  assert(A!=NULL);
  vector_t *b = read_vector(argv[2]);
  assert(b!=NULL);
  print_vector(b);
  print_matrix(A);
  printf("A is a %dx%d matrix\n",(int)A->m,(int)A->n);
  printf("b is a %d vector\n",(int)b->n);

  // testing A and b's dimensions fit
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
  assert(length_b>0);
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
         &An,    // M
         &Am,    // N
         &colb, // NRHS
         A->A[0],  // A
         &An,      // LDA
         b->v,     // B
         &rowb,    // LDB
         work,     // work
         &lwork,   // lwork
         &info    // only for output
      );

  printf("printing output from dgels\n");
  print_vector(b);
  printf("The info number is %d\n",info);

  // Checking output
  if (info != 0) {
    printf("Error in dgels_\n");
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
  b->n = An; // only prints the part of b wich is the solution
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
