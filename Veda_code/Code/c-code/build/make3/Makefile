###############################################################################################
# This makefile demonstrates the creation of a simple makefile with multiple targets          #
# and usage of macros                                                                         #
# Team	 : Veda                                                                               #
# Version: 1.0										      ################################################################################################

# which compiler
CC=gcc

# where to install
INSTALL_PATH=/root

# name of the application
TAR_NAME=app

# path of the source files
SRC_DIR=.

# present working directory
CUR_DIR=.

# target=app(creating the application)
$(TAR_NAME): ui.c gifhandler.o handlers.h
	$(CC) -o $(TAR_NAME) $(SRC_DIR)/ui.c $(CUR_DIR)/gifhandler.o
	@echo "Application Created Succesfully"

# target=clean(removing the existing one)
clean:
	rm -f $(CUR_DIR)/gifhandler.o $(CUR_DIR)/$(TAR_NAME) $(INSTALL_PATH)/$(TAR_NAME)
	@echo "Application Removed Succesfully"

# target=creation of gifhandler.o
gifhandler.o:
	$(CC) -c $(SRC_DIR)/gifhandler.c
	@echo "gifhandler.o created succesully"

# target = installing the application where we want to install
install: $(TAR_NAME)
	cp -f $(CUR_DIR)/$(TAR_NAME) $(INSTALL_PATH)/$(TAR_NAME)	
	@echo "Application Installed Succesfully at $(INSTALL_PATH)"
