
//include guard - je treba zvolit a definovat v Guidelines
#ifndef __RETEZCE_H__
#define __RETEZCE_H__ //nadefinujeme symbol pro kompilator - jen poku jeste neni definovany
#pragma once // rika, ze se inlude vlozi jen jednou, pokud se jiz vkladal
#pragma message ("Vkladam Retezce.h")

/*
delka
porovnani
kopirovani
hledani
spojovani
prevod mala na velka

*/

//funkce vraci delku retezce, coz znamena:
// - pocet nenulovych znaku
// - index nuloveho znaku
size_t cpp_strlen(const char* str);

//byte allignment - int c -> asci hodnota characteru
//Funkce hleda prvni vyskyt znaku c uvnitr retezce 
//Vraci ukazatel na nalezeny znak uvitr retezce
// pokud znak neni nalezen vracime nullptr.
//Hledat je mozne take nulovy znak na konci retezce
const char* cpp_strchr(const char* str, int c);

//Funkce prevadi mala pismena
//Vraci ukazatel na zacatek prevedeneho retezce
char* cpp_strupr(char* str); // vstup-vystupni parametr
char* cpp_strupr2(char* str);

//dst = src
//Funkce kopiruje vsechny znaky retezce src (vcetne nuloveho znaku)
//do bufferu dst
//Vracime ukazatel na zacatek dst retezce
//Problem preteceni dst, davat pozor - radeji ukoncit chybou (deterministicky) nez nechat nedeterministicke chovani aplikace
char* cpp_strcpy(char* dst, const char* src);

//dst += src
//Funkce kopiruje vsechny znaky retezce src (vcetne nuloveho znaku)
//na konec retezce dst
//Vracime ukazatael na zacatek dst retezce
char* cpp_strcpy(char* dst, const char* src);

// s1 < s2  vracime libovolne zaparne cislo
// s1 == s2 vracime 0
// s1 > s2  vracime libovolne kladne cislo
//v priapde  -1 , 0 , 1 -> int obsahuje jeste mnoho dalsich cisel, ktere by davali nedefinovany stav
//Funkce hleda prvni rozdilny znak a vraci rozdil ASCII hodnot
// Vracime nulu pokud neni nalezen rozdiln znak a oba retezce konci. 
// V pripade rozdilne delky se porovna nulovy znak, ktery je mensi nez vsechny ostatni.
int cpp_strcmp(const char* s1, const char* s2);




#endif// __RETEZCE_H__