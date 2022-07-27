# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/07 19:14:12 by seozcan           #+#    #+#              #
#    Updated: 2022/07/27 18:55:25 by seozcan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::PATHS::

APATH		 	:= philo

BPATH			:= philo_bonus

ODIR			:= $(addprefix $(APATH)/, objs)

BODIR			:= $(addprefix $(BPATH)/, objs)

SDIR			:= $(addprefix $(APATH)/, srcs)

BDIR			:= $(addprefix $(BPATH)/, srcs)

IDIR			:= $(addprefix $(APATH)/, inc)

LDIR 			:= libft

PFDIR			:= ft_printf

MDIR			:= minilibx-linux

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::TARGET::

NAME			:= $(addprefix $(APATH)/, philo)

BNAME			:= $(addprefix $(BPATH)/, philo_bonus)

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::SOURCES::

SRCS			:= philo_main.c philo_init.c philo_utils.c philo_tools.c\
philo_routine.c philo_threads.c philo_mutexes.c

OBJS			= $(addprefix $(ODIR)/, $(SRCS:.c=.o))

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::BONUS::

BSRCS			:= 

BOBJS			= $(addprefix $(BODIR)/,$(BSRCS:.c=.o))

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::COMPILERS::

CC				:= gcc

WFLAGS			:= -MMD -Wall -Wextra -Werror -Wconversion

GFLAG			:= -g3

SANFLAG			:= -fsanitize=address

SANTHREAD		:= -fsanitize=thread

TSAN_OPTIONS	=second_deadlock_stack=1

THREADS			:= -pthread

AR				:= ar

ARFLAGS			:= rcs

MLXFLAGS		:= -lXext -lX11

MATHFLAG		:= -lm

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::HEADERS::

LINC			= $(addprefix $(LDIR)/, $(IDIR))

PFINC			= $(addprefix $(PFDIR)/, $(IDIR))

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::LIBRARY::

IS_LIBFT		:= false

LIB				:= libft.a

LIBTF_PATH		= $(addprefix $(LDIR)/, ${LIB})

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::FT_PRINTF::

IS_PRINTF		:= false

PRINTF			:= libftprintf.a

PRINTF_PATH		= $(addprefix $(PFDIR)/, $(PRINTF))

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::MINILIBX::

IS_MINILIBX		:= false

MINILIBX		:= libmlx_Linux.a

MINILIBX_PATH	= $(addprefix $(MDIR)/, ${MINILIBX})

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::COLORS::

NO_COLOR		=	\033[m

BLACK			=	\033[0;30m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
ORANGE 		 	=	\033[0;33m
BLUE			=	\033[0;34m
PURPLE			=	\033[0;35m
CYAN			=	\033[0;36m
WHITE			= 	\033[0;37m

# High Intensty
HIGREEN			=	\033[0;92m
HIORANGE	 	=	\033[0;93m
HIPURPLE		=	\033[0;95m

# Bold
BORANGE 		=	\033[1;33m
BBLUE			=	\033[1;34m
BPURPLE			=	\033[1;35m
BCYAN			=	\033[1;36m

# Bold High Intensity
BHIGREEN		=	\033[1;92m
BHIORANGE	 	=	\033[1;93m
BHIPURPLE		=	\033[1;95m

# Italic
ICYAN			=	\033[3;36m

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::PARAMS::

INCLUDE_FLAGS		=	$(addprefix -I , $(IDIR))

ifeq ($(IS_LIBFT),true)
	INCLUDE_FLAGS	+=	$(addprefix -I , $(LINC))
endif

ifeq ($(IS_PRINTF), true)
	INCLUDE_FLAGS	+= $(addprefix -I , $(PFINC))
endif

ifeq ($(IS_MINILIBX), true)
	INCLUDE_FLAGS	+= $(addprefix -I , $(MDIR))
endif

DEPS				= $(OBJS:.o=.d)
BDEPS				= $(BOBJS:.o=.d)

vpath %.c $(SDIR)\
		$(BDIR)
vpath %.o $(ODIR)\
		$(BODIR)

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::MANDATORY::

all:			header lib h2 message $(NAME)

$(ODIR)/%.o:	%.c 
	@$(CC) $(WFLAGS) $(GFLAG) $(SANTHREAD) $(THREADS) $(INCLUDE_FLAGS) -c $< -o $@ 
	@echo "$(HIGREEN)compilation:\t\t\t\t\t\t[OK]$(NO_COLOR)"

$(NAME):		$(OBJS)	
	@$(CC) $(WFLAGS) $(GFLAG) $(SANTHREAD) $(THREADS) $(OBJS) -o $(NAME)
	@echo "$(HIGREEN)$(NAME) executable:\t\t\t\t\t[OK]$(NO_COLOR)"

$(OBJS):		| $(ODIR)

$(ODIR):
	@mkdir -p $(ODIR)
	@echo "$(HIGREEN)objs folder:\t\t\t\t\t\t[OK]$(NO_COLOR)"

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::BONUS::

bonus:			header lib h3 message_b $(BNAME)

$(BODIR)/%.o:	%.c 
	@$(CC) $(WFLAGS) $(GFLAG) $(INCLUDE_FLAGS) -c $< -o $@ 
	@echo "$(HIGREEN)bonus compilation:\t\t\t\t\t[OK]$(NO_COLOR)"

$(BNAME):		$(BOBJS)
	@$(CC) $(WFLAGS) $(GFLAGS) $(SANFLAG) $(BOBJS) -o $(BNAME)
	@echo "$(HIGREEN)bonus exe:\t\t\t\t\t\t[OK]$(NO_COLOR)"

$(BOBJS):		| $(BODIR)

$(BODIR):
	@mkdir -p $(BODIR)
	@echo "$(HIGREEN)objs_bonus folder:\t\t\t\t\t[OK]$(NO_COLOR)"

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::RULES::

lib:
ifeq ($(IS_LIBFT),true)
	@make -C $(LDIR) --quiet
endif
ifeq ($(IS_PRINTF),true)
	@make -C $(PFDIR) --quiet
endif
ifeq ($(IS_MINILIBX),true)
	@make -C $(MDIR) --quiet 
endif

update:		header fclean
	@git pull

push:		header fclean
	@echo "$(HIGREEN)"
	@git add .
	@git commit --quiet
	@git push --quiet
	@echo "$(HIGREEN)git push:\t\t\t\t\t\t[OK]$(NO_COLOR)"

clean:		header
	@rm -rf $(ODIR)
	@rm -rf $(BODIR)
	@echo "$(HIORANGE)objs folder:\t\t\t\t\t\t[RM]$(NO_COLOR)"

fclean:		header clean
	@rm -f $(NAME)
	@rm -f $(BNAME)
	@echo "$(HIORANGE)$(NAME) executable:\t\t\t\t\t[RM]$(NO_COLOR)"

fcleanlib:	header fclean
ifeq ($(IS_LIBFT),true)
	@make -C $(LDIR) --quiet fclean
endif
ifeq ($(IS_PRINTF),true)
	@make -C $(PFDIR) --quiet fclean
endif
ifeq ($(IS_MINILIBX),true)
	@make -C $(MDIR) --quiet clean
endif

header:
	@echo "$(BHIPURPLE)"
	@echo "   ______________________________________________________"
	@echo "  /\     __________    ________    ___   ___    _______  \ "
	@echo " /  \   /\         \  /\   __  \  /\  \ /\  \  /\  ____\  \ "
	@echo "/    \  \ \  \ _/\  \ \ \   __  \ \ \  \ /_ /_ \ \  _\_/_  \ "
	@echo "\     \  \ \__\_/ \__\ \ \__\-\__\ \ \__\  \__\ \ \______\  \ "
	@echo " \     \  \/__/  \/__/  \/__/ /__/  \/__/ \/__/  \/______/   \ "
	@echo "  \     \_____________________________________________________\ "
	@echo "   \    /                                                     / "
	@echo "    \  /                   $(CYAN) S E O Z C A N \$(NO_COLOR)$(BHIPURPLE)            ____   / "
	@echo "     \/______________________________________________/\   \_/ "
	@echo "                                                     \ \___\ "
	@echo "                                                      \/___/ "
	@echo "$(NO_COLOR)"

h2:
	@echo "\n$(BHIPURPLE):::::::::::::::::::::::::::::::::::::::::::::::::::::PHILO::\n$(NO_COLOR)"

h3:
	@echo "\n$(BHIPURPLE):::::::::::::::::::::::::::::::::::::::::::::::::::::BONUS::\n$(NO_COLOR)"

message:
	@make -q $(NAME) && echo "$(BHIGREEN)All files are already up to date$(NO_COLOR)" || true

message_b:
	@make -q $(BNAME) && echo "$(BHIGREEN)All bonus files are already up to date$(NO_COLOR)" || true

re:		header fclean all 

-include $(DEPS)
-include $(BDEPS)

.PHONY:	all bonus clean fclean re push update o_dir h1 h2 header 
