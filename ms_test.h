#ifndef MS_TEST_H
# define MS_TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_word
{
	int			count;
	int			flag;
	int			single_quote_flag;
	int			double_quote_flag;
	int			quote_flag;
	const char	*start;
	const char	*end;
}			t_word;

void	ft_tokenizer(char *line);
void	ft_print(char *line);
void	ft_find_pipe(char *line);

//utils
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(char const *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s);

// ft_split.c
char	**split(const char *s, char c, int size, char **p);
char	**ft_split(const char *s, char c);
void	flag1_case(t_word *word, char s, char c);
int		count_words(const char *s, char c);
void	end_of_word(const char **s, char c, t_word *word);

//ft_split_utils.c
void	ft_free(char **p, int sz);
void	init_word(t_word *word);
int		is_quote(const char *s);

#endif /* MS_TEST_H*/