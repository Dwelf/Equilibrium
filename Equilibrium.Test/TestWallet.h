#pragma once
#include "../Equilibrium.Core/Wallet.h"

class TestWallet :public IWallet
{
public :
	TestWallet::TestWallet(double StartingValue);
	void Pay(double value);
	void Charge(double value);
	double CurrentWealth() const;
private:
	double _wealth = 0;
};
