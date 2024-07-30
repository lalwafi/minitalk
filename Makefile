SERVER = server.c
CLIENT = client.c

SERVERBONUS = server_bonus.c
CLIENTBONUS = client_bonus.c

PRINTF = ft_printf_copy/libftprintf.a
LIBFT = libft_copy/libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

SERVEROBJ = $(SERVER:.c=.o)
CLIENTOBJ = $(CLIENT:.c=.o)

SERVERBONUSOBJ = $(SERVERBONUS:.c=.o)
CLIENTBONUSOBJ = $(CLIENTBONUS:.c=.o)

all : client server

$(LIBFT):
	make -C libft_copy
	
$(PRINTF):
	make -C ft_printf_copy

client: $(CLIENTOBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(CLIENTOBJ) $(LIBFT) $(PRINTF) -o client

server: $(SERVEROBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(SERVEROBJ) $(LIBFT) $(PRINTF) -o server

client_bonus: $(CLIENTBONUSOBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(CLIENTBONUSOBJ) $(LIBFT) $(PRINTF) -o client_bonus

server_bonus: $(SERVERBONUSOBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(SERVERBONUSOBJ) $(LIBFT) $(PRINTF) -o server_bonus


bonus : client_bonus server_bonus


re : fclean all


clean :
	rm -f $(SERVEROBJ) $(CLIENTOBJ) $(SERVERBONUSOBJ) $(CLIENTBONUSOBJ)
	make -C libft_copy clean
	make -C ft_printf_copy clean

fclean : clean
		rm -f client server client_bonus server_bonus
		make -C libft_copy fclean
		make -C ft_printf_copy fclean

.PHONY : all clean fclean re