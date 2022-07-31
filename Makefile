# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrown <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/28 16:28:46 by jbrown            #+#    #+#              #
#    Updated: 2022/07/30 13:48:14 by jbrown           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#							Edit this section								   #
NAME		=	fdf
COMPILER	=	gcc
SOURCE_EXT	=	c
ARCHIVE_EXT	=	a
COMP_STD	=	-std=c99
COMP_FLAGS	=	-Wall -Wextra -Werror -g
UNAME		=	$(shell uname)
# 																			   #
# **************************************************************************** #

#				Colours
_USER		=	$(shell printenv USER)

CB_BLK		=	$(shell tput setab 0)
CB_RED		=	$(shell tput setab 1)
CB_GRN		=	$(shell tput setab 2)
CB_YEL		=	$(shell tput setab 3)
CB_BLU		=	$(shell tput setab 4)
CB_MAG		=	$(shell tput setab 5)
CB_CYN		=	$(shell tput setab 6)
CB_WHT		=	$(shell tput setab 7)

# 	Text Colour
CT_BLK		=	$(shell tput setaf 0)
CT_RED		=	$(shell tput setaf 1)
CT_GRN		=	$(shell tput setaf 2)
CT_YEL		=	$(shell tput setaf 3)
CT_BLU		=	$(shell tput setaf 4)
CT_MAG		=	$(shell tput setaf 5)
CT_CYN		=	$(shell tput setaf 6)
CT_WHT		=	$(shell tput setaf 7)

CAL_RST		=	$(shell tput sgr0)

# Modify the below variables to change the colour output of the following
# 	VARIABLE		DESCRIPTION				EXAMPLE
# 	C_CLN_MS		Clean Message			Cleaning;
# 	C_CLN_VA		Clean Variables			$(NAME) ./build
#	C_LNK_MS		Linking Message			Linking
# 	C_LNK_V1		Linking Source File		sources/main.c
# 	C_LNK_V2		Linking Object File		build/main.o
# 	C_FIN_VA		Final Build Variable	$(NAME)
# 	C_FIN_MS		Final Build Message		ready to be run
C_CLN_MS	=	$(CB_WHT)$(CT_BLK)
C_CLN_VA	=	$(CT_YEL)
C_LNK_MS	=	$(CB_YEL)$(CT_BLK)
C_LNK_V1	=	$(CT_RED)
C_LNK_V2	=	$(CT_BLU)
C_FIN_MS	=	$(CB_GRN)$(CT_BLK)
C_FIN_VA	=	$(CT_MAG)

ifeq ($(_USER),prossi)
_MSG = echo "${CB_RED}${CT_YEL} Hmm, something doesn't seem right... ${CAL_RST}"; sleep 1;
_2SG = osascript -e 'tell application (path to frontmost application as text) to display dialog "Shutting Down..." buttons "Stop Shutdown" with icon stop'; osascript -e "set volume output volume 40"; say "Hi there Pasquale"
else
_MSG = echo "${CB_YEL}${CT_CYN} CHECKING ACCESS... ${CAL_RST}"
_2SG = echo "${CB_GRN} Approved $(_USER) ${CAL_RST}"
endif

#				Progress Bar
ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
	-nrRf $(firstword $(MAKEFILE_LIST)) \
	ECHO="COUNTTHIS" | grep -c "COUNTTHIS")
N := x
C = $(words $N)$(eval N := x $N)
ECHO = echo "`expr " [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]${CAL_RST}"
endif

#				Directories, Files, Flags and Utilities
SRC_DIR		=	./srcs
HDR_DIR		=	./headers
BUILD_DIR	=	./build
ARCH_DIR	=	./archives
REPO_DIR	=	./extra

PRINTF		=	$(REPO_DIR)/printf/
MLX			=	$(REPO_DIR)/mlx/
GNL			=	$(REPO_DIR)/gnl/

GNL_FLAGS	=	-D BUFFER_SIZE=42
GNL_SOURCES	=	$(GNL)get_next_line.c
GNL_OBJECTS	=	$(GNL_SOURCES:$(GNL)%.$(SOURCE_EXT)=$(GNL)%.o)
GNLIB		=	gnl.a

SOURCES		=	$(shell find $(SRC_DIR) -name '*.$(SOURCE_EXT)')
OBJECTS		=	$(SOURCES:$(SRC_DIR)/%.$(SOURCE_EXT)=$(BUILD_DIR)/%.o)
DEPS		=	$(OBJECTS:.o=.d)
ARCHIVES	=	$(ARCH_DIR)/*.$(ARCHIVE_EXT)
REPOS		=	$(REPO_DIR)

ifeq ($(UNAME), Linux)
MLX_FLAGS = -L/usr/lib -Imlx -lXext -lX11 -lm -lz
else
MLX_FLAGS = -Imlx -Lmlx -lmlx -framework OpenGL -framework AppKit
endif

CFLAGS		+=	-$(COMP_STD) $(COMP_FLAGS)
LDFLAGS		+=	$(MLX_FLAGS)
INCLUDES	=	-I $(HDR_DIR)

CLEAN_LST	=	$(NAME) $(BUILD_DIR)

RM			=	rm -rf
MKDIR		=	mkdir -p

# 				 Start Rules
# Default rule to make the program
all: $(NAME)
	@echo ""
	@$(_MSG)
	@$(_2SG)

# Makes the build directory, links the object files to the program
$(NAME): $(REPOS) $(OBJECTS)
	@$(ECHO) "${C_FIN_MS}    Ready       ${CAL_RST}	${C_FIN_VA}$@${CAL_RST}"
	@$(MKDIR) $(BUILD_DIR)
	@$(COMPILER) $(OBJECTS) $(ARCHIVES) $(LDFLAGS) $(GNL_SOURCES) $(GNL_FLAGS) -o $@

$(GNL)/%.o : $(SRC_DIR)/%.$(SOURCE_EXT)
	@$(ECHO) "${C_LNK_MS}    Linking     ${CAL_RST}	${C_LNK_V1}$< ${CAL_RST}${CT_WHT}to ${CAL_RST}${C_LNK_V2}$@ ${CAL_RST}"
	@$(MKDIR) $(@D)
	@$(COMPILER) $(CFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

$(REPOS): $(PRINTF) $(MLX) $(GNL)

$(GNL):
	@printf "get_next_line dependency needed. Download now? [y/N]"
	@read ans && [ $${ans:-N} = y ]
	@git clone https://github.com/t0mmusic/get_next_line.git $(GNL)
	@cp -r $(GNL)get_next_line_bonus.h $(HDR_DIR)


$(PRINTF):
	@printf "printf dependency needed. Download now? [y/N]"
	@read ans && [ $${ans:-N} = y ]
	@git clone https://github.com/t0mmusic/ft_printf.git $(PRINTF)
	@if [ -d "$(PRINTF)" ]; then\
		$(MAKE) bonus -C $(PRINTF) --no-print-directory; \
		cp -r $(PRINTF)$(ARCH_DIR)/. $(ARCH_DIR); \
		cp -r $(PRINTF)$(HDR_DIR)/. $(HDR_DIR); \
	fi

$(MLX):
	@printf "mlx dependency needed. Download now? [y/N]"
	@read ans && [ $${ans:-N} = y ]
	@if [ $(UNAME) != Linux ]; then \
		git clone https://github.com/dannywillems/minilibx-mac-osx.git $(MLX); \
		cp -r $(MLX)mlx.h $(HDR_DIR); \
		cp -r $(MLX)libmlx.a $(ARCH_DIR); \
	else \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX); \
		cd $(MLX) && bash configure >/dev/null;\
		cd ../..; \
		cp -r $(MLX)mlx.h $(HDR_DIR); \
		cp -r $(MLX)libmlx_Linux.a $(ARCH_DIR); \
	fi

# Removes files and folders listed in clean_list
c clean:
	@$(ECHO) "${C_CLN_MS}    Cleaning    ${CAL_RST}	${C_CLN_VA}$(CLEAN_LST)${CAL_RST}"
	@$(RM) $(CLEAN_LST)

# Removes files and folders listed in clean_list and clears the command window
cc:
	@clear
	@$(ECHO) "${C_CLN_MS}    Cleaning    ${CAL_RST}	${C_CLN_VA}$(CLEAN_LST)${CAL_RST}"
	@$(RM) $(CLEAN_LST)

# Cleans all files and remakes them
r re: c all

# Uses apple's leaks utility (/usr/bin) to check for leaks upon exit
m mem: all
	@leaks --atExit -- ./$(NAME) > leak_out.txt || true
	@grep -E '(Process) [0-9]{1,}: [0-9]{1,} (leaks)' leak_out.txt
	@grep -E '(ROOT LEAK): <' leak_out.txt || true
	@rm leak_out.txt

# Include the dependancies into the compiler so all files can be built
-include $(DEPS)

# Builds the object files from the source directory using the header files and
# 	dependacies, ie: source/main.cpp is linked to object file build/main.o
# From that, the $(NAME) rule can determine all the function definitions inside
# 	each object file
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.$(SOURCE_EXT)
	@$(ECHO) "${C_LNK_MS}    Linking     ${CAL_RST}	${C_LNK_V1}$< ${CAL_RST}${CT_WHT}to ${CAL_RST}${C_LNK_V2}$@ ${CAL_RST}"
	@$(MKDIR) $(@D)
	@$(COMPILER) $(CFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@