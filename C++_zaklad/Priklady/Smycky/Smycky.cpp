#include <iostream> // konzolove vstupni/vystupni proudy
#include <fstream> // souborove proudy

using namespace std;

void ctiSoubor() 
{
    cout << "Standardni makra\n"; // jsou prenositelna
    cout << __FILE__ << "\n"; //makro - preddefinovane, skryte symboly
    cout << __LINE__ << "\n"; //aktulani cislo radky
    cout << __DATE__ << "\n";
    cout << __TIME__ << "\n";
    cout << "\n";

    cout << "Microsoft makra\n"; // nejsou prenositelna, napr. na gcc jsou, ale maji jiny nazev
    cout << __FUNCTION__ << "\n"; // v c++23 by toto melo byt ve standardu
    cout << __FUNCSIG__ << "\n";
    cout << "\n";

    ifstream is{__FILE__}; //basic_ifstream<char, char_traits<char>>    
    //ifstream ifs("test.txt", std::ifstream::in); // moznost inicializatiovat pomoci kulatych zavorek - starsi    
    is >> noskipws; //modifikator, nebudou preskakovane bile znaky    
    
    while (is.good()) {        
        cout << (char)is.get();
    }
    /*
    char znak;
    while (is >> znak) {
        cout << znak;
    }
    */
} //automaticky se zde injektuji destruktory vsech objektu - automaticka sprava zdroju (vyhoda oproti C)

void obesenec()
{
    srand((unsigned)time(0)); // nevraci pseudonahodne
    constexpr int rozsah = 1024;
    constexpr int maxpocet = 10; //je to compile-time konstanta
    //const int cislo = rand() % 10; // vraci pouze 0 - 10    
    const int cislo = rand() % rozsah;
    int tip = 0;
    int pokus = 0;

    do {
        cout << ++pokus << ") Zadej int 0.."<<rozsah-1 << ": ";
        cin >> tip;
        if (tip != cislo)
        {
            cout << "Hledane cislo je: " <<( cislo > tip ? "vetsi" : "mensi") << "\n";
        }
    //} while (tip != cislo);
    } while (pokus < maxpocet && tip != cislo);

    if (tip == cislo)
    {
        cout << "Vyhral jsi\n";
    }
    else {
        cout << "Prohral jsi. Hledane cislo bylo " << cislo << ".\n";
    }
}

// iota oznaceni pro rostouci funkci
void cpp_iota(int prvni, int posledni)
{    
    for (int i = prvni; i <= posledni; i++)
    {
        cout << i << " ";
    }
    cout << "\n";
}

void line(int length) {
    string ret = " ";
    for (int i = 0; i < length; i++)
    {
        ret += '*';
    }
    cout << ret << "\n";
}

unsigned faktorial(unsigned n)
{
    unsigned vysledek = 1;    

    /*
    for (unsigned i = 2; i <=n; i++)
    {
        vysledek = vysledek * i;
    }
    */
    
    for (int i = n; i >= 2; i--)
    {
        //vysledek = vysledek * i;                
        vysledek *= i; // lepsi zapis pro C++        
    }
    
    return vysledek;
}

void rect(size_t cols, size_t rows)
{
    cout << "Oteviram tiskarnu...\n\n";
    int pocet = 0;

    for (size_t y = 0; y < rows; y++)
    {
        for (size_t x = 0; x < cols; x++)
        {
            cout << "*";
            ++pocet;

            if (pocet == 20)
            {
                break;
            }
        }
        cout << "\n";
    }

    cout << "\n";
    cout << "Uzaviram tiskarnu...\n";
}


int main()
{
    cout << "***** smycky *****\n";
    //ctiSoubor();

    //srand(10'000);//seed - staticka hodnota    
    cout << rand() << "\n"; //pseudonahodne cislo, kdy vrati nahodnou hodnotu, ale pote vzdy vraci stejnou nahodnou   

    //obesenec();

    //1 2 3 4 5 6 7 8 9
    cpp_iota(1,9);
    //15...20
    cpp_iota(15, 20);
    line(8); //*********
    line(4); //****

    cout << "\n";
    cout << "faktorial(0) = " << faktorial(0) << "\n";
    cout << "faktorial(1) = " << faktorial(1) << "\n";
    cout << "faktorial(8) = " << faktorial(8) << "\n"; //40320

    rect(8, 5);
    cout << "\n";

    return 0;
}



