/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Extern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:17:36 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/17 18:37:45 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Extern.hpp"

void removeChar(std::string *str, char ch)
{
	for (std::string::iterator it = str->begin(); it != str->end(); it++)
	{
		if (*it == ch)
		{
			it = str->erase(it);
			it--;
		}
	}
}

int stringToInt(const std::string& str)
{
	std::stringstream ss(str);
	int result;
	ss >> result;
	return result;
}


size_t	stringToSizet(const std::string& str)
{
	std::stringstream ss(str);
	size_t result;
	ss >> result;
	return result;
}