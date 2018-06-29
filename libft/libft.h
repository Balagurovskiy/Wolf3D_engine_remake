/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 15:19:04 by obalagur          #+#    #+#             */
/*   Updated: 2017/12/08 19:34:49 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strchr(const char *s, int c);
int					ft_atoi(const char *str);
void				ft_strdel(char **as);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_putstr(char const *s);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lst_delone(t_list **f, t_list *one,
						void (*del)(t_list *));
void				ft_list_clear(t_list *node);
void				ft_list_add(t_list **first_node, t_list *new_node);
int					ft_atoi_base(const char *str, int base);
char				**ft_splinter(char const *s, char *c);
int					ft_tolower(int c);
int					ft_str_contains(char *source, char *target);
void				ft_memdel(void **ap);
char				*ft_strtrim(char const *s);

#endif
