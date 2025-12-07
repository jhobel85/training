#include "SablonyFunkci.h"

#include <deque>
#include <queue>

using namespace std;

int obousmernaFronta()
{
	cout << "Producer loop\n";
	deque<int> a;
	generate_n(back_inserter(a), 20, Rand{ 10, 20 });
	CPP_ZOBRAZ(a);
	cout << "\n";

	cout << "Consumer loop\n";
	CPP_ZOBRAZ(a);
	while (!a.empty())
	{
		a.pop_front();
		CPP_ZOBRAZ(a);
	}
	return 0;
}

int fronta()
{
	queue<int> a;
	Rand fn{ 10, 20 };
	cout << "Producer loop\n";

	for (size_t i = 0; i < 20; i++)
	{
		a.push(fn());
	}

	cout << "Consumer loop\n";
	CPP_ZOBRAZ(a._Get_container());
	while (!a.empty())
	{
		a.pop();
		CPP_ZOBRAZ(a._Get_container());
	}

	return 0;
}

int prioritniFronta()
{
	auto zobraz = [](auto a) {
		while (!a.empty())
		{
			cout << a.top() << " ";
			a.pop();
		}	
		cout << "\n";
	};

	priority_queue<int> a;
	Rand fn{ 10, 20 };
	cout << "Producer loop\n";

	for (size_t i = 0; i < 20; i++)
	{
		a.push(fn());
	}

	cout << "Consumer loop\n";
	zobraz(a);
	while (!a.empty())
	{
		a.pop();
		zobraz(a);
	}

	return 0;
}