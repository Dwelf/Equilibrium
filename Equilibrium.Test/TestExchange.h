#pragma once
#include "stdafx.h"
#include <bemapiset.h>
#include "TestWallet.h"
class TestExchange
{
public:
	TestExchange(int sleepTime);
	TestExchange(double supply, double demand, int sleepTime);
	~TestExchange();
	double GetBuyValue() const;
	double GetSellValue() const;	
	double GetRawValue() const;
	void Buy(double volume, TestWallet * userWallet);
	void EmulateActivity();
	void Sell(double volume, TestWallet * userWallet);
private:
	double _supply;
	double _demand;
	int _sleepTime;
};