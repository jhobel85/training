#include "Retezce.h"
#include <iostream>
#include <cctype>

size_t cpp_strlen(const char* str)
{
	auto zac = str;
	for (;*str != '\0'; str++)
	{
		
	}
	return str - zac;
}


const char* cpp_strchr(const char* str, int c)
{
	for (; *str != c; str++) {
		if (*str == '\0') {
			return nullptr;
		}
	}
	return str;
}

char* cpp_strupr(char* str)
{
	char* zac = str;

	for (; *str != '\0'; str++) {
		if (*str >= 'a' && *str <= 'z') {
			//*str -= 'a' - 'A';
			*str = *str - 32;
		}
	}
	return zac;
}

char* cpp_strupr2(char* str)
{
	auto zac = str;

	for (; *str != '\0'; str++) {
		//if (islower(*str)) {			
			*str = toupper(*str);
		//}
	}
	return zac;
}

//Funkce nakopiruje a nahradi znaky v dst
char* cpp_strcpy(char* dst, const char* src)
{
	char* zac = dst;
	for (;; ++src, ++dst) { // sekvencni operator carka - libovolny prikaz rozdelit na dva podprikazy (sekvenci prikazu)
		*dst = *src;
		if (*dst == '\0') { //koncovy znak ze src je take nakopirovany
			return zac;
		}
	}
	return nullptr;
}

//Neoptimalizaovat, protoze to vede jen k necitelnosti kodu.
char* cpp_strcpy2(char* dst, const char* src)
{
	char* zac = dst;
	/*
	for (;; ++src, ++dst) {		
		if ((*dst = *src) == '\0') { //koncovy znak ze src je take nakopirovany
			return zac;
		}
	}
	*/
	/*
	for (; (*dst = *src) != '\0'; ++src, ++dst)
	{

	}
	*/

	/*
	for (; *dst = *src; ++src, ++dst) {

	}
	*/
	
	while (*dst++ == *src++) {

	}

	return nullptr;
}

int cpp_strcmp(const char* s1, const char* s2)
{		
	for (; *s1 == *s2; ++s1, ++s2) {
		if (*s1 == '\0') {
			return 0;
		}		
	}
	return *s1 - *s2;
}
