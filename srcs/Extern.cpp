/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Extern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:17:36 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/16 15:22:51 by alborghi         ###   ########.fr       */
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
