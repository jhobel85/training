#include "SablonyFunkci.h"

#include <algorithm>
#include <filesystem>
#include <functional>
#include <numeric>
#include <string>

namespace fs = std::filesystem;
using namespace std;

void neclenskaFunkce()
{
	cout << __FUNCSIG__ << "\n";
}

class Trida
{
public:
	int stav = 0;

	void clenskaFunkce()
	{
		cout << __FUNCSIG__ << " stav=" << stav++ << "\n";
	}
};

class Functor
{
public:
	int stav = 0;

	void operator() ()
	{
		cout << __FUNCSIG__ << " stav=" << stav++ << "\n";
	}
};

int volatelneEntity()
{
	cout << "Volatelne entity:\n";
	cout << "1) neclenska funkce\n";
	neclenskaFunkce();
	void (*ptrNeclenskaFunkce)() = nullptr;
	ptrNeclenskaFunkce = &neclenskaFunkce;
	(*ptrNeclenskaFunkce)();
	ptrNeclenskaFunkce();
	cout << "\n";

	cout << "2) clenska funkce\n";
	Trida instance;
	Trida* ptrInstance = &instance;
	instance.clenskaFunkce();
	ptrInstance->clenskaFunkce();

	void (Trida::*ptrClenskaFunkce)() = nullptr;
	ptrClenskaFunkce = &Trida::clenskaFunkce;
	(instance.*ptrClenskaFunkce)();
	(ptrInstance->*ptrClenskaFunkce)();
	cout << "\n";

	cout << "3) funkcni objekt\n";
	Functor functor;
	functor();
	cout << "\n";

	int stav = 0;
	auto lambda = [&stav] {
		cout << __FUNCSIG__ << " stav=" << stav++ << "\n";
	};
	cout << "4) Lambda funkce\n";
	lambda();
	cout << "\n";

	cout << "5) Polymorficka funkce\n";
	function<void()> fn;
	fn = &neclenskaFunkce;
	fn();
	fn = bind(&Trida::clenskaFunkce, ptrInstance);
	fn();
	fn = functor;
	fn();
	fn = lambda;
	fn();
	cout << "\n";

	return 0;
}

int lambdaVyrazy()
{
	auto identity = [](int a) {
		return a;
	};
	auto add = [](int a, int b) {
		return a + b;
	};
	auto sub = [](int a, int b) {
		return a - b;
	};
	auto mul = [](int a, int b) {
		return a * b;
	};
	auto identityf = [](int a) {
		return [a] {
			return a;
		};
	};

	cout << "identify  = " << identity(10) << "\n";
	cout << "add       = " << add(20, 10) << "\n";
	cout << "sub       = " << sub(20, 10) << "\n";
	cout << "mul       = " << mul(20, 10) << "\n";
	cout << "identifyf = " << identityf(10)() << "\n";
	return 0;
}

int forEach()
{
	int pole[] = { 4, 7, 1, 3, 1 };
	CPP_ZOBRAZ(pole);
	cout << "\n";

	int minVal = pole[0];
	int maxVal = pole[0];
	double soucet = pole[0];

	cpp_for_each(next(pole), end(pole), [&](int prvek) {
		soucet += prvek;
		if (prvek < minVal)
		{
			minVal = prvek;
		}
		else if (maxVal < prvek)
		{
			maxVal = prvek;
		}
	});
	cout << "minVal = " << minVal << "\n";
	cout << "maxVal = " << maxVal << "\n";
	cout << "soucet = " << soucet << "\n";
	cout << "prumer = " << soucet / size(pole) << "\n";
	return 0;
}

string& encode(string& text)
{
	constexpr string_view klic = "PA$$W0RD"sv;
	unsigned index = 0;
	cpp_transform(begin(text), end(text), begin(text), [&index](char znak) {
		return znak ^ klic[index++ % klic.size()];
	});
	return text;
}

int generatorUnarniPredikat()
{
	int pole[20] = {};
	CPP_ZOBRAZ(pole);
	cout << "\n";

	cout << "Algoritmus generate\n";
	cpp_generate(pole, end(pole), Rand{10, 20});
	CPP_ZOBRAZ(pole);
	cout << "\n";

	string text = "skakal pes pres oves";
	cout << "text = " << text << "\n";
	cout << "text = " << encode(text) << "\n";
	cout << "text = " << encode(text) << "\n";
	cout << "\n";

	cout << "Algoritmus count_if\n";
	cout << "Pocet prvku vetsich nez 15 je ";
	cout << cpp_count_if(pole, end(pole), [](int prvek) {
		return prvek > 15;
	}) << "\n";
	cout << "\n";
	cout << "Pocet prvku vetsich nez 15 je ";

	using namespace placeholders;
	cout << cpp_count_if(pole, end(pole), bind(greater<int>{}, _1, 15)) << "\n";
	cout << "\n";

	cout << "Pocet sudych cisel je ";
	cout << cpp_count_if(pole, end(pole), &jeSude) << "\n";
	cout << "\n";

	cout << "Pocet lichych cisel je ";
	cout << cpp_count_if(pole, end(pole), not_fn(&jeSude)) << "\n";
	cout << "\n";

	cout << "Algoritmus find_if\n";
	cout << "Pozice prvniho prvku mensiho nez 12 je ";
	cout << cpp_find_if(pole, end(pole), bind(less<int>{}, _1, 12)) - pole
		 << "\n";

	return 0;
}

int binarniFunkce()
{
	const char slova[][8] = {
		"skakal",
		"pes",
		"pres",
		"oves"
	};
	CPP_ZOBRAZ(slova);

	cout << "Nejkratsi slovo je: " << *cpp_min_element(slova, end(slova),
		[](auto a, auto b) {
			return strlen(a) < strlen(b);
	}) << "\n";

	cout << "Nejmensi slovo je: " << *cpp_min_element(slova, end(slova),
		[](auto a, auto b) {
			return strcmp(a, b) < 0;
		}) << "\n";

	int cisla[8];
	iota(cisla, end(cisla), 1);
	CPP_ZOBRAZ(cisla);

	// 40320
	cout << "Soucin cisel je ";
	cout << cpp_accumulate(cisla, end(cisla), 1, multiplies<int>{});
	cout << "\n";
	return 0;
}

int algoritmusReplace()
{
	int pole[20] = {};
	cpp_generate(pole, end(pole), Rand{ 10, 20 });
	CPP_ZOBRAZ(pole);

	int kopie[20];
	cout << "Algoritmus replace_copy\n";
	int* konecKopie = replace_copy(pole, end(pole), kopie, 18, 0);
	cpp_zobraz(kopie, konecKopie, "kopie=");

	cout << "Algoritmus replace\n";
	replace(pole, end(pole), 18, 0);
	CPP_ZOBRAZ(pole);

	cout << "Algoritmus replace_if\n";
	replace_if(pole, end(pole), &jeSude, 1);
	CPP_ZOBRAZ(pole);

	return 0;
}

int removeUnique()
{
	int pole[20] = {};
	cpp_generate(pole, end(pole), Rand{ 10, 20 });
	CPP_ZOBRAZ(pole);
	cout << "\n";

	int licha[20];
	int* konecLicha = remove_copy_if(pole, end(pole), licha, &jeSude);
	cpp_zobraz(licha, konecLicha, "licha=");

	int suda[20];
	int* konecSuda = copy_if(pole, end(pole), suda, &jeSude);
	cpp_zobraz(suda, konecSuda, "suda=");
	cout << "\n";

	cout << "Algoritmus remove\n";
	int* konec = remove(pole, end(pole), 18);
	CPP_ZOBRAZ(pole);
	cpp_zobraz(pole, konec, "pole=");
	cout << "\n";

	cout << "Algoritmus remove_if\n";
	konec = remove_if(pole, konec, &jeSude);
	CPP_ZOBRAZ(pole);
	cpp_zobraz(pole, konec, "pole=");
	cout << "\n";

	cout << "Algoritmus unique\n";
	sort(pole, konec);
	konec = unique(pole, konec);
	cpp_zobraz(pole, konec, "pole=");
	cout << "\n";

	return 0;
}

int oddily()
{
	int pole[20] = {};
	cpp_generate(pole, end(pole), Rand{ 10, 20 });
	CPP_ZOBRAZ(pole);
	cout << "\n";
	
	int suda[20];
	int licha[20];

	auto [konecSuda, konecLicha] = partition_copy(pole, end(pole), suda, licha, jeSude);
	cpp_zobraz(suda, konecSuda, "suda=");
	cpp_zobraz(licha, konecLicha, "licha=");
	cout << "\n";

	iota(pole, end(pole), 10);
	CPP_ZOBRAZ(pole);

	cout << "(nestabilni) partition\n";
	partition(pole, end(pole), jeSude);
	CPP_ZOBRAZ(pole);
	cout << "\n";

	iota(pole, end(pole), 10);
	cout << "stable_partition\n";
	stable_partition(pole, end(pole), jeSude);
	CPP_ZOBRAZ(pole);
	cout << "\n";

	return 0;
}

int anyAllNoneOf()
{
	int pole[20] = {};
	cpp_generate(pole, end(pole), Rand{ 10, 20 });
	CPP_ZOBRAZ(pole);
	cout << "\n";

	cout << "Algoritmus any_of, all_of, none_of:\n";
	cout << "Je v poli sude cislo? ";
	cout << ranges::any_of(pole, jeSude) << "\n";
	cout << "Jsou vsechna cisla v poli suda? ";
	cout << ranges::all_of(pole, jeSude) << "\n";
	cout << "Jsou vsechna cisla v poli licha? ";
	cout << ranges::none_of(pole, jeSude) << "\n";
	cout << "\n";

	cout << "Alternativy s vyuzitim find, count:\n";
	cout << "Je v poli sude cislo? " << (ranges::find_if(pole, &jeSude) != end(pole)) << "\n";
	cout << "Je v poli sude cislo? " << (0 != ranges::count_if(pole, &jeSude)) << "\n";
	return 0;
}

bool jePalindrom(string_view slovo)
{
	return equal(
		slovo.begin(), next(slovo.begin(), slovo.size() / 2), 
		slovo.rbegin(),
		[](char a, char b) {
			return toupper(a) == toupper(b);
	});
}

bool isSubpathOf(const fs::path& base, const fs::path& cesta)
{
	auto result = mismatch(base.begin(), base.end(), cesta.begin(), cesta.end());
	return result.first == base.end() || result.first->empty();
}

int equalMismatch()
{
	constexpr string_view slova[] = {
		"Anna"sv,
		"rotor"sv,
		"nejen"sv,
		"madam"sv,
		"vlk"sv,
	};

	for (auto slovo : slova)
	{
		cout << "jePalindrom " << slovo << " " << jePalindrom(slovo) << "\n";
	}

	cout << "\n";
	cout << "Algoritmus mismatch\n";
	string_view reference = "{38647C7D-57FC-4373-B490-90128615359A}"sv;
	string_view actual    = "{38647C7D-57FC-4373-B490-90128115359A}"sv;
	cout << "reference = " << reference << "\n";
	cout << "actual    = " << actual << "\n";
	string ruler(
		max(reference.length(), actual.length()),
		'-'
	);
	auto [refPos, actPos] = mismatch(reference.begin(), reference.end(), actual.begin());
	if (refPos != reference.end())
	{
		ruler[distance(reference.begin(), refPos)] = '^';
	}
	cout << "ruler     = " << ruler << "\n";
	cout << "is_permutation = " << is_permutation(reference.begin(), reference.end(), actual.begin()) << "\n";
	cout << "\n";

	fs::path base = L"E:\\SKOLENI\\";
	fs::path cesty[] = {
		L"E:\\SKOLENI\\Priklady\\",
		L"E:\\cinder_0.9.2_vc2015\\",
	};

	cout << "base = " << base << "\n";
	for (auto& cesta : cesty)
	{
		cout << "is subpath " << cesta << " " << isSubpathOf(base, cesta) << "\n";
	}
	return 0;
}

int rotateReverse()
{
	string text = "abcd1234efgh";
	cout << text << "\n";
	auto mid = ranges::find(text, '1');
#if 1
	rotate(begin(text), mid, end(text));
#else
	// rotate = 3xreverse
	reverse(begin(text), mid);
	reverse(mid, end(text));
	reverse(begin(text), end(text));
#endif 
	cout << text << "\n";
	return 0;
}