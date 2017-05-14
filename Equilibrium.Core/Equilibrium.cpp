#include "stdafx.h"
#include "Equilibrium.h"
#include <mutex>
#include <math.h>
//std::mutex _swapMutex;


Equilibrium::Equilibrium(std::vector<IExchange*> *exchanges, const int size) : _size(size)
{
	this->setupCollections(exchanges, size);
	this->_stop = false;
}

void Equilibrium::StartBalancing(IWallet * wallet)
{
	this->balancingThread = std::thread(&Equilibrium::balance, this, wallet);
}

void Equilibrium::StopBalancing()
{
	this->_stop = true;
	this->balancingThread.join();
}

void Equilibrium::balance(IWallet * wallet)
{
	while (this->isBalancing())
	{
		this->updateCollections();
		auto exchangeSellingAtPrice = this->BestSell->SellingAt();
		auto exchangeBuyingAtPrice = this->BestBuy->BuyingAt();
		// is it profitable
		if (exchangeBuyingAtPrice > exchangeSellingAtPrice)
		{
			auto spendingMoney = wallet->CurrentWealth(); // spend 1 /3 
			auto itemCount = floor(spendingMoney / exchangeBuyingAtPrice); // how much to buy
			this->BestSell->Buy(itemCount, wallet); // has lowest selling price so buy
			this->BestBuy->Sell(itemCount, wallet); // has highest buying price so sell		
		}
	}
}


void Equilibrium::updateCollections()
{
	int buyIndex = -1;
	int sellIndex = -1;
	double buyPrice = 0;
	double sellPrice = 999999;

	for(int i =0; i <this->_size; i++)
	{
		double indexBuyPrice = this->_exchanges->at(i)->BuyingAt();
		double indexSellingIndex = this->_exchanges->at(i)->SellingAt();
		if(indexBuyPrice > buyPrice)
		{
			buyIndex = i;
			buyPrice = indexBuyPrice;
		}

		if (indexSellingIndex < sellPrice)
		{
			sellIndex = i;
			sellPrice = indexSellingIndex;
		}
	}

	this->BestBuy = this->_exchanges->at(buyIndex);
	this->BestSell = this->_exchanges->at(sellIndex);
}


bool Equilibrium::isBalancing()
{
	this->balancing_Mutex.lock();
	auto returnValue = this->_stop;
	this->balancing_Mutex.unlock();
	return !returnValue;
}

void Equilibrium::setupCollections(std::vector<IExchange *> *  exchanges , const int size)
{
	this->_exchanges = exchanges;
}

Equilibrium::~Equilibrium()
{
	this->BestSell = nullptr;
	this->BestBuy = nullptr;
}