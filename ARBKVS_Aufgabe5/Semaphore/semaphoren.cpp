#include "semaphoren.h"
using namespace std;


/*
	Der Mutex wird bei einem Funktionsaufruf blockiert.
	Sobald der Aufruf beendet ist, wird eine Notify abgesendet.
	Sobald der Mutex die Benachrichtigung bekommt, wird dieser freigegeben.
	Nun kann der nächste Thread arbeiten.
*/

void semaphore::freigeben()
{
	/*
	1. Bekommt Unique Lock und Mutex wird blockiert für Ausgabe.
	2. Ein Thread wird freigemacht.
	3. Benutzer wird benachrichtigt, dass Thread nun weitermachen.
	4. Mutex wird freigegeben.
	*/

	unique_lock<mutex> lock(dermutex);

	anzahl++;
	cout << "---------- Der naechste Thread wird benachrichtigt. ----------" << endl << endl;
	
	con_var.notify_one();
}


void semaphore::blockieren(int id)
{

	/*
	1.		Funktion bekommt ein Unique Lock und Mutex wird geblockt.
	2.		Sollte kein Thread frei sein, wird der Benutzer informiert
	2.1		Thread mit ID wird angezeigt welcher wartet.
	2.2		Condition_Variable wartet solange auf den Mutex wie er geblockt ist.
	2.3		Sobald Mutex Notify von fertigen Thread bekommt, wird dieser geöffnet.
	2.4		Benutzer wird benachrichtigt, dass Thread nun läuft.
	3.		Freie Threads werden beim blockieren runtergezählt.
	*/

	unique_lock<mutex> lock(dermutex);

	if(anzahl == 0)
	{
		cout << endl;
		cout << "---------- Folgender Thread wartet auf den Start: " << id << " ----------" << endl;
		con_var.wait(lock);
		cout << "---------- Folgender Thread startet nun: " << id << " ----------" << endl;
	}

	anzahl--;
}
