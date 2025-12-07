//projektove interni hlavicky -
#include "Retezce.h" // kompilator kouka do projektu a do Additinal Include Directories

//externi hlavicky
#include <iostream> //standardni knihovny - automaticky jde kompiler do svych zdrojovych kodu

using namespace std;

int main()
{
    cout << "Retezce!\n";
    cout << "cpp_strlen: " << cpp_strlen("Ahoj") << "\n";

    //%s - formatovaci znak pro string
    //%s je vypustka pro printf (neco jako genericita) - vypustku ale v produkci nepouzivat
    printf("cpp_strchar '%s'\n ", cpp_strchr("Ahoj", 'A'));  //Ahoj
    printf("cpp_strchar '%s'\n ", cpp_strchr("Ahoj", 'h'));  //hoj
    printf("cpp_strchar '%s'\n ", cpp_strchr("Ahoj", 'H'));  //'(null)'
    printf("cpp_strchar '%s'\n ", cpp_strchr("Ahoj", '\0')); //''

    char string[80] = "Skakal pes, pres oves. ";
    cout << "cpp_strupr: " << cpp_strupr(string) << "\n";
    char string2[80] = "Skakal pes, pres oves. ";
    cout << "cpp_strupr: " << cpp_strupr2(string2) << "\n";

    char string1[80] = "XXXXXXXX";
    cout << "cpp_strcpy: " << cpp_strcpy(string1, "Ahoj") << "\n";    
    char string3[80] = "XXXXXXXX";
    cout << "cpp_strcpy2: " << cpp_strcpy(string3, "Ahoj") << "\n";

    cout << "cpp_strcmp: " << cpp_strcmp("AA", "AB") << "\n";
    cout << "cpp_strcmp: " << cpp_strcmp("AB", "AB") << "\n";
    cout << "cpp_strcmp: " << cpp_strcmp("AB", "AA") << "\n";


    return 0;
}