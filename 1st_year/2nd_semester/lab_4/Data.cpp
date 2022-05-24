#define _CRT_SECURE_NO_WARNINGS
#include "Data.h"
#include "EDataException.h"
#include <string.h>
#include <stdio.h>


Data::Data(char* Name, char* Surname, char* Patronymic, int group, int* exam, int* test)
{
    if (group <= 0)
    {
        delete[]_Name;
        delete[]_Surname;
        delete[]_Patronymic;
        throw EOutofrangeException(group, 0, 7000);
        return;
    }
    _Name = _strdup(Name);
    _Surname = _strdup(Surname);
    _Patronymic = _strdup(Patronymic);
    _group = group;
    _exam = new int[SIZEexam];
    for (int i = 0; i < SIZEexam; i++)
    {
        //unsigned a = exam[i];
        if ((exam[i] < 2) || (exam[i] > 5))
        {
            delete[]_Name;
            delete[]_Surname;
            delete[]_Patronymic;
            delete[]_exam;
            throw EOutofrangeException((int)exam[i]);
            //exception
            return;
        }
        _exam[i] = exam[i];
    }
    _test = new int[SIZEtest];
    for (int i = 0; i < SIZEtest; i++)
    {
        if ((test[i] < 2) || (test[i] > 5))
        {
            delete[]_Name;
            delete[]_Surname;
            delete[]_Patronymic;
            delete[]_exam;
            delete[]_test;
            throw EOutofrangeException((int)test[i]);
            //exception
            //return;
        }
        _test[i] = test[i];
    }
}
Data::Data()
{
    _Name = _strdup("Петя");
    _Surname = _strdup("Васечкин");
    _Patronymic = _strdup("Александрович");
    _group = 6112;
    _exam = new int[SIZEexam];
    for (int i = 0; i < SIZEexam; i++)
    {
        _exam[i] = 3;
    }
    _test = new int[SIZEtest];
    for (int i = 0; i < SIZEtest; i++)
    {
        _test[i] = 4;
    }
}
Data::Data(const Data& a)
{
    _Name = _strdup(a.getName());
    _Surname = _strdup(a.getSurname());
    _Patronymic = _strdup(a.getPatronymic());
    _group = a.getGroup();
    _exam = new int[SIZEexam];
    int* tmp = a.getExam();
    for (int i = 0; i < SIZEexam; i++)
    {
        _exam[i] = tmp[i];
    }
    _test = new int[SIZEtest];
    tmp = a.getTest();
    for (int i = 0; i < SIZEtest; i++)
    {
        _test[i] = tmp[i];
    }
}
void Data::PrintData() const
{
    printf("Фамилия: %s\nИмя: %s\nОтчество: %s\nГруппа: %d\nЭкзамены: ", _Surname, _Name, _Patronymic, _group);

    for (int i = 0; i < SIZEexam; i++)
    {
        printf("%d ", _exam[i]);
    }
    printf("\nЗачеты: ");
    for (int i = 0; i < SIZEtest; i++)
    {
        printf("%d ", _test[i]);
    }
}
void Data::setName(const char* Name)
{
    _Name = _strdup(Name);
}
char* Data::getName() const { return _Name; }

void Data::setSurname(const char* Surname)
{
    _Surname = _strdup(Surname);
}
char* Data::getSurname()const { return _Surname; }

void Data::setPatronymic(const char* Patronymic)
{
    _Patronymic = _strdup(Patronymic);
}
char* Data::getPatronymic() const { return _Patronymic; }

void Data::setGroup(int group)
{
    if (group < 0) { throw EOutofrangeException(group, 0, 7000); }
    _group = group;
}
int Data::getGroup() const { return _group; }
void Data::setExam(const int* exam)//как-то начать контрольровать значения внутри и убивать если плохо
{
    for (int i = 0; i < SIZEexam; i++)
    {
        if ((exam[i] < 2) || (exam[i] > 5))
        {
            throw EOutofrangeException((int)exam[i]);
        }
        _exam[i] = exam[i];
    }
}
int* Data::getExam() const { return _exam; }

void Data::setTest(const int* test)
{
    for (int i = 0; i < SIZEtest; i++)
    {
        if ((test[i] < 2) || (test[i] > 5))
        {
            throw EOutofrangeException((int)test[i]);
        }
        _test[i] = test[i];
    }
}
int* Data::getTest() const { return _test; }

Data::~Data()
{
    delete[]_Name;
    delete[]_Surname;
    delete[]_Patronymic;
    delete[]_exam;
    delete[]_test;
}