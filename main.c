#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double function(double *x) {
    return 1 / pow((1.1 + *x), 2);
}

double leftRectangle(double *a, double *b, int *n) {
    double h = (*b - *a) / *n;
    double result = 0.0;

    for (int i = 0; i < *n; i++) {
        double x = *a + i * h;
        result += function(&x);
    }

    return result * h;
}

double rightRectangle(double *a, double *b, int *n) {
    double h = (*b - *a) / *n;
    double result = 0.0;

    for (int i = 1; i <= *n; i++) {
        double x = *a + i * h;
        result += function(&x);
    }

    return result * h;
}

double trapezoid(double *a, double *b, int *n) {
    double h = (*b - *a) / *n;
    double result = (function(a) + function(b)) / 2.0;

    for (int i = 1; i < *n; i++) {
        double x = *a + i * h;
        result += function(&x);
    }

    return result * h;
}

double simpson(double *a, double *b, int *n) {
    double h = (*b - *a) / *n;
    double result = function(a) + function(b);

    for (int i = 1; i < *n; i++) {
        double x = *a + i * h;
        if (i % 2 == 0) {
            result += 2 * function(&x);
        } else {
            result += 4 * function(&x);
        }
    }

    return result * h / 3;
}

double getIntegralByMethod(double *a, double *b, int *n, int *method){
    switch (*method) {
        case 1:
            return leftRectangle(a, b, n);
        case 2:
            return rightRectangle(a, b, n);
        case 3:
            return trapezoid(a, b, n);
        case 4:
            return simpson(a, b, n);
    }
}


double checkN(double *a, double *b, double *epsilon, int *method, int *N){
    double I1, I2;
    do {
        I1 = getIntegralByMethod(a, b, N, method);
        *N += 2;
        I2 = getIntegralByMethod(a, b, N, method);

    } while(fabs(I1 - I2) > *epsilon);

    return I2;
}

int main() {
    double a, b, epsilon;
    int n, method;
    int N = 2;

    printf("Введіть нижню межу a: ");
    scanf("%lf", &a);
    printf("Введіть верхню межу b: ");
    scanf("%lf", &b);

    do {
        printf("Виберіть метод обрахунку (Л.П./П.П/Тр/Сім) => (1/2/3/4): ");
        scanf("%d", &method);
        if (method < 1 || method > 4) {
            printf("Помилка: Введено некоректний метод. Спробуйте ще раз.\n");
        }
    } while (method < 1 || method > 4);

    do {
        printf("Введіть кількість поділок n: ");
        scanf("%d", &n);
        if (method == 4 && n % 2 != 0) {
            printf("Помилка: для методу Сімпсона кількість поділок n повинна бути парною. Спробуйте ще раз.\n");
        }
    } while (method == 4 && n % 2 != 0);

    do {
        printf("Введіть похибку: ");
        scanf("%lf", &epsilon);
        if (epsilon < 0.00001 || epsilon > 0.001) {
            printf("Помилка: Похибка має бути в межах 0.00001 ≤ ε ≤ 0.001.\n");
        }
    } while (epsilon < 0.00001 || epsilon > 0.001);

    double I2 = checkN( &a,  &b,  &epsilon,  &method, &N);

    switch (method) {
        case 1:
            printf("Метод лівих прямокутників: %lf\n", leftRectangle(&a, &b, &n));
            break;
        case 2:
            printf("Метод правих прямокутників: %lf\n", rightRectangle(&a, &b, &n));
            break;
        case 3:
            printf("Метод трапецій: %lf\n", trapezoid(&a, &b, &n));
            break;
        case 4:
            printf("Метод Сімпсона: %.9lf\n", simpson(&a, &b, &n));
            break;
    }

    printf("N: %d; Integral: %lf", N, I2);

    return 0;
}
