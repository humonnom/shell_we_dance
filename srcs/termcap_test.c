#include "../incs/minishell.h"

#include <stdio.h>

#define BACKSPACE 127
#define LEFT_ARROW 4479771
#define RIGHT_ARROW 4414235
#define UP_ARROW 4283163
#define DOWN_ARROW 4348699

int	inst_list[BUF_SIZE];

void get_cursor_pos(int *col, int *row)
{
	int		cnt;
	int		idx;
	char	buf[255];
	int		read_size;

	write(STDIN_FILENO, "\033[6n", ft_strlen("\033[6n"));
	read_size = read(STDIN_FILENO, buf, 255); 
	buf[read_size] = '\0';
	idx = -1;
	while (!ft_isdigit(buf[idx]))
		++idx;
	*row = 0;
	while (ft_isdigit(buf[idx]))
		*row = *row * 10 + buf[idx++] - '0'; 
	++idx;
	*col = 0;
	while (ft_isdigit(buf[idx]))
		*col = *col * 10 + buf[idx++] - '0'; 
}

void move_cursor_left()
{
	write(STDIN_FILENO, "\033[D", 4);
}

void move_cursor_right()
{
	write(STDIN_FILENO, "\033[C", 4);
}

void	tc_setting(struct termios *term)
{
	tcgetattr(STDIN_FILENO, term);
	term->c_lflag &= ~ICANON;
	term->c_lflag &= ~ECHO;
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}

#if 1
int test()
{
	struct	termios term;
#if 1
	tc_setting(&term);

	tgetent(NULL, "xterm");
	char *tc_str[3];
	tc_str[TC_CM] = tgetstr("cm", NULL); 
	tc_str[TC_DL] = tgetstr("dl", NULL); 
	tc_str[TC_CE] = tgetstr("ce", NULL); 
#endif
#if 0
	char c;
	while (read(STDIN_FILENO, &c, sizeof(c)) > 0) {
		printf("keycode: %c\n", c);
	}
#endif
#if 1
	int col;
	int row;
	char *prompt;

	long c;
	prompt = ">> ";
	while (1)
	{
		get_cursor_pos(&col, &row);
		//printf("col: %d, row: %d\n", col, row);
		ft_cursor_mv_head(tc_str, row);
		write(1, prompt, ft_strlen(prompt));
		c = 0;
		char *str_in = ft_strdup("");
		while (read(0, &c, sizeof(c)) > 0)
		{
			//printf("keycode: %ld\n", c);
			if (c == '\n')
				break ;
			get_cursor_pos(&row, &col);
			if (col > 3 && c == LEFT_ARROW)
				ft_cursor_mv_left();
			else if (c == RIGHT_ARROW)
				ft_cursor_mv_right();
			else if (c == UP_ARROW)
			{
				ft_cursor_clr_line_all(tc_str, row);
				write(1, prompt, ft_strlen(prompt));
			}
#if 0
			else if (c == DOWN_ARROW)
				write(STDIN_FILENO, "\033[B", ft_strlen("\033[B"));
#endif
			else if (c == BACKSPACE)
				ft_cursor_clr_line_end(tc_str);
			else 
			{
				ft_putchar_fd(c, 1);
				char *tmp = cvt_char_to_str(c);
				str_in = ft_strjoin(str_in, tmp);
			}
			get_cursor_pos(&row, &col);
			c = 0;
		}
		printf("str_in: %s\n", str_in);
	}
#endif
#if 0
	while (1)
	{
		write(STDIN_FILENO, "\033[A", ft_strlen("\033[A"));
		char buf[100];
		read(STDOUT_FILENO, buf, 5);
		buf[4] = '\0';
		printf("buf: %s\n", buf);
	}
#endif
#if 0
	long d;
	while (read(STDIN_FILENO, &d, sizeof(d)) > 0) {
		printf("keycode: %ld\n", d);
	}
#endif
	return (0);	
}
#endif
