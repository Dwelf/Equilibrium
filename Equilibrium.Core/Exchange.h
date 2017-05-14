#pragma once
#include "Wallet.h"
class IExchange
{
public:
	virtual double BuyingAt() const =0;
	virtual double SellingAt()const =0;
	virtual double GetRawValue()const =0;
	virtual void Buy(double volume, IWallet * userWallet)= 0;
	virtual void Sell(double volume, IWallet * userWallet) = 0;
};
