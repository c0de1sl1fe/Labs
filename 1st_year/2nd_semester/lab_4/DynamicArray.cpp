#define _CRT_SECURE_NO_WARNINGS
#include "DynamicArray.h"
#include "Data.h"
#include "EDataException.h"
#include <stdio.h>

char* StrSearch(char* str1, char* str2)
{
	char* strtmp1;
	char* strtmp2;
	while (*str2 == ' ')
	{
		str2++;
	}
	strtmp2 = str2;
	if (*strtmp2 == 0)
	{
		return str1;
	}
	while (*str1 != 0)
	{
		if (tolower(*str1) != tolower(*strtmp2))
		{
			str1++;
			continue;
		}
		strtmp1 = str1;
		while (true)
		{
			if (*strtmp2 == 0)
			{
				return str1;
			}
			if (tolower(*strtmp1++) != tolower(*strtmp2++))
			{
				break;
			}
		}
		strtmp2 = str2;
		str1++;
	}
	return NULL;
}

DynamicArray::DynamicArray() : _size(0), _capacity(0), _growth(5), _array(NULL) {};
DynamicArray::DynamicArray(const DynamicArray& a)
{
    _array = new Data*[a._size];
    _size = a._size;
    _capacity = a._capacity;
	_growth = a._growth;
    for (unsigned i = 0; i < a._size; i++) _array[i] = a._array[i];
}
int DynamicArray::GetSize()const { return _size; }

void DynamicArray::Create()
{
	if (_size == _capacity)
	{
		_capacity += _growth;
		Data** tmp = new Data * [_capacity];
		for (unsigned i = 0; i < _size; i++)
		{
			tmp[i] = _array[i];
		}
		Data* tmpelem = new Data();
		tmp[_size] = tmpelem;
		if (_size != 0)
		{
			for (unsigned i = 0; i < _size; i++)		// errorable place
			{
				delete _array[i];
			}
		}
		delete[]_array;
		_array = tmp;
		_size++;
	}
	else
	{
		Data* tmpelem = new Data();
		_array[_size] = tmpelem;
		_size++;
	}
}
void DynamicArray::PrintDynamicArray() const
{
	for (unsigned i = 0; i < _size; i++)
	{
		printf("\n№%u: ", i + 1);
		_array[i]->PrintData();
		printf("\n");
	}
}
void DynamicArray::ClearArray()
{
	if (_size == 0) throw EisEmpty("Нельзя удалить пустой массив");
    for (unsigned i = 0; i < _size; i++)
    {
        delete _array[i];
    }
    delete[]_array;
    _array = NULL;
    _size = 0;
    _capacity = 0;
}
void DynamicArray::DeleteElement(unsigned index)
{
	if (_size == 0) throw EisEmpty("Нельзя удалить несуществующий объект");
	if (index >= _size) throw EInvalidIndex(index, 0, _size);
	delete _array[index];
	for (unsigned i = index; i < _size - 1; i++)
	{
		_array[i] = _array[i + 1];
	}
	_size--;
}
DynamicArray::~DynamicArray()
{
	for (unsigned i = 0; i < _size; i++)
	{
		delete _array[i];
	}
    delete[]_array;
}
void DynamicArray::SortArray(int(*elemCmp)(Data*, Data*))
{
	if (_size == 0) return;
	for (unsigned i = 0; i < _size-1; i++)
	{
		bool swapped = false;
		for (unsigned j = 0; j < _size - i - 1; j++)
		{
			char* test1 = _array[i]->getSurname();
			char* test2 = _array[i + 1]->getSurname();
			if ((*elemCmp)(_array[j], _array[j + 1]) > 0)
			{
				Data* tmp = new Data(*_array[j]);
				delete _array[j];
				_array[j] = _array[j + 1];
				_array[j + 1] = tmp;
				swapped = true;
			}
		}
		if (!swapped) break;

	}
}
unsigned DynamicArray::FindSurname(char* str, unsigned begin)
{
	// вопрос нужно ли это?
	if (begin > _size) throw EInvalidIndex(begin, 0, _size);
	for (unsigned i = begin; i < _size; i++)
	{
		if (StrSearch(_array[i]->getSurname(), str)) { return i; }
	}
	return -1;
}
void DynamicArray::AddtoEnd(Data* addition)
{
	if (_size == _capacity)
	{
		_capacity += _growth;

		Data** tmp = new Data * [_capacity];

		memcpy(&tmp[0], &(_array[0]), sizeof(Data**) * (_size));
		tmp[_size] = addition;
		delete[]_array;
		_array = tmp;
		_size++;
	}
	else
	{
		_array[_size] = addition;
		_size++;
	}
}

void DynamicArray::AddBefore(Data* addition, unsigned index)
{
	//
	if (index >= _size) throw EInvalidIndex(index, 0, _size);
	if (_size == _capacity)
	{
		_capacity += _growth;
		Data** tmp = new Data * [_capacity];
		memcpy(&tmp[0], &(_array[0]), sizeof(Data**) * (index-1));
		tmp[index] = addition;
		memcpy(&tmp[index+1], &(_array[index]), sizeof(Data**) * (_size-index));
		delete[]_array;
		_array = tmp;
		_size++;
	}
	else
	{
		for (unsigned i = _size; i > index; i--)
		{
			_array[i] = _array[i - 1];
		}
		_array[index] = addition;
		_size++;
	}
}

void DynamicArray::ReadBinFile(const char* path)
{
	FILE* input = NULL;
	input = fopen(path, "rb");
	if (!input)
	{
		throw EFileException(path, "невозможно открыть файл");
	}
	unsigned count;
	int check = fread(&count, sizeof(unsigned), 1, input);
	if (check != 1)
	{
		throw EFileException(path, "Открываемый файл - пустой");
	}
	char* NameTmp = new char[128];
	char* SurnameTmp = new char[128];
	char* PatronymicTmp = new char[128];
	int groupTmp;
	int* examTmp = new int[SIZEexam];
	int* testTmp = new int[SIZEtest];

	unsigned length;
	for (unsigned i = 0; i < count; i++)
	{
		fread(&length, sizeof(unsigned), 1, input);
		fread(NameTmp, length, 1, input);
		NameTmp[length] = '\0';

		fread(&length, sizeof(unsigned), 1, input);
		fread(SurnameTmp, length, 1, input);
		SurnameTmp[length] = '\0';

		fread(&length, sizeof(unsigned), 1, input);
		fread(PatronymicTmp, length, 1, input);
		PatronymicTmp[length] = '\0';

		fread(&groupTmp, sizeof(int), 1, input);

		fread(&length, sizeof(unsigned), 1, input);
		fread(examTmp, sizeof(unsigned), length, input);

		fread(&length, sizeof(unsigned), 1, input);
		fread(testTmp, sizeof(unsigned), length, input);

		Data* tmp = new Data(NameTmp, SurnameTmp, PatronymicTmp, groupTmp, examTmp, testTmp);
		AddtoEnd(tmp);
	}
	delete[] NameTmp;
	delete[] SurnameTmp;
	delete[] PatronymicTmp;
	delete[] examTmp;
	delete[] testTmp;
	fclose(input);
}
void DynamicArray::WriteBinFile(const char* path)
{

	FILE* output = NULL;
	output = fopen(path, "wb+");
	if (!output)
	{
		throw EFileException(path, "невозможно открыть файл");
		return;
	}
	fwrite(&_size, sizeof(unsigned), 1, output);
	unsigned length;
	for (unsigned i = 0; i < _size; i++)
	{
		length = strlen(_array[i]->getName());
		fwrite(&length, sizeof(unsigned), 1, output);
		fwrite(_array[i]->getName(), length, 1, output);

		length = strlen(_array[i]->getSurname());
		fwrite(&length, sizeof(unsigned), 1, output);
		fwrite(_array[i]->getSurname(), length, 1, output);

		length = strlen(_array[i]->getPatronymic());
		fwrite(&length, sizeof(unsigned), 1, output);
		fwrite(_array[i]->getPatronymic(), length, 1, output);

		int group = _array[i]->getGroup();
		fwrite(&group, sizeof(int), 1, output);

		length = SIZEexam;
		fwrite(&length, sizeof(unsigned), 1, output);
		fwrite(_array[i]->getExam(), sizeof(unsigned), length, output);

		length = SIZEtest;
		fwrite(&length, sizeof(unsigned), 1, output);
		fwrite(_array[i]->getTest(), sizeof(unsigned), length, output);
	}
	fclose(output);
}

Data* DynamicArray::GetElement(unsigned index) const
{
	if (index >= _size || index < 0) throw EInvalidIndex(index, 0, _size);
	return _array[index];
}
Data* DynamicArray::GetElementS(unsigned index)
{
	if (index >= _size || index < 0) throw EInvalidIndex(index, 0, _size);
	char* NameTmp = _strdup(_array[index]->getName());
	char* SurnameTmp = _strdup(_array[index]->getSurname());
	char* PatronymicTmp = _strdup(_array[index]->getPatronymic());
	int groupTmp = _array[index]->getGroup();
	int* examTmp = new int[SIZEexam];
	int* testTmp = new int[SIZEtest];
	for (unsigned i = 0; i < SIZEexam; i++)
	{
		examTmp[i] = _array[index]->getExam()[i];
	}

	
	for (unsigned i = 0; i < SIZEtest; i++)
	{
		testTmp[i] = _array[index]->getTest()[i];
	}
	Data* tmp = new Data(NameTmp, SurnameTmp, PatronymicTmp, groupTmp, examTmp, testTmp);

	delete[] NameTmp;
	delete[] SurnameTmp;
	delete[] PatronymicTmp;
	delete[] examTmp;
	delete[] testTmp;
	return tmp;
}