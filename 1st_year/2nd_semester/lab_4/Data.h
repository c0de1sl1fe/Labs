#pragma once
#include <string.h>
#define SIZEexam 4
#define SIZEtest 3
class Data
{
private:
    char* _Name;
    char* _Surname;
    char* _Patronymic;
    int _group;
    int* _exam;
    int* _test;
public:
    Data(char* Name, char* Surname, char* Patronymic, int group, int* exam, int* test);
    Data();
    Data(const Data& a);
    void PrintData() const;
    void setName(const char* Name);
    char* getName() const;
    void setSurname(const char* Surname);
    char* getSurname() const;
    void setPatronymic(const char* Patronymic);
    char* getPatronymic() const;
    void setGroup(int group);
    int getGroup() const;
    void setExam(const int* exam);
    int* getExam() const;
    void setTest(const int* test);
    int* getTest() const;
    ~Data();
};