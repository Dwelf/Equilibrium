// Equilibrium.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "../Equilibrium.Test/TestExchange.h"
#include <thread>
#include "../Equilibrium.Test/TestWallet.h"
#include "../Equilibrium.Test/TestBench.h"
#include "../Equilibrium.Core/Equilibrium.h"
int main()
{
	printf("Hello C++ I'm back\n");
	auto exchanges = 4;
	IWallet  * wallet = new TestWallet(100000);
	printf("Setup Wallet with %f\n", wallet->CurrentWealth());
	auto testBench = new TestBench(exchanges, 1000000, 1200000, 100);
	printf("Setup %d exchanges\n", exchanges);
	auto testAlog = new Equilibrium(testBench->GetExchanges(), exchanges);
	testBench->Emulate();
	printf("Started emulation\n");
	testAlog->StartBalancing(wallet);
	printf("Start Balancing\n");
	Sleep(20000);
	printf("Current Wealth is %f\n", wallet->CurrentWealth());
	Sleep(2000);
	testBench->StopEmulation();
	testAlog->StopBalancing();
	Sleep(200);
	getchar();
}
