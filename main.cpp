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
        bool bentVienasPazymys = false; // Patikrinimas, ar buvo įvestas bent vienas pažymys

        cout << "Iveskite studento namu darbu rezultatus (-1 baigti ivedineti): ";
        while (true) {
            cin >> pazymys;
            if (pazymys == -1 && bentVienasPazymys == true)
                break;
            if (pazymys < 0 || pazymys > 10 || cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Netinkamas pazymys. Prašome įvesti skaičių nuo 0 iki 10: ";
                continue;
            }
            naujas_studentas.nd.push_back(pazymys);
            bentVienasPazymys = true; // Nustatome, kad buvo įvestas bent vienas pažymys
            cout << "Iveskite kitos namu darbu rezultata (-1 baigti ivedineti): ";
        }

        if (!bentVienasPazymys) 
        { // Jei neįvestas bent vienas pažymys, prašome vartotojo įvesti iš naujo
            cout << "Bent vienas pažymys turi būti įvestas. Bandykite dar kartą." << endl;
            continue; // Pradėti ciklą iš naujo
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

    // Pasirinkimas, ar išvesti tik vidurkį, tik medianą arba abu
    char isvedimoPasirinkimas;
    cout << "Ar norite isvesti tik GalutiniVidurki (V) arba tik GalutiniMediana (M) arba abu (A)? ";
    cin >> isvedimoPasirinkimas;

    cout << endl;
    cout << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde";

    if (isvedimoPasirinkimas == 'V' || isvedimoPasirinkimas == 'A') {
        cout << setw(15) << right << "Galutinis (Vid.)";
    }
    if (isvedimoPasirinkimas == 'M' || isvedimoPasirinkimas == 'A') {
        cout << setw(17) << right << "Galutinis (Med.)";
    }
    cout << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    for (int i = 0; i < studentai.size(); ++i) {
        double vidurkis = skaiciuotiGalutiniVidurki(studentai[i].nd, studentai[i].egzaminas);
        double mediana = skaiciuotiGalutiniMediana(studentai[i].nd, studentai[i].egzaminas);

        cout << setw(20) << left << studentai[i].vardas << setw(20) << left << studentai[i].pavarde;

        if (isvedimoPasirinkimas == 'V' || isvedimoPasirinkimas == 'A') {
            cout << setw(15) << right << fixed << setprecision(2) << vidurkis;
        }
        if (isvedimoPasirinkimas == 'M' || isvedimoPasirinkimas == 'A') {
            cout << setw(17) << right << fixed << setprecision(2) << mediana;
        }
        cout << endl;
    }

    return 0;
}
