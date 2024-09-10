#ifndef MS_TEST_H
# define MS_TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_flag
{
	int	pipe;
}	t_flag;

typedef struct s_tokken_list
{
	char			*content;
	struct s_tokken_list	*next;
}					t_tokken_list;

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

//libft.c
int	ft_is_digit(char c);
int	ft_is_alpha(char c);

//lst_util.c
t_tokken_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_tokken_list **lst, t_tokken_list *new);
void	ft_lstclear(t_tokken_list **lst);

//token
void	ft_tokenizer(char *line, char **envp);
void	ft_in_pipe(char *line, char **envp, t_tokken_list **tokken);
char	*ft_alpha_digit(char *line, int *i);
char	*ft_double_qoute_check(char *line, int *i, char **envp);
char	*ft_export_ptr(char *line, int *i, char **envp);
char	*ft_export_push(char *temp, char **envp);
char	*ft_single_qoute_check(char *line, int *i);
char	*ft_redirection_check(char *line, int *i);
char	*ft_option(char	*line, int *i);

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

//ft_qoute.c
int		ft_double_qoute(char *line, int i, char **envp);
int		ft_single_qoute(char *line, int i);
void	ft_qoute_check(char *line, char **envp, t_flag *flag);

//ft_export.c
void	ft_print_export(char *temp, char **envp);
int		ft_export_check(char *line, int i, char **envp);

#endif /* MS_TEST_H*/