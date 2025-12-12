/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:00:51 by codespace         #+#    #+#             */
/*   Updated: 2025/12/09 09:46:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACCOUNT_HPP
# define ACCOUNT_HPP

#include <iostream>
#include <vector>

struct Account
{
	private :
		size_t _id = 0;
		size_t _value;
		void _setId();
		void _setValue(size_t p_value) { _value = p_value; }
	public :
		size_t getId() const;
		size_t getValue() const;

	Account();
	

	friend std::ostream& operator << (std::ostream& p_os, const Account& p_account);
};

#endif