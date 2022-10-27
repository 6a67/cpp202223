#include <gsl/gsl_randist.h>


#define SIGMA 1.0

int main(int argc, char** argv) {
    for(double x = -5.0; x <= 5.0; x += 0.1) {
        printf("%f %f\n", x, gsl_ran_gaussian_pdf(x, SIGMA));
    }
}