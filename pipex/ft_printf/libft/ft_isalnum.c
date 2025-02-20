/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:54:57 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/20 08:56:16 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int a)
{
	if (ft_isalpha(a) == 1 || ft_isdigit(a) == 1)
		return (1);
	return (0);
}

/* int main() {
    char test_chars[] = {'a', '1', '#', 'Z', '9', ' ', '\0'};
    
    for (int i = 0; test_chars[i] != '\0'; i++) {
        char c = test_chars[i];
        printf("Character: %c\n", c);
        printf("ft_isalnum: %d\n", ft_isalnum(c));
        printf("\n");
    }
    return 0;
}
 */