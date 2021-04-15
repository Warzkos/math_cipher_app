#include <iostream>
#include <conio.h>
#include <ctime>
#include <vector>
#include <cstdlib>


using namespace std;

const int rozmiar = 97;
vector <char> ostatnioSzyfrowane;
int ostatniDzien, ostatniMiesiac, ostatniRok;

const char znaki[rozmiar]={'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f', 'G', 'g',
                           'H', 'h', 'I', 'i', 'J', 'j', 'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n',
                           'O', 'o', 'P', 'p', 'Q', 'q', 'R', 'r', 'S', 's', 'T', 't', 'U', 'u',
                           'V', 'v', 'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z', '1', '2', '3', '4',
                           '5', '6', '7', '8', '9', '0', ' ', ',', '.', '?', '!', '\'', '"', ';',
                           ':', '/', '\\', '|', '-', '_', '+', '=', '<', '>', '(', ')', '*', '&',
                           '^', '%', '$', '#', '@', '[', ']', '{', '}', '~', '`', 3, 1};

void strToDate(string tekst, int &d, int &m, int &r){
    d = atoi((tekst.substr(0, 2)).c_str());
    m = atoi((tekst.substr(3, 2)).c_str());
    r = atoi((tekst.substr(8, 2)).c_str());
    return;
}

void pobierzDate(int &d, int &m, int &y){
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    d = local_time->tm_mday;
    m = local_time->tm_mon+1;
    y = local_time->tm_year-100;
}

int dodawanieModulo(int a, int b){
    return (a+b)%rozmiar;
}

int odejmowanieModulo(int a, int b){
    int ans=a-b;
    while(ans<0)
        ans=ans+rozmiar;
    return ans;
}

int mnozenieModulo(int a, int b){
    return (a*b)%rozmiar;
}

int dzielenieModulo(int a, int b){
    if(b==0){
        cout << endl; cout << "Blad, dzielenie przez 0, podano bledny szyfr";
        exit(EXIT_FAILURE);
    }
    while(a%b!=0)
        a=a+rozmiar;
    return (a/b)%rozmiar;
}

void zapiszSzyfr(vector <char> szyfr, int d, int m, int r){
    if(ostatnioSzyfrowane.empty()==false)
        ostatnioSzyfrowane.clear();

    for(unsigned int i=0; i<szyfr.size(); i++)
        ostatnioSzyfrowane.push_back(szyfr[i]);

    ostatniDzien = d;
    ostatniMiesiac = m;
    ostatniRok = r;

    return;
}

void wczytajSzyfr(vector <int> &szyfrLiczby, int &d, int &m, int &r){
    for(unsigned int i=0; i<ostatnioSzyfrowane.size(); i++)
        for(int j=0; j<rozmiar; j++)
            if(ostatnioSzyfrowane[i]==znaki[j])
               szyfrLiczby.push_back(j);
    d = ostatniDzien;
    m = ostatniMiesiac;
    r = ostatniRok;

    cout << "Data stworzenia szyfru: " << d << "."; if(m<10) cout << "0"; cout << m << "." << r+2000 << endl;

    cout << "Wczytany szyfr: ";
    for(unsigned int i=0; i<ostatnioSzyfrowane.size(); i++)
        cout << ostatnioSzyfrowane[i];
    cout << endl;

    return;
}

void szyfrowanie(){
    system("CLS");

    cout << "Co chcesz zrobic?" << endl;
    cout << "1. Wczytaj date z systemu" << endl;
    cout << "2. Wpisz samemu date" << endl; cout << endl;
    cout << "Powrot - wcisnij dowolny przycisk" << endl;

    int dzien, miesiac, rok;

    switch(getch()){
        case '1':
            system("CLS");
            pobierzDate(dzien, miesiac, rok);
            break;
        case'2':{
            system("CLS");
            cout << "Podaj date (DD.MM.RRRR): ";
            string data; getline(cin, data);
            strToDate(data, dzien, miesiac, rok);
            break;
        }
        default:
            return;
    }

    system("CLS");
    cout << "Data: " << dzien << "."; if(miesiac<10) cout << "0"; cout << miesiac; cout << "." << rok+2000 << endl;
    cout << "Podaj tekst do zaszyfrowania: "; string tekst; getline(cin, tekst);

    for(unsigned int i=0; i<tekst.length(); i++){
        bool czyJest = false;
        for(int j=0; j<rozmiar; j++)
            if(tekst[i]==znaki[j])
                czyJest = true;
        if(czyJest==false){
            cout << endl;
            cout << "Ten znak \"" << tekst[i] << "\" nie znajduje sie w tablicy znakow." << endl;
            cout << "Prosze uzywac znakow znajdujacych sie w tablicy." << endl;
            cout << endl; cout << "Wcisnij dowolny przycisk, aby wrocic do menu glownego."; getch();
            return;
        }
    }

    vector <char> tekstJawny;
    for(unsigned int i=0; i<tekst.length(); i++)
        tekstJawny.push_back(tekst[i]);

    vector <char> przesunietaTablicaZnakow;
    srand(dzien*miesiac*rok*tekstJawny.size());
    for(int i=0; i<rozmiar; i++)
        while(true){
            int liczba = rand()%rozmiar; bool znaleziono = false;
            for(unsigned int j=0; j<przesunietaTablicaZnakow.size(); j++)
                if(przesunietaTablicaZnakow[j]==znaki[liczba])
                    znaleziono = true;
            if(znaleziono == false){
                przesunietaTablicaZnakow.push_back(znaki[liczba]);
                break;
            }
        }

    vector <int> liczby;
    for(unsigned int i=0; i<tekstJawny.size(); i++)
        for(int j=0; j<rozmiar; j++)
            if(tekstJawny[i]==przesunietaTablicaZnakow[j]){
                liczby.push_back(j);
                break;
            }

    for(unsigned int i=2; i<liczby.size(); i++)
        liczby[i] = dodawanieModulo(dodawanieModulo(liczby[i], liczby[i-1]), liczby[i-2]);

    int suma = 0;
    for(unsigned int i=0; i<liczby.size(); i++)
        suma = dodawanieModulo(suma, mnozenieModulo(liczby[i], i));

    for(unsigned int i=0; i<liczby.size(); i++)
        liczby[i]=dodawanieModulo(suma, liczby[i]);

    vector <char> szyfrogram;
    for(unsigned int i=0; i<liczby.size(); i++)
        for(int j=0; j<rozmiar; j++)
            if(liczby[i]==j){
                szyfrogram.push_back(znaki[j]);
                break;
            }

    cout << endl;
    cout << "Szyfrogram: ";
    for(unsigned int i=0; i<szyfrogram.size(); i++)
        cout << szyfrogram[i];

    cout << endl; cout << endl;
    cout << "Wcisnij 1, aby zapisac szyfr lub wcisnij dowolny przycisk, aby wrocic do menu glownego.";
    if(getch()=='1')
        zapiszSzyfr(szyfrogram, dzien, miesiac, rok);

    return;
}

void deszyfrowanie(){
    system("CLS");

    cout << "Co chcesz zrobic?" << endl;
    cout << "1. Zdeszyfruj zapisany szyfr" << endl;
    cout << "2. Zdeszyfruj wlasny szyfr" << endl; cout << endl;
    cout << "Powrot - wcisnij dowolny przycisk" << endl;

    int dzien,miesiac,rok;
    vector <int> szyfrogramLiczby;

    switch(getch()){
            case '1':
                system("CLS");
                if(ostatnioSzyfrowane.empty()){
                    cout << "Nie zostal zapisany zaden szyfr." << endl << "Nacisnij dowolny przycisk, aby powrocic do menu glownego.";
                    getch();
                    return;
                }
                wczytajSzyfr(szyfrogramLiczby, dzien, miesiac, rok);


                break;
            case'2':{
                system("CLS");
                cout << "Podaj date stworzenia szyfru (DD.MM.RRRR): ";
                string data; getline(cin, data);
                strToDate(data, dzien, miesiac, rok);
                cout << "Podaj szyfrogram: "; string szyfr; getline(cin, szyfr);

                for(unsigned int i=0; i<szyfr.length(); i++){
                    bool czyJest = false;
                    for(int j=0; j<rozmiar; j++)
                        if(szyfr[i]==znaki[j])
                            czyJest = true;
                    if(czyJest==false){
                        cout << endl;
                        cout << "Ten znak \"" << szyfr[i] << "\" nie znajduje sie w tablicy znakow." << endl;
                        cout << "Prosze uzywac znakow znajdujacych sie w tablicy." << endl;
                        cout << endl; cout << "Wcisnij dowolny przycisk, aby wrocic do menu glownego."; getch();
                        return;
                    }
                }

                for(unsigned int i=0; i<szyfr.length(); i++)
                    for(int j=0; j<rozmiar; j++)
                        if(szyfr[i]==znaki[j])
                            szyfrogramLiczby.push_back(j);
                break;
            }
            default:
                return;
        }

    int suma = 0;
    for(unsigned int i=0; i<szyfrogramLiczby.size(); i++){
        suma = dodawanieModulo(suma, mnozenieModulo(szyfrogramLiczby[i], i));
    }

    suma = dzielenieModulo(suma, dodawanieModulo(dzielenieModulo(mnozenieModulo(odejmowanieModulo(szyfrogramLiczby.size(), 1), szyfrogramLiczby.size()), 2), 1));

    for(unsigned int i=0; i<szyfrogramLiczby.size(); i++)
        szyfrogramLiczby[i] = odejmowanieModulo(szyfrogramLiczby[i], suma);

    for(int i=szyfrogramLiczby.size()-1; i>1; i--)
        szyfrogramLiczby[i]=odejmowanieModulo(odejmowanieModulo(szyfrogramLiczby[i], szyfrogramLiczby[i-2]), szyfrogramLiczby[i-1]);

    vector <char> przesunietaTablicaZnakow;
    srand(dzien*miesiac*rok*szyfrogramLiczby.size());
    for(int i=0; i<rozmiar; i++)
        while(true){
            int liczba = rand()%rozmiar; bool znaleziono = false;
            for(unsigned int j=0; j<przesunietaTablicaZnakow.size(); j++)
                if(przesunietaTablicaZnakow[j]==znaki[liczba])
                    znaleziono = true;
            if(znaleziono == false){
                przesunietaTablicaZnakow.push_back(znaki[liczba]);
                break;
            }
        }

    vector <char> tekstJawny;
    for(unsigned int i=0; i<szyfrogramLiczby.size(); i++)
        for(int j=0; j<rozmiar; j++)
            if(j==szyfrogramLiczby[i])
                tekstJawny.push_back(przesunietaTablicaZnakow[j]);

    cout << endl;
    cout << "Odszyfrowana wiadomosc: ";

    for(unsigned int i=0; i<tekstJawny.size(); i++)
        cout << tekstJawny[i];

    cout << endl; cout << endl;
    cout << "Wcisnij dowolny przycisk, aby powrocic do menu glownego.";
    getch();

    return;
}

void wyswietlMenu(){
    system("CLS");
    cout << "Co chcesz zrobic? Wcisnij odpowiadajacy przycisk:" << endl;
    cout << "1. Zaszyfruj wiadomosc" << endl;
    cout << "2. Deszyfruj wiadomosc" << endl; cout << endl;
    cout << "Wyjdz - wcisnij dowolny przycisk" << endl;
};

int main(){

    system("title Aplikacja szyfrujaca");

    while(true){
        wyswietlMenu();
        switch(getch()){
            case '1':
                szyfrowanie();
                break;
            case'2':
                deszyfrowanie();
                break;
            default:
                return 0;
        }
    }
    return 0;
}
