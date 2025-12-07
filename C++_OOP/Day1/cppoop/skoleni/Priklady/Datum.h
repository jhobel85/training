#pragma once 
#include <ostream>

class Datum
{
public:
	//Vychozi konstruktor
	Datum();
	Datum(int den, int mesic, int rok);

	int getDen() const;
	int getMesic() const;
	int getRok() const;

	void set(int den, int mesic, int rok);
	void validate();
	int getMaxDenMesic();
private:
	int m_den;
	int m_mesic;
	int m_rok;
};

//pretezovani operatoru
std::ostream& operator << (std::ostream& os, const Datum& datum);

