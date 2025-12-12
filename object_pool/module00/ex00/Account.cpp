/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:22:24 by codespace         #+#    #+#             */
/*   Updated: 2025/12/09 09:35:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"

void Account::_setId() 
{
	if (!(!_id))
	{
		static int currentId = 0;
		_id = currentId;
		currentId++;
	}
}

Account::Account()
{
	_setId();
}

size_t Account::getId() const
{
	return (_id);
}

size_t Account::getValue() const
{
	return (_value);
}

std::ostream& operator << (std::ostream& p_os, const Account& p_account)
{
	p_os << "[" << p_account._id << "] - [" << p_account._value << "]";
	return (p_os);
}
