#ifndef MS_TEST_H
# define MS_TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

void	ft_tokenizer(char *line);
void	ft_print(char *line);
void	ft_find_pipe(char *line);

//utils
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(char const *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s);

#endif /* MS_TEST_H*/