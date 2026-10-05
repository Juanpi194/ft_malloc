/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanpi194 <juanpi194@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:39:04 by jvizcain          #+#    #+#             */
/*   Updated: 2026/10/05 13:50:52 by juanpi194        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H 1

# define TRUE 1
# define FALSE 0

# define DEFAULT_FD 1
# define ERR_FD 2

// BASE HEADERS:
# include <stdlib.h>
# include <unistd.h>

// UTILS HEADERS:
# include <limits.h>

// BASIC FUNCTIONS:
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

size_t	ft_strlen(const char *str);
void	*ft_memset(void *s, int c, size_t n);

void	ft_bzero(void *str, size_t count);
void	*ft_memcpy(void *dest, const void *src, size_t count);
void	*ft_memmove(void *dest, const void *src, size_t count);
size_t	ft_strlcpy(char *dest, const char *src, size_t count);
size_t	ft_strlcat(char *dest, const char *src, size_t count);

int		ft_toupper(int c);
int		ft_tolower(int c);

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);

// BASIC FUNCTIONS THAT USE MALLOC
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);

// ADDITIONAL FUNCTIONS: 
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// LIST FUNCTIONS:
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// EXTRA FUNCTIONS:
/*
@brief	Casts a string to long.
@param	*nptr	The string that will be casted.
@return	The string casted to long. 0 if `*nptr` is `NULL`
*/
long	ft_atol(char *nptr);

/*
@brief	Checks if a character is a space character.
@param	c	The character to be evaluated.
@return	1 if `c` is a space character. 0 if it is not.
@note	These characters will be considered space characters:
		
		- `\t`	-> (horizontal tab)

		- `\n`	-> (new line)
		
		- `\v`	-> (vertical tab)
		
		- `\f`	-> (form feed)

		- `\r`	-> (carriage ret)

		- ` `	-> SPACE
*/
int		ft_isspace(char c);

/*
@brief	Checks if a string is castable to a number.
@param	str	String to be evaluated.
@return	1 if `str` is castable to a number. 0 if it
		is not or if `str` is `NULL`.
*/
int		ft_str_isdigit(char *str);

/*
@brief	Prints all the arguments followed by a newline.
@param	**args	The double pointer with the arguments to be printed.
@note	If `args` is `NULL`, nothing will be printed.
*/
void	ft_print_args(char **args);

/*
@brief	Gets the length of a number.
@param	num	The number to be evaluated.
@return	The length of the number.
@note	If the number is negative, the `-` sign will count
		as a number too.
*/
size_t	ft_num_len(long long num);

/*
@brief	Prints in the specified file descriptor an unsigned integer number.
@param	n	The number to be printed.
@param	fd	The file descriptor where the number will be printed.
*/
void	ft_putunbr_fd(unsigned int n, int fd);

/*
@brief	Prints in the specified file descriptor a long number.
@param	n	The number to be printed.
@param	fd	The file descriptor where the number will be printed.
*/
void	ft_putlnbr_fd(long n, int fd);

/*
@brief	Prints in the specified file descriptor an unsigned long number.
@param	n	The number to be printed.
@param	fd	The file descriptor where the number will be printed.
*/
void	ft_putulnbr_fd(unsigned long n, int fd);

/*
@brief	Prints in the specified file descriptor an integer number
		converted to a specified base representation.
@param	n		The number to be converted to a base and then printed.
@param	*base	The string with the base to work with.
@param	fd		The file descriptor where the number will be printed.
@note	The number will be casted to `unsigned int`, so if `n`
		is negative, it will overflow. This is still good behavior though.
*/
void	ft_putnbr_base_fd(unsigned int n, char const *base, int fd);

/*
@brief	Prints in the specified file descriptor a long number converted to
		a specified base representation.
@param	n		The number to be converted to a base and then printed.
@param	*base	The string with the base to work with.
@param	fd		The file descriptor where the number will be printed.
@note	The number will be casted to `unsigned long`, so if `n` is negative,
		it will overflow. This is still good behavior though.
*/
void	ft_putlnbr_base_fd(unsigned long n, char const *base, int fd);

#endif