#include <iostream>
#include <thread>
using namespace std;


void thread1()
{
	char klein;

	for (klein = 'a'; klein <= 'z'; klein++)
	{
		cout << klein << " " << endl;
	}
}

void thread2()
{
	int zahlen;

	for (zahlen = 0; zahlen <= 32; zahlen++)
	{
		cout << zahlen << " " << endl;
	}
}

void thread3()
{
	char gross;

	for (gross = 'A'; gross <= 'Z'; gross++)
	{
		cout << gross << " " << endl;
	}
}


int main()
{
	thread T1(thread1);
	thread T2(thread2);
	thread T3(thread3);

	cout << "Start die unsynchronen Threads:" << endl;
	T1.join();
	T2.join();
	T3.join();
	cout << endl << "Die unsynchronen Threads sind fertig." << endl;

	system("Pause");
	return 0;
}