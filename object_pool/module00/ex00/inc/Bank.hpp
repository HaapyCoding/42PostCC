/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bank.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykeciri <ykeciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:23:19 by codespace         #+#    #+#             */
/*   Updated: 2026/11/28 14:01:02 by ykeciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <stddef.h>
#include "Colors.hpp"

class Bank {
public:
	class	Account;
	class	Loan;
private:

	float					_fund;
	std::vector<Account*>	_accounts;
	std::vector<Loan*>		_loans;

	Bank& operator=(const Bank& src);

	Bank(Bank &src);
public:
	class Loan{
			public:
				~Loan( void );
				Bank*	getBank( void ) ;
				Account*	getAccount( void );
				void	refundAmount(int amount);
				float	getAmount( void ) const;
			private:
				Loan( void );
				Loan(Account* account, Bank* bank,float amount);

				friend class	Bank;

				float			_amount;
				Account*		_account;
				Bank*			_bank;
		};

	class Account{
		private:
			friend class		Bank;

			float				_liquidity;
			std::vector<Loan*>	_myLoans;
			int					_account_id;

			void				refundLoan(Loan* loan, float amount);
		public:
			Account(int id);
			Account& operator=(const Account& src);
			~Account();

			float				getMyFunds( void );
			size_t				getLoanCount( void ) const;
			Loan*				getLoan(size_t index);
	};

	Bank();
	~Bank();
	
	Account*	createAccount( void );
	Account* operator[](int account_id);
	bool		makeDeposit(Account* acc, float amount);
	bool		askForLoan(Account*  acc, float amountAsked);
	bool		checkLiquidity(float liquidity);
	void		deleteAccount(Account* account);
	bool		addLiquidity(Account* account, float liquidity);
	void		addFund(float amount);
	float		getFund( void ) const;
	size_t		getAccountCount( void ) const;

};

