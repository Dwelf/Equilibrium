#pragma once
#include "stdafx.h"
#include "TestWallet.h"
#include "../Equilibrium.Core/Exchange.h"

class TestExchange :public IExchange
{
public:
	TestExchange();
	TestExchange(double supply, double demand, int sleepTime);
	~TestExchange();
	double BuyingAt() const override;
	double SellingAt() const override;
	double GetRawValue() const override;
	void  Buy(double volume, IWallet * userWallet) override;
	void EmulateActivity();
	void Sell(double volume, IWallet * userWallet) override;
private:
	double _supply;
	double _demand;
	int _sleepTime;
};
