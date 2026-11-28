/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bank.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykeciri <ykeciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 16:04:32 by ykeciri           #+#    #+#             */
/*   Updated: 2026/11/28 13:57:41 by ykeciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bank.hpp"

Bank::Account* Bank::createAccount( void ) {
	for (size_t i = 0; i < _accounts.size(); ++i)
	{
		if (_accounts[i] == NULL)
		{
			Account* new_account = new Bank::Account(static_cast<int>(i));
			_accounts[i] = new_account;
			return (new_account);
		}
	}

	Account* new_account = new Bank::Account(static_cast<int>(_accounts.size()));
	_accounts.push_back(new_account);
	return (new_account);
}

void Bank::deleteAccount(Bank::Account* account)
{
    if (account == NULL)
        return;

    int id = account->_account_id;

    if (id < 0 || id >= static_cast<int>(_accounts.size()))
        return;

    if (_accounts[id] != account)
        return;

    delete _accounts[id];
    _accounts[id] = NULL;
}

bool Bank::addLiquidity(Account* account, float liquidity)
{
	if (this->checkLiquidity(liquidity))
	{
		account->_liquidity += liquidity;
		this->_fund -= liquidity;
		return (1);
	}
	return (0);
}

void	Bank::addFund(float amount) {
	this->_fund += amount;
}

Bank::Account* Bank::operator[](int account_id)
{
	return(_accounts.at(account_id));
}

Bank& Bank::operator=(const Bank& src)
{
	if (this != &src)
	{
		for (size_t i = 0; i < _accounts.size(); ++i)
			delete _accounts[i];
		_accounts.clear();

		_fund = src._fund;
		_accounts.reserve(src._accounts.size());
		for (size_t i = 0; i < src._accounts.size(); ++i)
		{
			if (src._accounts[i] == NULL)
				_accounts.push_back(NULL);
			else
			{
				Account* copy = new Account(static_cast<int>(i));
				copy->_liquidity = src._accounts[i]->_liquidity;
				_accounts.push_back(copy);
			}
		}
	}
	return (*this);
}

Bank::Bank(Bank &src) { *this = src; }

Bank::Bank(void) : _fund(0)
{
}

Bank::~Bank(void)
{
	for (size_t i = 0; i < _accounts.size(); ++i)
		delete _accounts[i];
	_accounts.clear();
}

bool	Bank::makeDeposit(Account* acc, float amount)
{
	float toBank;
	toBank = amount * 0.05;
	amount -= toBank;
	acc->_liquidity = amount;
	this->_fund = toBank;
	return (1);
}

bool	Bank::askForLoan(Account*  acc, float amountAsked)
{
	if (amountAsked > _fund)
	{
		std::cout << FRED("the bank don't have enough fund") << std::endl;
		return (0);
	}
	acc->_myLoans.push_back(new Loan(acc, this, amountAsked));
	std::cout << FGRN("A new Loan has been granted to Account [") << FGRN(acc->_account_id) << FGRN("]") << std::endl;
	return (1);
}

bool	Bank::checkLiquidity(float liquidity)
{
	return (liquidity < _fund);
}

float Bank::getFund(void) const
{
	return (_fund);
}

size_t Bank::getAccountCount(void) const
{
	return (_accounts.size());
}
