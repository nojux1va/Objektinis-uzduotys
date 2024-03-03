#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egzaminas;
    double galutinisVid;
    double galutinisMed;
};

double skaiciuotiGalutiniVidurki(const vector<int>& nd, int egzaminas) {
    double suma = 0;
    for (size_t i = 0; i < nd.size(); i++) {
        suma += nd[i];
    }
    return suma / nd.size() * 0.4 + egzaminas * 0.6;
}

double skaiciuotiGalutiniMediana(vector<int> nd, int egzaminas) {
    sort(nd.begin(), nd.end());
    double mediana;
    if (nd.size() % 2 == 0) {
        mediana = (nd[nd.size() / 2 - 1] + nd[nd.size() / 2]) / 2.0;
    } else {
        mediana = nd[nd.size() / 2];
    }
    return mediana * 0.4 + egzaminas * 0.6;
}

void skaitytiIsFailo(vector<Studentas>& studentai, const string& failoPavadinimas) {
    ifstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failoPavadinimas << endl;
        return;
    }
    // Praleidžiama antraštė
    string eilute;
    getline(failas, eilute);

    while (getline(failas, eilute)) {
        istringstream eilutesSrautas(eilute);
        Studentas s;
        eilutesSrautas >> s.vardas >> s.pavarde;
        int pazymys;
        while (eilutesSrautas >> pazymys && pazymys != -1) {
            s.nd.push_back(pazymys);
        }
        s.egzaminas = s.nd.back();
        s.nd.pop_back();
        s.galutinisVid = skaiciuotiGalutiniVidurki(s.nd, s.egzaminas);
        s.galutinisMed = skaiciuotiGalutiniMediana(s.nd, s.egzaminas);
        studentai.push_back(s);
    }
    failas.close();
}

bool compareVardas (const Studentas& a, const Studentas& b) {
    return a.vardas < b.vardas; // Palyginimas pagal vardą kaip pavyzdyje
}

bool comparePavarde (const Studentas& a, const Studentas& b) {
    return a.pavarde < b.pavarde; 
}

bool compareGalutinisVid (const Studentas& a, const Studentas& b) {
    return a.galutinisVid < b.galutinisVid; 
}

bool compareGalutinisMed (const Studentas& a, const Studentas& b) {
    return a.galutinisMed < b.galutinisMed;
}

int main() {
    vector<Studentas> studentai;
    char pasirinkimas;

    cout << "Pasirinkite veiksmą:\n";
    cout << "1 - įvesti ranka\n";
    cout << "2 - skaityti iš failo 'studentai.txt'\n";
    cout << "Jūsų pasirinkimas: ";
    cin >> pasirinkimas;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Išvalo įvesties buferį

    switch (pasirinkimas) {
        case '1':
            // Čia galite įtraukti savo esamą kodą studentų duomenų įvedimui ranka
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
                        break;
                    }
                    
                    case '4':
                        cout << "Darbas baigtas.\n";
                        break;
                    default:
                        cout << "Neteisingas pasirinkimas.\n";
                }
            } while (pasirinkimas != '4');
            break;
        case '2':
            skaitytiIsFailo(studentai, "studentai10000.txt");
            break;
        default:
            cout << "Neteisingas pasirinkimas. Programa baigiama." << endl;
            return 0;
    }

    cout << "Pasirinkite rūšiavimo būdą:\n";
    cout << "1 - Pagal vardą\n";
    cout << "2 - Pagal pavardę\n";
    cout << "3 - Pagal galutinį vidurkį\n";
    cout << "4 - Pagal galutinę medianą\n";
    cout << "Jūsų pasirinkimas: ";
    cin >> pasirinkimas;

    // Rūšiavimas pagal pasirinkimą
    switch (pasirinkimas) {
        case '1':
            
            // Tada naudojate šią funkciją su sort
            sort(studentai.begin(), studentai.end(), compareVardas);
            
            //sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            //    return a.vardas < b.vardas;
            //});
            break;
        case '2':
            sort(studentai.begin(), studentai.end(), comparePavarde);
            //sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            //    return a.pavarde < b.pavarde;
            //});
            break;
        case '3':
            sort(studentai.begin(), studentai.end(), compareGalutinisVid);
            //sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            //    return a.galutinisVid < b.galutinisVid;
            //});
            break;
        case '4':
            sort(studentai.begin(), studentai.end(), compareGalutinisMed);
            //sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            //    return a.galutinisMed < b.galutinisMed;
            //});
            break;
        default:
            cout << "Neteisingas pasirinkimas. Naudojama numatytoji rūšiavimo tvarka (pagal vardą)." << endl;
            sort(studentai.begin(), studentai.end(), compareVardas);

    }

    // Išvedimas į ekraną
    cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" 
         << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    cout << string(70, '-') << endl;
    //for (const auto& s : studentai) {
    //    cout << setw(15) << s.vardas << setw(15) << s.pavarde 
    //         << setw(20) << fixed << setprecision(2) << s.galutinisVid 
    //         << setw(20) << fixed << setprecision(2) << s.galutinisMed << endl;
    //}
    for (size_t i = 0; i < studentai.size(); ++i) {
        cout << setw(15) << studentai[i].vardas << setw(15) << studentai[i].pavarde 
         << setw(20) << fixed << setprecision(2) << studentai[i].galutinisVid 
         << setw(20) << fixed << setprecision(2) << studentai[i].galutinisMed << endl;
    }



    return 0;
}
