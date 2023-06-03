
#include <fstream> 
#include <cstring> 
#include <vector>
#include <functional>
#include <algorithm>
#include <tuple>
#include <stdexcept>
#include <memory>
#ifdef _WIN32
#include <windows.h>
#else
#include <locale.h>
#endif
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

struct tree
{
    int value; //информационное поле
    tree* left;//указатедь на левую часть дерева
    tree* right;//указатедь на правую часть дерева
};


#define LN { std::cout << __LINE__ << std::endl; }
#define DEB(x) { std::cout << #x << "=(" << (x) << ") "; }

static std::string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";

void insert(tree* (*p), int d) // фунуция добовление узла 
{
    if (*p == NULL) // если иказатель пустой
    {// создаем новый узел
        *p = new tree;
        (*p)->value = d;
        (*p)->left = NULL;
        (*p)->right = NULL;
    }
    else {
        if (d < (*p)->value) insert(&(*p)->left, d); //идет в левую часть
        if (d > (*p)->value) insert(&(*p)->right, d); // идем в правую часть
        // ПРИМЕЧАНИЕ ОДИНАКОВЫЕ ЗНАЧЕНИЯ НЕ ДОБОВЛЯЕМ 
    }
}


void printtree(tree const* node, bool high = true, std::vector<std::string> const& lpref = std::vector<std::string>(), std::vector<std::string> const& cpref = std::vector<std::string>(), std::vector<std::string> const& rpref = std::vector<std::string>(), bool root = true, bool left = true, std::shared_ptr<std::vector<std::vector<std::string>>> lines = nullptr) {
    if (!node) return;
    typedef std::vector<std::string> VS;
    auto VSCat = [](VS const& a, VS const& b) { auto r = a; r.insert(r.end(), b.begin(), b.end()); return r; };
    if (root) lines = std::make_shared<std::vector<VS>>();
    if (node->left)
        printtree(node->left, high, VSCat(lpref, high ? VS({ " ", " " }) : VS({ " " })), VSCat(lpref, high ? VS({ ch_ddia, ch_ver }) : VS({ ch_ddia })), VSCat(lpref, high ? VS({ ch_hor, " " }) : VS({ ch_hor })), false, true, lines);
    auto sval = std::to_string(node->value);
    size_t sm = left || sval.empty() ? sval.size() / 2 : ((sval.size() + 1) / 2 - 1);
    for (size_t i = 0; i < sval.size(); ++i)
        lines->push_back(VSCat(i < sm ? lpref : i == sm ? cpref : rpref, { std::string(1, sval[i]) }));
    if (node->right)
        printtree(node->right, high, VSCat(rpref, high ? VS({ ch_hor, " " }) : VS({ ch_hor })), VSCat(rpref, high ? VS({ ch_rddia, ch_ver }) : VS({ ch_rddia })), VSCat(rpref, high ? VS({ " ", " " }) : VS({ " " })), false, false, lines);
    if (root) {
        VS out;
        for (size_t l = 0;; ++l) {
            bool last = true;
            std::string line;
            for (size_t i = 0; i < lines->size(); ++i)
                if (l < (*lines).at(i).size()) {
                    line += lines->at(i)[l];
                    last = false;
                }
                else line += " ";
            if (last) break;
            out.push_back(line);
        }
        for (size_t i = 0; i < out.size(); ++i)
            std::cout << out[i] << std::endl;
    }
}
void clear(tree **p) // полная очистка дерева 
{
    if ((*p) != NULL)
    {
        clear(&(*p)->left);
        clear(&(*p)->right);
        delete* p;
        *p = NULL;

    }
}

bool find_value(const tree* p, int value2) {
    if (p == NULL) return false;//дерево пусто 
    if (p->value == value2)return true;
    return(find_value(p->left, value2) || find_value(p->right, value2));
}








//удаление
tree* DeleteNode(tree* node, int value) {
    if (node == NULL)
        return node;

    if (value == node->value) {

        tree* tmp;
        if (node->right == NULL)
            tmp = node->left;
        else {

            tree* ptr = node->right;
            if (ptr->left == NULL) {
                ptr->left = node->left;
                tmp = ptr;
            }
            else {

                tree* pmin = ptr->left;
                while (pmin->left != NULL) {
                    ptr = pmin;
                    pmin = ptr->left;
                }
                ptr->left = pmin->right;
                pmin->left = node->left;
                pmin->right = node->right;
                tmp = pmin;
            }
        }

        delete node;
        return tmp;
    }
    else if (value < node->value)
        node->left = DeleteNode(node->left, value);
    else
        node->right = DeleteNode(node->right, value);
    return node;
}

void printpr(const tree* p) {
    if (p != NULL)
    {
        cout << p->value << " ";
        printpr(p->left);
        printpr(p->right);

    }

}

void printob(const tree* p) {
    if (p != NULL)
    {
        
        printob(p->left);
        printob(p->right);
        cout << p->value << " ";

    }

}

void printsh(const tree* p) {
    if (p != NULL)
    {

        printsh(p->left);
        cout << p->value << " ";
        printsh(p->right);
        

    }

}














int main()
{
    
    
    tree* root = NULL;
    
    
    int w ;
    int call1;


    int  notification = 0;



    setlocale(0, "");
    setlocale(LC_ALL, "Rus"); // Подключение русского языка
    {
        while (true) {

            system("cls");

            cout << "____________________________________________________________________________________" << "\n";
            cout << "|                                 Меню :                                           |" << "\n";
            cout << "|   1) 1 Создание бинарного дерева                                                 |" << "\n";
            cout << "|   2) 2 Инструметы (вставка , удаление ,получение )                               |" << "\n";
            cout << "|   3) 3 Прямой обход                                                              |" << "\n";
            cout << "|   4) 4 Обратный обход                                                            |" << "\n";
            cout << "|   5) 5 Обход в ширину                                                            |" << "\n";
            cout << "|   6) 6 Генерация заданнй                                                         |" << "\n";
            cout << "|   0) 0 Выход из программы                                                        |" << "\n";
            cout << "|__________________________________________________________________________________|" << "\n";
            if (notification == 0) {
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!Дерево пусто создайте его!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << "\n";
                cout << "            _______ .______      .______        ______   .______                    " << "\n";
                cout << "           |   ____||   _        |   _         /  __     |   _                      " << "\n";
                cout << "           |  |__   |  |_)  |    |  |_)  |    |  |  |  | |  |_)  |                  " << "\n";
                cout << "           |   __|  |      /     |      /     |  |  |  | |      /                   " << "\n";
                cout << "           |  |____ |  |    ----.|  |    ----.| `- - ' | |  |    ----.            " << "\n";
                cout << "           |_______|| _| `._____|| _| `._____|  ______/  | _| `._____|              " << "\n";
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!Дерево пуст создайте его!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << "\n";


            }
            cout << "Выберите пункт : ";

            int choice;
            cin >> choice;
            switch (choice) {
            case 0:
                system("cls");


                cout << "___________________________________________$$$$$$$$$$$$" << "\n";
                cout << "________________________________________$$$$$$$$$_ __$$$" << "\n";
                cout << "____________________________________$$$$$$$$_____( &)_$$$$" << "\n";
                cout << "________________________________$$$$$$$$$$________ ____$$$$" << "\n";
                cout << "_____________________________$$$$$$$$$$$$$$$____§ §§§_____$" << "\n";
                cout << "___________________________$$$$$$$$$$$$$$$$$$§§ ?§_§§§_____$" << "\n";
                cout << "_________________________$$$$$$$$$$$$$$$$$$$$$§§ §§§_§____" << "\n";
                cout << "______________________$$$$$$$$$$$$$$$$$$_$$$$___§ §§__§_$" << "\n";
                cout << "____________________$$$$$$$$$$$$$_$$$$$$$$_$______ __§" << "\n";
                cout << "___________________$$$$$$$$$$$$$$$$$$$$$$$$_$" << "        Спасибо за просмотр" << "\n";
                cout << "_________________$$$$$$$$$_$$$$$$$$$$$$$$$$_$" << "          попугай вторник" << "\n";
                cout << "_______________$$$$$$$$_§$$$$$$$$$§$$$$$$$$_$" << "\n";
                cout << "_____________$$$$$$$_$$§§§$$$§$$§§$$$$§§$_ $$$" << "\n";
                cout << "____________$$$$$$_§§§$$§§$$§§§$$§§$$§ ?$_$$$" << "\n";
                cout << "___________$$$$$_$§§§$$$$§§§$$$§§§§§$$_ $$$$$" << "\n";
                cout << "__________$$$$$_§§§§§§$$§§§$$§§§§§§ §_$$$$$$" << "\n";
                cout << "_________$$$$_§§0§§§§§§§§§§§§§§§ ?_$$$$$$$" << "\n";
                cout << "________$$$_000§§§00§§§§§000§00§_$$$$$$" << "\n";
                cout << "________$$_0000§§0000§§§00§0§_$$$$$$" << "\n";
                cout << "_______$_0000§§00000§0000_$$$$$$$" << "\n";
                cout << "_____§§00000§000§0000_$$$$$$$$" << "\n";
                cout << "___§00000§0000000_$$$$$$$$$$" << "\n";
                cout << "___000§00000§_§§§§$$$$$$$$$$$$$___......" << "\n";
                cout << "___000§00000§_§§§§$$$$$$$$$$$$$___......" << "\n";
                cout << "_000§0_§§§§§§$$$$$$$_§000_$$$§§§_000000 0000000000000" << "\n";
                cout << "00____§§§§§$$$$$$$_§§00000_$§§§_00000000 000000000000" << "\n";
                cout << "______§§§§$$$$$$$_§§§_’’______§§§__???’" << "\n";

                return 0;
            case 1:
               
                cout << "Создание нового бинарного дерева удалит старое \n";
                cout << "     Вы готовы к этому ? 1- да 0 - нет \n";
                char deleteoldlist;
                cin >> deleteoldlist;
                system("cls");

                srand(time(NULL));

                
                if (deleteoldlist == '1') {
                    notification = 1;
                    clear(&root);

                    system("cls");
                    cout << "____________________________________________________________________________________" << "\n";
                    cout << "|                                 Меню :                                           |" << "\n";
                    cout << "|   Создание бинарного дерева                                                      |" << "\n";
                    cout << "|   1) 1 - Ввести данные вручную                                                   |" << "\n";
                    cout << "|   2) 2 - Заполнить данные рандомно                                               |" << "\n";
                    cout << "|   3) 3 - Прочитать данные с файла                                                |" << "\n";
                    cout << "|   0) 0 - Вернуться в меню                                                        |" << "\n";
                    cout << "|                                                                                  |" << "\n";
                    cout << "|__________________________________________________________________________________|" << "\n";
                    cout << "Ваш выбор: ";

                    cin >> call1;
                    if (call1 == 1) {
                        char whtr = 'y';
                        int exit = 0, w = NULL;
                        cout << "Введите числа :";
                        while (exit == 0) {

                            if (whtr != 'n') {

                                cin >> w;
                                insert(&root, w);
                                cout << "Хотите продолжить (y/n) :";

                                cin >> whtr;
                            }
                            else {
                                exit = 1;

                            }


                        }
                        
                        printtree(root, true);
                    }
                    if (call1 == 2) {
                        cout << "Ввежите размерность бинарного дерево : ";
                        int n;
                        cin >> n;
                        auto start = chrono::steady_clock::now();
                        for (int i = 0; i < n; ++i) {
                            w = ((rand() % 200) - 99); // рандомное заполнение от -99 до 100
                            insert(&root, w);
                        }
                        
                        printtree(root, true);
                    }
                    if (call1 == 3) {
                        
                        
                         ifstream fin("input.txt"); //сколько всего чисел
                         string str, s;
                         int k = 0;
                                while (getline(fin, str))
                                {
                                    str += ' ';
                                    for (int i = 0; i < str.length(); i++)
                                    {
                                        if (isdigit(str[i]))
                                            s += str[i];
                                        if (!(isdigit(str[i])))
                                        {
                                            if (s != "")
                                                k++;
                                            s = "";
                                        }
                                    }
                                }
                                int N;
                                
                                int* grades = new int[k];
                                
                               
                                string inFileName = "input.txt";
                                ifstream inFile;
                                inFile.open(inFileName.c_str());
                                cout << "Данные полученные из файла : \n";
                                if (inFile.is_open())
                                {
                                    for (int i = 0; i < k; i++)
                                    {
                                        inFile >> grades[i];
                                        cout << grades[i] << " ";
                                    }

                                    inFile.close(); // CLose input file
                                }
                                else { //Error message
                                    cerr << "Не могу найти файл " << inFileName << endl;
                                }
                                cout << "\n";
                                for (int i = 0; i < k; i++)
                                {
                                    insert(&root, grades[i]);
                                    
                                }
                                printtree(root, true);
	
	                    
                    }
                }
                if (deleteoldlist == '0') {
                    cout << "Изменения не были применены";
                }
               
                
                

                system("pause");
                break;
            case 2:

                system("cls");
                cout << "____________________________________________________________________________________" << "\n";
                cout << "|                                 Меню :                                           |" << "\n";
                cout << "|   Инструменты:                                                                   |" << "\n";
                cout << "|   1) 1 - Поиск элементов                                                         |" << "\n";
                cout << "|   2) 2 - Вставка элементов                                                       |" << "\n";
                cout << "|   3) 3 - Удаление элементов                                                      |" << "\n";
                cout << "|   0) 0 - Вернуться в меню                                                        |" << "\n";
                cout << "|                                                                                  |" << "\n";
                cout << "|__________________________________________________________________________________|" << "\n";
                cout << "Ваш выбор: ";
                int call2;
                cin >> call2;
                if (call2 == 1) {
                    
                    printtree(root, true);
                    
                    cout << "Введите число";
                    int cifro;
                    cin >> cifro;

                    auto start = chrono::steady_clock::now();
                    if (find_value(root, cifro))cout << "В дереdе есть данное значение " << endl;
                    else cout << "В дереdе нет данного значения" << endl;
                    auto end = chrono::steady_clock::now();
                    cout << "Время поиска: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " наносекунды" << endl;
                }
                if (call2 == 2) {
                    printtree(root, true);
                    int a;
                    cout << "Введите число которое хоотите вставить : ";
                            cin >> a;
                            auto start = chrono::steady_clock::now();
                            insert(&root, a);
                            auto end = chrono::steady_clock::now();
                            cout << "Время поиска: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " наносекунды" << endl;
                            printtree(root, true);
                }
                if (call2 == 3) {
                    int m;
                    printtree(root, true);
                    
                    cout << "Введите элемент который хотите удалить : ";
                    cin >> m;
                    auto start = chrono::steady_clock::now();
                    root = DeleteNode(root, m);
                    auto end = chrono::steady_clock::now();
                    cout << "Время поиска: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " наносекунды" << endl;
                    
                    printtree(root, true);

                }
                system("pause");
                break;
            case 3:
                cout << "ПРЯМОЙ ОБХОД:" << endl;
                printtree(root, true);
                cout << "Распечатка дерева в прямом порядке : " << endl;
                printpr(root);


                system("pause");
                break;
            case 4:
                system("cls");
                cout << "ОБРАТНЫЙ ОБХОД:" << endl;
                
                printtree(root, true);
                cout << "Распечатка дерева в обратном порядке : " << endl;
                printob(root);

                system("pause");
                break;
            case 5:
                system("cls");
                cout << "ОБХОД В ШИРИНУ:" << endl;
                printtree(root, true);
                cout << "Распечатка дерева в обходе в ширину : " << endl;
                printsh(root);

                system("pause");
                break;
            
            case 6:
                system("cls");

                system("pause");
                break;


            default:
                cout << "\n не найден данный символ " << choice << " d" << endl;
                system("pause");
                break;
            }
        }
    }


    return 0;
}


   
    

   