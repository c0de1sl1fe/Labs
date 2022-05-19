#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

struct tv
{
    char manufacturer[25]{};
    char name[25]{};
    int size = 0;
    int day = 0, month = 0, year = 0;
    int warranty=0;
}tv;
const int sizeOfArray = 15;
struct tv TV[sizeOfArray];

//Functions
int getSize(bool file);
void readfile(bool file);
void write(int n, bool file, bool type);
void printfOneRecord(int n, bool file);
void writeOneRecord(char manufacturer[], char name[], int size, int day, int month, int year, int warranty, bool file, bool type);
void fillfileTV(int length);
void cleanFile(bool file);

void PrintMenu()
{
    system("CLS");
    printf("Здравствуйте, выберите пункт меню: \n");
    printf("1. Загрузить данные из файла\n");
    printf("2. Работа с данными \n");
    printf("3. Сохранить данные в новый файл\n");
    printf("4. Выйти\n\n");

    printf("Введите значение: ");
}

void PrintMenu1()
{
    printf("Какой файл открыть? \n");
    printf("1. Файл с телевизорами\n");
    printf("2. Файл с просроченными телевизорами\n");
    printf("Введите значение: ");
}

void PrintMenu2()
{
    printf("Здравствуйте, выберите пункт подменю: \n");
    printf("1. Следующая запись\n");
    printf("2. Предыдущая запись \n");
    printf("3. Добавить запись\n");
    printf("4. Удалить запись\n");
    printf("5. Изменить запись\n");
    printf("6. Назад\n\n");

    printf("Введите значение: ");
}

void PrintMenu25()
{
    printf("Здравствуйте, что будем редактировать? выберите пункт подподменю: \n");
    printf("1. Производителя\n");
    printf("2. Название \n");
    printf("3. Размер\n");
    printf("4. День покупки\n");
    printf("5. Месяц покупки\n");
    printf("6. Год покупки\n");
    printf("7. Гарантию\n");
    printf("8. Выход\n\n");
    printf("Введите значение: ");
}

void main()
{
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    int length = 0, n = 0;
    unsigned choice = 0, choice1 = 0, choice2 = 0, choice25 = 0;
    bool exit = false, exit2 = false, exit25 = 0;

    int userDay = 0, userMonth = 0, userYear = 0, userWarranty = 0, userSize = 0;
    char userManufacturer[25]{};
    char userName[25]{};
    
    int day = 0, month = 0, year = 0, warranty = 0, size = 0;
    char manufacturer[25]{};
    char name[25]{};

    const bool fileTV = true, fileOverdue = false; // Переменная для выбора пути файла
    const bool typeA = true, typeW = false;
    while (!exit)
    {
        PrintMenu();
        scanf_s("%u", &choice);
        switch (choice)
        {
        case(1):
        {
            PrintMenu1();
            scanf_s("%d", &choice1);
            switch (choice1)
            {
            case(1):
            {
                readfile(fileTV);
                break;
            }
            case(2):
            {
                readfile(fileOverdue);
                break;
            }
            default:
                printf("Something went wrong!");
                break;
            }
            
            _getch();
            break;
        }
        case(2):
        {
            while (!exit2)
            {
                length = getSize(fileTV);
                printf("Всего записей (нумерация с нуля): %d\n", length + 1);
                //printf("Выберите номер записи: ");
                //scanf_s("%d", &n);
                //if (n > length)
                //{
                //    printf("Такоой записи не существует, выводим последнюю");
                //    n = length;
                //}
                //printfOneRecord(n, fileTV);

                PrintMenu2();
                scanf_s("%u", &choice2);

                switch (choice2)
                {
                case(1):
                {
                    n++;
                    if (n > length)
                    {
                        n = length;
                    }
                    printfOneRecord(n, fileTV);
                    _getch();
                    break;
                }
                case(2):
                {
                    n--;
                    printfOneRecord(n, fileTV);
                    _getch();
                    break;
                }
                case(3): 
                {               // вот тут запись в конец
                    printf("Введите производителя: ");
                    gets_s(manufacturer);
                    gets_s(manufacturer);
                    printf("Введите название модели: ");
                    gets_s(name);
                    
                    printf("Введите диагональ экрана: ");
                    scanf_s("%d", &size);

                    printf("Введение дату покупки: \n");
                    printf("Введите день покупки: ");
                    scanf_s("%d", &day);

                    printf("Введите месяц покупки: ");
                    scanf_s("%d", &month);

                    printf("Введите год покупки: ");
                    scanf_s("%d", &year);

                    printf("Введите гарантийный срок: ");
                    scanf_s("%d", &warranty);

                    writeOneRecord(manufacturer, name, size, day, month, year, warranty, fileTV, typeA);
                    
                    break;

                }
                case(4):
                {               // Переписывание файла без одной строки = r+ или r
                    length = getSize(fileTV);
                    for (int i = 0; i <= length; i++)
                    {
                        printf("%d", i);
                        printfOneRecord(i, fileTV);
                    }
                    printf("Выберите какую строчку хотите удалить: ");
                    int del = 0;
                    scanf_s("%d", &del);
                    if ((del > length) || (del < 0))
                    {
                        printf("Вы хотите удалить несуществующую строку");
                    }
                    else
                    {
                        cleanFile(fileTV);
                        for (int i = 0; i <= length; i++)
                        {
                            if (i == del)
                            {
                                continue;
                            }
                            write(i, fileTV, typeA);
                        }
                    }

                    length = getSize(fileTV);
                    for (int i = 0; i <= length; i++)
                    {
                        printf("%d", i);
                        printfOneRecord(i, fileTV);
                    }
                    _getch();
                    break;
                }
                case(5):
                {               // Переписывание файла но уже с изменение одной строки = r+ или r
                    length = getSize(fileTV);
                    for (int i = 0; i <= length; i++)
                    {
                        printf("%d ", i);
                        printfOneRecord(i, fileTV);
                    }
                    int edit = 0;
                    printf("Введите номер строки, которую хотите редактировать: ");
                    scanf_s("%d", &edit);
                    if ((edit > length) || (edit < 0))
                    {
                        printf("Вы хотите редактировать несуществующую строку");
                    }
                    else
                    {
                        while (!exit25)
                        {
                            PrintMenu25();
                            scanf_s("%u", &choice25);
                            switch (choice25)
                            {
                            case(1):
                            {
                                printf("Редактирование пункта \"производитель\": ");
                                gets_s(TV[edit].manufacturer);
                                gets_s(TV[edit].manufacturer);
                                fillfileTV(length);
                                
                                break;
                            }
                            case(2):
                            {
                                printf("Редактирование пункта \"модель\": ");
                                gets_s(TV[edit].name);
                                gets_s(TV[edit].name);
                                fillfileTV(length);
                                
                                break;
                            }
                            case(3):
                            {
                                printf("Редактирование пункта \"размер экрана\": ");
                                scanf_s("%d", &TV[edit].size);
                                fillfileTV(length);
                                
                                break;
                            }
                            case(4):
                            {
                                printf("Редактирование пункта \"день покупки\": ");
                                scanf_s("%d", &TV[edit].day);
                                fillfileTV(length);
                                
                                break;
                            }
                            case(5):
                            {
                                printf("Редактирование пункта \"месяц покупки\": ");
                                scanf_s("%d", &TV[edit].month);
                                fillfileTV(length);
                                
                                break;
                            }
                            case(6):
                            {
                                printf("Редактирование пункта \"год покупки\": ");
                                scanf_s("%d", &TV[edit].year);
                                fillfileTV(length);
                                
                                break;
                            }
                            case(7):
                            {
                                printf("Редактирование пункта \"срок гарантии\": ");
                                scanf_s("%d", &TV[edit].warranty);
                                fillfileTV(length);
                                
                                break;
                            }
                            case(8):
                            {
                                printf("You've chosen 8, editing is over, good bye");
                                exit25 = true;
                                
                                break;
                            }
                            default:
                                printf("Something went wrong!25");
                                
                                break;
                            }
                        }
                    }
                    
                    
                }
                case(6):
                {
                    printf("Выход из подменю");
                    exit2 = true;
                    
                    break;
                }
                default:
                    printf("Something went wrong!2");
                    break;
                }
            }
            break;
        }
        case(3):
        {
            printf("Введите день: ");
            scanf_s("%d", &userDay);
            printf("Введите месяц: ");
            scanf_s("%d", &userMonth);
            printf("Введите год: ");
            scanf_s("%d", &userYear);
            printf("%d.%d.%d\n", userDay, userMonth, userYear);
            length = getSize(fileTV);
            if (length < 0)
            {
                printf("Error: length of file is less than zero");
                return;
            }
            cleanFile(fileOverdue);
            for (int i = 0; i <= length; i++)   // бежим по всему исходному файлу, находя все просроченные телевизоры
            {                                   // и сразу занося их в новый файл, после этого for, будем сортировать по марке и модели 
                day = TV[i].day;
                month = TV[i].month;
                year = TV[i].year;
                warranty = TV[i].warranty;

                month += warranty;
                if (month > 12)
                {
                    year += (month / 12);
                    month -= 12 * (month / 12);
                    if (month == 0)
                    {
                        month = 1;
                    }
                }
                if (((TV[i].day == 31) && ((TV[i].month == 1) || (TV[i].month == 3) || (TV[i].month == 5) || (TV[i].month == 7) || (TV[i].month == 8) || (TV[i].month == 10) || (TV[i].month == 12)))
                    || ((TV[i].day == 30) && ((TV[i].month == 4) || (TV[i].month == 6) || (TV[i].month == 9) || (TV[i].month == 11)))
                    || ((TV[i].day == 28) && (TV[i].month == 2)))
                {
                    if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
                    {
                        day = 31;
                    }
                    else
                    {
                        if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
                        {
                            day = 30;
                        }
                        else
                        {
                            if (month == 2)
                            {
                                day = 28;
                            }
                        }
                    }
                }
                            // Вот тут нужно читать файл с записью в конец
                if (year < userYear)                // Сама проверка, просрочен ли товар + запись в файл
                {
                    write(i, fileOverdue, typeA);
                }
                else
                {
                    if ((month < userMonth) && (year == userYear))
                    {
                        write(i, fileOverdue, typeA);
                    }
                    else
                    {
                        if ((day < userDay) && (year == userYear) && (month == userMonth))
                        {
                            write(i, fileOverdue, typeA);
                        }
                    }
                }
            }
            printf("Test");
            length = getSize(fileOverdue);
            printf("Test1");
            if (length > 3)                         // Вот тут уже с записью, но уже "с чистого листа"
            {
                for (int i = 0; i < length; i++)
                {
                    int counter = 1;
                    for (int j = length; j > i; j--)
                    {
                        if (( strcmp(TV[i].manufacturer, TV[j].manufacturer)==0 ) && (j != i + 1))
                        {
                            strcpy(manufacturer, TV[i + counter].manufacturer);
                            strcpy(name, TV[i + counter].name);
                            size = TV[i + counter].size;
                            day = TV[i + counter].day;
                            month = TV[i + counter].month;
                            year = TV[i + counter].year;
                            warranty = TV[i + counter].warranty;

                            strcpy(TV[i + counter].manufacturer, TV[j].manufacturer);
                            strcpy(TV[i + counter].name, TV[j].name);
                            TV[i + counter].size = TV[j].size;
                            TV[i + counter].day = TV[j].day;
                            TV[i + counter].month = TV[j].month;
                            TV[i + counter].year = TV[j].year;
                            TV[i + counter].warranty = TV[j].warranty;

                            strcpy(TV[j].manufacturer, manufacturer);
                            strcpy(TV[j].name, name);
                            TV[j].size = size;
                            TV[j].day = day;
                            TV[j].month = month;
                            TV[j].year = year;
                            TV[j].warranty = warranty;

                            counter++;
                        }
                    }
                }

                for (int i = 0; i < length; i++)
                {
                    int counter = 1;
                    for (int j = length; j > i; j--)
                    {
                        if ((strcmp(TV[i].manufacturer, TV[j].manufacturer) == 0) && (strcmp(TV[i].name, TV[j].name) == 0) && (j != i + 1))
                        {
                            strcpy(manufacturer, TV[i + counter].manufacturer);
                            strcpy(name, TV[i + counter].name);
                            size = TV[i + counter].size;
                            day = TV[i + counter].day;
                            month = TV[i + counter].month;
                            year = TV[i + counter].year;
                            warranty = TV[i + counter].warranty;

                            strcpy(TV[i + counter].manufacturer, TV[j].manufacturer);
                            strcpy(TV[i + counter].name, TV[j].name);
                            TV[i + counter].size = TV[j].size;
                            TV[i + counter].day = TV[j].day;
                            TV[i + counter].month = TV[j].month;
                            TV[i + counter].year = TV[j].year;
                            TV[i + counter].warranty = TV[j].warranty;

                            strcpy(TV[j].manufacturer, manufacturer);
                            strcpy(TV[j].name, name);
                            TV[j].size = size;
                            TV[j].day = day;
                            TV[j].month = month;
                            TV[j].year = year;
                            TV[j].warranty = warranty;

                            counter++;
                        }
                    }
                }
            }
            cleanFile(fileOverdue);
            for (int i = 0; i <= length; i++)
            {
                printf("\n %d\n", i);
                write(i, fileOverdue, typeA);
            }
            _getch();
            break;
        }
        case(4):
        {
            printf("You've chosen 4, good bye");
            exit = true;

            break;
        }
        default:
            printf("Something went wrong! Try again");
            _getch();
            break;
        }

    }
}


void write(int n, bool file, bool type) // запись в новый файл
{
    FILE* output = NULL;

    if (file) // Выбор файла
    {
        if (type) // Выбор типа записи
        {
            output = fopen("D:\\Test\\TVs.txt", "a");
        }
        else
        {
            output = fopen("D:\\Test\\TVs.txt", "w");
        }
    }
    else
    {
        if (type)
        {
            output = fopen("D:\\Test\\Overdue.txt", "a+");
        }
        else
        {
            output = fopen("D:\\Test\\Overdue.txt", "w");
        }
    }
    
    if (output == NULL)
    {
        printf("Error");
        return;
    }
    int r = fprintf(output, "%s\t%s\t%d\t%d %d %d\t%d\n", TV[n].manufacturer, TV[n].name, TV[n].size, TV[n].day, TV[n].month, TV[n].year, TV[n].warranty);
    if (r == -1)
    {
        printf("Error fprintf");
        return;
    }
    fclose(output);
}


int getSize(bool file) // блок чтобы узнать количество исходных элементов и занести их в переменные структуры
{
    FILE* input = NULL;

    if (file)
    {
        input = fopen("D:\\Test\\TVs.txt", "r");
    }
    else
    {
        input = fopen("D:\\Test\\Overdue.txt", "r");
    }
    if (input == NULL)
    {
        printf("Error");
        return -1;
    }
    int n = 0;
    while (!feof(input))
    {
        int r = fscanf(input, "%s\t%s\t%d\t%d %d %d\t%d", TV[n].manufacturer, TV[n].name, &TV[n].size, &TV[n].day, &TV[n].month, &TV[n].year, &TV[n].warranty);
        if (r == 7)
        {
            n++; 
        }
        else
        {
            return (n-1);
        }   
    }
    fclose(input);
    return (n-1);
}


void readfile(bool file)  // Выводим содержимое файла
{
    FILE* input = NULL;

    if (file)
    {
        input = fopen("D:\\Test\\TVs.txt", "r");
    }
    else
    {
        input = fopen("D:\\Test\\Overdue.txt", "r");
    }

    if (input == NULL)
    {
        printf("Error");
        return;
    }
    //printf("manufacture\t name\t size\t date\t warranty\n");
    printf("manufacture\tname\t        size\tdate\t\twarranty\n");
    while (!feof(input))
    {
        int r = fscanf(input, "%s\t%s\t%d\t%d %d %d\t%d", tv.manufacturer, tv.name, &tv.size, &tv.day, &tv.month, &tv.year, &tv.warranty);
        if (r == 7)
        {
            //printf("%s %s %d %d.%d.%d %d", tv.manufacturer, tv.name, tv.size, tv.day, tv.month, tv.year, tv.warranty);
            printf("%-16s%-16s%-8d%d.%d.%-11d%d\n", tv.manufacturer, tv.name, tv.size, tv.day, tv.month, tv.year, tv.warranty);
            /*printf("manufacturer: %s name: %s size: %d date: %d.%d.%d warranty: %d", tv.manufacturer, tv.name, tv.size, tv.day, tv.month, tv.year, tv.warranty);*/
            /*printf("\n");*/
        }
    }
    fclose(input);
}


void printfOneRecord(int n, bool file)
{
    if (n < 0)
    {
        n = 0;
    }
    printf("%-16s%-16s%-8d%d.%d.%-12d%d", TV[n].manufacturer, TV[n].name, TV[n].size, TV[n].day, TV[n].month, TV[n].year, TV[n].warranty);
}


void writeOneRecord(char manufacturer[], char name[], int size, int day, int month, int year, int warranty, bool file, bool type)
{
    FILE* output = NULL;

    if (file) // Выбор файла
    {
        if (type) // Выбор типа записи
        {
            output = fopen("D:\\Test\\TVs.txt", "a+");
        }
        else
        {
            output = fopen("D:\\Test\\TVs.txt", "r+");
        }
    }
    else
    {
        if (type)
        {
            output = fopen("D:\\Test\\Overdue.txt", "a+");
        }
        else
        {
            output = fopen("D:\\Test\\Overdue.txt", "r+");
        }
    }
    if (output == NULL)
    {
        printf("Error");
        return;
    }

    int r = fprintf(output, "%s\t%s\t%d\t%d %d %d\t%d\n", manufacturer, name, size, day, month, year, warranty);
    if (r == -1)
    {
        printf("Error fprintf");
        return;
    }
    fclose(output);
}


void fillfileTV(int length)
{
    FILE* output = NULL;
    output = fopen("D:\\Test\\TVs.txt", "w+");
    if (output == NULL)
    {
        printf("Error");
        return;
    }
    int r = 0;
    for (int i = 0; i <= length; i++)
    {
        r = fprintf(output, "%s\t%s\t%d\t%d %d %d\t%d\n", TV[i].manufacturer, TV[i].name, TV[i].size, TV[i].day, TV[i].month, TV[i].year, TV[i].warranty);
        if (r == -1)
        {
            printf("Error fprintf");
            return;
        }
        
    }
    fclose(output);
}


void cleanFile(bool file)
{
    FILE* output = NULL;

    if (file)
    {
        output = fopen("D:\\Test\\TVs.txt", "w");
    }
    else
    {
        output = fopen("D:\\Test\\Overdue.txt", "w");
    }

    fclose(output);
}
