# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/07 19:14:12 by seozcan           #+#    #+#              #
#    Updated: 2022/06/08 19:11:04 by seozcan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::TARGET::

NAME	:= philo

BNAME	:= 

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::PATHS::

ODIR	:= objs

BODIR	:= objs_bonus

SDIR	:= srcs

BDIR	:= bonus

IDIR	:= inc

LDIR 	:= libft

PFDIR	:= ft_printf

MDIR	:= minilibx-linux

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::SOURCES::

SRCS	:= 

OBJS	= $(addprefix $(ODIR)/, $(SRCS:.c=.o))

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::BONUS::

BSRCS	:= 

BOBJS	= $(addprefix $(BODIR)/,$(BSRCS:.c=.o))

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::COMPILERS::

CC		:= gcc

WFLAGS	:= -MMD -Wall -Wextra -Werror

GFLAG	:= -g3

SANFLAG	:= -fsanitize=address

AR		:= ar

ARFLAGS	:= rcs

MLXFLAGS := -lXext -lX11

MATHFLAG := -lm

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::HEADERS::

LINC	= $(addprefix $(LDIR)/, $(IDIR))

PFINC	= $(addprefix $(PFDIR)/, $(IDIR))

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

BLUE		=	\033[1;34m
CYAN		=	\033[0;36m
GREEN		=	\033[0;92m
BGREEN		=	\033[1;92m
ORANGE  	=	\033[0;33m
NO_COLOR	=	\033[m
PURPLE		=	\033[0;35m
BPURPLE		=	\033[1;35m
BCYAN		=	\033[1;36m
ICYAN		=	\033[3;36m

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
	@$(CC) $(WFLAGS) $(GFLAG) $(SANFLAG) $(INCLUDE_FLAGS) -c $< -o $@ 
	@echo "$(GREEN)compilation:\t\t\t\t\t\t[OK]$(NO_COLOR)"

$(NAME):		$(OBJS)	
	@$(CC) $(WFLAGS) $(GFLAG) $(SANFLAG) $(OBJS) -o $(NAME)
	@echo "$(GREEN)mandatory exe:\t\t\t\t\t\t[OK]$(NO_COLOR)"

$(OBJS):		| $(ODIR)

$(ODIR):
	@mkdir -p $(ODIR)
	@echo "$(GREEN)objs folder:\t\t\t\t\t\t[OK]$(NO_COLOR)"

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::BONUS::

bonus:			header lib h3 message_b $(BNAME)

$(BODIR)/%.o:	%.c 
	@$(CC) $(WFLAGS) $(GFLAG) $(SANFLAG) $(INCLUDE_FLAGS) -c $< -o $@ 
	@echo "$(GREEN)bonus compilation:\t\t\t\t\t[OK]$(NO_COLOR)"

$(BNAME):		$(BOBJS)
	@$(CC) $(WFLAGS) $(GFLAGS) $(SANFLAG) $(BOBJS) -o $(BNAME)
	@echo "$(GREEN)bonus exe:\t\t\t\t\t\t[OK]$(NO_COLOR)"

$(BOBJS):		| $(BODIR)

$(BODIR):
	@mkdir -p $(BODIR)
	@echo "$(GREEN)objs_bonus folder:\t\t\t\t\t[OK]$(NO_COLOR)"

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

update:	header fclean
	@git pull

push:	header fclean
	@echo "$(GREEN)"
	@git add .
	@git commit --quiet
	@git push --quiet
	@echo "$(GREEN)git push:\t\t\t\t\t\t[OK]$(NO_COLOR)"

clean:	header
ifneq ($(wildcard ./$(ODIR)),)
	@make -C $(LDIR) --quiet clean	
	@make -C $(PFDIR) --quiet clean
	@make -C $(MDIR) --quiet clean
	@rm -rf $(ODIR)
	@rm -rf $(BODIR)
	@echo "$(ORANGE)objs folder:\t\t\t\t\t\t[RM]$(NO_COLOR)"
else
	@make -C $(LDIR) --quiet clean
	@make -C $(PFDIR) --quiet clean
	@make -C $(MDIR) --quiet clean
	@rm -f $(wildcard *.o)
	@rm -f $(wildcard *.d)
	@echo "$(ORANGE)obj files:\t\t\t\t\t\t[RM]$(NO_COLOR)"
endif

fclean:	header clean
ifeq ($(IS_LIBFT),true)
	@make -C $(LDIR) --quiet fclean
endif
ifeq ($(IS_PRINTF),true)
	@make -C $(PFDIR) --quiet fclean
endif
	@rm -f $(NAME)
	@rm -f $(BNAME)
	@echo "$(ORANGE)$(NAME) executable:\t\t\t\t\t\t[RM]$(NO_COLOR)"

header:
	@echo "$(BPURPLE)"
	@echo "   ______________________________________________________"
	@echo "  /\     __________    ________    ___   ___    _______  \ "
	@echo " /  \   /\         \  /\   __  \  /\  \ /\  \  /\  ____\  \ "
	@echo "/    \  \ \  \ _/\  \ \ \   __  \ \ \  \ /_ /_ \ \  _\_/_  \ "
	@echo "\     \  \ \__\_/ \__\ \ \__\-\__\ \ \__\  \__\ \ \______\  \ "
	@echo " \     \  \/__/  \/__/  \/__/ /__/  \/__/ \/__/  \/______/   \ "
	@echo "  \     \_____________________________________________________\ "
	@echo "   \    /                                                     / "
	@echo "    \  /                   $(SCYAN) S E O Z C A N \$(NO_COLOR)$(BPURPLE)            ____   / "
	@echo "     \/______________________________________________/\   \_/ "
	@echo "                                                     \ \___\ "
	@echo "                                                      \/___/ "
	@echo "$(NO_COLOR)"

h2:
	@echo "\n$(BPURPLE):::::::::::::::::::::::::::::::::::::::::::::::::::::::FDF::\n$(NO_COLOR)"

h3:
	@echo "\n$(BPURPLE):::::::::::::::::::::::::::::::::::::::::::::::::::::BONUS::\n$(NO_COLOR)"

message:
	@make -q $(NAME) && echo "$(BGREEN)All files are already up to date$(NO_COLOR)" || true

message_b:
	@make -q $(BNAME) && echo "$(BGREEN)All bonus files are already up to date$(NO_COLOR)" || true

re:		header fclean all 

-include $(DEPS)
-include $(BDEPS)

.PHONY:	all bonus clean fclean re push update o_dir h1 h2 header 
