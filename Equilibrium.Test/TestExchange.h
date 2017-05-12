#pragma once
#include "stdafx.h"
#include <bemapiset.h>

class TestExchange
{
public:
	TestExchange(double supply, double demand, int sleepTime);
	~TestExchange();
	double GetBuyValue() const;
	double GetSellValue() const;	
	double GetRawValue() const;
	void Buy(double volume);
	void EmulateActivity();
	void Sell(double volume);
private:
	double _supply;
	double _demand;
	int _sleepTime;
};