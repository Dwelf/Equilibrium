#include "stdafx.h"
#include "TestWallet.h"

TestWallet :: TestWallet(double StartingValue)
{
	this->Wealth = StartingValue;
}

void TestWallet :: Pay(double value)
{
	this->Wealth += value;
}

void TestWallet :: Charge(double value)
{
	this->Wealth -= value;
}

double TestWallet :: CurrentWealth() const
{
	return this->Wealth;
}
