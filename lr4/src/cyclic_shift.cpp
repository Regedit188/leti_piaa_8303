#include <QCoreApplication>
#include <iostream>
#include <fstream>

using namespace std;


vector <int> prefixFunction(vector <int> pFunc, char* string, int size) {
    for (int i=0; i<size; i++)
        pFunc.push_back(0);
    int j = 0;            // индекс префикса
    int i = 1;            // индекс суффикса
    while(i < size){       //Пока не пройдены все символы образца
        if (string[i] == string[j]){     //Если символы i и j индекса совпадают, то оба смещаются вправо, изменяется массив префикс-функций
            pFunc[i] = j+1;
            i++;
            j++;
            cout << "prefix index(j) = " << j << ", suffix index(i) = " << i << ", str[i] == str[j],  i++,  j++,  pFunc[i] = " << j << endl << endl;
        }
        else{
            if (j==0){                  //Иначе, если j указывает на начальный символ строки, то на i символ значение префикс-функции 0
                pFunc[i] = 0;
                i++;                    //i-тый указатель смещается вправо
                cout << "prefix index(j) = " << j << ", suffix index(i) = " << i << ", s[i] != s[j],  i++,  pFunc[i] = 0" << endl << endl;
            }
            else{
                j = pFunc[j-1];            //Если указатель j не указывает на начальный символ, то сравниваются префиксы и суффиксы меньшего размера
                cout <<  "prefix index(j) = " << j << ", suffix index(i) = " << i << ", s[i] != s[j],  j = " << pFunc[j] << endl << endl;
            }
        }

    }

    cout << "\nPrefix function:\n";
    for (int i=0; i<size; i++)
        cout << string[i] << " ";
    cout << endl;
    for (int i=0; i<size; i++)
        cout << pFunc[i] << " ";
    cout <<"\n\n";
    return pFunc;
}


void cyclic(string& str1, string& str2) {
    if (str1.size() != str2.size()) {
        cout << -1;                                            //Если строки не равны по длине, то одна не может быть циклическим сдвигом другой
        return;
    }

    int size = str1.size();

    char* temp = new char[3 * size];                        // Массив для поиска результата

    int i = 0;
    while (i < size) {
        temp[i] = str2[i];          // Записывается первая строка
        ++i;
    }

    for (int k = 0; k < 2; ++k) {                           // Два раза записывается вторая строка
        for (int j = 0; j < size; ++j) {
            temp[i++] = str1[j];
        }
    }
    vector <int> pFunc;
    pFunc = prefixFunction(pFunc, temp, size * 3);           // Получается массив их префикс функций

    cout << "Find cyclic shift" << endl<<endl;
    for (int i = 2 * size - 1; i < 3 * size; ++i) {         // Обход массива результата

        for (int k = 0; k < size*3; k++)               // Вывод промежуточных результатов
            cout << temp[k] << " ";
        cout << endl;
        for (int k = 0; k < size*3; k++)
            cout << pFunc[k] <<" ";
        cout << endl;
        for (int k=0; k < i; k++)
            cout << "  ";
        cout << "i ";
        if (pFunc[i] == size) {                                //Если значение префикс функции на символе равно размеру введенной строки, то найден циклический сдвиг
            cout << "\nCyclic Shift is found. Size = " << size << ", pFunc[i] = " <<pFunc[i] <<endl;
            cout <<"Cyclic shift index: "<< i + 1 - 2 * size;    //Вывод результата
            delete [] temp;
            return;
        }
        else{
            cout << "\nNot cyclic shift, size = " << size << ", pFunc[i] = " <<pFunc[i] << ", size != pFunc[i]"<<endl;
            cout << "Continue, i++" << endl << endl;
        }
    }
    cout << -1;                            //Если циклический сдвиг не найден
    delete [] temp;
}


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    string str1;
    string str2;
    cout << "Write first string: ";
    cin >> str1;
    cout << "Write second string: ";
    cin >> str2;

    cyclic(str1, str2);  //Запуск алгоритма поиска циклического сдвига

    return a.exec();
}
