/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bank.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykeciri <ykeciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:23:19 by codespace         #+#    #+#             */
/*   Updated: 2026/11/24 23:36:57 by ykeciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>

class Bank {
public:
	class	Account;
	class	Loan;
private:

	float					_fund;
	std::vector<Account*>	_accounts;
	std::vector<Loan*>		_loans;

	Account*				CreateAccount();
	void					DeleteAccount(Account* account);
	bool					addLiquidity(Account* account, float liquidity);
	void					AddFund(float amount);

	Account* operator[](int account_id);
	Bank& operator=(const Bank& src);

	Bank(Bank &src);
public:
	class Loan{
			public:
				~Loan();

				
				const Bank&	getBank() const;
				Account	getAccount() const;
				void	refundAmount(int amount);
			private:
				Loan();
				Loan(Account* account, Bank* bank,float amount);

				friend class Bank;
				float	_amount;
				Account* _account;
				Bank* _bank;
		};

	class Account{
		private:
			friend class Bank;
			float				_liquidity;
			std::vector<Loan>	_myLoans;
			int					_account_id;

			float				GetMyFunds( void );
		public:
			Account(int id);
			~Account();
	};

	Bank();
	~Bank();

	bool	MakeDeposit(Account* acc, float amount);
	bool	AskForLoan(Account*  acc, float amountAsked);
	bool	checkLiquidity(float liquidity);

};

