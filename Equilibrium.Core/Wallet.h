#pragma once
class IWallet
{
public :
	virtual void Pay(double value) = 0;
	virtual void Charge(double value) = 0;
	virtual double CurrentWealth() const = 0;
};
