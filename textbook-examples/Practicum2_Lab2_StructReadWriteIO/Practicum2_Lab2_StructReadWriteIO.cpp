#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    struct Tutors {
        char name[25];
        int year;
        char step[10];
        int stag;
    };

    string name = "tutors.dat";

    Tutors t[10] = {
        "Иванов", 25, "ktn", 3,
        "Петров", 45, "no", 20,
        "Сидоров", 35, "ktn", 6,
        "Куликов", 58, "dtn", 30,
        "Морозов", 45, "ktn", 22,
        "Малышева", 43, "no", 10,
        "Мартынова", 50, "ktn", 28,
        "Яров", 60, "ktn", 35,
        "Мышкин", 39, "no", 17,
        "Филлипова", 45, "ktn", 18,
    };

    ofstream out;
    out.open(name, ios::binary);

    if (!out) {
        cout << "файл для чтения не открыт " << name << " не открыт" << endl;
        return 1;
    }

    out.write((char*)&t, sizeof t);
    out.close();
    
}