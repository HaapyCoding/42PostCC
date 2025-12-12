/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bank.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:23:19 by codespace         #+#    #+#             */
/*   Updated: 2025/12/09 10:16:50 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BANK_HPP
# define BANK_HPP

# include "Account.hpp"

struct Bank
{
	private :
		size_t _liquidity;
		std::vector<Account *> _clientAccounts;
		
	public :
		Bank();
		~Bank();
		void addAccount(Account* p_account);
		void removeAccount(size_t p_id);
		size_t getLiquidity() const;
		size_t getNumberOfAccounts() const;
		size_t giveLoan(size_t p_amount, size_t p_id);
	
	friend std::ostream& operator << (std::ostream& p_os, const Bank& p_bank);
	
};

#endif