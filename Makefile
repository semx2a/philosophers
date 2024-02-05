# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/07 19:14:12 by seozcan           #+#    #+#              #
#    Updated: 2024/02/05 22:34:01 by seozcan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include settings.mk

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::DIRECTORIES::

S		=	src/
O		=	obj/
I 		=	inc/
D 		=	dep/
L 		=	Libft/
P 		=	ft_printf/
M 		=	minilibx-linux/

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::CUSTOM FLAGS::

CFLAGS	+=	-I$I

CFLAGS 	+=	-pthread

LDFLAGS	=

ifeq ($(IS_LIB), true)
	CFLAGS	+=	-I$L$I
	LDFLAGS	+=	-L$L -lft
endif

ifeq ($(IS_PTF), true)
	CFLAGS	+=	-I$P$I
	LDFLAGS	+=	-L$P -lftprintf
endif

ifeq ($(IS_MLX), true)
	CFLAGS	+=	-I$M
	LDFLAGS	+=	-L$M -lmlx
	ifeq ($(shell uname -s), Darwin)
		LDFLAGS += -framework OpenGL -framework AppKit -lX11 -lXext
	else ifeq ($(shell uname -s), Linux)
		LDFLAGS += -lXext -lX11 -lm
	endif
endif

ifeq (debug, $(filter debug,$(MAKECMDGOALS)))
	CFLAGS	+=	-g3
endif
ifeq (sanadd, $(filter sanadd,$(MAKECMDGOALS)))
	CFLAGS	+=	-fsanitize=address
endif
ifeq (santhread, $(filter santhread,$(MAKECMDGOALS)))
	CFLAGS	+=	-fsanitize=thread
endif

RM		=	/bin/rm -rf

SPACE 	= 	awk -F ':' '{ printf "%-61s %s\n", $$1 ":", $$2 }'


# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::OBJECTS::

OBJ		=	$(SRC:$S%=$O%.o)

DEP		=	$(SRC:$S%=$D%.d)

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::RULES::

all: header lib h2 message $(NAME)

$O:
	@mkdir -p $@
	@echo "$(HIGREEN)creating $O folder:[OK]$(NO_COLOR)" | $(SPACE)

$(OBJ): | $O

$(OBJ): $O%.o: $S%
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(HIGREEN)compiling $<:[OK]$(NO_COLOR)" | $(SPACE)

$D:
	@mkdir -p $@
	@echo "$(HIGREEN)creating $D folder:[OK]$(NO_COLOR)" | $(SPACE)

$(DEP): | $D

$(DEP): $D%.d: $S%
	@$(CC) $(CFLAGS) -MM -MF $@ -MT "$O$*.o $@" $<
	@echo "$(HIGREEN)compiling $<:[OK]$(NO_COLOR)" | $(SPACE)


$(NAME): $(OBJ) $(DEP)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "$(HIGREEN)compiling $(NAME):[OK]$(NO_COLOR)" | $(SPACE)

lib:
ifeq ($(IS_LIB),true)
	@make -C $L --quiet
endif
ifeq ($(IS_PTF),true)
	@make -C $P --quiet
endif
ifeq ($(IS_MLX),true)
	@make -C $M --quiet 
endif

cleanobj:
	@$(RM) $(O)
	@echo "$(HIORANGE)removing $O folder:[RM]$(NO_COLOR)" | $(SPACE)

cleandep:
	@$(RM) $(D)
	@echo "$(HIORANGE)removing $D folder:[RM]$(NO_COLOR)" | $(SPACE)

clean: header h2 cleanobj cleandep

fcleanlib: header
ifeq ($(IS_LIB),true)
	@make -C $L --quiet fclean
endif
ifeq ($(IS_PTF),true)
	@make -C $P --quiet fclean
endif
ifeq ($(IS_MLX),true)
	@make -C $M --quiet clean
endif

fclean: header fcleanlib h2 clean
	@$(RM) $(NAME)
	@echo "$(HIORANGE)removing $(NAME):[RM]$(NO_COLOR)" | $(SPACE)
	
re:	header fclean all

include colors.mk output.mk header.mk

.PHONY:	all clean fclean re