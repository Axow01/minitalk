SRCSS = server.c server_func.c

OBJSS = ${SRCSS:.c=.o}

SRCC = client.c errors.c

OBJSC = ${SRCC:.c=.o}

NAMES = server

NAMEC = client
 
CC	 = gcc
 
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft.a
LIBFTDIR = libft/

all	: ${LIBFTDIR}${LIBFT} ${NAMES} ${NAMEC}
	@echo Project built successfully 🤪
${LIBFTDIR}${LIBFT}:
					${MAKE} -C ${LIBFTDIR}
					${MAKE} -C ${LIBFTDIR} bonus
${NAMES}: ${OBJSS}
					${CC} ${CFLAGS} -g -o ${NAMES} ${OBJSS} ${LIBFTDIR}${LIBFT}
${NAMEC}: ${OBJSC}
					${CC} ${CFLAGS} -g -o ${NAMEC} ${OBJSC} ${LIBFTDIR}${LIBFT}

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
