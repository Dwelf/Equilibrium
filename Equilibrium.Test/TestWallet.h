#pragma once
class TestWallet
{
public :
	TestWallet::TestWallet(double StartingValue);
	void Pay(double value);
	void Charge(double value);
	double CurrentWealth() const;
private:
	double Wealth = 0;
};