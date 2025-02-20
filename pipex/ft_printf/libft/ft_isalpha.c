/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:28:09 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/20 08:57:47 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int	ft_isalpha(int a)
{
	if ((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z'))
		return (1);
	return (0);
}

/* int main() {
    char test_chars[] = {'a', '1', '#', 'Z', '9', ' ', '\0'};
    
    for (int i = 0; test_chars[i] != '\0'; i++) {
        char c = test_chars[i];
        printf("Character: %c\n", c);
        printf("ft_isalpha: %d\n", ft_isalpha(c));
        printf("\n");
    }
    return 0;
}
 */