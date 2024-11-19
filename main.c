#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void func(double* x1, double* x2, unsigned int* N, double* delta, int count) {
    printf("\nПочатковий аргумент: %lf; Кінцевий аргумент: %lf; К-сть точок: %u; Дельта: %lf\n", *x1, *x2, *N, *delta);

    printf("****************************************\n");
    printf("*     N  *           X  *        F(X)  *\n");
    printf("****************************************\n");

    int widthN = 4;
    int widthX = 12;
    int widthF = 11;
    int i;

    for (i = 0; *x1 + *delta * i <= *x2; i++) {
        double x = *x1 + *delta * i;
        double F = pow((x - 10), 3) * sin((x + 10) / 100) - 10 * x + 12;

        printf("*  %*d *  %*.*lf *  %*lf *\n", widthN, i + 1, widthX, 2, x, widthF, F);
        printf("****************************************\n");

        if ((i + 1) % count == 0 && *x1 + *delta * (i+1) <= *x2) {
            printf("Натисніть enter для продовження...\n");
            getchar();
            system("cls");
            return func(x1, x2, N, delta, count+10);
        }
    }
    printf("Програму розробив Нетреба Станіслав Сергійович\nНатисніть enter для завершення...\n");
    getchar();

}

int main()
{
    int variant;
    double x1, x2, delta;
    unsigned int N;

    printf("Впишіть варіант(1/2): ");
    scanf("%d", &variant);

    printf("Впишіть Х1 та Х2(через пробіл): ");
    scanf("%lf%lf", &x1, &x2);

    switch(variant){
    case 1:
        printf("Вкажіть кількість точок: ");
        scanf("%u", &N);

        getchar();

        delta = ((x2 - x1) / (N - 1));

        func(&x1,&x2,&N, &delta, 10);
        break;
    case 2:
        printf("Вкажіть дельту: ");
        scanf("%lf", &delta);

        getchar();

        N = ((x2 - x1) / (delta - 1));

        func(&x1,&x2,&N, &delta, 10);
        break;
    default:
        printf("Обраний варіант не вірний, скрипт запускається з початку\n\n");
        return main();
    }

    return 0;
}