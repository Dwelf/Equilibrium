#pragma once
class IWallet
{
public :
	virtual void Pay(double value);
	virtual void Charge(double value);
	virtual double CurrentWealth() const;
};