#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

//Producer Consumer Library - PPL 
//reseni pomoci enqueu() a dequeue() - tz. 
class UnboudedBuffer // fronta, kterou chci sdilet (vice neni treba sdilet - vyhoda)
{
public:
	void enqueue(int data)
	{
		{
			lock_guard lock{ m_mutex };
			m_queue.push_back(data);
		}
		m_cv.notify_one();
	}
	int dequeue()
	{
		unique_lock lock{ m_mutex };

		m_cv.wait(lock, [this]() { return !m_queue.empty(); });

		int data = m_queue.front();
		m_queue.pop_front();
		return data;
	}
private:
	condition_variable m_cv;
	mutex m_mutex;
	deque<int> m_queue;
};

const int stop = -1;

int main()
{
	UnboudedBuffer queue;
	thread consumer{ [&queue] {
		for (; ; )
		{			
			int element = queue.dequeue();
			if (element == stop)
			{
				cout << "Stop signal received!\n";
				break;
			}
			cout << format("consumer: {}\n", element);
		}
	} };

	for (size_t i = 0; i < 20; i++)
	{
		int data = rand() % 10 + 10;
		cout << format("producer: {}\n", data);
	}
	queue.enqueue(stop);
	consumer.join();
	return 0;
}