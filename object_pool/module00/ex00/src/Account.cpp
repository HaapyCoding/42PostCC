/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykeciri <ykeciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 17:21:53 by ykeciri           #+#    #+#             */
/*   Updated: 2026/11/28 13:57:41 by ykeciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bank.hpp"

Bank::Account::Account(int id) : _liquidity(0), _account_id(id)
{
	std::cout << FBLU("Account ") << FBLU(id) << FBLU(" has been created") << std::endl;
}

Bank::Account& Bank::Account::operator=(const Bank::Account& src)
{
    if (this != &src)
    {
        _liquidity = src._liquidity;
        _account_id = src._account_id;
        _myLoans = src._myLoans;
    }
    return (*this);
}

float	Bank::Account::getMyFunds(void)
{
	return (this->_liquidity);
}

void	Bank::Account::refundLoan(Loan* loan, float amount)
{
	if (_liquidity < amount)
	{
		std::cout << FBLU("You don't have enough liquidity to refund that much amount on your loan");
		return ;
	}
	_liquidity -= amount;
	loan->refundAmount(amount);
}

size_t Bank::Account::getLoanCount(void) const
{
	return (_myLoans.size());
}

Bank::Loan* Bank::Account::getLoan(size_t index)
{
	if (index >= _myLoans.size())
		return (NULL);
	return (_myLoans[index]);
}

Bank::Account::~Account()
{
	for (size_t i = 0; i < _myLoans.size(); ++i)
		delete _myLoans[i];
	_myLoans.clear();
}