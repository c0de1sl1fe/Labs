#include <stdio.h>
#include <locale>
#include <conio.h>
#include <math.h>

void PrintMenu()
{
    system("CLS");
    printf("Здравствуйте, это меню, выберите, пожалуйста, пункт: \n");
    printf("1. Пункт первый: вычислить значение функции с заданной точность \n");
    printf("2. Пункт второй: вычислить значение функции с заданным числом челонов разложения \n");
    printf("3. Пункт третий: выйти\n\n");
    printf("Введите значение: ");
}

long long int fact(int number)
{
    if (number < 0)
        return 0;
    else if (number == 0)
        return 1;
    else
        return number * fact(number - 1);
}


double formula(double x, double n)
{
    return ( (double)((pow((-1), n)) * (fact(n * 2)) * (pow(x, n))) / ((1 - n * 2) * (pow((fact(n)), 2)) * (pow(4, n))) );
}


void main()

{
    setlocale(LC_ALL, "Rus");
    int choice = 0;
    double x = 0, epc = 0;

    int N = 0;
    bool exit = false;
    double result = 0;



    while (!exit)
    {
        PrintMenu();
        scanf_s("%d", &choice);

        switch (choice)
        {

        case (1):
        {
            result = 0;
            //system("CLS");
            printf("Выполняется пункт 1\n");
           
            printf("Введите, пожалуйста переменную x и точность эпсилон: ");
            scanf_s("%lf", &x);
            scanf_s("%lf", &epc);
            printf("\n");
            bool checkEpc = true;
            if ((epc < 0) || ((x > 1) || (x < -1)))
            {
                printf("Введенные значения не соответствуют условию(");
                exit = true;
                break;
            }
            else
            {
                
                for (double n = 0; checkEpc ; n++)
                {
                   
                    double a = 0;
                    a = formula(x, n);
                   

                    result = result + a;

                    if ( ( (fabs((result - sqrt((x + 1))))) <= epc )&&(n != 1) && (n != 0))
                    {
                        checkEpc = false;
                    }
                   
                } 

            }
            
            
            printf("%lf", result);
           _getch();
            break;
        }

        case(2):
        {
            result = 0;
            //system("CLS");
            printf("Выполняется пункт 2\n");
            
            scanf_s("Введите, пожалуйста переменную x и число разложения: ");
            scanf_s("%lf", &x);
            scanf_s("%d", &N);
            printf("\n");

            if ((((x > 1) || (x < -1)))||(N<=10))
            {
                printf("Введенные значения не соответствуют условию(");
                exit = true;
                break;
            }
            else
            {
                for (double n = 0; n<=N; n++)
                {
                    double a = 0;
                    a = formula(x, n);
                   // a = ((pow((-1), n)) * (fact(n * 2)) * (pow(x, n))) / ((1 - n * 2) * (pow((fact(n)), 2)) * (pow(4, n)));

                    result = result + a;
                }
            }

            printf("%lf", result);
            _getch();
            break;
        }






        case (3):
        {
            //system("CLS");
            printf("Выполняется пункт 3, до скорых встреч!");
            exit = true;
            break;
        }
        default:
            printf("\nЧто-то пошло не так, повторите запрос позже(");
            exit = true;
            break;
        
        }
    }
}