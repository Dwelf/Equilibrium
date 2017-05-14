#include "stdafx.h"
#include "../Equilibrium.Core/Exchange.h"
#include "TestBench.h"
#include <mutex>

TestBench::TestBench(const int NumberOfExchanges, const double supplyBase, const double demandBase, const double timeBase) : _exchangeCount(NumberOfExchanges)
{
	this->_exchanges = std::vector<IExchange*> (NumberOfExchanges);

	for (int i = 0; i < NumberOfExchanges; i++)
	{
		auto supply = rand() % 60000;
		auto demand = rand() % 60000;
		auto time = rand() % 200;
		supply += supplyBase;
		demand += demandBase;
		time += timeBase;
		this->_exchanges[i] = new TestExchange(supply, demand, time);
	}
}
void TestBench::Emulate()
{
	this->_threads = new std::thread[this->_exchangeCount]();

	for (int i = 0; i < this->_exchangeCount; i++)
	{
		this->_threads[i] = std::thread(&TestExchange::EmulateActivity, static_cast<TestExchange*>(this->_exchanges[i]));
	}
}

void TestBench::StopEmulation() const
{
	for (int i = 0; i < this->_exchangeCount; i++)
	{
		this->_threads[i].join();
	}
}
void TestBench::emulateExchange(TestExchange * exchange)
{
	this->emulation_Mutex.lock();
	if (_isEmulating == false)
	{
		return;
	}
	this->emulation_Mutex.unlock();
	exchange->EmulateActivity();
}
std::vector<IExchange*> * TestBench::GetExchanges()
{
	return &(this->_exchanges);
}