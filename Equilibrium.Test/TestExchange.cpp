#include "stdafx.h"
#include "TestExchange.h"
#include <exception>
#include <synchapi.h>

TestExchange::TestExchange(double supply, double demand, int sleepTime)
{
	this->_supply = supply;
	this->_demand = demand;
	this->_sleepTime = sleepTime;
}

TestExchange::~TestExchange()
{
}

double TestExchange::GetBuyValue() const
{
	return this->_demand / this->_supply;
}

double TestExchange::GetSellValue() const
{
	return this->_demand / this->_supply - 0.02;
}

double TestExchange::GetRawValue() const
{
	return this->_demand / this->_supply;
}

void TestExchange::Buy(double volume)
{
	if(volume > this->_supply)
	{
		throw std::exception("Can't Buy more than the supplier has");
	}
	this->_supply -= volume;
}

void TestExchange::EmulateActivity()
{	
	auto currentValue = (this->_demand / this->_supply);
	auto difference = currentValue - 1.0;
	this->_demand -= (this->_demand / 100) * difference;
	auto newValue = (this->_demand / this->_supply);
	Sleep(this->_sleepTime);
	printf("market shift from %f to %f \n", currentValue, newValue);
	this->EmulateActivity();
}

void TestExchange::Sell(double volume)
{
	this->_supply += volume;
}