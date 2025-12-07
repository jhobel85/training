// Lokalni hlavicky
#include "Datum.h"

// 3rd party hlavicky

// Standardni hlavicky
#include <iostream>

using namespace std;

void zobraz(const Datum* datum)
{
    cout << "den   = " << datum->getDen() << "\n";
    cout << "mesic = " << datum->getMesic() << "\n";
    cout << "rok   = " << datum->getRok() << "\n";
    cout << "\n";
}

int zapouzdreni()
{
    cout << "***** Zapouzdreni *****\n";
    Datum po;
    po.set(24, 5, 2021);
    zobraz(&po);

    Datum ut;
    ut.set(25, 5, 2021);
    zobraz(&ut);
    zobraz(&ut);

    return 0;
}

int pretezovaniOperatoru()
{
    cout << "***** Pretezovani operatoru *****\n";
    Datum po;
    po.set(24, 5, 2021);
    cout << "po=" << po << "\n";
    return 0;
}

Datum zadejDatum()
{
    int den = 0, mesic = 0, rok = 0;
    cout << "Zadej den mesic rok:\n";
    cin >> den >> mesic >> rok;
    Datum datum;
    datum.set(den, mesic, rok);

    return datum;
}

int reference()
{
    double destination = 42;
    double& ref = destination;
    double* ptr = nullptr;
    ptr = &destination;

    cout << "ref  = " << ref << "\n";
    cout << "ptr  = " << ptr << "\n";
    cout << "*ptr = " << *ptr << "\n";

    ref = 3.14;

    cout << "ref  = " << ref << "\n";
    cout << "*ptr = " << *ptr << "\n";

    return 0;
}

int vyjimky()
{
    cout << "***** Vyjimky *****\n";
    bool isRunning = true;
    while (isRunning)
    {
        try
        {
            Datum datum;
            datum = zadejDatum();                        
            datum.validate();
            cout << "datum =" << datum << "\n";
        }
        catch (const exception& e)
        {
            cerr << "Chyba: " << e.what() << "\n";
            isRunning = false;
        }
    }
    return 0;
}

int POD() {

    Datum datum;
    cout << "datum=" << datum << "\n";

    /*
    struct POD {
        int data;
    };

    POD a;
    POD b(); // toto neni nova instance ale deklarace funkce.
    cout << "a.data=" << a.data << "\n";
    //cout << "b.data=" << b.data << "\n";
    */

    return 0;
}

int main() {
    Datum datum;
    cout << "datum=" << datum << "\n";

}