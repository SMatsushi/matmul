#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define IBL  256
// 48GB = 8(double) * 3(Matrix) * 2 * 1024 * 1024 * 1024 = 8 * 3 * (1.414 * 32 * 1024)^2
//       = 8(double) * 3 * (46333)^2
// #define NMAT (long)46000
#define NMAT (long)600
#define NLOOP 1

double a[NMAT][NMAT], b[NMAT][NMAT], c[NMAT][NMAT];
double sumup();
main()
{
    long ncalc = 2 * NMAT * NMAT * NMAT * NLOOP;
    long ncalcsum = NMAT * NMAT;
    int n;
    double gcalc = ((double)ncalc) / 1000.0 / 1000.0 / 1000.0;
    double gcalcsum = ((double)ncalcsum) / 1000.0 / 1000.0 / 1000.0;
    double elapse, sum;
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
    // sumup matrix C to avoid optimizer remove all the calculation
    // maybe OK because calculating external matrix.
    start = now;
    sum = sumup(); 
    now = clock();
    elapse = (double)(now - start)/CLOCKS_PER_SEC;
    printf("sum of C is %lf, took %.3lf, %lf GFlops\n", sum, elapse, gcalcsum/elapse);
}

setup()
{
    int i, j;
    double va = 10.0; 
    double vb = 1.1; 
    double da  = 0.01;
    double db  = 0.03;
    for (i = 0; i < NMAT; i++) {
        for (j = 0; j < NMAT; j++) {
            a[i][j] = va;
            b[i][j] = vb;
            va += da;
            vb += db;
        }
    }
}

matmul()
{
    int ib, jb, kb, i, j, k;
    for (ib = 0; ib < NMAT; ib += IBL) {
        for (jb = 0; jb < NMAT; jb += IBL) {
            for (kb = 0; kb < NMAT; kb += IBL) {
                for (i=ib; i < ib + IBL; i++) {
                    for (j=jb; j < jb + IBL; j++) {
                        for (k=kb; k < kb + IBL; k++) {
                            c[i][j] += a[i][k] * b[k][j];                              
                        }
                    }
                }
            }
        }
    }
}

double sumup() {
    int i, j;
    double sum = 0.0; 
    for (i = 0; i < NMAT; i++) {
        for (j = 0; j < NMAT; j++) {
            sum += c[i][j];
        }
    }
    return sum;
}
