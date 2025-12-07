#include <iostream>
#include <thread>
using namespace std;

int thisThread()
{
    cout << "TID main " << this_thread::get_id() << "\n";
    this_thread::sleep_for(1s);
    cout << "probuzeno...\n";
    cout << "hardware_concurrency = " << thread::hardware_concurrency() << ""; // max. pocet skutecnych paralelnich uloh pro dany procesor.

    return 0;
}

void threadProc()
{
    cout << "TID threadProc " << this_thread::get_id() << "\n";
    for (size_t i = 0; i < 6; i++)
    {
        this_thread::sleep_for(500ms);
    }
    cout << "probuzeno...\n";
}


//C++11 -> nutno volat join pred destruktorem.
int tridaThread()
{
    //thisThread();
    thread vlakno;
    cout << "joinable = " << vlakno.joinable() << "\n,"; //joinable = je vytvoreny fork?
    
    cout << "fork...\n";
    vlakno = thread(&threadProc);//fork operace
    cout << "joinable = " << vlakno.joinable() << "\n,"; // joinable = 1
    vlakno.join(); // destruktor probehne v poradku - davat pozor, vzdy nutno zavolat!!
    cout << "joinable = " << vlakno.joinable() << "\n,"; //joinable = 0, jinak error.

    //thisThread();
    return 0;
}

void earlyExit(stop_token stop)
{
    cout << "TID threadProc " << this_thread::get_id() << "\n";
    for (size_t i = 0; i < 6; i++)
    {
        if (stop.stop_requested()) { //zajisteni rychleho destruktoru, neceka na finalni exit.
            break;
        } // co nejrychlejsi ukonceni asynchronni processingu.
        this_thread::sleep_for(500ms);
    }
    cout << "probuzeno...\n";
}

//Nove od C++20
int ukoncovaniVlaken()
{
    jthread vlakno;
    cout << "joinable = " << vlakno.joinable() << "\n";

    cout << "fork...\n";
    vlakno = jthread{ &earlyExit }; // early exit je navazany na stopToken jtread tridu
    cout << "joinable = " << vlakno.joinable() << "\n";

    return 0;
}

void sectiPtr(int a, int b, int* vysledek)
{
    *vysledek = a + b;

}

void sectiRef(int a, int b, int& vysledek)
{
    vysledek = a + b;
}

int poleVlaken1() {
    int vysledek1;

    cout << "fork...\n";
    thread pole[] = {
        thread{&sectiPtr,10,20,&vysledek1}
    };

    //cout << "vysledek1 = " << vysledek1 << "\n"; // nedefinovana hodnota - vlakno tisken, ale jeste nema spocitano.
    //muze se stat, ze se vysledek vypisuje v prubehu pocitani - vysledek bude napr. jen 10 nebo 0, atd.
    //zaklad je treba vyresit synchronizaci a zamykat sdilene hodnoty -> udelat promennou atomickou !!!
    //jednodussi reseni - posunout vypis az po skonceni pocitani.
    //--> mezi for-join data nesmim cist/zapisovat - davat pozor - casty zdroj chyb.
    cout << "join...\n"; // ukonci vechny vlakna a pokracuj v hlavnim vlakne.
    for (auto& vlakno : pole) {
        vlakno.join();
    }

    cout << "vysledek1 = " << vysledek1 << "\n"; // vlakno uz neexistuje, dopracovalo, mohu vklidu tisknout.

    return 0;
}

int secti(int a, int b)
{
    return a + b;
}

int predavaniParametru() {
    int vysledek1 = 0;
    int vysledek2 = 0;
    int vysledek3 = 0;

    cout << "fork...\n";
    thread pole[] = {
        thread{&sectiPtr,10,20,&vysledek1},
        thread{&sectiRef,11,22,ref(vysledek2)},        // reference z int hodnoty -> kompilacni chyba v novem C++ -> reseni variadicky reference wrapper (neni to vstupni parameter, ale vystupni.)
        thread{[&vysledek3] { // labda vyraz pro vyuziti navratouvou hodnotu - velmi caste
                vysledek3 = secti(13, 23);
          } } 
        //dalsi moznost bind -> nakeshovani navratove hodnoty -> ale lamba je lepsi.
    };

    for (auto& vlakno : pole) {
        vlakno.join();
    }

    cout << "vysledek1 = " << vysledek1 << "\n"; 
    cout << "vysledek2 = " << vysledek2 << "\n";
    cout << "vysledek3 = " << vysledek3 << "\n";

    return 0;
}


