#include "../incs/minishell.h"

static char	*show_type_error(char *str)
{
	char	c[2];

	show_error("zsh: parse error near");
	show_error(" `");
	c[0] = str[0];
	c[1] = '\0';
	show_error(c);
	if (str[1] && is_bracket(str[1]))
	{ c[0] = str[1];
		c[1] = '\0';
		show_error(c);
	}
	show_error("'\n");
	return (NULL);
}

static int	join_char_to_args(char **str, char c)
{
	int		ret;
	char	*tmp;
	char	*c_str;

	c_str = cvt_char_to_str(c);
	tmp = ft_strjoin(*str, c_str);
	free(c_str);
	free(*str);
	*str = tmp;
	return (1);
}

static char	*set_fd_part(t_set *set, char *str, char *str_cpy)
{
	char	*ret;
	int		idx;
	int		idx_inc;
	int		tmp_type;

	idx = 0;
	idx_inc = 1;
	ret = ft_strdup("");
	set->type = 0;
	while (idx_inc > 0 && str_cpy[idx])
	{
		tmp_type = set_bracket_type(&str_cpy[0], &idx);
		set->type |= tmp_type;
		if (set->type & TYPE_ERROR)
			return (show_type_error(&str_cpy[idx]));
		if (set->type & (TYPE_REIN | TYPE_REOUT | TYPE_REOUT_D))
		{
		printf("tmp_type: %d========================\n", tmp_type);
			idx_inc = set_fd_info(set, &str_cpy[idx], tmp_type);
		printf("idx_inc: %d========================\n", idx_inc);
		}
		else
			idx_inc = join_char_to_args(&ret, str[idx]);
		idx += idx_inc;
	}
	if (idx_inc == 0)
		return (NULL);
	printf("set_fd_part::ret: %s\n", ret);
	return (ret);
}

char	*set_fd(t_set *set, char *set_str)
{
	char	*ret;
	char	*set_str_cpy;

    set_str_cpy = ft_strdup(set_str);
	handle_quote(set_str, &set_str_cpy, ' ');
	handle_quote(set_str_cpy, &set_str_cpy, '<');
	handle_quote(set_str_cpy, &set_str_cpy, '>');
	printf("gen_set::set_str_cpy: %s\n", set_str_cpy);
	set->fd_in_idx = 0;
	set->fd_out_idx = 0;
	ret = set_fd_part(set, set_str, set_str_cpy);
	free(set_str_cpy);
	return (ret);
}
