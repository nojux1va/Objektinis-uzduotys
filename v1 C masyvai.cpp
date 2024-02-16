#include <iostream>
#include <algorithm>
#include <iomanip> 
#include <cstdlib>
#include <ctime>

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    int* nd;
    int egzaminas;
    double galutinis;
};

double skaiciuotiGalutiniVidurki(const int* nd, int dydis, int egzaminas) {
    double suma = 0;
    for (int i = 0; i < dydis; ++i) {
        suma += nd[i];
    }
    double vidurkis = (suma / dydis) * 0.4 + egzaminas * 0.6;
    return vidurkis;
}

double skaiciuotiGalutiniMediana(const int* nd, int dydis, int egzaminas) {
    int* temp_nd = new int[dydis];
    for (int i = 0; i < dydis; ++i) {
        temp_nd[i] = nd[i];
    }
    sort(temp_nd, temp_nd + dydis);
    double mediana = 0.0;
    if (dydis % 2 == 0) {
        mediana = (temp_nd[dydis / 2 - 1] + temp_nd[dydis / 2]) / 2.0;
    } else {
        mediana = temp_nd[dydis / 2];
    }
    double galutinis = mediana * 0.4 + egzaminas * 0.6;
    delete[] temp_nd;
    return galutinis;
}

int main() {
    Studentas* studentai = nullptr;
    char pasirinkimas;

    srand(time(NULL));

    int maxStudentu = 10; // maksimalus studentų skaičius
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
                if (ivestiStudentai < maxStudentu) {
                    Studentas naujas_studentas;
                    naujas_studentas.nd = new int[10]; 
                    cout << "Iveskite studento varda: ";
                    cin >> naujas_studentas.vardas;
                    cout << "Iveskite studento pavarde: ";
                    cin >> naujas_studentas.pavarde;

                    int pazymys;
                    bool bentVienasPazymys = false;

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

                    cout << "Iveskite studento namu darbu rezultatus (-1 baigti ivedineti): ";
                    int pazymiuSkaicius = 0;
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
                        naujas_studentas.nd[pazymiuSkaicius++] = pazymys;
                        bentVienasPazymys = true;
                        cout << "Iveskite kitos namu darbu rezultata (-1 baigti ivedineti): ";
                    }

                    if (!bentVienasPazymys) {
                        cout << "Bent vienas pažymys turi būti įvestas. Bandykite dar kartą." << endl;
                        delete[] naujas_studentas.nd; 
                        continue;
                    }

                    Studentas* naujas_masyvas = new Studentas[ivestiStudentai + 1];
                    for (int i = 0; i < ivestiStudentai; ++i) {
                        naujas_masyvas[i] = studentai[i];
                    }
                    naujas_masyvas[ivestiStudentai++] = naujas_studentas;
                    delete[] studentai;
                    studentai = naujas_masyvas;
                } else {
                    cout << "Pasiektas maksimalus studentų skaičius (" << maxStudentu << ").\n";
                }
                break;
            }
            case '2': {
                if (ivestiStudentai < maxStudentu) {
                    Studentas naujas_studentas;
                    naujas_studentas.nd = new int[3]; 
                    cout << "Iveskite studento varda: ";
                    cin >> naujas_studentas.vardas;
                    cout << "Iveskite studento pavarde: ";
                    cin >> naujas_studentas.pavarde;

                    // Sugeneruojame tris atsitiktinius pažymius
                    for (int i = 0; i < 3; ++i) {
                        naujas_studentas.nd[i] = rand() % 10 + 1;
                    }

                    naujas_studentas.egzaminas = rand() % 10 + 1;
                    Studentas* naujas_masyvas = new Studentas[ivestiStudentai + 1];
                    for (int i = 0; i < ivestiStudentai; ++i) {
                        naujas_masyvas[i] = studentai[i];
                    }
                    naujas_masyvas[ivestiStudentai++] = naujas_studentas;
                    delete[] studentai;
                    studentai = naujas_masyvas;
                } else {
                    cout << "Pasiektas maksimalus studentų skaičius (" << maxStudentu << ").\n";
                }
                break;
            }
            case '3': {
                if (ivestiStudentai < maxStudentu) {
                    Studentas naujas_studentas;
                    naujas_studentas.nd = new int[3]; 
                    string vardai[] = {"Nojus", "Domas", "Mykolas", "Vytenis", "Rokas", "Emilis", "Edgaras", "Karolis", "Petras", "Matas"};
                    string pavardes[] = {"Kazlauskas", "Petrauskas", "Jankauskas", "Butkus", "Paulauskas", "Vasiliauskas", "Urbonas", "Navickas", "Ramanauskas", "Kavaliauskas"};

                    naujas_studentas.vardas = vardai[rand() % 10];
                    naujas_studentas.pavarde = pavardes[rand() % 10];

                    for (int i = 0; i < 3; ++i) {
                        naujas_studentas.nd[i] = rand() % 10 + 1;
                    }

                    naujas_studentas.egzaminas = rand() % 10 + 1;
                    Studentas* naujas_masyvas = new Studentas[ivestiStudentai + 1];
                    for (int i = 0; i < ivestiStudentai; ++i) {
                        naujas_masyvas[i] = studentai[i];
                    }
                    naujas_masyvas[ivestiStudentai++] = naujas_studentas;
                    delete[] studentai;
                    studentai = naujas_masyvas;
                } else {
                    cout << "Pasiektas maksimalus studentų skaičius (" << maxStudentu << ").\n";
                }
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

    if (studentai != nullptr) 
    {
        cout << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(15) << right << "Galutinis (Vid.)" << setw(17) << right << "Galutinis (Med.)" << endl;
        cout << "-------------------------------------------------------------------------" << endl;

        for (int i = 0; i < ivestiStudentai; ++i) {
            double vidurkis = skaiciuotiGalutiniVidurki(studentai[i].nd, 3, studentai[i].egzaminas);
            double mediana = skaiciuotiGalutiniMediana(studentai[i].nd, 3, studentai[i].egzaminas);

            cout << setw(20) << left << studentai[i].vardas << setw(20) << left << studentai[i].pavarde << setw(15) << right << fixed << setprecision(2) << vidurkis << setw(17) << right << fixed << setprecision(2) << mediana << endl;
            delete[] studentai[i].nd; 
        }
        delete[] studentai; 
    } else {
        cout << "Nera studentu duomenu.\n";
    }

    return 0;
}
