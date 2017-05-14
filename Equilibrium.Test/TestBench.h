#pragma once
#include "../Equilibrium.Core/Exchange.h"
#include "TestExchange.h"
#include <thread>
#include <mutex>
#include <vector>

class TestBench
{
public:
	TestBench(const int NumberOfExchanges, const double supplyBase, const double demandBase, const double timeBase);
	void Emulate();
	void StopEmulation() const;
	std::vector<IExchange*> * GetExchanges();
private:
	bool _isEmulating;
	std::vector<IExchange*> _exchanges;
	std::thread * _threads;
	const int _exchangeCount;
	std::mutex emulation_Mutex;
	void emulateExchange(TestExchange * exchange);
};
