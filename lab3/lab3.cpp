#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <process.h>
#include <Windows.h>
#define BRANCH 5

typedef struct BTnode {//Структура вузла дерева
    struct BTnode* left;//Покажчик на ліву вершину
    int key;//поле ключ
    struct BTnode* right;//Покажчик на праву вершину
};


typedef struct Tree_desc {//Дескриптор дерева
    int size;//к-сть вершин
    BTnode* root;//корінь дерева
};


void printfile(FILE* fp, BTnode* tree);//друк дерева у файл
void preOrder(BTnode* node);//прямий обхід
void inOrder(BTnode* node);//симетричний обхід
void postOrder(BTnode* node);//зворотній обхід
void clear_Tree(BTnode* node);//очистити дерево
void print_tree(Tree_desc* const_root, BTnode* tree, short x, short y, char c);
//візуалізація дерева
int height_tree(BTnode* node);//функція отримання висоти дерева
int GetSize(Tree_desc* tree);//перевірка на порожнечу
int countStrs(FILE* fd);//к-сть строк у файлі
int scann(int& N);//зчитування числа
void tree_print(BTnode* tree, int depth, char* path, int direction);//візуалізація дерева

void prepare_print(BTnode* tree);//вивід дерева



BTnode* Add(Tree_desc* dsTree, BTnode* subTree, int key);//додавання ел-тів до дерева
BTnode* search(BTnode* root, int key);//пошук вершини
BTnode* remove(BTnode* root, int key);//видалення вершини

Tree_desc* readfile(FILE* fp, Tree_desc* tree);//читання з файлу
Tree_desc* createTree(void);//створення дерева
int main()

{

    FILE* fp = NULL;        //дескриптор файлу
    Tree_desc* tree = NULL; //вершина
    BTnode* temproot = NULL;//тимчасова вершина
    BTnode* temp = (BTnode*)malloc(sizeof(BTnode));//виділення пам'яті під вершину
    

        if (!temp) {
            puts("Помилка виділення пам'яті");
            return 0;
        }


    char filename[256]; //назва файлу
    int howmany;        //змінна пункту меню
    int menu;           //змінна пункту меню
    int initm;          //змінна пункту меню
    int findkey;        //змінна пункту меню
    int removekey;      //змінна пункту меню
    int key;            //ключ
    int swork;          //змінна пункту меню
    int low;
    int high;


    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    do {

        puts("Виберіть пункт меню");
        puts("0)Створити дерево\n1)Додати елементи до дерева\n2)Вивести  дерево\n3)Знайти елемент\n4)Видалення дерева");
            puts("5)Видалити вузол\n6)Записати дерево у файл\n7)Зчитати дерево з файлу\n8)Висота дерева\n9)Перевірка на порожнечу\n10)Завершити роботу\n11)Дерево як дерево");
                puts("12)cls");
        scann(menu);

        if (menu > 12 || menu < 0)
        {
            puts("Невірний пункт меню,повторіть введення");
            break;
        }


        switch (menu)
        {
        case 0:

            tree = createTree();
            if (createTree == NULL)
            {
                puts("Something went wrong");
                exit(0);
            }
            puts("Створено!");

            break;

        case 1: {

            if (!tree)
            {
                puts("Дерева не існує");
                break;

            }

            puts("Як хочете ввести данні \n1)Вручну\n2)Kлюч з файлу\n3)рандомно");
            scann(swork);
            switch (swork) {

            case 1:
                puts("Скільки елементів хочете додати ?");
                scann(howmany);

                for (int i = 0; i < howmany; i++) {
                    puts("Введіть ключ");
                    scann(key);
 

                    temproot = search(tree->root, key);//якщо було знайдено такий ключ
                    
                        if (temproot != NULL)
                        {

                            puts("Такий ключ вже існує його буде перезаписано");

                        }

                    if (tree->root == NULL)
                    {
                        tree->root = Add(tree, tree->root, key);//додавання елементів
                        
                    }
                    else
                    {
                        Add(tree, tree->root, key);
                    }
                    if (Add == NULL)
                    {
                        puts("Something went wrong");
                        exit(0);
                    }


                }
                puts("Додано!");
                break;
            case 2:

            {
                puts("Введіть назву файлу:");
                do {
                    fgets(filename, 1024, stdin);
                    if (filename[0] == '\n') {
                        printf("Текст не повинен бути пустим, спробуйте ще раз:");
                    }
                } while (filename[0] == '\n');
                filename[strlen(filename) - 1] = '\0';
                if (filename[strlen(filename) - 4] != '.' && filename[strlen(filename) - 3] != 't' && filename[strlen(filename) - 2] != 'x' &&
                    filename[strlen(filename) - 1] != 't') {
                    strcat(filename, ".txt");
                }
                if ((fp = fopen(filename, "r")) == NULL)
                {
                    printf("Виникла помилка при відкритті файлу %s! \n", filename);
                    return 1;
                }


                int c_l = countStrs(fp);


                puts("Однакові ключі буде перезаписано");
                for (int j = 0; j <= c_l; j++)
                {

                    fscanf(fp, "%d", &key);





                    if (tree->root == NULL)
                    {
                        tree->root = Add(tree, tree->root, key);
                    }
                    else
                    {
                        Add(tree, tree->root, key);
                    }
                    if (Add == NULL)
                    {
                        puts("Something went wrong");
                        exit(0);
                    }

                }
                puts("Додано!");
                break;
            }
            case 3:
            {
                printf("Введіть границі рандому:\n");
                printf("Введіть нижню границю рандому:");
                scanf("%d", &low);

                printf("Введіть верхню границю рандому:");
                scanf("%d", &high);

                if (low > high)
                {

                    printf("Low must be < then high");
                    break;
                }

                key = low - 1 + rand() % ((high - low) + 1); ;

                if (tree->root == NULL)
                {
                    tree->root = Add(tree, tree->root, key);
                }
                else
                {
                    Add(tree, tree->root, key);
                }
                if (Add == NULL)
                {
                    puts("Something went wrong");
                    exit(0);
                }
                break;
            }
            }

            break;
        }
        case 2:
        {
            if (!tree)
            {
                puts("Дерева не існує");
                break;

            }

            puts("1.Симетричний\n2.Прямий\n3.Зворотній");
            scann(initm);
            switch (initm) {
            case 1:
                puts("Симетричний:\n");
                inOrder(tree->root);
                break;
            case 2:
                puts("Прямий:\n");
                preOrder(tree->root);
                break;
            case 3:
                puts("Зворотній:\n");
                postOrder(tree->root);
                break;
            }
            puts("Виведено!");
            break;
        }
        case 3:
            if (!tree)
            {
                puts("Дерева не існує");
                break;

            }

            puts("Введіть ключ");
            scann(findkey);

            temproot = search(tree->root, findkey);
            if (temproot == NULL)
            {

                puts("Такого ключа не було знайдено!");
                break;
            }
            if (search == NULL)
            {
                puts("Something went wrong");
                exit(0);
            }
            printf("%d\n", temproot->key);
            puts("Знайдено!");
            break;

        case 4:

            if (!tree)
            {
                puts("Дерева не існує");
                break;

            }
            puts("1)Без дескриптора\n2)З дескриптором");
            int cle_tree;
            scanf("%d", &cle_tree);
            if (cle_tree == 1)
            {
                clear_Tree(tree->root);
            }
            else if (cle_tree == 2)
            {
                clear_Tree(tree->root);
                free(tree);
                tree = NULL;

            }
            if (clear_Tree == NULL)
            {
                puts("Something went wrong");
                exit(0);
            }
            puts("Очищено!");
            break;

        case 5:

            if (!tree)
            {
                puts("Дерева не існує");
                break;

            }

            puts("Введіть ключ");
            scann(removekey);
            temproot = search(tree->root, removekey);
            if (temproot != NULL)
            {
                tree->root = remove(tree->root, removekey);
                tree->size--;
            }
            else
            {

                puts("Такого ключа не знайдено");

            }

            puts("Done!");
            break;

        case 6:
            if (!tree)
            {
                puts("Дерева не існує");
                break;

            }
            if (tree->root == NULL)
            {
                printf("Створено лише дескриптор!\n");
                break;
            }
            puts("Введіть назву файлу:");
            do {
                fgets(filename, 1024, stdin);
                if (filename[0] == '\n') {
                    printf("Текст не повинен бути пустим, спробуйте ще раз:");
                }
            } while (filename[0] == '\n');
            filename[strlen(filename) - 1] = '\0';
            if (filename[strlen(filename) - 4] != '.' && filename[strlen(filename) - 3] !=
                'b' && filename[strlen(filename) - 2] != 'i' &&
                filename[strlen(filename) - 1] != 'n') {
                strcat(filename, ".bin");
            }
            if ((fp = fopen(filename, "wb+")) == NULL)
            {
                printf("Виникла помилка при відкритті файлу %s! \n", filename);
                return 1;
            }
            printfile(fp, tree->root);
            if (fclose(fp) == EOF)
            {
                printf("Виникла помилка при закритті файлу %s! \n", filename);
                return 1;
            }
            puts("Записано!");

            break;
        case 7:
            if (!tree)
            {
                tree = createTree();
            }
            clear_Tree(tree->root);
            puts("Введіть назву файлу:");
            do {
                fgets(filename, 1024, stdin);
                if (filename[0] == '\n') {
                    printf("Текст не повинен бути пустим, спробуйте ще раз:");
                }
            } while (filename[0] == '\n');
            filename[strlen(filename) - 1] = '\0';
           
            if ((fp = fopen(filename, "rb")) == NULL)
            {
                printf("Виникла помилка при відкритті файлу %s! \n", filename);
                return 1;
            }
            tree = readfile(fp, tree);
            if (fclose(fp) == EOF)
            {
                printf("Виникла помилка при закритті файлу %s! \n", filename);
                return 1;
            }
            puts("Зчитано!");
            break;
        case 8:
            if (!tree)
            {
                puts("Дерева не існує");
                break;

            }
            int height;
            height = height_tree(tree->root);
            printf("Висота дерева : %d\nК-сть елементів: %d\n", height, tree->size);
            break;

        case 9:

            if (!tree) {
                puts("Дерева не існує");
                break;

            }

            if (GetSize(tree) == 0)
            {
                puts("Дерево порожнє,к-сть вузлів 0");

            }
            else
            {

                puts("Дерево не порожнє");
            }
            break;

        case 10:
            return 0;
            break;

        case 11:
            if (!tree) {
                puts("Дерева не існує");
                break;


            }
            system("cls");
            prepare_print(tree->root);
            break;


        case 12:
            system("cls");
            break;
        }



    } while (menu != 13);

    _getch();
    return 0;

}

/*Функція createTree
Функція створення дерева
Результат:
Створене дерево
*/

Tree_desc* createTree(void) {
    Tree_desc* dsBST;
    dsBST = (Tree_desc*)malloc(sizeof(Tree_desc));
    if (!dsBST) {
        return NULL;
    }
    dsBST->root = NULL;
    dsBST->size = 0;
    return dsBST;
}




/*Функція Add
Функція додавання вершин
Вхід:
dsTree - дескриптор дерева, передача по посиланню
subTree - корінь дерева, передача по посиланню
key - ключ, передача за значенням
Результат:
Додана вершина
*/

BTnode* Add(Tree_desc* dsTree, BTnode* subTree, int key) {

   

    if (!subTree) {
        subTree = (BTnode*)malloc(sizeof(BTnode));
        if (!subTree)
        {
            return NULL;
        }
        int tmp;       
        tmp = key;
        subTree->key = tmp;


        subTree->left = subTree->right = NULL;
        dsTree->size++;
        return (subTree);
    }
    else if (subTree->key == key)
    {
        return subTree;
    }
    else if (subTree->key > key)
    {
        subTree->left = Add(dsTree, subTree->left, key);//пірнаємо у ліве піддерево
        

    }
    else if (subTree->key < key)
    {
        subTree->right = Add(dsTree, subTree->right, key);//пірнаємо у праве піддерево
        

    }
    return subTree;
}

/*Функція search
Функція пошуку вершини
Вхід:і
root - корінь дерева, по посиланню
key - ключ, передача за значенням
Результат:
Знайдена вершина
*/

BTnode* search(BTnode* root, int key) {
    if (!root)
    {
        return NULL;
    }
    if (root->key == key)
    {
        return (root);
    }
    else if (root->key > key)
    {
        return (search(root->left, key));////пірнаємо у ліве піддерево
    }
    else
    {
        return (search(root->right, key));//пірнаємо у праве піддерево
    }
}

/*Функція min_root
Функція знаходження термінальної вершини
Вхід:
root - корінь дерева, передача по посиланню
Результат:
Знайдена термінальна вершина
*/

BTnode* min_root(BTnode* root)
{
    return root->left ? min_root(root->left) : root;
}

/*Функція remove_min_root
Функція знаходження термінальної вершини
Вхід:
root - корінь дерева, передача по посиланню
Результат:
Знайдена термінальна вершина
*/

BTnode* remove_min_root(BTnode* node)
{
    BTnode* current = node;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

/*Функція remove
Функція видалення вершин
Вхід:
root - корінь дерева, передача по посиланню
key - ключ, передача за значенням
Результат:
Видалена вершина
*/

BTnode* remove(BTnode* root, int key)
{
    if (root == NULL)
    {
        return root;
    }
    if (key < root->key)
    {
        root->left = remove(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = remove(root->right, key);
    }

    else
    {
        if (root->left == NULL)
        {
            BTnode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            BTnode* temp = root->left;
            free(root);
            return temp;
        }
        BTnode* temp = remove_min_root(root->right);

        root->key = temp->key;

        root->right = remove(root->right, temp->key);

    }
    return root;
}

/*Функція inOrder
Функція обходу дерева
Вхід:
tree - корінь дерева, передача по посиланню
Результат:
Виведене дерево
*/

void inOrder(BTnode* tree) {
    if (tree) {
        inOrder(tree->left);
        printf("%d\n ", tree->key);
        inOrder(tree->right);
    }
    return;
}




/*Функція preOrder
Функція обходу дерева
Вхід:
tree - корінь дерева, передача по посиланню
Результат:
Виведене дерево
*/

void preOrder(BTnode* tree) {
    if (tree) {
        printf("%d\n ", tree->key);
        preOrder(tree->left);
        preOrder(tree->right);
    }
    return;
}

/*Функція postOrder
Функція обходу дерева
Вхід:
tree - корінь дерева, передача по посиланню
Результат:
Виведене дерево
*/

void postOrder(BTnode* tree) {
    if (tree) {
        postOrder(tree->left);
        postOrder(tree->right);
        printf("%d\n ", tree->key);
    }
    return;
}


/*Функція clear_Tree
Функція очищення дерева
Вхід:
node - корінь дерева, передача по посиланню
Результат:
Очищене дерево
*/

void clear_Tree(BTnode* node)
{
    if (node)
    {
        clear_Tree(node->left);
        clear_Tree(node->right);
        free(node);
    }
}

/*Функція printfile
Функція друку дерева у файл
Вхід:
fp - дескриптор файлу,передача за значенням
node - корінь дерева, передача по посиланню
Результат:
Записане дерево у файл
*/

void printfile(FILE* fp, BTnode* tree) {
    if (tree) {

        fprintf(fp, "%d\n", tree->key);
        printfile(fp, tree->left);
        printfile(fp, tree->right);
    }
    return;
}

/*Функція height_tree
Функція отримання висоти дерева
Вхід:
node - корінь дерева, передача по посиланню
Результат:
Висота дерева
*/

int height_tree(BTnode* node)
{
    if (node == 0)
    {
        return 0;
    }
    int left, right;
    if (node->left != NULL) {
        left = height_tree(node->left);
    }
    else
    {
        left = -1;
    }
    if (node->right != NULL) {
        right = height_tree(node->right);
    }
    else
    {
        right = -1;
    }
    int max = left > right ? left : right;
    return max + 1;
}

/*Функція readfile
Функція зчитування дерева з файлу
Вхід:
fp - дескриптор файлу,передача за значенням
tree - дескриптор дерева, передача по посиланню
Результат:
Зчитане дерево
*/

Tree_desc* readfile(FILE* fp, Tree_desc* tree)
{
    int key;


    key = 0;
    int file_size = countStrs(fp);
    printf("------%d-----", file_size);
    rewind(fp);
    for (int i = 0; i <= file_size; i++)
    {
        if (fscanf(fp, "%d\n", &key) != 1) {
            return tree;
        }

        if (tree->root == NULL)
        {
            tree->root = Add(tree, tree->root, key);
        }
        else
        {
            Add(tree, tree->root, key);
        }
    }
    return tree;
}

/*Функція scann
Функція зчитування числа
Вхід:
N - змінна куди потрібно записати,передача за посиланням
Результат:
Зчитане число
*/

int scann(int& N)
{
    int isEntered = 0;
    do {
        do {
            isEntered = scanf_s("%d", &N);// перевірка на те що введене значення є числом
                while (getchar() != '\n');
            while (isEntered < 1) {
                printf("Ви ввели некоректне значення,повторіть введення: ");
                isEntered = scanf_s("%d", &N);
                while (getchar() != '\n');
            }
        } while (isEntered < 1);
    } while (isEntered != 1);
    return N;
}




/*Функція GetSize
Функція отримання розміру файлу
Вхід:
tree - дескриптор дерева, передача по посиланню
Результат:
К-сть вершин у дереві
*/

int GetSize(Tree_desc* tree)
{
    return tree->size;
}


/*Функція countStrs
Функція підрахунку к-сті строк у файлі
Вхід:
fd - дескриптор файлу,передача по посиланню
Результат:
к-сть строк у файлі
*/

int countStrs(FILE* fd)

{
    int quant = 0;
    while (!feof(fd))
    {
        fscanf(fd, "%*[^\n]\n");//ігноруємо перехід на іншу строку
        quant++;
    }
    rewind(fd);//перематуємо файл
    return quant;
}

/*Функція prepare_print
Функція підготовки значень для виводу масиву
Вхід:
tree - корінь дерева, передача по посиланню
Результат:
Підготовані значення для виводу
*/

void prepare_print(BTnode* tree)
{

    char* path = (char*)calloc(256, sizeof(char));


    tree_print(tree, 0, path, 0);
}


/*Функція tree_print
Функція виводу дерева
Вхід:
depth - змінна, що потрібна для виводу,передача за значенням
path - змінна, що потрібна для виводу,передача за значенням
direction - змінна, що потрібна для виводу,передача за значенням
tree - корінь дерева, передача по посиланню
Результат:
Виведене дерево
*/

void tree_print(BTnode* tree, int depth, char* path, int direction)
{

    if (tree == NULL)
        return;


    depth++;


    tree_print(tree->right, depth, path, 1);

    path[depth - 2] = 0;

    if (direction)
        path[depth - 2] = 1;

    if (tree->left)
        path[depth - 1] = 1;

    printf("\n");

    for (int i = 0; i < depth - 1; i++)
    {
        if (i == depth - 2)
            printf("+");
        else if (path[i])
            printf("|");
        else
            printf(" ");

        for (int j = 1; j < BRANCH; j++)
            if (i < depth - 2)
                printf(" ");
            else
                printf("-");
    }

    printf("(%d)\n", tree->key);

    for (int i = 0; i < depth; i++)
    {
        if (path[i])
            printf("|");
        else
            printf(" ");

        for (int j = 1; j < BRANCH; j++)
            printf(" ");
    }
    tree_print(tree->left, depth, path, 0);
}
