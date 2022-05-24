#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
struct node
{
    int x;
    int y;
    struct node* next;
};


void clear(node** head);
node* findNode(node* head, int n);
node* del(node* head, int number);
void print_list(node* head);
void add_last(node** head);
node* add(node* cur);

void printMenu()
{
    printf("Здравствуйте, выберите действие: ");

    printf("\nРабота со списком: 1");
    printf("\nВыполнить задачу лабораторной работы: 2");
    printf("\nОтчистить список: 3");
    printf("\nВыйти: 4\n");
}
void printMenu2()
{
    printf("Выберите действие: ");

    printf("\nВывести весь список: 1");
    printf("\nДобавить значение(в конец): 2");
    printf("\nУдалить элемент: 3");
    printf("\nВыйти: 4\n");
}
void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    node* head = NULL;
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
            int choice2;
            bool exit2 = false;
            while (!exit2)
            {
                printMenu2();
                scanf_s("%d", &choice2);
                switch (choice2)
                {
                case(1):
                {
                    print_list(head);
                    break;
                }
                case(2):
                {
                    add_last(&head);
                    break;
                }
                case(3):
                {
                    int number;
                    printf("Введите номер узла, который хотите удалить(номер головы 1): ");
                    scanf_s("%d", &number);
                    while (number < 1)
                    {
                        printf("Что-то пошло не так, попробуйте заново\n");
                        scanf_s("%d", &number);
                    }
                    head = del(head, number);
                    break;
                }
                case(4):
                {
                    printf("\nДо свидания\n");
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

        case(2):
        {
            int n, k;
            printf("Введите, пожалуйста, номер точки: ");
            scanf_s("%d", &n);
            while (n < 1)
            {
                printf("Что-то пошло не так, попробуйте заново\n");
                scanf_s("%d", &n);
            }
            printf("Введите, пожалуйста, количество копий: ");
            scanf_s("%d", &k);
            while (k < 1)
            {
                printf("Что-то пошло не так, попробуйте заново\n");
                scanf_s("%d", &k);
            }

            node* dublicate = findNode(head, n);
            if (!dublicate) break;
            for (int i = 0; i < k; i++)
            {
                dublicate = add(dublicate);
            }
            break;

        }
        case(3):
        {
            clear(&head);
            break;
        }
        case(4):
        {
            exit = true;
            break;
        }
        default:
            printf("Please try again\n");
            break;
        }
    }
    clear(&head);
}

node* del(node* head, int number)
{
    int i = 1;
    if (head == NULL)
    {
        printf("\nСписок пуст\n");
        return NULL;
    }
    node* tmp = head, * pointer = NULL;
    while ((tmp) && (i != number))
    {
        pointer = tmp;
        tmp = tmp->next;
        i++;
    }
    if (tmp == head)
    {
        pointer = tmp->next;
        free(tmp);
        return pointer;
    }
    if (!tmp)
    {
        printf("Данного элемента в списке нет\n");
        return head;
    }
    pointer->next = tmp->next;
    free(tmp);
    return (head);
}

node* add(node* cur)
{
    if (cur == NULL) return(NULL);

    node* tmp;
    tmp = (node*)malloc(sizeof(node));
    tmp->next = cur->next;
    tmp->x = cur->x;
    tmp->y = cur->y;
    cur->next = tmp;
    return(tmp);
}

node* findNode(node* head, int n)
{
    int i = 1;
    if (head == NULL)
    {
        printf("\nСписок пуст\n");
        return NULL;
    }
    node* tmp = head;
    while ((tmp) && (i != n))
    {
        tmp = tmp->next;
        i++;
    }
    if (tmp == head)
    {
        return tmp;
    }
    if (!tmp)
    {
        printf("Данного элемента в списке нет\n");
        return head;
    }
    return (tmp);
}

void clear(node** head)
{
    node* p;
    while (*head)
    {
        p = *head;
        *head = (*head)->next;
        free(p);
    }
}

void add_last(node** head)
{
    int x, y;
    printf("\nВведите значение элемента: ");
    scanf_s("%d", &x);
    printf("Введите значение элемента: ");
    scanf_s("%d", &y);
    getchar();
    node* tmp;
    tmp = (node*)malloc(sizeof(node));
    tmp->x = x;
    tmp->y = y;
    tmp->next = NULL;
    node* pointer = *head;
    if (*head == NULL) *head = tmp;
    else
    {
        while (pointer->next != NULL) pointer = pointer->next;
        pointer->next = tmp;
    }
}
void print_list(node* head)
{
    while (head)
    {
        printf("[%d, %d]->", head->x, head->y);
        head = head->next;
    }
    printf("NULL\n");
}

