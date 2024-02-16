#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> // Šis headeris reikalingas spausdinant skaičius su tikslumu

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egzaminas;
    double galutinis;
};

double skaiciuotiGalutiniVidurki(vector<int> nd, int egzaminas) {
    double suma = 0;
    for (int i = 0; i < nd.size(); ++i) {
        suma += nd[i];
    }
    double vidurkis = (suma / nd.size()) * 0.4 + egzaminas * 0.6;
    return vidurkis;
}

double skaiciuotiGalutiniMediana(vector<int> nd, int egzaminas) {
    sort(nd.begin(), nd.end());
    int dydis = nd.size();
    double mediana = 0.0;
    if (dydis % 2 == 0) {
        mediana = (nd[dydis / 2 - 1] + nd[dydis / 2]) / 2.0;
    } else {
        mediana = nd[dydis / 2];
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
        while (cin >> pazymys && pazymys != -1) {
            naujas_studentas.nd.push_back(pazymys);
            cout << "Iveskite kitos namu darbu rezultata (-1 baigti ivedineti): ";
        }

        cout << "Iveskite studento egzamino rezultata: ";
        cin >> naujas_studentas.egzaminas;

        studentai.push_back(naujas_studentas);

        cout << "Ar norite ivesti naujo studento duomenis? (taip/ne): ";
        cin >> pasirinkimas;
    } while (pasirinkimas == 'T' || pasirinkimas == 't');

    cout << endl;
    cout << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(15) << right << "Galutinis (Vid.)" << setw(15) << right << "Galutinis (Med.)" << endl;
    cout << "--------------------------------------------------------------------" << endl;

    for (int i = 0; i < studentai.size(); ++i) {
        double vidurkis = skaiciuotiGalutiniVidurki(studentai[i].nd, studentai[i].egzaminas);
        double mediana = skaiciuotiGalutiniMediana(studentai[i].nd, studentai[i].egzaminas);

        cout << setw(20) << left << studentai[i].vardas << setw(20) << left << studentai[i].pavarde << setw(15) << right << fixed << setprecision(2) << vidurkis << setw(15) << right << fixed << setprecision(2) << mediana << endl;
    }

    return 0;
}
