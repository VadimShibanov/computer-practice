#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>
#include <limits>
#include <windows.h>

using namespace std;

struct Toy {
    char name[50];
    int article;
    double price;
    char country[30];
    char category[20];
};

void printFile(fstream& f, int n) {
    Toy t;
    f.seekg(0);
    cout
        << left << setw(15) << "Название"
        << left << setw(15) << "Артикул"
        << left << setw(15) << "Цена"
        << left << setw(15) << "Страна"
        << left << setw(15) << "Категория" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < n; i++) {
        f.read((char*)&t, sizeof(t));
        cout 
            << left << setw(15) << t.name
            << left << setw(15) << t.article
            << left << setw(15) << t.price
            << left << setw(15) << t.country
            << t.category << endl;
    }
}

int createBinaryFile(const char* txtName, const char* binName) {
    ifstream in(txtName);
    ofstream out(binName, ios::binary);

    if (!in || !out) {
        cout << "Ошибка открытия файлов!" << endl;
        return 0;
    }

    int count = 0;
    Toy t;

    while (in >> t.name >> t.article >> t.price >> t.country) {
        string catLine;
        getline(in, catLine);

        size_t start = catLine.find_first_not_of(" \t\r\n");
        string cleanCat = (start != string::npos) ? catLine.substr(start) : "";

        strncpy(t.category, cleanCat.c_str(), sizeof(t.category) - 1);
        t.category[sizeof(t.category) - 1] = '\0';

        out.write((char*)&t, sizeof(t));
        count++;
    }

    in.close();
    out.close();
    return count;
}

void sortByCountry(const char* binName, int n) {
    fstream f(binName, ios::in | ios::out | ios::binary);
    if (!f) return;

    Toy min, curr;
    for (int i = 0; i < n - 1; i++) {
        f.seekg(i * sizeof(Toy));
        f.read((char*)&min, sizeof(min));
        int idxMin = i;

        for (int j = i + 1; j < n; j++) {
            f.read((char*)&curr, sizeof(curr));
            if (strcmp(curr.country, min.country) < 0) {
                min = curr;
                idxMin = j;
            }
        }

        if (idxMin != i) {
            f.seekg(i * sizeof(Toy));
            f.read((char*)&curr, sizeof(curr));

            f.seekp(i * sizeof(Toy));
            f.write((char*)&min, sizeof(min));

            f.seekp(idxMin * sizeof(Toy));
            f.write((char*)&curr, sizeof(curr));
        }
    }
    f.close();
}

void filterAndPrint(const char* binName, int n, double maxPrice, const char* targetCat) {
    fstream f(binName, ios::in | ios::binary);
    if (!f) return;

    Toy t;
    bool found = false;
    cout << "\nРезультат фильтрации:" << endl;
    cout
        << left << setw(15) << "Название"
        << left << setw(15) << "Артикул"
        << left << setw(15) << "Цена"
        << left << setw(15) << "Страна"
        << left << "Категория" << endl;
    cout << string(70, '-') << endl;

    f.seekg(0);
    for (int i = 0; i < n; i++) {
        f.read((char*)&t, sizeof(t));
        if (t.price <= maxPrice && strcmp(t.category, targetCat) == 0) {
            cout 
                << left << setw(15) << t.name
                << left << setw(15) << t.article
                << left << setw(15) << fixed << setprecision(0) << t.price
                << left << setw(15) << t.country
                << left << t.category << endl;
            found = true;
        }
    }

    if (!found) cout << "Игрушки по заданным критериям не найдены." << endl;
    f.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const char* TXT_FILE = "toys.txt";
    const char* BIN_FILE = "toys.bin";

    int count = createBinaryFile(TXT_FILE, BIN_FILE);

    if (count == 0) {
        cout << "Не удалось создать бинарный файл. Проверьте toys.txt" << endl;
        return 1;
    }

    cout << "Бинарный файл создан. Записано игрушек: " << count << "\n\n";

    sortByCountry(BIN_FILE, count);
    cout << "Данные отсортированы по странам.\n\n";

    cout << "Все игрушки,отсортированные по странам:" << endl;
    {
        fstream f(BIN_FILE, ios::in | ios::binary);
        printFile(f, count);
        f.close();
    }

    double maxPrice;
    char targetCat[50];

    cout << "\nВведите максимальную стоимость (руб.): ";
    cin >> maxPrice;

    cout << "Введите категорию (Мальчикам/Девочкам/Тем и другим): ";
    cin.ignore(1000, '\n');
    cin.getline(targetCat, sizeof(targetCat));

    filterAndPrint(BIN_FILE, count, maxPrice, targetCat);

    return 0;
}