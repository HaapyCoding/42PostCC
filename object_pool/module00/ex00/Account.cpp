/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:22:24 by codespace         #+#    #+#             */
/*   Updated: 2025/12/12 14:00:34 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"

void Account::_setId() 
{
	if (!(!id))
	{
		static int currentId = 0;
		id = currentId;
		currentId++;
	}
}

Account::Account()
{
	_setId();
}

size_t Account::getId() const
{
	return (id);
}

size_t Account::getValue() const
{
	return (value);
}

std::ostream& operator << (std::ostream& p_os, const Account& p_account)
{
	p_os << "[" << p_account.id << "] - [" << p_account.value << "]";
	return (p_os);
}
