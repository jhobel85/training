#include "SablonyFunkci.h"

#include <algorithm>
#include <cstdlib>
#include <format>
#include <iostream>
#include <numeric>

using namespace std;

constexpr unsigned faktorial(unsigned n)
{
    unsigned vysledek = 1;
    for (unsigned i = 2; i <= n; i++)
    {
        vysledek *= i;
    }
    return vysledek;
}

int programovaniVDobeKompilace()
{
    static_assert(faktorial(8) == 40320);
    
    cout << "faktorial(8) = " << faktorial(8) << "\n";
    int pokus[faktorial(3)];

    return 0;
}

int preferujteAlgoritmy()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << (a < b) ? a : b << '\n';
    std::cout << (a < b) ? b : a << '\n';
    return 0;
}

int makra()
{
    cout << "CPP_MIN(2, 1) = " << CPP_MIN(2, 1) << "\n";
    cout << "CPP_MIN(2.8, 1.4) = " << CPP_MIN(2.8, 1.4) << "\n";
    cout << "CPP_MIN(2, 1.4) = " << CPP_MIN(2, 1.4) << "\n";
    cout << "CPP_MIN(\"BB\", \"AA\") = " << CPP_MIN("BB", "AA") << "\n";

    int x = 1, y = 5;
    cout << "CPP_MIN(2, 5) = " << CPP_MIN(++x, y) << "\n";

    return 0;
}

int sablonovaFunkce()
{
    cout << "cpp_min(2, 1) = " << cpp_min(2, 1) << "\n";
    cout << "cpp_min(2.8, 1.4) = " << cpp_min(2.8, 1.4) << "\n";
    cout << "cpp_min(2, 1.4) = " << cpp_min<double>(2, 1.4) << "\n";
    cout << "cpp_min(\"BB\", \"AA\") = " << cpp_min("BB", "AA") << "\n";

    int x = 1, y = 5;
    cout << "cpp_min(2, 5) = " << cpp_min(++x, y) << "\n";

    return 0;
}

int cviceniSwap()
{
    {
        int x = 1, y = 5;
        cout << format("x={} y={}", x, y) << "\n";
        cpp_swap(x, y);
        cout << format("x={} y={}", x, y) << "\n";
    }

    {
        double x = 1, y = 5;
        cout << format("x={} y={}", x, y) << "\n";
        cpp_swap(x, y);
        cout << format("x={} y={}", x, y) << "\n";
    }
    return 0;
}

int copyCountFind()
{
    const int n = 5;
    const int pole[n] = {4, 7, 1, 3, 1};
    // 4 7 1 3 1
    CPP_ZOBRAZ(pole);

    double kopie[10];
    cout << "Algoritmus copy\n";
    double* konecKopie = cpp_copy(pole, pole + n, kopie);
    cpp_zobraz(kopie, konecKopie, "kopie=");

    cout << "Algoritmus count\n";
    cout << "pocet prvku 1 je " << cpp_count(pole, pole + n, 1) << "\n";
    cout << "\n";

    cout << "Algoritmus find\n";
    cout << "Pozice cisla 7 je ";
    cout << cpp_find(pole, pole + n, 7) - pole << "\n";
    cout << "\n";

    return 0;
}

auto minElementAccumulateReduce() -> int
{
    const int pole[] = { 4, 7, 1, 3, 1 };
    cpp_zobraz(begin(pole), end(pole), "pole=");
    cout << "Algoritmus min_element\n";
    cout << "Pozice nejmensiho cisla je ";
    cout << cpp_min_element(pole, end(pole)) - pole << "\n";
    cout << "\n";

    cout << "Algoritmus accumulate\n";
    cout << "Soucet prvku pole je ";
    cout << cpp_accumulate(pole, end(pole), 0) << "\n";
    cout << "\n";

    cout << "Algoritmus reduce\n";
    cout << "Soucet prvku pole je ";
    cout << cpp_reduce(pole, end(pole)) << "\n";
    cout << "\n";
    return 0;
}

int fillIota()
{
    int pole[10] = {};
    CPP_ZOBRAZ(pole);
    cout << "\n";

    cout << "Algoritmus fill\n";
    fill(pole, end(pole), 1);
    CPP_ZOBRAZ(pole);
    cout << "\n";

    ranges::fill(pole, 2);
    CPP_ZOBRAZ(pole);
    cout << "\n";

    fill_n(pole, 10, 3);
    CPP_ZOBRAZ(pole);
    cout << "\n";

    cout << "Algoritmus iota\n";
    iota(pole, end(pole), 0);
    CPP_ZOBRAZ(pole);
    cout << "\n";

    return 0;
}

int porovnejInt(const void* lhs, const void* rhs)
{
    auto a = static_cast<const int*>(lhs);
    auto b = static_cast<const int*>(rhs);

    return *a - *b;
}

int trideni()
{
    int pole[] = { 4, 7, 1, 3, 1 };
    CPP_ZOBRAZ(pole);
    cout << "\n";

#if 1
    cout << "Algoritmus qsort\n";
    qsort(pole, size(pole), sizeof(*pole), porovnejInt);
    CPP_ZOBRAZ(pole);
    qsort(pole, size(pole), sizeof(*pole), 
        [](const void* lhs, const void* rhs) {
            auto a = static_cast<const int*>(lhs);
            auto b = static_cast<const int*>(rhs);
            return *b - *a;
        });
    CPP_ZOBRAZ(pole);
    cout << "\n";

#else
    cout << "Algoritmus sort\n";
    ranges::sort(pole);
    CPP_ZOBRAZ(pole);
    cout << "\n";
#endif // 0
    return 0;
}