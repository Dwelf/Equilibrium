#include "stdafx.h"
#include "TestExchange.h"
#include <exception>
#include <synchapi.h>
#include "TestWallet.h"
#include <random>
#include <iostream>

TestExchange::TestExchange()
{
	this->_sleepTime = 1000;
	this->_demand = 1;
	this->_supply = 1;
}


TestExchange::TestExchange(double supply, double demand, int sleepTime)
{
	this->_supply = supply;
	this->_demand = demand;
	this->_sleepTime = sleepTime;
}

TestExchange::~TestExchange()
{
}

double TestExchange::BuyingAt() const
{
	return this->_demand / this->_supply - 0.02;
}

double TestExchange::SellingAt() const
{
	return this->_demand / this->_supply;
}

double TestExchange::GetRawValue() const
{
	return this->_demand / this->_supply;
}

void TestExchange::Buy(double volume, IWallet * userWallet)
{
	if(volume > this->_supply)
	{
		throw std::exception("Can't Buy more than the supplier has");
	}
	double sellingAt = this->SellingAt();
	this->_supply -= volume;	
	userWallet->Charge(volume * sellingAt);
}

void TestExchange::EmulateActivity()
{	
	auto currentValue = (this->_demand / this->_supply);
	auto difference = currentValue - 1.0;
	this->_demand -= (this->_demand / 100) * difference;
	auto newValue = (this->_demand / this->_supply);
	Sleep(this->_sleepTime);
	//printf("market shift from %f to %f \n", currentValue, newValue);	
}

void TestExchange::Sell(double volume, IWallet * userWallet)
{
	double buyingAt = this->BuyingAt();
	this->_supply += volume;
	userWallet->Pay(volume *buyingAt);
}