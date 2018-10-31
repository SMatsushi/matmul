#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/times.h>
#include <unistd.h>
#include <time.h>

#ifdef SXLG
#define NBLKS 80
#else  // SXLG
#define NBLKS 20
#endif // SXLG

#ifdef SXVE
#define IBL  256
// 48GB = 8(double) * 3(Matrix) * 2 * 1024 * 1024 * 1024 = 8 * 3 * (1.414 * 32 * 1024)^2
//       = 8(double) * 3 * (46333)^2
// 46000/128 = 359
// 46000/256 = 179
#else // SXVE
#define IBL  16
#endif // SXVE

#define NMAT ((long)(IBL * NBLKS))
#define NMATC (NMAT + 1)        // making it odd to prevent cache line conflicts
#define NLOOP 1

static void prtimes(char *, double, clock_t, struct tms *, struct tms *);

double a[NMAT][NMATC], b[NMAT][NMATC], c[NMAT][NMATC];
double sumup();
main()
{
    long ncalc = 2 * NMAT * NMAT * NMAT * NLOOP;
    long ncalcsum = NMAT * NMAT;
    int n;
    double gcalc = ((double)ncalc) / 1000.0 / 1000.0 / 1000.0;
    double gcalcsum = ((double)ncalcsum) / 1000.0 / 1000.0 / 1000.0;
    double elapse, sum;
    struct  tms tmsstart, tmsnow;
    clock_t start, now;
    static char mbuf[1024];

    printf("Matrix size %d * %d Block=%d, %lf GFlop, setting up... \n", NMAT, NMAT, IBL, gcalc);
    start = times(&tmsstart);
    setup();
    now = times(&tmsnow);
    prtimes("Setup", 0, now - start, &tmsstart, &tmsnow);

    start = now; tmsstart = tmsnow;
    for (n = 0; n < NLOOP; n++) {
        printf("%d, ", n);
        matmul();
    }
    now = times(&tmsnow);
    sprintf(mbuf, "\n%d loops of MatMul", NLOOP);
    prtimes(mbuf, gcalc, now - start, &tmsstart, &tmsnow);
    // sumup matrix C to avoid optimizer remove all the calculation
    // maybe OK because calculating external matrix.
    start = now; tmsstart = tmsnow;
    sum = sumup(); 
    now = times(&tmsnow);
    sprintf(mbuf, "sum of C is %lf", sum);
    prtimes(mbuf, gcalcsum, now - start, &tmsstart, &tmsnow);
}

static void
prtimes(char *msg, double gflop, clock_t real, struct tms *tmsstart, struct tms *tmsnow)
{
    static long clktck = 0;
    double rt;
    if (clktck == 0) {
        if ((clktck = sysconf(_SC_CLK_TCK)) < 0) {
            printf("sysconf error : code=%d\n", clktck);
        }
    }
    rt = real / (double)clktck;
    printf("%s, took %.3lf sec (real)", msg, rt);
    if (gflop > 0) {
        printf(", %lf GFlops", gflop/rt);
    }
    printf("\n");
    printf(" user: %7.2f, sys: %7.2f\n", 
        (tmsnow->tms_utime - tmsstart->tms_utime) / (double)clktck,
        (tmsnow->tms_stime - tmsstart->tms_stime) / (double)clktck);
    printf("    child user: %7.2f, child sys: %7.2f\n",
        (tmsnow->tms_cutime - tmsstart->tms_cutime) / (double)clktck,
        (tmsnow->tms_cstime - tmsstart->tms_cstime) / (double)clktck);
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
                for (i = ib; i < (ib + IBL); i++) {
                    for (j = jb; j < (jb + IBL); j++) {
                        for (k = kb; k < (kb + IBL); k++) {
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
