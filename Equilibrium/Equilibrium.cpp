// Equilibrium.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "../Equilibrium.Test/TestExchange.h"
#include <thread>
#include "../Equilibrium.Test/TestWallet.h"

int main()
{
	printf("Hello C++ I'm back\n");
	auto wallet = new TestWallet(1000000);
	auto MegaMarket = new TestExchange(1000000, 1200000,100);
	std::thread first(&TestExchange::EmulateActivity,MegaMarket);
	printf("Created Mega Market Test Exchange\n");
	printf("Current Value is %f\n", MegaMarket->GetBuyValue());
	printf("Buying 40000 from MegaMarket\n");
	MegaMarket->Buy(40000,wallet);
	printf("Current Wealth is %f\n", wallet->CurrentWealth());
	printf("Current Value is %f\n", MegaMarket->GetBuyValue());
	printf("Selling 80000 to MegaMarket\n");
	MegaMarket->Sell(80000,wallet);
	printf("Current Wealth is %f\n", wallet->CurrentWealth());
	printf("Current Value is %f\n", MegaMarket->GetBuyValue());
	printf("Current Sale Value is %f\n", MegaMarket->GetSellValue());
	Sleep(20000);
	first.join();
	getchar();
}
