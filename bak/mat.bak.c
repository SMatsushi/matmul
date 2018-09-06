#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define IBL  256
// 48GB = 8(double) * 3(Matrix) * 2 * 1024 * 1024 * 1024 = 8 * 3 * (1.414 * 32 * 1024)^2
//       = 8(double) * 3 * (46333)^2
#define NMAT 46000
#define NLOOP 10

double a[NMAT][NMAT], b[NMAT][NMAT], c[NMAT][NMAT];
double sumup();
main()
{
    int ncalc = 2 * NMAT * NMAT * NLOOP;
    int n;
    double gcalc = (double ncalc) / 1000.0 / 1000.0 / 1000.0;
    double elapse;
    clock_t start, now;
    /* srand(12345678); */
    printf("Matrix size %d * %d, %lf GFlop, setting up... \n", NMAT, NMAT, gcalc);
    start = clock();
    setup(a, b);
    now = clock();
    printf("Setup took %.3lf\n", (double)(now - start)/CLOCKS_PER_SEC);
    start = now;
    for (n = 0; n < NLOOP; n++) {
        printf("%d, ", n);
        matmul();
    }
    now = clock();
    elapse = (double)(now - start)/CLOCKS_PER_SEC;
    printf("\n%d loops of MatMul took %.3lf = %lf GFlops\n", elapse, gcalc/elapse);
    // 
}

setup()
{
    int ib, jb, kb, i, j, k;
}

matmul()
{
    int ib, jb, kb, i, j, k;
    for (ib = 0; ib < NMAT; ib += IBL) {
        for (jb = 0; jb < NMAT; jb += IBL) {
            for (kb = 0; kb < NMAT; kb += IBL) {
                for (i=ib; i<ib+ibl; i++) {
                    for (j=jb; j<jb+ibl; j++) {
                        for (k=jb; k<kb+ibl; k++) {
                            c[i][j] += a[i][k] * b[k][j];                              
                        }
                    }
                }
            }
        }
    }
}

double sumup() {
}
