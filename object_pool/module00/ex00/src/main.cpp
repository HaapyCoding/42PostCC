/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykeciri <ykeciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 12:27:16 by ykeciri           #+#    #+#             */
/*   Updated: 2026/11/28 13:59:18 by ykeciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bank.hpp"

int main()
{
	Bank bank;

	bank.addFund(200);

	Bank::Account* accountA = bank.createAccount();
	Bank::Account* accountB = bank.createAccount();
	Bank::Account* accountC = bank.createAccount();

	bank.addLiquidity(accountA, 50);
	bank.addLiquidity(accountB, 50);
	bank.addLiquidity(accountC, 50);

	bank.askForLoan(accountA, 30);
	bank.askForLoan(accountB, 20);

	std::cout << "\nBefore removal" << std::endl;
	std::cout << "Bank fund: " << bank.getFund() << std::endl;
	for (size_t i = 0; i < bank.getAccountCount(); ++i)
	{
		Bank::Account* account = bank[i];
		if (account == NULL)
			std::cout << "Account " << i << ": removed" << std::endl;
		else
		{
			std::cout << "Account " << i << ": liquidity="
				<< account->getMyFunds() << ", loans="
				<< account->getLoanCount();
			for (size_t j = 0; j < account->getLoanCount(); ++j)
				std::cout << " [amount=" << account->getLoan(j)->getAmount() << "]";
			std::cout << std::endl;
		}
	}

	std::cout << "\nRemoving account B" << std::endl;
	bank.deleteAccount(accountB);

	Bank::Account* accountD = bank.createAccount();
	bank.addLiquidity(accountD, 25);

	std::cout << "\nAfter removal and recreation" << std::endl;
	std::cout << "Bank fund: " << bank.getFund() << std::endl;
	for (size_t i = 0; i < bank.getAccountCount(); ++i)
	{
		Bank::Account* account = bank[i];
		if (account == NULL)
			std::cout << "Account " << i << ": removed" << std::endl;
		else
		{
			std::cout << "Account " << i << ": liquidity="
				<< account->getMyFunds() << ", loans="
				<< account->getLoanCount();
			for (size_t j = 0; j < account->getLoanCount(); ++j)
				std::cout << " [amount=" << account->getLoan(j)->getAmount() << "]";
			std::cout << std::endl;
		}
	}

	return (0);
}