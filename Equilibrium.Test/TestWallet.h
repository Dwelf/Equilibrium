#pragma once
class TestWallet
{
public :
	TestWallet::TestWallet(double StartingValue);
	void Pay(double value);
	void Charge(double value);
private:
	int Wealth = 0;
};