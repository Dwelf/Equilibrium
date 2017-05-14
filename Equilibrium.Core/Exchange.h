#pragma once
#include "Wallet.h"
class IExchange
{
public:
	virtual double GetBuyValue() const;
	virtual double GetSellValue() const;
	virtual double GetRawValue() const;
	virtual void Buy(double volume, IWallet * userWallet);
	virtual void Sell(double volume, IWallet * userWallet);
};
