#include <iostream>
#include <thread>
#include <mutex>
using namespace std;


mutex dermutex;

void thread1()
{
	dermutex.lock();

	char klein;
	for (klein = 'a'; klein <= 'z'; klein++)
	{
		cout << klein << endl;
	}

	dermutex.unlock();
}

void thread2()
{
	dermutex.lock();

	int zahlen;
	for (zahlen = 0; zahlen <= 32; zahlen++)
	{
		cout << zahlen << endl;
	}

	dermutex.unlock();
}


void thread3()
{
	dermutex.lock();

	char gross;
	for (gross = 'A'; gross <= 'Z'; gross++)
	{
		cout << gross << endl;
	}

	dermutex.unlock();
}

int main()
{
	thread T1(thread1);
	thread T2(thread2);
	thread T3(thread3);

	cout << "Starte die synchronen Threads:" << endl;
	T1.join();
	T2.join();
	T3.join();
	cout << endl;
	cout << "Die synchronen Threads sind fertig.";

	system("PAUSE");
	return 0;
}