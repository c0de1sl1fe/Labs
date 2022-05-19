#include <stdio.h>
#include <locale>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <Windows.h>
//test
//тесе

int placeofterminator = 0;
int spacebefore = 0, spaceafter = 0;

void PrintMenu()
{

	printf("Здравствуйте, это меню, выберите, пожалуйста, пункт: \n");
	printf("1. Ввести предложение и после взять все глаголы неопределенной формы в скобки \n");
	printf("2. Выйти \n");

	printf("Введите значение: ");
}
void puttingVerbIntoBracket(char sentence[], char arr1[], int i, int placeofterminator, int spaceafter, int spacebefore)
{
	for (int i1 = i; (sentence[i1] == arr1[6]) || (i1 >= 0); i1--)
	{

		spacebefore = i1;
		if (sentence[i1] == arr1[6])
		{
			spacebefore = i1 + 1;
			break;
		}
	}
	for (int j = placeofterminator + 1; j > spaceafter; j--) // braker after verb
	{
		sentence[j] = sentence[j - 1];
	}
	sentence[spaceafter] = arr1[5];
	for (int j = placeofterminator + 2; j > spacebefore; j--) // braker before verb
	{
		sentence[j] = sentence[j - 1];
	}

	sentence[spacebefore] = arr1[4];
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int choice = 1;
	bool exit = false;

	const int size = 255;
	char arr1[] = "ться() ТЬСЯ ";
	char sentence[size] = "Люблю думаТЬ ";



	while (!exit)
	{
		PrintMenu();
		//scanf_s("%d", &choice);

		switch (choice)
		{

		case (1):
		{
			printf("\nВот тут вводить текст: ");
			gets_s(sentence);
			printf("\n\n");
			printf("%s\n", sentence);

			for (int i = 0; i < size; i++)
			{
				if (sentence[i] == '\0')
				{
					placeofterminator = i;
					break;
				}
			}

			for (int i = 0; ((i < size) && (sentence[i] != '\0')); i++)
			{
				if ( ((sentence[i] == arr1[0]) && (sentence[i + 1] == arr1[1])) || ((sentence[i] == arr1[7]) && (sentence[i + 1] == arr1[8])) )
				{
					if ((sentence[i + 2] != arr1[2])||(sentence[i + 2] != arr1[9]))				// вариант для ть
					{
						spaceafter = i + 2;
						puttingVerbIntoBracket(sentence, arr1, i, placeofterminator, spaceafter, spacebefore);
						i += 1;
						placeofterminator += 2;
					}


					else										// вариант для ться
					{
						spaceafter = i + 4;
						puttingVerbIntoBracket(sentence, arr1, i, placeofterminator, spaceafter, spacebefore);
						i += 1;
						placeofterminator += 2;
					}
				}
			}


			printf("%s\n\n", sentence);
			break;





		}


		case (2):
		{
			printf("Выполняется пункт 2, до скорых встреч!");
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
