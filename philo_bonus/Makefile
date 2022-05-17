NAME			:= philo_bonus
OBJS_DIR		:= ./objs
SRCS_DIR		:= ./srcs
INC_DIR			:= ./includes

CC				:= gcc
RM				:= rm -rf
CFLAGS			:= -Wall -Wextra -Werror

C_MAIN			:= init.c philo.c simulation.c time.c utils.c
SRCS			:= $(addprefix $(SRCS_DIR)/, $(C_MAIN))
OBJS			:= $(addprefix $(OBJS_DIR)/, $(C_MAIN:.c=.o))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $^ -I${INC_DIR}


all:			$(NAME)
				@echo "Philo ready to use: Usage: ./philo_bonus [#_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [[#_times_eat]]"

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

bonus:			$(NAME)
				@echo "Philo ready to use: Usage: ./philo_bonus [#_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [[#_times_eat]]"

clean:
				@$(RM) $(OBJS_DIR)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean $(NAME)

rebonus:		fclean $(NAME)

.PHONY:			all bonus clean fclean re rebonus


