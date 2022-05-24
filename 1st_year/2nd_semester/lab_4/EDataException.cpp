#define _CRT_SECURE_NO_WARNINGS
#include "EDataException.h"
#include <string.h>
#include <stdio.h>

EDataException::EDataException(const char* err)
{
    strncpy(_err, err, 255);
    _err[255] = 0;
}
void EDataException::Print()
{
    printf("\n%s", _err);
}
EDataException::~EDataException(){}


EInvalidIndex::EInvalidIndex(unsigned index, unsigned min, unsigned max) : EDataException("Некорректный индекс: "), _index(index), _min(min), _max(max){}
void EInvalidIndex::Print()
{
	EDataException::Print();
	if (_min == _max)
	{
		printf("Индекс с номером %d не принадлежит { пустому множетсву }\n", _index);
	}
	else
	{
		printf("Индекс с номером %d не принадлежит [%d, %d]\n", _index, _min, _max - 1);
	}
}
EInvalidIndex::~EInvalidIndex() {}


EFileException::EFileException(const char* path, const char* details) : EDataException("Ошибка работы с файлом: ")
{
	strncpy(_details, details, 127);
	_details[127] = 0;
	strncpy(_path, path, 127);
	_path[127] = 0;
}
void EFileException::Print()
{
	EDataException::Print();
	printf("\n%s %s\n", _path, _details);
}
EFileException::~EFileException(){}


EOutofrangeException::EOutofrangeException(int index, int min, int max) : EDataException("Некорректное число: "), _number(index), _min(min), _max(max) {}
void EOutofrangeException::Print()
{
	EDataException::Print();
	if (_min == _max)
	{
		printf("Элемента со значением %d не равен числу %d\n", _number, _max);
	}
	else
	{
		printf("Элемент со значением %d не принадлежит [%d, %d]\n", _number, _min, _max);
	}
}
EOutofrangeException::~EOutofrangeException(){}


EisEmpty::EisEmpty(const char* details) :EDataException("Массив пуст.")
{
	strncpy(_details, details, 127);
	_details[127] = 0;
}
void EisEmpty::Print()
{
	EDataException::Print();
	printf("%s", _details);
}
EisEmpty::~EisEmpty() { }