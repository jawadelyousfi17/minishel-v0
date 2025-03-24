#include "../include/minishell.h"

/**
 * to test: 1/2
 * done: raw value && fix ambs right ✅done
 */

char *ft_join_raw_value(t_token *t)
{
	char *r;

	r = NULL;
	if (t && t->type == SPACES)
		t = t->next;
	while (t && !ft_is_op_space(t))
	{
		r = ft_strjoin(r, t->raw_value, GB_C);
		if (!r)
			return NULL;
		if (t)
			t = t->next;
	}
	return r;
}

void ft_add_txt_tk(char *s, t_token **t)
{
	while (*s)
	{
		if (*s == ' ' || *s == '\t')
		{
			while (*s && (*s == ' ' || *s == '\t'))
				s++;
			ft_add_token(t, " ", SPACES);
		}
		else
		{
			while (*s && *s != ' ' && *s != '\t')
			{
				ft_add_token(t, ft_strndup(s, 1, GB_C), TEXT);
				s++;
			}
		}
	}
}

t_token *ft_split_var_file_name(t_token *t)
{
	t_token *new;

	new = NULL;
	if (t && t->type == SPACES)
		t = t->next;
	while (t && !ft_is_op_space(t))
	{
		if (t->type != TEXT)
			ft_add_token(&new, t->value, TEXT);
		else
			ft_add_txt_tk(t->value, &new);
		if (t)
			t = t->next;
	}
	return new;
}

int check_space_or_empty(t_token *t)
{
	int is_empty;

	is_empty = 1;
	if (t && t->type == SPACES)
		t = t->next;
	while (t)
	{
		if (is_empty && t->type == TEXT)
			is_empty = 0;
		if (t->type == SPACES && t->next)
			return 1;
		t = t->next;
	}
	return 0;
}

int check_ambs(t_token *tokens)
{
	t_token *t;

	t = tokens;
	while (t)
	{
		if (t->type == REDIRECT_INPUT || t->type == REDIRECT_OUTPUT || t->type == APPEND)
		{
			t_token *new_t = ft_split_var_file_name(t->next);
			if (!new_t || check_space_or_empty(new_t))
			{
				t->is_ambs = 1;
				t->value = ft_join_raw_value(t->next);
				if (!t->value)
					return 0;
			}
		}
		if (t)
			t = t->next;
	}
	return 1;
}
