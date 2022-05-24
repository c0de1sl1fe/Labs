#include <stdio.h>
#include <iostream>
#include <math.h>
#include <cstdio>
#include <Windows.h>

class PointClass
{
private:
    double acceleration;
    double speed;
    double start;
    double time;


public:

    double position() const
    {
        return (start + speed * time + (pow(time, 2) * acceleration) / 2);
    }
    void setAcceleration(double acceleration) { this->acceleration = acceleration; }
    double getcceleration() const { return acceleration; }

    void setSpeed(double speed) { this->speed = speed; }
    double getSpeed() const { return speed; }

    void setStart(double start) { this->start = start; }
    double getStart() const { return start; }

    void setTime(double time)
    {
        if (time < 0)
        {
            this->time = 0;
        }
        this->time = time;
    }
    double getTime() const { return time; }

    /*double IsMeetTime(double acceleration2, double speed2, double start2) const
    {
        double time1, time2;
        double a = (acceleration - acceleration2) / 2, b = speed - speed2, c = start - start2;
        if ((a == 0) && (b == 0) && (c == 0))
        {
            return 0;
        }
        if ((a == 0) && (b == 0) && (c != 0))
        {
            return NAN;
        }
        if ((a == 0) && (b != 0))
        {
            time1 = -c / b;
            if (time1 < 0) { return NAN; }
            return time1;
        }
        double D = pow((b), 2) - 4 * (a) * (c);
        if (D >= 0)
        {
            time1 = (-b + sqrt(D)) / (2 * a);
            time2 = (-b - sqrt(D)) / (2 * a);
            if ((time1 >= 0) && (time2 >= 0))
            {
                if (time1 < time2)
                {
                    return time1;
                }
                return time2;
            }
            if (time1 >= 0)
            {
                return time1;
            }
            if (time2 >= 0)
            {
                return time2;
            }
        }        
        return NAN;
    }*/
    double IsMeetPosition(double time1)
    {
        return (start + speed * time1 + (pow(time1, 2) * acceleration) / 2);
    }

    PointClass(double acceleration = 0, double speed = 0, double start = 0) //конструктор, без времени
    {
        setAcceleration(0);
        setAcceleration(acceleration);
        setSpeed(0);
        setSpeed(speed);
        setStart(0);
        setStart(start);
        setTime(0);
    }
};

//bool checkCorrect(const char* stmp, double* value)
//{
//    char* endptr;
//    *value = strtod(stmp, &endptr);
//    if (endptr == stmp) return false;
//    if ((*value == DBL_MAX || *value == DBL_MIN) && errno == ERANGE) return false;
//
//    while (*endptr)
//    {
//        if ((*endptr != ' ') && (*endptr != '\n')) return false;
//        endptr++;
//    }
//    return true;
//}
//
//double EnterNumber()
//{
//    double tmp;
//    char stmp[24];
//    gets_s(stmp);
//    while (!checkCorrect(stmp, &tmp))
//    {
//        printf("\nErrorWithNumber\n");
//        gets_s(stmp);
//    }
//    return tmp;
//}

double EnterNumber()
{
    double tmp;
    char stmp[24];


    bool exit1 = false;
    while (!exit1)
    {
        bool exit = true;
        gets_s(stmp);
        char* endptr = stmp;
        tmp = strtod(stmp, &endptr);
        if (endptr == stmp)
        {
            exit = false;
            continue;
        }
        if ((tmp == DBL_MAX || tmp == DBL_MIN) && errno == ERANGE)
        {
            exit = false;
            continue;
        }

        while (*endptr)
        {
            if ((*endptr != ' ') && (*endptr != '\n'))
            {
                exit = false;
                break;
            }
            endptr++;
        }
        if (exit)
        {
            exit1 = true;
        }
        else
        {
            exit1 = false;
            printf("\nsomething wrong with number\n");
        }

    }
    return tmp;
}


void printMenu()
{
    printf("Здравствуйте, выберите действие:\n ");

    printf("\nРабота с отдельной точкой(узнать координату в определнный момент времени): 1");
    printf("\nВыполнить задачу лабораторной работы: 2");
    printf("\nВыйти: 3\n");
}
void printMenu2()
{
    printf("\nВыберите действие: ");

    printf("\nУзнать время встречи: 1");
    printf("\nУзнать координату встречи: 2");
    printf("\nВыйти: 3\n");
}


double IsMeetTime(const PointClass& p1, const PointClass& p2)
{
    double time1, time2;
    double a = ((p1.getcceleration() - p2.getcceleration()) / 2), b = (p1.getSpeed() - p2.getSpeed()), c = (p1.getStart() - p2.getStart());
    if ((a == 0) && (b == 0) && (c == 0))
    {
        return 0;
    }
    if ((a == 0) && (b == 0) && (c != 0))
    {
        return NAN;
    }
    if ((a == 0) && (b != 0))
    {
        time1 = -c / b;
        if (time1 < 0) { return NAN; }
        return (time1);
    }
    double D = pow((b), 2) - 4 * (a) * (c);
    if (D >= 0)
    {
        time1 = (-b + sqrt(D)) / (2 * a);
        time2 = (-b - sqrt(D)) / (2 * a);
        if ((time1 >= 0) && (time2 >= 0))
        {
            if (time1 < time2)
            {
                return time1;
            }
            return time2;
        }
        if (time1 >= 0)
        {
            return time1;
        }
        if (time2 >= 0)
        {
            return time2;
        }
    }
    return NAN;
}


void main()
{
    PointClass p1;
    PointClass p2;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    bool exit = false;
    int choice;

    while (!exit)
    {
        printMenu();
        scanf_s("%d", &choice);
        switch (choice)
        {
        case(1):
        {
            getchar();
            printf("Введите ускорение: ");        
            p1.setAcceleration(EnterNumber());
            printf("Введите скорость: ");
            p1.setSpeed(EnterNumber());
            printf("Введите начальную позицию: ");
            p1.setStart(EnterNumber());

            printf("Введите время: ");
            double *tmp = new double(EnterNumber());
            while (*tmp < 0)
            {
                *tmp = EnterNumber();
            }
            p1.setTime(*tmp);
            delete(tmp);
            printf("Позици в указанное время: %lf\n\n", p1.position());
            break;
        }

        case(2):
        {
            int choice2;
            bool exit2 = false;
            while (!exit2)
            {
                printMenu2();
                scanf_s("%d", &choice2);
                char pet[1];
                gets_s(pet);
                switch (choice2)
                {
                case(1):
                {
                    // gets_s(pet);
                    printf("\nВведите ускорение1: ");
                    p1.setAcceleration(EnterNumber());
                    printf("Введите скорость1: ");
                    p1.setSpeed(EnterNumber());
                    printf("Введите начальную позицию1: ");
                    p1.setStart(EnterNumber());

                    printf("Введите ускорение2: ");
                    p2.setAcceleration(EnterNumber());
                    printf("Введите скорость2: ");
                    p2.setSpeed(EnterNumber());
                    printf("Введите начальную позицию2: ");
                    p2.setStart(EnterNumber());

                    double time = IsMeetTime(p1, p2);
                    if (!isnan(time))
                    {
                        printf("\nВремя встречи %lf\n", time);
                    }
                    else
                    {
                        printf("\nВремя встречи невозможно\n");
                    }

                    break;

                }
                case(2):
                {
                    printf("\nВведите ускорение1:\n");
                    p1.setAcceleration(EnterNumber());
                    printf("Введите скорость1:\n");
                    p1.setSpeed(EnterNumber());
                    printf("Введите начальную позицию1:\n");
                    p1.setStart(EnterNumber());

                    printf("Введите ускорение2:\n");
                    p2.setAcceleration(EnterNumber());
                    printf("Введите скорость2:\n");
                    p2.setSpeed(EnterNumber());
                    printf("Введите начальную позицию2:\n");
                    p2.setStart(EnterNumber());

                    double time = IsMeetTime(p1, p2);
                    //double time = p1.IsMeetTime(p2.getcceleration(), p2.getSpeed(), p2.getStart());
                    if (!isnan(time))
                    {
                        printf("\nМесто встречи %lf\n", p1.IsMeetPosition(time));
                    }
                    else
                    {
                        printf("\nВремя встречи невозможно\n");
                    }
                    break;
                }
                case(3):
                {
                    printf("good bye\n");
                    exit2 = true;
                    break;
                }
                default:
                    printf("Please try again\n");
                    break;
                }

            }
            break;

        }
        case(3):
        {
            exit = true;
            break;
        }
        default:
            printf("Please try again\n");
            break;
        }
    }

}