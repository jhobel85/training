#include "Datum.h"
/*
#include <iostream>
#include <string.h>
#include <vector>*/
using namespace std;
const int MIN_YEAR = 1970;

Datum::Datum()
    :m_den{ 1 }
    , m_mesic{1}
    , m_rok{ MIN_YEAR }
{           
    /*
    m_den = 1;
    m_mesic = 1;
    m_rok = MIN_YEAR;
    */
}

Datum::Datum(int den, int mesic, int rok)
    : m_den{ 1 }
    , m_mesic{ 1 }
, m_rok{ MIN_YEAR }
{
    validate();
}

int Datum::getDen() const
{
    return m_den;
}

int Datum::getMesic() const
{
    return m_mesic;
}

int Datum::getRok() const
{
    return m_rok;
}

void Datum::validate()
{
    bool isValid = true;
    isValid &= m_den >= 1 && m_den <= getMaxDenMesic();
    isValid &= m_mesic >= 1 && m_mesic <= 12;
    isValid &= m_rok >= MIN_YEAR;        

    if (!isValid) {
        throw invalid_argument("neplatne datum");
    }
}

int GetMaxDenMesic2(int mesic) {
    int maxMesic = 31;
    switch (mesic) {
    case 1:
        break;
    case 2:
        maxMesic = 28;
        break;
    case 3:
        break;
    case 4: maxMesic--;
        break;
    case 6: break;
    }
    return maxMesic;
}

int Datum::getMaxDenMesic(){
    int maxMesic = 30;
    switch (m_mesic) {
    case 1:
        maxMesic = 31;
        break;
    case 2:
        maxMesic = 28;
        break;
    case 3:
        maxMesic = 31;
        break;
    case 4:
        maxMesic = 30;
        break;
    case 5:
        maxMesic = 31;
        break;
    case 6:
        maxMesic = 30;
        break;
    case 7:
        maxMesic = 31;
        break;
    case 8:
        maxMesic = 31;
        break;
    case 9:
        maxMesic = 30;
        break;
    case 10:
        maxMesic = 31;
        break;
    case 11:
        maxMesic = 30;
        break;
    case 12:
        maxMesic = 31;
        break;
    }
    return maxMesic;
}

void Datum::set(int den, int mesic, int rok)
{
    this->m_den = den;
    this->m_mesic = mesic;
    this->m_rok = rok;
}

std::ostream& operator<<(std::ostream& os, const Datum& datum)
{
    const char delim = '.';
    os << datum.getDen() << delim;
    os << datum.getMesic() << delim;
    os << datum.getRok();
    return os;
}
