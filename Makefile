SRCSS = server.c

OBJSS = ${SRCSS:.c=.o}

SRCC = client.c

OBJSC = ${SRCC:.c=.o}

NAMES = server

NAMEC = client
 
CC	 = gcc
 
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft.a
LIBFTDIR = libft/

all	: ${LIBFTDIR}${LIBFT} ${NAMES} ${NAMEC}
	@echo Making the project 🤪
${LIBFTDIR}${LIBFT}:
					${MAKE} -C ${LIBFTDIR}
					${MAKE} -C ${LIBFTDIR} bonus
${NAMES}: ${OBJSS}
					${CC} ${CFLAGS} -o ${NAMES} ${LIBFTDIR}${LIBFT} ${OBJSS}
${NAMEC}: ${OBJSC}
					${CC} ${CFLAGS} -o ${NAMEC} ${LIBFTDIR}${LIBFT} ${OBJSC}

clean  :  
					@rm -f ${OBJSS} ${OBJSC}
					${MAKE} -C ${LIBFTDIR} fclean
 
fclean : clean
					@rm -f ${NAMES} ${NAMEC}
 
re     : fclean all

run	: all
					@./server

push : fclean
		@git add .
		@git commit -m "ATOMATIC PUSH BY MAKEFILE"
		@git push origin master
