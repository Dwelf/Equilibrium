#include "stdafx.h"
#include "TestWallet.h"

TestWallet :: TestWallet(double StartingValue)
{
	this->_wealth = StartingValue;
}

void TestWallet :: Pay(double value)
{
	this->_wealth += value;
}

void TestWallet :: Charge(double value)
{
	this->_wealth -= value;
}

double TestWallet :: CurrentWealth() const
{
	return this->_wealth;
}
