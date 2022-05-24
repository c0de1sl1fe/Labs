#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <ctime>
using namespace std;

class Progression
{
protected:
	double a;
	double b;
public:
	Progression(double a = 0, double b = 0) : a(a), b(b) {};
	virtual ~Progression() = default;

	virtual double element(int n) const = 0;
	virtual void Print() const = 0;
	virtual double Sum(int n) const = 0;
	double getA()const { return a; }
	double getB()const { return b; }
	void setA(double a) { this->a = a; }
	void setB(double b) { this->b = b; }
};

class Arithmetic : public Progression
{
public:
	Arithmetic(double start = 0, double step = 0): Progression(start, step) {}
	double element(int i)const { return a + (((double)i - 1) * b); }
	double Sum(int n)const { return (2 * a + ((double)n - 1) * b) * n / 2; }
	void Print()const
	{
		printf("Arithemtic progression start %lf, step: %lf", a, b);
	}
};

class Geometric : public Progression
{
public:
	Geometric(double start = 0, double step = 0) : Progression(start, step) {}
	double element(int i)const { return a * pow(b, i - 1); }
	double Sum(int n)const 
	{ 
		if (b != 1)
		{
			return a * (1 - pow(b, n)) / (1 - b);
		}
		return n * a;
	}
	void Print()const
	{
		printf("Geometric progression start: %lf, step: %lf", a, b);
	}
};

void Menu()
{
	printf("Choose one:\n");
	printf("1. Работать с массивом значений\n");
	printf("2. Выполнить задание лабораторной работы\n");
	printf("3. Exit\n");
	printf("Choice: ");
}
void SubMenu_1()
{
	printf("Choose one:\n");
	printf("1. Создание элемента\n");
	printf("2. Добавить в конец случайный элемент\n");
	printf("3. Удалить элемент по индексу\n");
	printf("4. Удалить весь массив\n");
	printf("5. Вывод коллекции(но не по заданию)\n");
	printf("6. Exit\n");
	printf("Choice: ");
}
void SubMenu_2()
{
	printf("Choose one:\n");
	printf("1. Расчет значение i'ого элемента прогрессии\n");
	printf("2. Расчет суммы первых n членов прогрессии\n");
	printf("3. Вывод прогрессий и значений до некоторого n\n");
	printf("4. Exit\n");
	printf("Choice: ");	
}

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

Progression * CreateElement(int type, double start, double step)
{
	if (type == 1)
	{
		return new Arithmetic(start, step);
	}
	if (type == 2)
	{
		return new Geometric(start, step);
	}
	return NULL;
}
void AddToArray(int* size, Progression*** array, Progression* element)
{
	if (element == NULL) { return; }
	Progression** tmparray = new Progression * [*size + 1];
	memcpy(&tmparray[0], &(*array[0]), sizeof(Progression**) * (*size));
	//for (int i = 0; i < *size; i++)
	//{
	//	tmparray[i] = (*array)[i];
	//}
	if ((*size) != 0)
	{
		delete[] * array;
	}
	*array = tmparray;
	(*array)[*size] = element;
	(*size)++;
}
void PrintArray(Progression** array, int size)
{
	if (size == 0)
	{
		printf("Список пуст\n");
	}
	for (int i = 0; i < size; i++)
	{
		printf("%d. ", i + 1);
		array[i]->Print();
		cout << endl;
	}
}

void ClearArray(Progression** array, int size)
{
	for (int i = 0; i < size; i++) delete[] array[i];
	delete[] array;
}

void DeleteCertainElement(Progression*** array, int* size, int number)
{
	Progression** tmparray = new Progression * [*size - 1];
	for (int i = 0; i < *size; i++)
	{
		if (i == number - 1)
		{
			tmparray[i] = (*array)[i + 1];
			i++;
			continue;
		}
		tmparray[i] = (*array)[i];
	}
	if ((*size != 0))
	{
		delete[] * array;
	}
	*array = tmparray;
	(*size)--;
}

void PrintArrayWithSum(Progression** array, int size, int n)
{
	if (size == 0)
	{
		printf("Список пуст\n");
	}
	for (int i = 0; i < size; i++)
	{
		printf("%d. ", i + 1);
		array[i]->Print();
		cout << " ";
		cout <<"Sum: "<< array[i]->Sum(n);
		cout << endl;
	}
}

void main()
{
	srand(time(NULL));

	setlocale(LC_ALL, "Rus");
	bool exit = false;
	int choice = 0;
	Progression** array = NULL;
	int size = 0;
	while (!exit)
	{
		Menu();
		cin >> choice;
		int subchoice = 0;
		bool subexit = false;
		int tmp = 0;
		double tmpa, tmpb;
		switch (choice)
		{
		case(1):
		{
			while (!subexit)
			{
				SubMenu_1();
				cin >> subchoice;
				switch (subchoice)
				{
				case(1):
				{
					cout << "Выберите тип прогрессии: 1. Арифметическая 2. Геометрическая: ";
					tmp = (int)EnterNumber();
					while ((tmp != 1) && (tmp != 2))
					{
						cout << "Error with type of progression" << endl;
						tmp = (int)EnterNumber();
					}
					cout << "Введите первый элемент прогрессии: ";
					tmpa = EnterNumber();
					cout << "Введите шаг прогрессии: ";
					tmpb = EnterNumber();
					AddToArray(&size, &array, CreateElement(tmp, tmpa, tmpb));
					break;
				}
				case(2):
				{
					tmp = 1 + rand() % 2;
					tmpa = 1 + rand() % 6;
					tmpb = 1 + rand() % 5;
					AddToArray(&size, &array, CreateElement(tmp, tmpa, tmpb));
					break;
				}
				case(3):
				{
					cout << "Введите номер элемента, который хотите удалить" << "(размер массива: " << size << "): ";
					int number = (int)EnterNumber();
					while ((number < 1) || (number > size + 1))
					{
						cout << "Счет начинатеся с 1: ";
						number = (int)EnterNumber();
					}
					DeleteCertainElement(&array, &size, number);
					break;
				}
				case(4):
				{
					if ((array == NULL) || (size == 0))
					{
						cout << "array is clear btw" << endl;
					}
					else
					{
						ClearArray(array, size);
						array = NULL;
						size = 0;
						cout << "array is clear now" << endl;
					}
					break;
				}
				case(5):
				{
					system("cls");
					PrintArray(array, size);
					break;
				}
				case(6):
				{
					cout << "Bye!" << endl;
					subexit = true;
					break;
				}
				default:
					cout << "fail" << endl;
					break;
				}
			}
			break;
		}
		case(2):
		{
			while (!subexit)
			{
				SubMenu_2();
				cin >> subchoice;
				int n;
				switch (subchoice)
				{
				case(1):
				{
					cout << "Выберите тип прогрессии: 1. Арифметическая 2. Геометрическая: ";
					tmp = (int)EnterNumber();
					while ((tmp != 1) && (tmp != 2))
					{
						cout << "Error with type of progression" << endl;
						tmp = (int)EnterNumber();
					}

					if (tmp == 1)
					{
						Arithmetic a;
						cout << "Введите первый элемент прогрессии: ";
						a.setA(EnterNumber());
						cout << "Введите шаг прогрессии: ";
						a.setB(EnterNumber());
						cout << "Введите номер элемента: ";
						n = (int)EnterNumber();
						while (n < 1)
						{
							cout << "Счет начинатеся с 1: ";
							n = (int)EnterNumber();
						}
						printf("Искомый %d-элемент: %lf\n", n, a.element(n));
					}
					else
					{
						Geometric b;
						cout << "Введите первый элемент прогрессии: ";
						b.setA(EnterNumber());
						cout << "Введите шаг прогрессии: ";
						b.setB(EnterNumber());
						cout << "Введите номер элемента: ";
						n = (int)EnterNumber();
						while (n < 1)
						{
							cout << "Счет начинатеся с 1: ";
							n = (int)EnterNumber();
						}
						printf("Искомый %d-элемент: %lf\n", n, b.element(n));
					}
					break;
				}
				case(2):
				{
					cout << "Выберите тип прогрессии: 1. Арифметическая 2. Геометрическая: ";
					int tmp = (int)EnterNumber();
					while ((tmp != 1) && (tmp != 2))
					{
						cout << "Error with type of progression" << endl;
						tmp = (int)EnterNumber();
					}

					if (tmp == 1)
					{
						Arithmetic a;
						cout << "Введите первый элемент прогрессии: ";
						a.setA(EnterNumber());
						cout << "Введите шаг прогрессии: ";
						a.setB(EnterNumber());
						cout << "Введите номер конечного элемента: ";
						n = (int)EnterNumber();
						while (n < 1)
						{
							cout << "Счет начинатеся с 1: ";
							n = (int)EnterNumber();
						}
						printf("Сумма первых %d элементов арифметической прогрессии: %lf\n", n, a.Sum(n));
					}
					else
					{
						Geometric b;
						cout << "Введите первый элемент прогрессии: ";
						b.setA(EnterNumber());
						cout << "Введите шаг прогрессии: ";
						b.setB(EnterNumber());
						cout << "Введите номер конечного элемента: ";
						n = (int)EnterNumber();
						while (n < 1)
						{
							cout << "Счет начинатеся с 1: ";
							n = (int)EnterNumber();
						}
						printf("Сумма первых %d элементов геометриче: %lf\n", n, b.Sum(n));
					}
					break;
				}
				case(3):
				{
					cout << "Введите количество суммируемых членов: ";
					n = (int)EnterNumber();
					while (n < 1)
					{
						cout << "Счет начинатеся с 1: ";
						n = (int)EnterNumber();
					}
					PrintArrayWithSum(array, size, n);
					//сюда нужно вставить функцию похожую на вывод всех элементов 
					//в массиве, но с небольшой хитростью в виде фукции подсчета сумммы
					break;
				}
				case(4):
				{
					cout << "Bye!" << endl;
					subexit = true;
					break;
				}
				default:
					cout << "fail" << endl;
					break;
				}
			}
			break;

		}
		case(3):
		{
			cout << "Bye!" << endl;
			exit = true;
			break;
		}
		default:
			cout << "fail" << endl;
			break;
		}
	}
	ClearArray(array, size);
}