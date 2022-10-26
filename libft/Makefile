SRCS  = ft_memset.c \
		ft_countwords.c	\
	    ft_bzero.c \
	    ft_freestrarr.c	\
	    ft_memalloc.c	\
	   	ft_memcpy.c \
	   	ft_memccpy.c \
	   	ft_memmove.c \
	  	ft_memchr.c \
	   	ft_memcmp.c \
	   	ft_strlen.c \
	   	ft_isalpha.c \
	   	ft_isdigit.c \
	   	ft_isalnum.c \
	   	ft_isspace.c	\
	   	ft_isascii.c \
	   	ft_isprint.c \
	   	ft_pathjoin.c	\
	   	ft_toupper.c \
	   	ft_tolower.c \
	   	ft_strstartswith.c	\
	   	ft_strendswith.c	\
	   	ft_strcmp.c	\
	   	ft_strchr.c \
	   	ft_strrchr.c \
	   	ft_strnstr.c \
	   	ft_strncmp.c \
	   	ft_strequ.c \
	   	ft_strlcat.c \
	   	ft_strlcpy.c \
	   	ft_atoi.c \
	   	ft_calloc.c\
	   	ft_strdup.c \
	   	ft_substr.c \
	   	ft_strjoin.c \
	   	ft_strjoincl.c	\
	   	ft_strjoinch.c	\
	   	ft_strjoinchcl.c	\
	   	ft_strreplace.c	\
	   	ft_itoa.c		\
	   	ft_strmapi.c	\
	   	ft_putchar.c \
	   	ft_putchar_fd.c \
	   	ft_putnstr.c	\
	   	ft_putstr_fd.c	\
	   	ft_putstr.c		\
	   	ft_putendl.c \
	   	ft_putendl_fd.c \
	   	ft_putnbr_fd.c	\
	    ft_strtrim.c	\
	   	ft_strnew.c \
	   	ft_strsplit.c	\
	   	ft_strstr.c	\
	    ft_split.c \
	    get_next_line.c \
	    get_next_line_utils.c

	   # ft_nstrlen.c \

	   # ft_strcpy.c \
	   # ft_strncpy.c \
	   # ft_strcat.c \
	   # ft_strncat.c \

	   # ft_strstr.c \

	   # ft_strncmp.c \
	   # ft_strrev.c \

	   # ft_memalloc.c \
	   # ft_memdel.c \
	   # ft_strnew.c \
	   # ft_strdel.c \
	   # ft_strclr.c \
	   # ft_striter.c \
	   # ft_striteri.c \
	   # ft_strmap.c \

	   # ft_strequ.c \
	   # ft_strnequ.c \

	   # ft_multistrjoin.c \

	   # ft_strsplit.c \
	   # ft_strsplitwith.c \
	   # ft_strprefix.c \
	   # ft_strsuffix.c \

	   # ft_utoa.c \
	   # ft_putchar.c \
	   # ft_putwchar.c \
	   # ft_putstr.c \
	   # ft_putwstr.c \
	   # ft_putnwstr.c \
	   # ft_putnstr.c \
	   # ft_putendl.c \
	   # ft_putnbr.c \
	   # ft_putnbrbase.c \

	   # ft_putwchar_fd.c \

	   # ft_putnstr_fd.c \
	   # ft_putwstr_fd.c \

OBJS 	= ${SRCS:.c=.o}

BONUS   = ft_lstnew.c \
          ft_lstadd_front.c \
          ft_lstsize.c \
          ft_lstlast.c \
          ft_lstadd_back.c \
          ft_lstdelone.c \
          ft_lstclear.c \
          ft_lstiter.c \
          ft_lstmap.c \

OBJS_BONUS  = ${BONUS:.c=.o}

HEAD	= libft.h
NAME 	= libft.a

CC		= gcc
RM 		= rm -f
CFLAGS 	= -Wall -Wextra -Werror
C 		= -c
O 		= -o
AR 		= ar rc

.c.o:
			${CC} ${CFLAGS} $(C) $< $(O) ${<:.c=.o}

$(NAME):	$(OBJS)	$(HEAD)
			$(AR) $(NAME) ${OBJS}

all: 		$(NAME)

clean:
			${RM} $(OBJS) $(OBJS_BONUS)

fclean: 	clean
			${RM} $(NAME)

re: 		fclean all

bonus:			$(OBJS) $(OBJS_BONUS)
				ar rc $(NAME) $(OBJS) $(OBJS_BONUS)

.PHONY: all, clean, fclean, re, bonus
