#include <iostream>
#include <locale>
#include <time.h>
#include <fstream>
#include <conio.h>
#define INF 99999
using namespace std;

int** Floyd(const int SIZE, int** a)
{
    int s, t,fiter=0,counter=0;
    int* find;
    int** base = new int* [SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        base[i] = new int[SIZE];
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            base[i][j] = a[i][j];
        }
    }
    int** next= new int* [SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        next[i] = new int[SIZE];
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (a[i][j] != INF)
            {
                next[i][j] = j;
            }
            else
            {
                next[i][j] = -1;
            }
        }
    }

    //================================================
    for (int k = 0; k < SIZE; k++)
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (a[i][j] > a[i][k] + a[k][j])
                {
                    a[i][j] = a[i][k] + a[k][j];
                    next[i][j] = next[i][k];
                }
    //=================================================

    cout << "Матрица кратчайших путей в графе" << endl;
    cout << "\t";

    cout << endl;
    for (int i = 0; i < SIZE; i++)
    {
        cout << i + 1 << "|\t";
        for (int j = 0; j < SIZE; j++)
        {
            if (a[i][j] != INF)
            {
                cout << a[i][j] << " ";
            }
            else
            {
                cout << "- ";
            }
        }
        cout << endl;
    }
    //=======================================
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (a[i][j] != base[i][j])
            {
                counter++;
            }
        }
    }
    find = new int[counter * 2];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (a[i][j] != base[i][j])
            {
                find[fiter] = i;
                find[fiter + 1] = j;
                fiter += 2;
            }
        }
    }
    cout << "\n\n";
    cout << "\nНайденны более короткие пути\n";//==============
    for (int i = 0; i < counter * 2; i += 2)
    {
        s = find[i];
        t = find[i + 1];
        cout << "\nПуть " << s+1 << " --> " << t+1 << ": ";
        while (s != t)
        {
            cout << s << " ";
            s = next[s][t];
        }
        cout << t << endl;
    }
    return a;
    
}

int** Get_matrix(string path, int& SIZE)
{
    int counter = 0;
    ifstream fin;
    fin.open(path);

    if (!fin.is_open())
    {
        cout << "\nОшибка открытия файла" << endl;
    }
    else
    {
        cout << "\nФайл открыт" << endl;
        int temp;
        while (fin >> temp)
        {
            counter++;
        }

    }
    fin.close();

    SIZE = sqrt(counter);
    int** A;
    A = new int* [SIZE];
    for (size_t i = 0; i < SIZE; i++)
    {
        A[i] = new int[SIZE];
    }
    fin.open(path);
    if (!fin.is_open())
    {
        cout << "\nОшибка отрытия файла" << endl;
    }
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                fin >> A[i][j];
            }
        }
    }
    return A;
}
int** Gen_matrix(const int SIZE)
{
    int** a = new int* [SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        a[i] = new int[SIZE];
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (!(i == j))
            {
                a[i][j] = rand() % 100;
            }
            else {
                a[i][j] = 0;
            }
        }
    }
    return a;
}
int** Write_matrix(const int SIZE)
{

    int** a = new int* [SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        a[i] = new int[SIZE];
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (!(i == j)) {
                cout << "Введите строку " << i + 1 << " столбец " << j + 1 << ": "; cin >> a[i][j];
            }
            else {
                a[i][j] = 0;
            }
        }
    }
    return a;
}
void Output(const int SIZE, int** a)
{
    //вывод матрицы в консоль
    cout << endl;

    for (int i = 0; i < SIZE; i++)
    {
        cout << "R" << i + 1 << "| ";
        for (int j = 0; j < SIZE; j++)
        {
            if (a[i][j] != INF)
            {
                cout << a[i][j] << " ";
            }
            else
            {
                cout << "- ";
            }
            
        }
        cout << endl;
    }
    cout << "=========================================================" << "\n\n";
}
void File_output(string path, const int SIZE, int** a)
{
    ofstream fout;
    fout.open(path);
    if (!fout.is_open())
    {
        cout << "Ошибка отрытия файла" << endl;
    }
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                fout << a[i][j] << " ";
            }
            fout << "\n";
        }
    }
    fout.close();
    
}

int main()
{
    setlocale(LC_ALL, "rus");
    int SIZE;
    int b;
    int** A;
    string path;
    cout << "--->1. Загрузить из файла" << endl;
    cout << "--->2. Записать через консоль" << endl;
    cout << "--->3. Сгенерировать случайно" << endl;
    cout << "--->0. Выход" << endl;
    b = _getch();

    if (b == '0')
    {
        return 0;
    }
    if (b == '1')
    {
        cout << "--->Введите путь к файлу: "; cin >> path; cout << endl;
        A = Get_matrix(path, SIZE);
        Output(SIZE, A);
        cout << "\n--->1.Найти кратчайшие пути: " << endl;
        b = _getch();
        if (b == '1')
        {
            Floyd(SIZE, A);

            cout << "--->1.Сохранить в файл" << endl;
            cout << "--->2.Вывести в консоль" << endl;
            b = _getch();
            if (b == '1')
            {
                cout << "Введите путь к файлу: "; cin >> path; cout << endl;
                File_output(path, SIZE, A);
            }
            if (b == '2')
            {
                Output(SIZE, A);
            }
            return 0;
        }

    }
    if (b == '2')
    {
        cout << "\n--->Введите кол-во вершин: "; cin >> SIZE; cout << endl;
        A = Write_matrix(SIZE);
        Output(SIZE, A);
        cout << "\n--->1.Найти кратчайшие пути: " << endl;
        b = _getch();
        if (b == '1')
        {
            Floyd(SIZE, A);

            cout << "--->1.Сохранить в файл" << endl;
            cout << "--->2.Вывести в консоль" << endl;
            b = _getch();
            if (b == '1')
            {
                cout << "Введите путь к файлу: "; cin >> path; cout << endl;
                File_output(path, SIZE, A);
            }
            if (b == '2')
            {
                Output(SIZE, A);
            }
        }
        return 0;
    }
    if (b == '3')
    {
        cout << "\n--->Введите кол-во вершин: "; cin >> SIZE; cout << endl;
        A = Gen_matrix(SIZE);
        Output(SIZE, A);
        cout << "\n--->1.Найти кратчайшие пути: " << endl;
        b = _getch();
        if (b == '1')
        {
            Floyd(SIZE, A);

            cout << "--->1.Сохранить в файл" << endl;
            cout << "--->2.Вывести в консоль" << endl;
            b = _getch();
            if (b == '1')
            {
                cout << "Введите путь к файлу: "; cin >> path; cout << endl;
                File_output(path, SIZE, A);
            }
            if (b == '2')
            {
                Output(SIZE, A);
            }
        }
        return 0;
    }

    return 0;
}