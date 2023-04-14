SRCLIENT = src/client.c

SRCSERVER = src/server.c

OBJSERVER = $(patsubst src/%.c,bin/%.o,$(SRCSERVER))

OBJCLIENT = $(patsubst src/%.c,bin/%.o,$(SRCLIENT))

NAMECLIENT = client

NAMESERVER = server

CC	 = gcc

CFLAGS = -Wall -Wextra -Werror

LIBFT = libft.a
LIBFTDIR = libft/

all: $(LIBFTDIR)$(LIBFT) $(NAMECLIENT) $(NAMESERVER)

$(LIBFTDIR)$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)
	$(MAKE) -C $(LIBFTDIR) bonus

$(NAMECLIENT): $(OBJCLIENT) $(LIBFTDIR)$(LIBFT)
	$(CC) $(CFLAGS) -g -o $(NAMECLIENT) $(LIBFTDIR)$(LIBFT) $(OBJCLIENT)

$(NAMESERVER): $(OBJSERVER) $(LIBFTDIR)$(LIBFT)
	$(CC) $(CFLAGS) -g -o $(NAMESERVER) $(LIBFTDIR)$(LIBFT) $(OBJSERVER)

bin/%.o: src/%.c
	mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -rf bin/
	$(MAKE) -C $(LIBFTDIR) fclean

fclean: clean
	@rm $(NAMESERVER) $(NAMECLIENT)

re: fclean all
