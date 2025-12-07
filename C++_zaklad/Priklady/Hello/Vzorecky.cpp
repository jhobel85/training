#include <iostream>

using namespace std;

/** Obvod obdelnika o stranach a, b. */
double obvodObdelnika(double a, double b);

/*Obvod kruznice o polomeru r*/
double obvodKruznice(double r);

/*Delka prepony pravouhleho trojuhelnika*/
double delkaPrepony(double a, double b);

/** Koreny kvadraticke rovnice a*x^2 + b*x + c */
double korenPlus(double a, double b, double c);
double korenMinus(double a, double b, double c);

int main(int argc, char* argv[])
{
	cout << "***** Vzorecky *****\n";
	cout << "obvodObdelnika(50) = " << obvodObdelnika(10,20) << "\n";
	//cout << "obvodObdelnika(10,20) = " << obvodObdelnika << "\n";
	return 0;
}