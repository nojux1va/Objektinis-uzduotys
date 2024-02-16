#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> 

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egzaminas;
    double galutinis;
};

double skaiciuotiGalutiniVidurki(const vector<int>& nd, int egzaminas) {
    double suma = 0;
    for (int i = 0; i < nd.size(); ++i) {
        suma += nd[i];
    }
    double vidurkis = (suma / nd.size()) * 0.4 + egzaminas * 0.6;
    return vidurkis;
}

double skaiciuotiGalutiniMediana(const vector<int>& nd, int egzaminas) {
    vector<int> temp_nd = nd;
    sort(temp_nd.begin(), temp_nd.end());
    int dydis = temp_nd.size();
    double mediana = 0.0;
    if (dydis % 2 == 0) {
        mediana = (temp_nd[dydis / 2 - 1] + temp_nd[dydis / 2]) / 2.0;
    } else {
        mediana = temp_nd[dydis / 2];
    }
    double galutinis = mediana * 0.4 + egzaminas * 0.6;
    return galutinis;
}

int main() {
    vector<Studentas> studentai;
    char pasirinkimas;

    do {
        Studentas naujas_studentas;
        cout << "Iveskite studento varda: ";
        cin >> naujas_studentas.vardas;
        cout << "Iveskite studento pavarde: ";
        cin >> naujas_studentas.pavarde;

        int pazymys;
        cout << "Iveskite studento namu darbu rezultatus (-1 baigti ivedineti): ";
        while (true) {
            cin >> pazymys;
            if (pazymys == -1)
                break;
            if (pazymys < 0 || pazymys > 10 || cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Netinkamas pazymys. Prašome įvesti skaičių nuo 0 iki 10: ";
                continue;
            }
            naujas_studentas.nd.push_back(pazymys);
            cout << "Iveskite kitos namu darbu rezultata (-1 baigti ivedineti): ";
        }

        cout << "Iveskite studento egzamino rezultata: ";
        while (true) {
            cin >> pazymys;
            if (pazymys < 0 || pazymys > 10 || cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Netinkamas pazymys. Prašome įvesti skaičių nuo 0 iki 10: ";
                continue;
            }
            naujas_studentas.egzaminas = pazymys;
            break;
        }

        studentai.push_back(naujas_studentas);

        cout << "Ar norite ivesti naujo studento duomenis? (t/n): ";
        cin >> pasirinkimas;
    } while (pasirinkimas == 'T' || pasirinkimas == 't');

    cout << endl;
    cout << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(15) << right << "Galutinis (Vid.)" << setw(17) << right << "Galutinis (Med.)" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    for (int i = 0; i < studentai.size(); ++i) {
        double vidurkis = skaiciuotiGalutiniVidurki(studentai[i].nd, studentai[i].egzaminas);
        double mediana = skaiciuotiGalutiniMediana(studentai[i].nd, studentai[i].egzaminas);

        cout << setw(20) << left << studentai[i].vardas << setw(20) << left << studentai[i].pavarde << setw(15) << right << fixed << setprecision(2) << vidurkis << setw(17) << right << fixed << setprecision(2) << mediana << endl;
    }

    return 0;
}
