#include <iostream>
#include <vector> // dynamicke pole
using namespace std;
//#define n 10; //C syntaxe

//void zobraz(double pole[5]) // nema smysl kopirovat (alokovat) vsechny prvky pole -> autoamticky se jedna o referencni typ (pointer) !
//void zobraz(double pole[]) // 5 zbytecna, adresa prniho prvku pole, nikoliv cele pole!
void zobraz(const double *pole, size_t n) //pointer na prvni prvke - jen lepsi konvence, velikost pole - take nutna!
{//*pole -> neni input parameter by default byRef, pokud vstup pak const
    //V C++ nebo C# vyssi abstrakce, ktera ma uvnitr tu dvojici.
    for (size_t i = 0; i < n; i++)
    {
        cout << pole[i] << " ";
    }
    //cout << "velikost pole = " << sizeof(pole) << " byte.\n\n";
}

int statickePole()
{
    cout << "Pole jazyka C\n";
    constexpr int n = 5; // 5000 compile-time warning -> stack je pretizeny, lepe presunout na haldu (dyn. alokace - vyssi abstrakce), tzn. pole nesmi byt moc velike.
    //double pole[n]; // jeden typ a delka -> dve promenne
    double pole[n] = {4,1,7,3,6}; // inicializator
    //double pole[n] = { }; // vynulovani pole
    cout << "Velikost pole = " << sizeof(pole) << " byte.\n";

    cout << "Indexovy prouchod polem.";
    for (size_t i = 0; i < n; i++)
    {        
        cout << pole[i] << " ";
    }
    cout << "\n";

    cout << "Indexovy pruchod polem.\n";
    cout << "C++ 11 Range-based for loop.\n";
    for (auto prvek : pole) {
        cout << prvek << " ";
    }    
    cout << "\n\n";

    cout << "Predani pole funkci.\n";
    zobraz(pole, n);
    cout << "\n";


    return 0;
}

int main()
{
    cout << " Trida vector - Dynamicka alokace - automaticka alokace - nehorazi memory leaky\n";    
    
    vector<double> pole { 4,1,7,3,6 }; // inicializator    
    cout << "Velikost pole = " << sizeof(pole) << " byte.\n";

    cout << "Indexovy prouchod polem.";
    for (size_t i = 0; i < pole.size(); i++)
    {
        cout << pole[i] << " ";
    }
    cout << "\n";
    pole.push_back(11);//pridani prvku
    pole.push_back(13);
    pole.push_back(16);
    cout << "Indexovy pruchod polem.\n";
    cout << "C++ 11 Range-based for loop.\n";
    for (auto prvek : pole) {
        cout << prvek << " ";
    }
    cout << "\n\n";
    pole.pop_back();//odebrani
    pole.pop_back();
    cout << "Predani pole funkci.\n";
    zobraz(pole.data(), pole.size());
    cout << "\n";

    return 0;
}