/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Loan.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykeciri <ykeciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 23:16:26 by ykeciri           #+#    #+#             */
/*   Updated: 2026/11/28 13:57:41 by ykeciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bank.hpp"

Bank::Loan::Loan(Account* account, Bank* bank,float amount) : _amount(amount), _account(account), _bank(bank) { }

Bank::Loan::~Loan( void ) { }

Bank*		Bank::Loan::getBank( void ) {
	return (this->_bank);
}

Bank::Account*	Bank::Loan::getAccount( void )
{
	return (this->_account);
}

void		Bank::Loan::refundAmount(int amount)
{
	this->_amount -= amount;
}

float Bank::Loan::getAmount(void) const
{
	return (_amount);
}

