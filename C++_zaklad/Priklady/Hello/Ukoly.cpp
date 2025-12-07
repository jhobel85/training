#define _USE_MATH_DEFINES
#include <iostream> 
#include <cmath>

using namespace std;

int y;
//const double PI = M_1_PI;
const double PI = 2.0 * acos(0.0); // spocitani hodnoty lepsi pri startu PC jednou nez vzdy v prubehu.

void promenne(double param) {
    double x = y;
}

/** Obvod obdelnika o stranach a, b. */
double obvodObdelnika(double a, double b);

/*Obvod kruznice o polomeru r*/
double obvodKruznice(double r);

/*Delka prepony pravouhleho trojuhelnika*/
double delkaPrepony(double a, double b);

/** Koreny kvadraticke rovnice a*x^2 + b*x + c */
double korenPlus(double a, double b, double c);
double korenMinus(double a, double b, double c);

/*
struct Koreny {
    double diskriminant;
    double korenPlus;
    double korenMinus;
};
*/

class Koreny {
    public:
    double diskriminant;
    double korenPlus;
    double korenMinus;
};

Koreny kvadratickaRovnice(double a, double b, double c);

// nemeli bysme v jedne metode zroven pocitat a zobrazovat !
void zobraz(const char* titulek, const Koreny* vysledky);

int main(int argc, char* argv[])
{   
    cout << "**** Vzorecky ****\n";
    
    cout << "obvodObdelnika(10, 20) = " << obvodObdelnika(10, 20) << "\n";//60
    cout << "obvodKruznice(50) = " << obvodKruznice(50) << "\n";//314
    cout << "delkaPrepony(3, 4) = " << delkaPrepony(3, 4) << "\n";//5
    cout << "korenPlus(2,-3,1) = " << korenPlus(2, -3, 1) << "\n";//1
    cout << "korenMinus(2,-3,1) = " << korenMinus(2, -3, 1) << "\n";//0.5
    cout << "\n";
    Koreny vysledky = kvadratickaRovnice(2, -3, 1);
    /*
    cout << "Koreny rovnice: 2*x^2 - 3x + 1 = 0\n";
    cout << "diskriminant = " << vysledky.diskriminant << "\n";
    cout << "korenPlus = " << vysledky.korenPlus << "\n";
    cout << "korenMinus = " << vysledky.korenMinus << "\n";    
    */
    zobraz("Koreny rovnice: 2*x^2 - 3x + 1 = 0", &vysledky);
    cout << "\n";
    vysledky = kvadratickaRovnice(1, 2, -63);
    zobraz("Koreny rovnice : x ^ 2 + 2x - 63 = 0", &vysledky);
    return 0;
}

double obvodObdelnika(double a, double b)
{
    auto ret = 2 * (a + b);
    return ret;
}

double obvodKruznice(double r)
{
    double obvod;
    
    obvod = 2 * PI * r;
    return obvod;
}

double delkaPrepony(double a, double b)
{
    const double c = sqrt(a * a + b * b); // dobre je oznacovat finalni hodnoty const hondotou   
    return c;
}

double korenPlus(double a, double b, double c)
{    
    double d = b * b - 4 * a * c;
    double x1 = (-b + sqrt(d)) / (2 * a);
    return x1;
}

double korenMinus(double a, double b, double c)
{
    double d = b * b - 4 * a * c;
    double x2 = (-b - sqrt(d)) / (2 * a);
    return x2;
}

Koreny kvadratickaRovnice(double a, double b, double c)
{
    Koreny vysledek; //ani neni treba inicializovat
    //Koreny vysledek = {1,2,3}; // seznam inicializatoru
    vysledek.diskriminant = b * b - 4 * a * c;
    double odmocnina = sqrt(vysledek.diskriminant);
    vysledek.korenPlus = (-b + odmocnina) / (2 * a);
    vysledek.korenMinus = (-b - odmocnina) / (2 * a);
    return vysledek;
}

/*
void zobraz(const char* titulek, Koreny vysledky)
{
    cout << titulek << "\n";    
    cout << "diskriminant = " << vysledky.diskriminant << "\n";
    cout << "korenPlus = " << vysledky.korenPlus << "\n";
    cout << "korenMinus = " << vysledky.korenMinus << "\n";
}
*/

// - by default syntaxe * syntaxe pro vystypni parametru - tzn. je to aktualne vstupne/vystupni parametr -> chceme jen vstupni const!
void zobraz(const char* titulek, const Koreny* vysledky)
{
    cout << titulek << "\n";
    cout << "diskriminant = " << vysledky->diskriminant << "\n";
    cout << "korenPlus = " << vysledky->korenPlus << "\n";
    cout << "korenMinus = " << vysledky->korenMinus << "\n";
}