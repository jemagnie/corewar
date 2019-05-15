/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strepur.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/10 14:24:24 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 18:34:11 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strepur(const char *s)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ft_isblank(s[i]))
		++i;
	while (s[i + j])
		++j;
	if (!j)
		return (0);
	while (ft_isblank(s[i + j - 1]))
		--j;
	if (!(new = ft_strndup(s + i, j)))
		return (NULL);
	return (new);
}

char	*ft_strnepur(const char *s, int n)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ft_isblank(s[i]))
		++i;
	while (s[i + j] && (i + j) < n)
		++j;
	if (!j)
		return (0);
	while (ft_isblank(s[i + j - 1]))
		--j;
	if (!(new = ft_strndup(s + i, j)))
		return (NULL);
	return (new);
}
