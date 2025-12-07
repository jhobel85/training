#include <iostream>

using namespace std;

enum Znamka
{
    Nedefinovano = 0,
    Vyborne = 1,
    Chvalitebne,
    Dobre,
    Dostatecne,
    Nedostatecne
};

int ternarniOperator()
{
    cout << "Immediate if.\n";
    cout << "Zadej dve cisla: ";
    double a = 0, b = 0; // by default inicializovat
    cin >> a >> b;

    bool porovnej = a < b; // dobre cachovat, v pripade, ze kontroluje napr. mnoho stringu!
    const double mensi = porovnej ? a : b;
    const double vetsi = porovnej ? b : a;

    cout << "mensi = " << mensi << "\n";    
    cout << "vetsi = " << vetsi << "\n";
    return 0;
}

int prikazIf() {
    cout << "**** prikaz if ****";
    int x = 0;
    cout << "Uplna forma if prikazu\n";
    if (x == 0) {
        cout << "x je nulove\n";
    }
    else {
        cout << "x je nenulove\n";
    }

    cout << "Vysvetlete nasledujici chovani\n";
    if (x = 0) { // operator prirazeni, hodnota nula je na int zobrazena jako false.
        cout << "x je nulove\n";
    }
    else {
        cout << "x je nenulove\n";
    }

    cout << "Nevhodne umisteny strednik\n";
    if (x > 0) /* nop*/;     
    { //nop=no operation -> tzn. toto se provede vzdy ; je rizeny ifem
        cout << x << " je vetsi nez nula\n";
    }

    cout << "Rozhodovaci zebrik\n";
    if (x > 0) { //p1
        cout << "x je kladne\n";
    } 
    else if (x < 0) { //p2
        cout << "x je zaporne\n";
    }
    else /*if (x == 0)*/ { // if tu byt nemusi - automaticka implikace
        //Problem napr. v pripade potreby statement coverage 95% - pomer vsech prikazu vuci tomu k co jsme prosli v testu
        //Condition coverage -> behem testovani kazdou podminku nastavit na true i false        
        
        cout << "x je nulove\n";
    }

    return 0;
}
    string toString(Znamka znamka)
    {
        string text; //pozor je inicializovan - spousti se konstruktor - neni to prim. dat typ
        switch (znamka)
        {
        case Vyborne:
            text = "Vyborne";
            break;
        case Chvalitebne:
            text = "Chvalitebne";
            break;
        case Dobre:
            text = "Dobre";
            break;
        case Dostatecne:
            text = "Dostatecne";
            break;
        case Nedostatecne:
            text = "Nedostatecne";
            break;
        default:
            break;
        }
        return text;
    }

int main() {
    Znamka cestina = Chvalitebne;
    cout << "cestina = " << "(" << cestina << ") \n";
    return 0;
}

