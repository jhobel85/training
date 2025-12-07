#pragma once
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <utility>

#define CPP_MIN(a, b)	((a) < (b) ? (a) : (b))

template <class T>
T cpp_min(T a, T b)
{
	return a < b ? a : b;
}

template <>
inline const char* cpp_min(const char* a, const char* b)
{
	return strcmp(a, b) < 0 ? a : b;
}

// cpp_swap
template < class T >
void cpp_swap(T& a, T& b)
{
	using std::move;

	T tmp{ move(a) };
	a = move(b);
	b = move(tmp);
}

// cpp_zobraz(zac, kon)

// T = double
// T = const double*
template < class INPUT_IT >
void cpp_zobraz(INPUT_IT zac, INPUT_IT kon)
{
	using std::cout;

	for (; zac != kon; ++zac)
	{
		cout << *zac << " ";
	}
	cout << "\n";
}

template < class INPUT_IT >
void cpp_zobraz(INPUT_IT zac, INPUT_IT kon, const char* title)
{
	using std::cout;
	cout << title;
	cpp_zobraz(zac, kon);
}

template < class T, size_t N >
void cpp_zobraz(T (&pole)[N], const char* title)
{
	cpp_zobraz(pole, pole + N, title);
}

template < class KONTEJNER >
void cpp_zobraz(const KONTEJNER& pole, const char* title)
{
	cpp_zobraz(pole.begin(), pole.end(), title);
}

#define CPP_ZOBRAZ(pole)	cpp_zobraz(pole, #pole "=")

// cpp_copy
template <class INPUT_IT, class OUTPUT_IT>
OUTPUT_IT cpp_copy(INPUT_IT zac, INPUT_IT kon, OUTPUT_IT cil)
{
	for (; zac != kon; ++zac, ++cil)
	{
		*cil = *zac;
	}
	return cil;
}

// cpp_transform
template <class INPUT_IT, class OUTPUT_IT, class UNARY_FN>
OUTPUT_IT cpp_transform(INPUT_IT zac, INPUT_IT kon, OUTPUT_IT cil, UNARY_FN fn)
{
	for (; zac != kon; ++zac, ++cil)
	{
		*cil = fn(*zac);
	}
	return cil;
}

// cpp_count
template <class INPUT_IT, class VALUE>
size_t cpp_count(INPUT_IT zac, INPUT_IT kon, VALUE value)
{
	size_t pocet = 0;
	for (; zac != kon; ++zac)
	{
		if (*zac == value)
		{
			++pocet;
		}
	}
	return pocet;
}

// cpp_count_if
template <class INPUT_IT, class UNARY_PRED>
size_t cpp_count_if(INPUT_IT zac, INPUT_IT kon, UNARY_PRED fn)
{
	size_t pocet = 0;
	for (; zac != kon; ++zac)
	{
		if (fn(*zac))
		{
			++pocet;
		}
	}
	return pocet;
}

// cpp_find
template <class INPUT_IT, class VALUE>
INPUT_IT cpp_find(INPUT_IT zac, INPUT_IT kon, VALUE value)
{
	for (; zac != kon; ++zac)
	{
		if (*zac == value)
		{
			break;
		}
	}
	return zac;
}

// cpp_find_if
template <class INPUT_IT, class UNARY_PRED>
INPUT_IT cpp_find_if(INPUT_IT zac, INPUT_IT kon, UNARY_PRED fn)
{
	for (; zac != kon; ++zac)
	{
		if (fn(*zac))
		{
			break;
		}
	}
	return zac;
}


// cpp_min_element
template <class FWD_IT>
FWD_IT cpp_min_element(FWD_IT zac, FWD_IT kon)
{
	FWD_IT minPos = zac;
	if (zac != kon)
	{
		for (++zac; zac != kon; ++zac)
		{
			if (*zac < *minPos)
			{
				minPos = zac;
			}
		}
	}
	return minPos;
}

// cpp_min_element
template <class FWD_IT, class BINARY_PRED>
FWD_IT cpp_min_element(FWD_IT zac, FWD_IT kon, BINARY_PRED fn)
{
	FWD_IT minPos = zac;
	if (zac != kon)
	{
		for (++zac; zac != kon; ++zac)
		{
			if (fn(*zac, *minPos))
			{
				minPos = zac;
			}
		}
	}
	return minPos;
}

// cpp_accumulate
template <class INPUT_IT, class VALUE>
VALUE cpp_accumulate(INPUT_IT zac, INPUT_IT kon, VALUE start)
{
	for (; zac != kon; ++zac)
	{
		// start = start + *zac;
		start += *zac;
	}
	return start;
}

template <class INPUT_IT, class VALUE, class BINARY_FN>
VALUE cpp_accumulate(INPUT_IT zac, INPUT_IT kon, VALUE start, BINARY_FN fn)
{
	for (; zac != kon; ++zac)
	{
		start = fn(start, *zac);
	}
	return start;
}

// cpp_reduce
template <class INPUT_IT>
auto cpp_reduce(INPUT_IT zac, INPUT_IT kon)
{
	// using VALUE = decltype(*zac + *zac);
	using VALUE = std::iterator_traits<INPUT_IT>::value_type;
	VALUE start{};
	for (; zac != kon; ++zac)
	{
		start += *zac;
	}
	return start;
}

template < class INPUT_IT, class UNARY_FN >
UNARY_FN cpp_for_each(INPUT_IT zac, INPUT_IT kon, UNARY_FN fn)
{
	for (; zac != kon; ++zac)
	{
		fn(*zac);
	}
	return fn;
}


template < class FWD_IT, class GENERATOR >
void cpp_generate(FWD_IT zac, FWD_IT kon, GENERATOR fn)
{
	for (; zac != kon; ++zac)
	{
		*zac = fn();
	}
}

class Rand
{
public:
	Rand(int a, int b)
		: m_distribution{a, b}
	{}
	int operator()()
	{
		return m_distribution(m_engine);
	}
private:
	std::default_random_engine m_engine;
	std::uniform_int_distribution<> m_distribution;
};

// jeSude
inline bool jeSude(int n)
{
	return n % 2 == 0;
}

template < class BIDIRECT_IT, class VALUE >
BIDIRECT_IT rfind(BIDIRECT_IT zac, BIDIRECT_IT kon, const VALUE& value)
{
	auto rbegin = std::make_reverse_iterator(kon);
	auto rend = std::make_reverse_iterator(zac);
	auto posledniPos = std::find(rbegin, rend, value);
	return posledniPos != rend ? std::prev(posledniPos.base()) : kon;
}

template <class KONTEJNER>
void alokacniStrategie()
{
	KONTEJNER k;
	k.reserve(90);

	std::cout << "sizeof = " << sizeof(k) << " byte\n";
	auto show = [&k] {
		std::cout << static_cast<void*>(k.data()) << " ";
		std::cout << std::setw(3) << k.size() << " ";
		std::cout << std::setw(3) << k.capacity() << "\n";
	};

	show();

	for (size_t i = 0; i < 100; i++)
	{
		k.push_back({});
		show();
	}

	k.shrink_to_fit();
	show();
}

class Int
{
public:
	inline static int counter;

	Int(int data)
		: m_data{data}
	{
	}
	operator int() const
	{
		return m_data;
	}
	Int& operator=(const Int& src)
	{
		++counter;
		m_data = src.m_data;
		return *this;
	}
private:
	int m_data;
};

template < class KONTEJNER, class HODNOTA>
void insertMulti(KONTEJNER& k, const HODNOTA& prvek)
{
	auto pos = std::upper_bound(begin(k), end(k), prvek);
	k.insert(pos, prvek);
}

template < class KONTEJNER, class HODNOTA>
bool insertUnique(KONTEJNER& k, const HODNOTA& prvek)
{
	auto pos = std::lower_bound(begin(k), end(k), prvek);
	if (pos == end(k) || *pos != prvek)
	{
		k.insert(pos, prvek);
		return true;
	}
	return false;
}

template < class KONTEJNER, 
	class HODNOTA, 
	class BINARY_PRED = std::less<typename KONTEJNER::value_type>>
auto binaryFind(KONTEJNER& k, const HODNOTA& prvek, BINARY_PRED fn = {})
{
	auto kon = end(k);
	auto pos = std::lower_bound(begin(k), kon, prvek, fn);
	if (pos != kon && fn(prvek, *pos))
	{
		pos = kon;
	}
	return pos;
}