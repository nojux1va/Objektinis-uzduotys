#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> 
#include <cstdlib>
#include <ctime>

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

    srand(time(NULL));

    int ivestiStudentai = 0; // skaičius jau įvestų studentų

    do {
        cout << "Pasirinkite veiksmą:\n";
        cout << "1 - įvesti ranka\n";
        cout << "2 - įvesti ranka vardą, pavardę, generuoti pažymius\n";
        cout << "3 - generuoti vardus, pavardes ir pažymius\n";
        cout << "4 - baigti darbą\n";
        cout << "Jūsų pasirinkimas: ";
        cin >> pasirinkimas;
        
        switch (pasirinkimas) {
            case '1': {
                Studentas naujas_studentas;
                cout << "Iveskite studento varda: ";
                cin >> naujas_studentas.vardas;
                cout << "Iveskite studento pavarde: ";
                cin >> naujas_studentas.pavarde;

                int pazymys;
                bool bentVienasPazymys = false;

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
                    bentVienasPazymys = true;
                    cout << "Iveskite kitos namu darbu rezultata (-1 baigti ivedineti): ";
                }

                if (!bentVienasPazymys) {
                    cout << "Bent vienas pažymys turi būti įvestas. Bandykite dar kartą." << endl;
                    continue;
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
                ivestiStudentai++;
                
                break;
            }
            case '2': {
                
                Studentas naujas_studentas;
                cout << "Iveskite studento varda: ";
                cin >> naujas_studentas.vardas;
                cout << "Iveskite studento pavarde: ";
                cin >> naujas_studentas.pavarde;

                // Sugeneruojame tris atsitiktinius pažymius
                for (int i = 0; i < 3; ++i) {
                    naujas_studentas.nd.push_back(rand() % 10 + 1);
                }

                naujas_studentas.egzaminas = rand() % 10 + 1;
                studentai.push_back(naujas_studentas);
                ivestiStudentai++;
                
                break;
            }
            case '3': {
                
                Studentas naujas_studentas;
                string vardai[] = {"Nojus", "Domas", "Mykolas", "Vytenis", "Rokas", "Emilis", "Edgaras", "Karolis", "Petras", "Matas"};
                string pavardes[] = {"Kazlauskas", "Petrauskas", "Jankauskas", "Butkus", "Paulauskas", "Vasiliauskas", "Urbonas", "Navickas", "Ramanauskas", "Kavaliauskas"};

                naujas_studentas.vardas = vardai[rand() % 10];
                naujas_studentas.pavarde = pavardes[rand() % 10];

                for (int i = 0; i < 3; ++i) {
                    naujas_studentas.nd.push_back(rand() % 10 + 1);
                }

                naujas_studentas.egzaminas = rand() % 10 + 1;
                studentai.push_back(naujas_studentas);
                ivestiStudentai++;    
                break;
            }
            
            case '4':
                cout << "Darbas baigtas.\n";
                break;
            default:
                cout << "Neteisingas pasirinkimas.\n";
        }
    } while (pasirinkimas != '4');

    // Išvedimas

    if (!studentai.empty()) 
    {
        cout << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(15) << right << "Galutinis (Vid.)" << setw(17) << right << "Galutinis (Med.)" << endl;
        cout << "-------------------------------------------------------------------------" << endl;

        for (int i = 0; i < studentai.size(); ++i) {
            double vidurkis = skaiciuotiGalutiniVidurki(studentai[i].nd, studentai[i].egzaminas);
            double mediana = skaiciuotiGalutiniMediana(studentai[i].nd, studentai[i].egzaminas);

            cout << setw(20) << left << studentai[i].vardas << setw(20) << left << studentai[i].pavarde << setw(15) << right << fixed << setprecision(2) << vidurkis << setw(17) << right << fixed << setprecision(2) << mediana << endl;
        }
    } else {
        cout << "Nera studentu duomenu.\n";
    }

    return 0;
}
