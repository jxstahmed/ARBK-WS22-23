#include <iostream>
#include <thread>
#include <mutex>

#include "semaphoren.h"

using namespace std;

// Unser Semaphore soll nur 1 Thread gleichzeitig erlauben.
semaphore s(1);

void thread1()
{
	s.blockieren(1);  // Wir über geben dem Semaphore den Thread mit seiner ID:

	char kleine;
	for (kleine = 'a'; kleine <= 'z'; kleine++)
	{
		cout << kleine << endl;
	}

	s.freigeben();  // Hier wird der Semaphore benachrichtig, dass der Thread fertig ist. Nun ist er wieder frei.
}

void thread2()
{
	s.blockieren(2);

	int zahlen;
	for (zahlen = 0; zahlen <= 32; zahlen++)
	{
		cout << zahlen << endl;
	}

	s.freigeben();
}


void thread3() {
	s.blockieren(3);
	
	char grosse;
	for (grosse = 'A'; grosse <= 'Z'; grosse++)
	{
		cout << grosse << endl;
	}

	s.freigeben();
}

int main()
{

	// Semaphore benachrichtigt über Freigabe und blockiert
	thread T1(thread1);
	thread T2(thread2);
	thread T3(thread3);

	cout << "Starte die Threads mit dem semaphoren." << endl;
	T1.join();
	T2.join();
	T3.join();
	cout << "Die Threads mit semaphoren sind fertig";

	system("PAUSE");
	return 0;
}