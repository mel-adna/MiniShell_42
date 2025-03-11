#include "../../includes/minishell.h"

t_env	*ft_lstnew(char *value)
{
	t_env	*elem;

	elem = (t_env *)malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

void	push_back(t_env **lst, char *value)
{
	t_env	*temp;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new = ft_lstnew(value);
	if (!new || !lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = lst;
		while (temp)
			temp = temp->next;
		temp->next = new;
	}
}
