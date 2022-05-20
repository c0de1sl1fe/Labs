#include <stdio.h>
#include <locale.h>


int main2()
{
    setlocale(LC_ALL, "RUS");
    float a, b;
    float c = 0;


    printf("Inpute a: ");
    scanf_s("%f", &a);

    printf("Inpute b: ");
    scanf_s("%f", &b);

    if (b == 0)
    {
        printf("Деление на ноль");
    }
    else
    {
        printf("%.0f / %.0f = %.3f", a, b, a / b);

    }


    return 0;
}

int main1()
{
    int a, b;
    setlocale(LC_ALL, "RUS");

    printf("Inpute a: ");
    scanf_s("%d", &a);
    printf("Inpute b: ");
    scanf_s("%d", &b);

    if (a < b)
    {
        int c = 0;
        c = (a * a) - (b * b);
        printf("%d", c);
    }

    else
    {
        if (a > b)
        {
            int c = 0;
            c = 2 * a * b;
            printf("%d", c);

        }

        else
        {
            printf("Ни одно из условия не было выполнено(");
        }



    }

    return 0;
}
