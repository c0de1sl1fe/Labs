#define _CRT_SECURE_NO_WARNINGS
#include "Data.h"
#include "DynamicArray.h"
#include "EDataException.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <ctime>
#include <ctype.h>
using namespace std;

void MenuArray()
{
    system("CLS");
    printf("/// Array level ///\n\n");
    printf("Choose one:\n");
    printf("1. Считать значение из файла\n");   
    printf("2. Записать значение в файл\n");    
    printf("3. Вывести на экран\n");
    printf("4. Удалить записи\n");
    printf("5. Сформаровать массив результат работы\n");
    printf("6. == Портал на уровень ниже ==\n");
    printf("7. Exit\n");
    printf("Choice: ");
}
void MenuElement()
{
    printf("\n\n/// Element level ///\n\n");
    printf("Choose one:\n");
    printf("1. -> Вперед -> \n");        // С возможностью удалить текущий элемент и продолжить просмотр
    printf("2. <- Назад <- \n");
    printf("3. Добавить запись\n");     // в конец или после определенного элемента // какую-то определенную или стандартную
    printf("4. Удалить запись\n");      // Эту или какую-то конкретную(вывести все элементы и спросить еще раз)?
    printf("5. Поиск фамилии по подстроке\n");  // вывести все фамилии и попросить ввести фамилию которую хочет увидеть пользователь, и вывести запись с этим человеком
    printf("6. == Портал на уровень выше ==\n");
    printf("7. == Портал на уровень ниже ==\n");
    printf("Choice: ");
}
void MenuInside()
{
    printf("\n\n/// Edit level ///\n\n");
    printf("Choose one:\n");
    printf("1. Редактировать эту запись\n");// внутри возможность редактировать поля разные но с жестким контролем
    printf("2. Редактировать конкретную запись\n");  // аналогично
    printf("3. == Портал на уровень выше ==\n");
    printf("Choice: ");
}
void MenuEdit()
{
    printf("\n/// Editing level ///\n\n");
    printf("Что будем редактировать?\n");
    printf("1. Имя\n");
    printf("2. Фамилия\n");
    printf("3. Отчество\n");
    printf("4. Группа\n");
    printf("5. Оценки за экзамены\n");
    printf("6. Оценки за тест\n");
    printf("7. == Exit ==\n");
    printf("Choice: ");
}

char* ReadLine()
{
    size_t size = 0;
    size_t capacity = 4;
    size_t growth = 2;
    char* str = new char[capacity];
    if (str == NULL) { return NULL; }
    while (true)    //опасно, можно застрять
    {
        int character = fgetc(stdin);
        if ((character == '\n') || (character == EOF))
        {
            break;
        }
        str[size] = (char)character;
        size++;
        if (size == capacity)
        {
            capacity *= growth;
            char* stradd = new char[capacity];
            if(stradd==NULL)
            {
                delete[]str;
                delete[]stradd;
                return NULL;
            }
            strncpy(stradd, str, size);
            delete[]str;
            str = stradd;
        }
    }
    str[size] = 0;
    return str;
}
int EnterNumber()
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
    return (int)tmp;
}

Data* CreateElement()
{
    char* NameTmp;
    char* SurnameTmp;
    char* PatronymicTmp;
    int groupTmp;
    int examTmp[SIZEexam];
    int testTmp[SIZEtest];
  
    printf("\nВведите имя: ");
    NameTmp = ReadLine();
    printf("\nВведите фамилию: ");
    SurnameTmp = ReadLine();
    printf("\nВведите отчество: ");
    PatronymicTmp = ReadLine();
    printf("\nВведите группу: ");
    groupTmp = EnterNumber();
    printf("\nВведите оценки за экзамен: ");
    for (unsigned i = 0; i < SIZEexam; i++)
    {
        examTmp[i] = EnterNumber();
    }
    printf("\nВведите оценки за тест: ");
    for (unsigned i = 0; i < SIZEtest; i++)
    {
        testTmp[i] = EnterNumber();
    }
    Data* tmp = new Data(NameTmp, SurnameTmp, PatronymicTmp, groupTmp, examTmp, testTmp);
    return tmp;
}

int CompareSurname(Data* lhs, Data* rhs)
{
    return (strcmp((lhs->getSurname()), (rhs->getSurname())));
}

void main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    DynamicArray a;

    int choiceArray = 0;
    bool exitArray = false;
    while (!exitArray)
    {
        MenuArray();
        choiceArray = EnterNumber();
        switch (choiceArray)
        {
        case(1):
        {
            try
            {
                system("cls");
                printf("Введите название файла: ");
                char* filenameTmp = ReadLine();
                a.ReadBinFile(filenameTmp);
                delete[]filenameTmp;
                printf("Операция выполнена, для продолжениея - ENTER");
                getchar();
            }
            catch (EFileException &err)
            {
                err.Print();
                printf("Произошла ошибка, для продолжения - ENTER");
                getchar();
            }
            break;
        }
        case(2):
        {
            system("cls");
            if (a.GetSize() == 0)
            {
                printf("Массив пустой!");
                printf("\nДля продолжения - ENTER");
                getchar();
            }
            else
            {
                try
                {
                    printf("Введите название файла: ");
                    char* filenameTmp = ReadLine();
                    a.WriteBinFile(filenameTmp);
                    delete[]filenameTmp;
                    printf("Операция выполнена, для продолжениея - ENTER");
                    getchar();
                }
                catch (EFileException& err)
                {
                    err.Print();
                    printf("Произошла ошибка, для продолжения - ENTER");
                    getchar();
                }
            }
            break;
        }
        case(3):
        {
            if (a.GetSize() == 0)
            {
                printf("Массив пуст");
                printf("\nДля продолжения - ENTER");
                getchar();
            }
            else
            {
                a.PrintDynamicArray();
                printf("Операция выполнена, для продолжениея - ENTER");
                getchar();
            }
            break;
        }
        case(4):
        {
            if (a.GetSize() == 0)
            {
                printf("Массив пуст");
                printf("\nДля продолжения - ENTER");
                getchar();
            }
            else
            {
                try
                {
                    a.ClearArray();
                    printf("Операция выполнена, для продолжениея - ENTER");
                    getchar();
                }
                catch (EisEmpty& err)
                {
                    err.Print();
                    printf("\nПроизошла ошибка, для продолжениея - ENTER");
                    getchar();
                }

            }
            break;
        }
        case(5):
        {
            DynamicArray newA;
            if (a.GetSize() == 0)
            {
                printf("Массив пуст");
                printf("\nДля продолжения - ENTER");
                getchar();
            }
            else
            {
                Data* tmp = NULL;
                int* tmpArray = NULL;
                unsigned size = a.GetSize();
                unsigned current = 0;
                double avgexam = 0;
                double avgtest = 0;
                int grouptmp = -1;
                while (grouptmp < 0)//
                {
                    printf("\nВведите номер обозреваемой группы: ");
                    grouptmp = EnterNumber();
                }
                try
                {
                    for (unsigned i = 0; i < size; i++)
                    {
                        tmpArray = (a.GetElement(i))->getExam();
                        for (unsigned j = 0;  j < SIZEexam;  j++)
                        {
                            avgexam += tmpArray[j];
                        }
                        tmpArray = NULL;
                    }
                    avgexam = (double)avgexam / ((double)size * (double)SIZEexam); // среднее по всем экз
                    for (unsigned i = 0; i < size; i++) // отбор с большим средним баллом
                    {
                        double avgexamCur = 0;
                        double flagtestCur = false;
                        tmpArray = (a.GetElement(i))->getExam();
                        for (unsigned j = 0; j < SIZEexam; j++)
                        {
                            avgexamCur += tmpArray[j];
                        }
                        avgexamCur = (double)avgexamCur / ((double)SIZEexam);
                        tmpArray = (a.GetElement(i))->getTest();
                        for (unsigned j = 0; j < SIZEtest; j++)
                        {
                            if (tmpArray[j] <= 2)
                            {
                                flagtestCur = true;
                            }
                        }
                        if ((avgexamCur >= avgexam) && (!flagtestCur) && (grouptmp == (a.GetElement(i))->getGroup()))
                        {
                            newA.AddtoEnd(a.GetElementS(i));

                        }
                    }
                    newA.PrintDynamicArray();
                    newA.SortArray(&CompareSurname);

                    newA.PrintDynamicArray();
                    printf("\nВведите название файла: ");
                    char* filenameTmp = ReadLine();
                    FILE* output = NULL;                            //чтобы точно записать данные в файл
                    output = fopen(filenameTmp, "wb+");
                    while (!output)
                    {
                        printf("Проблема с именем файла, попробуйте снова: ");
                        delete[]filenameTmp;
                        filenameTmp = ReadLine();
                        output = fopen(filenameTmp, "wb+");
                    }
                    fclose(output);

                    newA.WriteBinFile(filenameTmp);
                    delete[]filenameTmp;
                    printf("Операция выполнена, для продолжениея - ENTER");
                    getchar();

                }
                catch (EInvalidIndex &err)
                {
                    err.Print();
                    printf("Произошла ошибка из-за индекса, для продолжения - ENTER");
                    getchar();
                }
                catch (EFileException& err)
                {
                    err.Print();
                    printf("Произошла ошибка из-за файла, для продолжения - ENTER");
                    getchar();
                }
                catch (EOutofrangeException& err)
                {
                    err.Print();
                    printf("Произошла ошибка данных, для продолжения - ENTER");
                    getchar();
                }
            }
            break;
        }
        case(6):
        {
            system("CLS");
            int choiceElement = 0;
            bool exitElement = false;
            int current = 0;
            while (!exitElement)
            {
                system("CLS");
                if (a.GetSize() != 0)
                {
                    try
                    {
                        printf("Запись №%d\n", current + 1);
                        a.GetElement(current)->PrintData();
                    }
                    catch (EInvalidIndex &err)
                    {
                        err.Print();
                    }
                }
                else
                {
                    printf("\nМассив пуст");
                    printf("\nДля продолжения - ENTER");
                    getchar();
                }
                MenuElement();
                choiceElement = (int)EnterNumber();
                switch (choiceElement)
                {
                case(1):
                {
                    if ((a.GetSize() != 0) && (current < a.GetSize() - 1))
                    {
                        current++;
                    }
                    else
                    {
                        printf("\nДальше нельзя, будет ошибка");
                        getchar();
                    }
                    break;
                }
                case(2):
                {
                    if ((a.GetSize() > 0) && (current > 0))
                    {
                        current--;
                    }
                    else
                    {
                        printf("\nДальше нельзя, будет ошибка");
                        getchar();
                    }
                    break;
                }
                case(3):
                {
                    int addwaychoice = 0;
                    printf("Куда добавить, в конец(0) или по выбранному индексу(1)?");
                    printf("Выбор: ");
                    addwaychoice = (int)EnterNumber();
                    if (addwaychoice == 1)             
                    {
                        try
                        {
                            printf("== всего: %u ==\n", a.GetSize());
                            printf("Введите индекс, после которого хотите добавить запись: ");
                            unsigned index = (unsigned)EnterNumber() - 1;
                            printf("Введите данные элемента, который хотите добавить\n");
                            Data* tmp = CreateElement();
                            a.AddBefore(tmp, index);
                        }
                        catch (EInvalidIndex &err)
                        {
                            err.Print();
                            printf("Произошла ошибка индекса, для продолжения - ENTER");
                            getchar();
                        }
                        catch (EOutofrangeException& err)
                        {
                            err.Print();
                            printf("Произошла ошибка из-за данных, для продолжения - ENTER");
                            getchar();
                        }
                    }

                    else
                    {
                        try
                        {
                            printf("Введите данные элемента, который хотите добавить\n");
                            Data* tmp = CreateElement();
                            a.AddtoEnd(tmp);
                        }
                        catch (EOutofrangeException& err)
                        {
                            err.Print();
                            printf("Произошла ошибка из-за данных, для продолжения - ENTER");
                            getchar();
                        }
                    }
                    break;
                }
                case(4):
                {
                    if (a.GetSize() == 0)
                    {
                        printf("Массив пуст");
                        printf("\nДля продолжения - ENTER");
                        getchar();
                    }
                    else
                    {
                        printf("Хотите удалить текущий элемент(1) или по индекусу(0): ");
                        int deletechoice = EnterNumber();
                        if (deletechoice == 1)
                        {
                            a.DeleteElement(current);
                        }
                        else
                        {
                            printf("Введите индекс удаляемого элемента (== всего: %u ==)\n", a.GetSize());
                            printf("Выбор: ");
                            int index = EnterNumber() - 1;
                            try
                            {
                                a.DeleteElement(index);
                            }
                            catch (EInvalidIndex& err)
                            {
                                err.Print();
                                printf("Произошла ошибка из-за индекса, для продолжения - ENTER");
                                getchar();
                            }
                        }
                    }

                    break;
                }
                case(5):
                {
                    if (a.GetSize() == 0)
                    {
                        printf("Массив пуст");
                        printf("\nДля продолжения - ENTER");
                        getchar();
                    }
                    else
                    {
                        printf("Поиск и последующее сохранение с самого начала(0) или с определенного места(1): ");
                        int searchchoice = 0;
                        searchchoice = EnterNumber();
                        if (searchchoice == 1)
                        {
                            printf("Введите строку: ");
                            char* tmpSurname = ReadLine();
                            printf("\nОткуда начать поиск(== всего: %u ==):", a.GetSize());
                            int index = (int)EnterNumber() - 1;
                            try
                            {
                                int tmpindex = a.FindSurname(tmpSurname, (unsigned)index);
                                if (tmpindex == -1)
                                {
                                    printf("Ничего не найдено");
                                    printf("\nДля продолжения - ENTER");
                                    getchar();
                                }
                                else
                                {
                                    printf("Найдено по номеру %d\n\n", tmpindex + 1);
                                    current = tmpindex;
                                    a.GetElement(tmpindex)->PrintData();
                                    printf("\nДля продолжения - ENTER");
                                    getchar();
                                }
                                delete[]tmpSurname;
                            }
                            catch (EInvalidIndex& err)
                            {
                                err.Print();
                                err.Print();
                                printf("Произошла ошибка из-за индекса, для продолжения - ENTER");
                                getchar();
                            }
                        }
                        else
                        {
                            printf("Введите строку: ");
                            char* tmpSurname = ReadLine();
                            int tmpindex = a.FindSurname(tmpSurname, 0);
                            if (tmpindex == -1)
                            {
                                printf("Ничего не найдено");
                                printf("\nДля продолжения - ENTER");
                                getchar();
                            }
                            else
                            {
                                printf("Найдено по номеру %d\n\n", tmpindex + 1);
                                //current = tmpindex;
                                a.GetElement(tmpindex)->PrintData();
                                printf("\nДля продолжения - ENTER");
                                getchar();
                            }
                            delete[]tmpSurname;
                        }
                    }
                    break;
                }
                case(6):
                {
                    exitElement = true;
                    break;
                }
                case(7):
                {
                    system("CLS");
                    bool exitInside = false;
                    int choiceInside = 0;
                    while (!exitInside)
                    {
                        MenuInside();
                        choiceInside = (int)EnterNumber();
                        switch (choiceInside)
                        {
                        case(1):
                        {
                            printf("Будем редактировать запись под номером %d\n", current);
                            a.GetElement(current)->PrintData();
                            bool exitEdit = false;
                            int choiceEdit = 0;
                            while (!exitEdit)
                            {
                                MenuEdit();
                                choiceEdit = (int)EnterNumber();
                                switch (choiceEdit)
                                {
                                case(1):
                                {
                                    printf("\n== Edit Name ==\n");
                                    printf("Введите имя: ");
                                    char* NameTmp = ReadLine();
                                    a.GetElement(current)->setName(NameTmp);
                                    delete[]NameTmp;
                                    break;
                                }
                                case(2):
                                {
                                    printf("\n== Edit Surname ==\n");
                                    printf("Введите фамилию: ");
                                    char* SurnameTmp = ReadLine();
                                    a.GetElement(current)->setSurname(SurnameTmp);
                                    delete[]SurnameTmp;
                                    break;
                                }
                                case(3):
                                {
                                    printf("\n== Edit Patronymic ==\n");
                                    printf("Введите отчество: ");
                                    char* PatronymicTmp = ReadLine();
                                    a.GetElement(current)->setPatronymic(PatronymicTmp);
                                    delete[]PatronymicTmp;
                                    break;
                                }
                                case(4):
                                {
                                    printf("\n== Edit Group ==\n");
                                    int groupTmp = 0;
                                    try
                                    {
                                        groupTmp = (int)EnterNumber();
                                        a.GetElement(current)->setGroup(groupTmp);
                                        printf("\nВсе успешно");
                                        printf("\nДля продолжения - ENTER");
                                        getchar();
                                    }
                                    catch (EOutofrangeException& err)
                                    {
                                        err.Print();
                                        printf("\nПроизошла ошибка из-за несоответствия числа");
                                        printf("\nДля продолжения - ENTER");
                                        getchar();

                                    }
                                    break;
                                }
                                case(5):
                                {
                                    printf("\n== Edit Exam ==\n");
                                    int examTmp[SIZEexam];
                                    printf("Введите оценки за экзамены\n");
                                    for (unsigned i = 0; i < SIZEexam; i++)
                                    {
                                        printf("Оценка за экзамен %u: ", i);
                                        examTmp[i] = (int)EnterNumber();
                                    }
                                    try
                                    {
                                        a.GetElement(current)->setExam(examTmp);
                                    }
                                    catch (EOutofrangeException& err)
                                    {
                                        err.Print();
                                        printf("\nВозникла ошибка из-за некорректных данных");
                                        printf("\nДля продолжения - ENTER");
                                        getchar();
                                    }
                                    break;
                                }
                                case(6):
                                {
                                    printf("== Edit Test ==\n");
                                    int testTmp[SIZEtest];
                                    printf("Введите оценки за экзамены\n");
                                    for (unsigned i = 0; i < SIZEtest; i++)
                                    {
                                        printf("Оценка за экзамен %u: ", i);
                                        testTmp[i] = (int)EnterNumber();
                                    }
                                    try
                                    {
                                        a.GetElement(current)->setTest(testTmp);
                                    }
                                    catch (EOutofrangeException& err)
                                    {
                                        err.Print();
                                        printf("\nВозникла ошибка из-за некорректных данных");
                                        printf("\nДля продолжения - ENTER");
                                        getchar();
                                    }
                                    break;
                                }
                                case(7):
                                {
                                    exitEdit = true;
                                    break;
                                }
                                default:
                                    printf("\n===Fail===\n");
                                    printf("ENTER to continue");
                                    getchar();
                                    break;
                                }
                            }

                            break;
                        }
                        case(2):
                        {

                            int indexEdit = 0;
                            try
                            {
                                printf("\n== всего: %u ==\n:", a.GetSize());
                                printf("Введите индекс элемента, который будем редактировать:");
                                indexEdit = (int)EnterNumber();


                                printf("Будем редактировать запись под номером %d\n", indexEdit);
                                a.GetElement(indexEdit)->PrintData();
                                bool exitEdit = false;
                                int choiceEdit = 0;
                                while (!exitEdit)
                                {
                                    MenuEdit();
                                    choiceEdit = (int)EnterNumber();
                                    switch (choiceEdit)
                                    {
                                    case(1):
                                    {
                                        printf("\n== Edit Name ==\n");
                                        printf("Введите имя: ");
                                        char* NameTmp = ReadLine();
                                        a.GetElement(indexEdit)->setName(NameTmp);
                                        delete[]NameTmp;
                                        break;
                                    }
                                    case(2):
                                    {
                                        printf("\n== Edit Surname ==\n");
                                        printf("Введите фамилию: ");
                                        char* SurnameTmp = ReadLine();
                                        a.GetElement(indexEdit)->setSurname(SurnameTmp);
                                        delete[]SurnameTmp;
                                        break;
                                    }
                                    case(3):
                                    {
                                        printf("\n== Edit Patronymic ==\n");
                                        printf("Введите отчество: ");
                                        char* PatronymicTmp = ReadLine();
                                        a.GetElement(indexEdit)->setPatronymic(PatronymicTmp);
                                        delete[]PatronymicTmp;
                                        break;
                                    }
                                    case(4):
                                    {
                                        printf("\n== Edit Group ==\n");
                                        int groupTmp = 0;
                                        try
                                        {
                                            groupTmp = (int)EnterNumber();
                                            a.GetElement(indexEdit)->setGroup(groupTmp);
                                            printf("\nВсе успешно");
                                            printf("\nДля продолжения - ENTER");
                                            getchar();
                                        }
                                        catch (EOutofrangeException& err)
                                        {
                                            err.Print();
                                            printf("\nПроизошла ошибка из-за несоответствия числа");
                                            printf("\nДля продолжения - ENTER");
                                            getchar();

                                        }
                                        break;
                                    }
                                    case(5):
                                    {
                                        printf("\n== Edit Exam ==\n");
                                        int examTmp[SIZEexam];
                                        printf("Введите оценки за экзамены\n");
                                        for (unsigned i = 0; i < SIZEexam; i++)
                                        {
                                            printf("Оценка за экзамен %u: ", i);
                                            examTmp[i] = (int)EnterNumber();
                                        }
                                        try
                                        {
                                            a.GetElement(indexEdit)->setExam(examTmp);
                                        }
                                        catch (EOutofrangeException& err)
                                        {
                                            err.Print();
                                            printf("\nВозникла ошибка из-за некорректных данных");
                                            printf("\nДля продолжения - ENTER");
                                            getchar();
                                        }
                                        break;
                                    }
                                    case(6):
                                    {
                                        printf("== Edit Test ==\n");
                                        int testTmp[SIZEtest];
                                        printf("Введите оценки за тест\n");
                                        for (unsigned i = 0; i < SIZEtest; i++)
                                        {
                                            printf("Оценка за тест %u: ", i);
                                            testTmp[i] = (int)EnterNumber();
                                        }
                                        try
                                        {
                                            a.GetElement(indexEdit)->setTest(testTmp);
                                        }
                                        catch (EOutofrangeException& err)
                                        {
                                            err.Print();
                                            printf("\nВозникла ошибка из-за некорректных данных");
                                            printf("\nДля продолжения - ENTER");
                                            getchar();
                                        }
                                        break;
                                    }
                                    case(7):
                                    {
                                        exitEdit = true;
                                        break;
                                    }
                                    default:
                                        printf("\n===Fail===\n");
                                        printf("ENTER to continue");
                                        getchar();
                                        break;
                                    }
                                }
                            }
                            catch (EInvalidIndex& err)
                            {
                                err.Print();
                                printf("\nВозникла ошибка из-за индекса изменяемого элемента");
                            }
                            break;
                        }
                        case(3):
                        {
                            exitInside = true;
                            break;
                        }
                        default:
                            printf("\n===Fail===\n");
                            printf("ENTER to continue");
                            getchar();
                            break;
                        }
                    }
                    //
                    break;
                }
                default:
                    printf("\n===Fail===\n");
                    printf("ENTER to continue");
                    getchar();
                    break;
                }
            }
            break;
        }
        case(7):
        {
            exitArray = true;
            break;
        }
        default:
            printf("\n===Fail===\n");
            printf("ENTER to continue");
            getchar();
            break;
        }
    }
}