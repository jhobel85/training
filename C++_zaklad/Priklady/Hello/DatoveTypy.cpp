//1. seznam inkludovanych knihoven
#include <iostream> 

//2. jmenne prostory
using namespace std; //vyhoda, definice na jednom miste.
//neexistujici jmenny prostor = globalni

//Dopredna deklarace funkce, je to prikaz -> ukoncen strednikem
void procedura(double parametr);

long secti(short ax, short ay)
{
    long result = ay;//zamezeni preteceni, ale v praxi se moc nepouziva -> spise stejne typy a validace parameteru
    return result + ay;
}

void datoveTypy()
{
    cout << "Datove typy!\n"; 
    
    //Primitivni datove typy (string neni primitivni dat. typ)
    cout << "Cela cisla\n"; // sekvence bitu o nejake delce    
    cout << "Velikost bool " << sizeof(bool) << " byte\n"; // zabira 1 byte, ale stacil by 1 bit - ale bity nemaji adresu!
    cout << "Velikost char " << sizeof(char) << " char\n";
    cout << "Velikost short " << sizeof(short) << " byte\n";//int16_t
    cout << "Velikost int " << sizeof(int) << " byte\n";//int32_t
    cout << "Velikost long " << sizeof(long) << " byte\n";//int32_t
    cout << "Velikost long long " << sizeof(long long) << " byte\n"; //int64_t
    //v pripade prenositelneho kodu (Win, Linux), tak pouzivat: int16_t, ...
    cout << "\n";

    cout << "Plovouci radova carka\n";    
    cout << "Velikost float " << sizeof(float) << " byte\n"; // 
    cout << "Velikost double " << sizeof(double) << " byte\n"; // dvojnasobna presnost nez float
    cout << "Velikost long double " << sizeof(long double) << " byte\n"; // na WIN stejne jako double (je to od urciteho roku, drive 16 bitova)
    
    cout << "\n";
}

//4. funkce
//Main nesmime volat v nasem programu, vola si ho prostredi automaticky.
int Xmain(int argc, char* argv[])
{
    cout << "Hello World!\n"; //cout je instance objektu (pouzivat objektu muzeme, ale nebudeme delat navrh)
    procedura(3.14);
    procedura(42);
    datoveTypy();
    return 0;
}

//Definice funkce
void procedura(double parametr) {
    cout << "parametr = " << parametr << "\n";
    return;
}

