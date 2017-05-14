#pragma once
#include <list>
#include "Exchange.h"
#include <stack>
#include <vector>
#include <mutex>
class Equilibrium
{
public:
	Equilibrium(std::vector<IExchange*>* exchanges, int _size);
	~Equilibrium();
	void StartBalancing(IWallet * wallet);
	void StopBalancing();

protected:
	void updateCollections();
	void setupCollections(std::vector<IExchange *> *, int size);
	void balance(IWallet * wallet);
	int partitionBuying(const int left, const int right);
	void quicksortBuying(const int left, const int right);
	int partitionSelling(const int left, const int right);
	void quicksortSelling(const int left, const int right);
	std::vector<IExchange*>  _buyingPrice;
	std::vector<IExchange*>  _sellingPrice;
private:
	bool isBalancing();
	const int _size;
	bool _stop;
	std::mutex balancing_Mutex;
	std::thread balancingThread;
};
