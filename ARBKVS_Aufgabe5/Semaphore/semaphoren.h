#pragma once
#include <mutex>
#include <iostream>
#include <condition_variable>


class semaphore
{

private:

	std::mutex dermutex;
	std::condition_variable con_var;
	int anzahl;

public:

	semaphore(int anzahl = 1) : anzahl(anzahl) {}
	void freigeben();
	void blockieren(int id);

};