#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> 
#include <cstdlib> // Pridedame šį headerį, kad galėtume naudoti rand() funkciją
#include <ctime> // Pridedame šį headerį, kad galėtume naudoti srand() funkciją

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

    srand(time(NULL)); // Inicializuojame atsitiktinių skaičių generatorių

    // Sukuriame masyvus su vardais ir pavardėmis
    string vardai[] = {"Nojus", "Domas", "Mykolas", "Vytenis", "Rokas", "Emilis", "Edgaras", "Karolis", "Petras", "Matas"};
    string pavardes[] = {"Kazlauskas", "Petrauskas", "Jankauskas", "Butkus", "Paulauskas", "Vasiliauskas", "Urbonas", "Navickas", "Ramanauskas", "Kavaliauskas"};

    do {
        Studentas naujas_studentas;
        
        // Sugeneruojame atsitiktinius vardus ir pavardes
        naujas_studentas.vardas = vardai[rand() % 10];
        naujas_studentas.pavarde = pavardes[rand() % 10];

        // Sugeneruojame atsitiktinius pažymius
        int pazymiuSkaicius = rand() % 10 + 1; // Nuolatinis pažymiu skaicius nuo 1 iki 10
        for (int i = 0; i < pazymiuSkaicius; ++i) {
            naujas_studentas.nd.push_back(rand() % 10 + 1); // Pažymiai nuo 1 iki 10
        }

        naujas_studentas.egzaminas = rand() % 10 + 1; // Egzamino rezultatas nuo 1 iki 10

        studentai.push_back(naujas_studentas);

        cout << "Ar norite ivesti naujo studento duomenis? (t/n): ";
        cin >> pasirinkimas;
    } while (pasirinkimas == 'T' || pasirinkimas == 't');

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
