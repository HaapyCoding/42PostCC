/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bank.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykeciri <ykeciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 16:04:32 by ykeciri           #+#    #+#             */
/*   Updated: 2026/11/24 23:15:52 by ykeciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bank.hpp"

Bank::Account* Bank::CreateAccount() {
	for (size_t i = 0; i < _accounts.size(); ++i)
	{
		if (_accounts[i] == nullptr)
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

void Bank::DeleteAccount(Bank::Account* account)
{
    if (account == nullptr)
        return;

    int id = account->_account_id;

    if (id < 0 || id >= static_cast<int>(_accounts.size()))
        return;

    if (_accounts[id] != account)
        return;

    delete _accounts[id];
    _accounts[id] = nullptr;
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

void	Bank::AddFund(float amount) {
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
			if (src._accounts[i] == nullptr)
				_accounts.push_back(nullptr);
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

