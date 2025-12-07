#include "SablonyFunkci.h"

#include <map>
#include <string>
#include <unordered_map>

using namespace std;

void zobraz(auto tabulka, const char* titulek)
{
	cout << titulek << "\n";
	for (const auto& [klic, hodnota] : tabulka)
	{
		cout << klic << " " << hodnota << "\n";
	}
}

int mapa()
{
	map<string, int> kurzy;
	kurzy.insert(pair<string, int>{"CPP_INTRO", 5});
	kurzy.insert(make_pair("CPP_OOP"s, 5));
	kurzy["CPP_STD"] = 5;
	kurzy.insert({"CPP_THR", 1});

	zobraz(kurzy, "kurzy:");

	for (;;)
	{
		cout << "\n";
		cout << "Zadej hledane skoleni (k - konec): ";
		string skoleni;
		cin >> skoleni;
		if (skoleni == "k")
		{
			break;
		}

#if 1
		auto pos = kurzy.find(skoleni);
		if (pos != kurzy.end())
		{
			cout << "Delka kurzu " << pos->first << " je " << pos->second << " dnu.\n";
		}
		else
		{
			cout << "Kurz nenalezen!\n";
		}
#elif 0
		cout << "Delka kurzu " << skoleni << " je " << kurzy[skoleni] << " dnu.\n";
#else
		try
		{
			cout << "Delka kurzu " << skoleni << " je " << kurzy.at(skoleni) << " dnu.\n";
		}
		catch (const exception& e)
		{
			cout << "kurz nenalezen!\n";
		}
#endif // 0
	}

	cout << "\n";
	zobraz(kurzy, "kurzy:");

	return 0;
}

int main()
{
	unordered_map<string, int> kurzy;
	kurzy.insert(pair<string, int>{"CPP_INTRO", 5});
	kurzy.insert(make_pair("CPP_OOP"s, 5));
	kurzy["CPP_STD"] = 5;
	kurzy.insert({ "CPP_THR", 1 });

	zobraz(kurzy, "kurzy:");

	for (;;)
	{
		cout << "\n";
		cout << "Zadej hledane skoleni (k - konec): ";
		string skoleni;
		cin >> skoleni;
		if (skoleni == "k")
		{
			break;
		}

		auto pos = kurzy.find(skoleni);
		if (pos != kurzy.end())
		{
			cout << "Delka kurzu " << pos->first << " je " << pos->second << " dnu.\n";
		}
		else
		{
			cout << "Kurz nenalezen!\n";
		}
	}
	return 0;
}
