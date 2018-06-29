/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 19:35:28 by obalagur          #+#    #+#             */
/*   Updated: 2018/01/20 19:35:29 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"

# define BUFF_SIZE 1
# define HAS_N (after_n = ft_strchr(*line, '\n')) != NULL

int		get_next_line(const int fd, char **line);
void	*for_each_gnl(char *file, void *(*f)(char *));

#endif
