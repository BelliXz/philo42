
#######################
# Colors
C_RE= \033[0m
C_Y = \033[1;33m
C_G	= \033[1;32m
C_C	= \033[1;36m
C_R	= \033[1;31m
########################

CC 			= cc
CFLAGS 		= -Wall -Werror -Wextra -I $(HEADER_NOW)

HEADER_NOW 	= philosophers.h
NAME 		= philo

SRC 		= main.c \
			  ft_eat.c \
			  ft_routine.c \
			  ft_set_and_free.c \
			  ft_utils.c

OBJ			= $(SRC:.c=.o)

all: $(NAME)
######################################################



lh1:
	make all
								./philo 5 800 200 100 1
	@echo "$(C_C)Run normal finish <======= $(C_RE)"
	valgrind  					./philo 5 800 200 100 1
	@echo "$(C_C)make leak finish <======= $(C_RE)"
	valgrind --tool=helgrind 	./philo 5 800 200 100 1
	@echo "$(C_C)make hell finish <======= $(C_RE)"

lh:
	make all
								./philo 5 800 200 100 10
	@echo "$(C_C)Run normal finish <======= $(C_RE)"
	valgrind  					./philo 5 800 200 100 10
	@echo "$(C_C)make leak finish <======= $(C_RE)"
	valgrind --tool=helgrind 	./philo 5 800 200 100 10
	@echo "$(C_C)make hell finish <======= $(C_RE)"

n:
	make && ./philo 5 800 	200 	100 	10	

l:
	make && valgrind  ./philo 5 800 	200 	100 	10	

h:
	make all
									./philo 5 800 200 100 10	
	make && valgrind --tool=helgrind ./philo 5 800 	200 	100 	10	

lhd:
	make all
								./philo 4 310 200 100	
	@echo "$(C_C)Run normal finish <======= $(C_RE)"
	valgrind  					./philo 4 310 200 100	
	@echo "$(C_C)make leak finish <======= $(C_RE)"
	valgrind --tool=helgrind 	./philo 4 310 200 100	
	@echo "$(C_C)make hell finish <======= $(C_RE)"

a:
	clear
	@echo "\nnb_philo	die	eat	sleep	meal"
	./philo 4 	300 	100 	200 	5

b:
	clear
	@echo "\nnb_philo	die	eat	sleep	meal"
	./philo 4 	310 	200 	100 	10

t22:
	clear
	@echo "\nnb_philo	die	eat	sleep	meal"
	./philo 2 	600 	200 	100 	10	


t1d:
	make all
								./philo 1 800 200 200
	@echo "$(C_C)Run normal finish <======= $(C_RE)"
	valgrind					./philo 1 800 200 200
	@echo "$(C_C)make leak finish <======= $(C_RE)"

	@echo "$(C_C)make hell finish <======= $(C_RE)"
#not eat  +shold die

t2:
	make all
								./philo  5 800 200 200 14
	@echo "$(C_C)Run normal finish <======= $(C_RE)"
	valgrind					./philo  5 800 200 200 14
	@echo "$(C_C)make leak finish <======= $(C_RE)"
	valgrind --tool=helgrind	./philo  5 800 200 200 14
	@echo "$(C_C)make hell finish <======= $(C_RE)"
#no die  +no stop !!!

t3:
	make all
								./philo 5 800 200 200 7
	@echo "$(C_C)Run normal finish <======= $(C_RE)"
	valgrind					./philo 5 800 200 200 7
	@echo "$(C_C)make leak finish <======= $(C_RE)"
	valgrind --tool=helgrind	./philo 5 800 200 200 7
	@echo "$(C_C)make hell finish <======= $(C_RE)"
#no die

t4:
	make all
								./philo 4 410 200 200 14
	@echo "$(C_C)Run normal finish <======= $(C_RE)"
	valgrind					./philo 4 410 200 200 14
	@echo "$(C_C)make leak finish <======= $(C_RE)"
	valgrind --tool=helgrind	./philo 4 410 200 200 14
	@echo "$(C_C)make hell finish <======= $(C_RE)"
#no die  +no stop !!!


t5d:
	make all
								./philo 4 310 200 100
	@echo "$(C_C)Run normal finish <======= $(C_RE)"
	valgrind					./philo 4 310 200 100
	@echo "$(C_C)make leak finish <======= $(C_RE)"
	valgrind --tool=helgrind	./philo 4 310 200 100
	@echo "$(C_C)make hell finish <======= $(C_RE)"
#have die


t6:
	make all
								./philo 5 900 295 60 10
	@echo "$(C_C)Run normal finish <======= $(C_RE)"
	valgrind					./philo 5 900 295 60 10
	@echo "$(C_C)make leak finish <======= $(C_RE)"
	valgrind --tool=helgrind	./philo 5 900 295 60 10
	@echo "$(C_C)make hell finish <======= $(C_RE)"
#no die <============================

l3d:
	clear
	./philo 4 200 205 200
#die
l4:
	clear
	./philo 5 800 200 200 7
#no one should die, simulation should stop after 7 eats
l5:
	clear
	./philo 4 410 200 200 10
#no one should die, simulation should stop after 10 eats

l6:
	clear
	./philo 5 800 200 200 
#no die
l7:
	clear
	./philo 5 600 150 150
#no die
l8:
	clear
	./philo 4 410 200 200
#no die
l9:
	clear
	./philo 100 800 200 200
#no die
l10:
	clear
	./philo 105 800 200 200
#no die
l11:
	clear
	./philo 200 800 200 200 

########################################################
$(NAME): $(OBJ) $(HEADER_NOW)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(C_Y)make $(NAME) finish <======= $(C_RE)"

%.o: %.c $(HEADER_NOW) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@echo "$(C_C)make clean finish$(C_RE)"

fclean: clean
	rm -f $(NAME)
	@echo "$(C_C)make fclean finish$(C_RE)"	

re: fclean all
	@echo "$(C_G)make re finish$(C_RE)"		

.PHONY: all clean fclean re
