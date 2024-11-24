/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:02:18 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/27 09:23:26 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H
#include <unistd.h>
	char	**ft_split(char const *s, char c);
	void	ft_putstr_fd(char *s, int fd);
	size_t	ft_strlen(const char *s);
	char	*ft_strdup(const char *s1);
	char	*ft_strchr(const char *chain, int c);
	int	ft_isalpha(int c);
	int	ft_isdigit(int c);
	char	*ft_strjoin(char const *s1, char const *s2);
	int is_number(char *str);
	int	ft_atoi(const char *str);


	// size_t	ft_strlcpy(char *dst, const char *src, size_t len);

#endif