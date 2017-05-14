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
		auto exchangeSellingAtPrice = this->_sellingPrice[0]->SellingAt();
		auto exchangeBuyingAtPrice = this->_buyingPrice[0]->BuyingAt();
		// is it profitable
		if (exchangeBuyingAtPrice > exchangeSellingAtPrice)
		{
			auto spendingMoney = wallet->CurrentWealth(); // spend 1 /3 
			auto itemCount = floor(spendingMoney / exchangeBuyingAtPrice); // how much to buy
			this->_sellingPrice[0]->Buy(itemCount, wallet); // has lowest selling price so buy
			this->_buyingPrice[0]->Sell(itemCount, wallet); // has highest buying price so sell
		
		}
	}
}

int Equilibrium::partitionBuying(const int left, const int right)
{
	const int mid = left + (right - left) / 2;
	const double pivot = this->_buyingPrice[mid]->BuyingAt();
	// move the mid point value to the front.
	std::swap(this->_buyingPrice[mid], this->_buyingPrice[left]);
	int i = left + 1;
	int j = right;
	while (i <= j) {

		auto value = this->_buyingPrice[i]->BuyingAt();

		while (i <= j && value >= pivot) {
			i++;
		}

		while (i <= j && value < pivot) {
			j--;
		}

		if (i < j) {
			std::swap(this->_buyingPrice[i], this->_buyingPrice[j]);
		}
	}
	std::swap(this->_buyingPrice[i - 1], this->_buyingPrice[left]);
	return i - 1;
}

void Equilibrium::updateCollections()
{
	this->quicksortBuying(0, this->_size - 1);
	this->quicksortSelling(0, this->_size - 1);
}

void Equilibrium::quicksortBuying(const int left, const int right) 
{
	if (left >= right) {
		return;
	}

	int part = this->partitionBuying(left, right);
	this->quicksortBuying(left, part - 1);
	this->quicksortBuying(part + 1, right);
}

int Equilibrium::partitionSelling(const int left, const int right) 
{
	const int mid = left + (right - left) / 2;
	const double pivot = this->_sellingPrice[mid]->SellingAt();
	// move the mid point value to the front.
	std::swap(this->_sellingPrice[mid], this->_sellingPrice[left]);
	int i = left + 1;
	int j = right;
	while (i <= j) {
		auto value = this->_sellingPrice[i]->SellingAt();

		while (i <= j && value <= pivot) {
			i++;
		}

		while (i <= j && value > pivot) {
			j--;
		}

		if (i < j) {
			std::swap(this->_sellingPrice[i], this->_sellingPrice[j]);
		}
	}
	std::swap(this->_sellingPrice[i - 1], this->_sellingPrice[left]);
	return i - 1;
}
void Equilibrium::quicksortSelling(const int left, const int right)
{
	if (left >= right) {
		return;
	}

	int part = this->partitionSelling( left, right);
	this->quicksortSelling(left, part - 1);
	this->quicksortSelling( part + 1, right);
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
	this->_buyingPrice = std::vector<IExchange*>(size);
	this->_sellingPrice = std::vector<IExchange*>(size);
	for (int i = 0; i < size; i++)	
	{
		this->_buyingPrice[i] = exchanges->at(i);
		this->_sellingPrice[i] = exchanges->at(i);
	}
	this->quicksortBuying(0, size - 1);
	this->quicksortSelling(0, size - 1);
}

Equilibrium::~Equilibrium()
{
	this->_buyingPrice.clear();
	this->_sellingPrice.clear();
}