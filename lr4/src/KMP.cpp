#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <conio.h>

using namespace std;

void prefixFunction (vector<int>& pFunc, string& string) {
    pFunc[0] = 0;
    int j = 0;            // индекс префикса
    int i = 1;            // индекс суффикса

    while(i < string.size()){       //Пока не пройдены все символы образца
        if (string[i] == string[j]){     //Если символы i и j индекса совпадают, то оба смещаются вправо, изменяется массив префикс-функций
            pFunc[i] = j+1;
            i++;
            j++;
            cout << "prefix index(j) = " << j << ", suffix index(i) = " << i << ", str[i] == str[j],  i++,  j++,  pFunc[i] = " << j << endl << endl;
        }
        else{
            if (j==0){                  //Иначе, если j указывает на начальный символ строки, то на i символ значение префикс-функции 0
                pFunc[i] = 0;
                i++;                    //индекс суффикса смещается вправо
                cout << "prefix index(j) = " << j << ", suffix index(i) = " << i << ", s[i] != s[j],  i++,  pFunc[i] = 0" << endl << endl;
            }
            else{
                j = pFunc[j-1];            //Если индекс префикса не указывает на начальный символ, то сравниваются префиксы и суффиксы меньшего размера
                cout <<  "prefix index(j) = " << j << ", suffix index(i) = " << i << ", s[i] != s[j],  j = " << pFunc[j] << endl << endl;
            }
        }

    }
    cout << "\nPrefix function array:\n";
    for (char k : string)
        cout << k << " ";
    cout << endl;
    for (int i=0; i<string.size(); i++)
        cout << pFunc[i] << " ";
    cout <<"\n\n";
}


vector <int> KMP(string subStr) {
    vector <int> result;                            // Вектор индексов вхождения подстроки
    vector <int> pFunc(subStr.size());             // Вектор значений префикс-функций

    prefixFunction(pFunc, subStr);
    int k = 0;                          // Индекс текущего элемента в строке-образце
    int l = 1;                          // Счетчик символов в строке поиска
    char ch = 0;
    cout << "Write search string: ";
    if (getch() == 13){
        result.push_back(-1);
        return result;
    }
    cin >> ch;
    while (true) {
        cout << "Current symbol: " << ch << endl;
        for (int i = 0; i < subStr.size(); i++){
            char sym = subStr[i];
            cout << sym << " ";
        }
        cout << endl;
        for (int i = 0; i < pFunc.size(); i++){
            cout << pFunc[i] <<" ";
        }
        cout << endl;
        for (int i=0; i<k; i++)
            cout << "  ";
        cout << "k" << endl;
        while ((k > 0) && (subStr[k] != ch)) {             //Если считанный символ не удовлетворяет условию, то изменяется индекс k
            k = pFunc[k-1];
            cout << "\nCurrent symbol != subStr[k], k = pFunc[k-1] = " << k << endl;
            for (int i = 0; i < subStr.size(); i++){
                char sym = subStr[i];
                cout << sym << " ";
            }
            cout << endl;
            for (int i = 0; i < pFunc.size(); i++){
                cout << pFunc[i] <<" ";
            }
            cout << endl;
            for (int i=0; i<k; i++)
                cout << "  ";
            cout << "k" << endl;
        }

        if (subStr[k] == ch) {         // Если считанный символ совпадает с текущим в образце, то индекс k сдвигается вправо
            k++;
            cout << "Current symbol == subStr[k], k++" << endl << endl;
        }
        else{
            cout << "Current symbol != subStr[k]"<< endl <<endl;
        }

        if (k == subStr.size()) {          // Если найдена подстрока, то индекс заносится в массив результата
            result.push_back(l - subStr.size());
            cout << "String entry in index: " << l - subStr.size() << endl<< endl;
        }
        l++;
        cout << "...\n" << endl;
        if (cin.peek() == '\n'){
            break;
        }
        cin >> ch;
    }

    if (result.empty()) {                   //Если не было найдено подстроки
        result.push_back(-1);
    }
    return result;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    string subStr;
    cout << "Write sample string: ";
    if (cin.peek() == '\n'){
        cout << -1;
        return 0;
    }
    cin >> subStr;

    vector<int> result = KMP(subStr);          //Запуск алгоритма Кнута-Морриса-Пратта
    cout << "\n\nResult:" << endl;     //Вывод результата
    if (result[0] == -1)
        cout << "Substring not found" << endl;
    else {
        for (int i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i != result.size() - 1) {
                cout << ',';
            }
        }
    }
    return a.exec();
}
