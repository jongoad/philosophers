NAME			:= philo
OBJS_DIR		:= ./objs
SRCS_DIR		:= ./srcs
INC_DIR			:= ./includes

CC				:= gcc
RM				:= rm -rf
CFLAGS			:= -Wall -Wextra -Werror

C_MAIN			:= init.c philo.c simulation.c time.c utils.c write.c
SRCS			:= $(addprefix $(SRCS_DIR)/, $(C_MAIN))
OBJS			:= $(addprefix $(OBJS_DIR)/, $(C_MAIN:.c=.o))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $^ -I${INC_DIR}

BONUS_RULE		:= cd ../philo_bonus && make
BONUS_CLEAN		:= cd ../philo_bonus && make clean
BONUS_FCLEAN	:= ../philo_bonus/philo_bonus

all:			$(NAME)
				@echo "Philo ready to use: Usage: ./philo [#_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [[#_times_eat]]"

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

bonus:			
				@$(BONUS_RULE)

clean:
				@$(RM) $(OBJS_DIR)
				@$(BONUS_CLEAN)

fclean:			clean
				@$(RM) $(NAME) $(BONUS_FCLEAN)

re:				fclean $(NAME)

rebonus:		fclean 
				@$(BONUS_RULE)

.PHONY:			all bonus clean fclean re rebonus
