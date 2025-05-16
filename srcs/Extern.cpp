/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Extern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:17:36 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/16 19:18:46 by fre007           ###   ########.fr       */
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
