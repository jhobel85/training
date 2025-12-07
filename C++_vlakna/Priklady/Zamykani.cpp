#include <iostream>
#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

class Citac
{
public:
	Citac() : m_citac{}
	{
	}
	int get() const
	{
		return m_citac;
	}
	void set(int citac)
	{
		m_citac = citac;
	}
	void inc() {
		++m_citac;
	}
private:
	int m_citac;
};

class AtomickyCitac
{
public:
	AtomickyCitac()
		: m_citac{}
	{
	}
	int get() const
	{
		return m_citac;
	}
	void set(int citac)
	{
		m_citac = citac;
	}
	void inc()
	{
		// m_citac = m_citac + 1;
		++m_citac;
	}
private:
	atomic<int> m_citac;
};

class MonitorCitac
{
public:
	int get() const
	{
		//c++14 auto dedukce - neni treba definovat typ lock_guard
		lock_guard lock{ m_mutex };
		return m_citac.get();
	}
	void set(int citac)
	{
		lock_guard lock{ m_mutex };
		m_citac.set(citac);
	}
	void inc() {
		lock_guard lock{ m_mutex };
		m_citac.inc();
	}
#if  0 //pred C++ 14
	void swap(MonitorCitac& jiny)
	{
		/* 
		int tmp = jiny.get(); // get je thread-safe -> je zde lock
		jiny.set(get()); // take zamek
		set(tmp); // take zamek
		// -> problem s tim, ze pracujeme se dvema promennyma moje instance a jina instance
		*/
		
		lock(m_mutex, jiny.m_mutex); // zamyka se ve stejnem poradi
		//lepsi pristup, ale vede k deadlocku
		lock_guard lockA{ m_mutex , adopt_lock}; //jeden zamkl
		lock_guard lockB{ jiny.m_mutex, adopt_lock }; // druhy zamkl ve stejnou dobu a nikdy mu uz nevrati "odemceno"		

		int tmp = jiny.m_citac.get();
		jiny.m_citac.set(m_citac.get());
		m_citac.set(tmp);
	}
#else // praktickejsi varianta prevence deadlocku
	void swap(MonitorCitac& jiny)
	{
		scoped_lock lock(m_mutex, jiny.m_mutex);

		int tmp = jiny.m_citac.get();
		jiny.m_citac.set(m_citac.get());
		m_citac.set(tmp);
	}
#endif // 0

private:
	Citac m_citac;
	mutable mutex m_mutex; //zasada vzdy pripojit mutable stav -> mutex nenese stav.	
};

const int n = 1'000'000;

int seriovyCitac() {
	Citac citac;
	for (int i = 0; i < n; i++)
	{
		citac.inc();
	}
	cout << "citac " << citac.get() << "\n";
	return 0;
}

// ilustrace problemu a jak osetrit.
int raceCondition()
{
	AtomickyCitac citac;
	vector<thread> vlakna{ thread::hardware_concurrency() - 1 }; // 1 thread pro hlavni vlakno

	auto fn = [&citac] {
		for (unsigned i = 0; i < n / thread::hardware_concurrency(); i++)
		{
			citac.inc();
		}
	};

	for (auto& vlakno : vlakna)
	{
		vlakno = thread{ fn };
	}

	fn();

	for (auto& vlakno : vlakna)
	{
		vlakno.join();
	}

	cout << "citac = " << citac.get() << "\n";

	return 0;
}

	int deadlock()
	{
		MonitorCitac a, b;
		a.set(100);
		b.set(200);

		auto fn = [](MonitorCitac& x, MonitorCitac& y) {
			for (size_t i = 0; i < 30'000; i++)
			{
				x.swap(y);
			}
		};

		thread vlakno{ fn, ref(a), ref(b) };

		fn(b, a);
		vlakno.join();
		cout << "a = " << a.get() << "\n";
		cout << "b = " << b.get() << "\n";
		return 0;
	}