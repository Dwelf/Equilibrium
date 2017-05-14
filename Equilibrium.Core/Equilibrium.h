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
	std::vector<IExchange*> * _exchanges;
	IExchange * BestBuy;
	IExchange * BestSell;
private:
	bool isBalancing();
	const int _size;
	bool _stop;
	std::mutex balancing_Mutex;
	std::thread balancingThread;
};
