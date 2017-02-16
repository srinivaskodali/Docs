###############################################################################################
# This makefile demonstrates checking of the dependencies and also the usage of multiple      #
# makefiles in a makefile.                                                                    #
# Team	 : Veda                                                                               #
# Version: 1.0										      #################################################################################################	

# target name 
TAR_NAME=app

# which compiler
CC=gcc

# root path 
C_PATH=.

# location for installing the application
INSTALL_PATH=/root

# default target
all:    ui.c handlers.h  
	@echo "Checking for the dependancy "gifhandler.o" .........." 
	@if test -e $(C_PATH)/gif/gifhandler.o; then echo "Dependancy Found: [True]"; $(MAKE) -s $(TAR_NAME); \
		else echo "Dependancy Found: [False]"; echo "Creating the Dependancy..."; $(MAKE) -s gifhandler.o; echo "Dependancy Created Succesfully"; $(MAKE) -s $(TAR_NAME); \
	fi
	

# making the target
$(TAR_NAME): 
	gcc -o $(TAR_NAME) ui.c $(C_PATH)/gif/gifhandler.o
	@echo "Application Created Succesfully"

# removing the existing one
clean:	
	@-rm -f $(TAR_NAME) $(INSTALL_PATH)/$(TAR_NAME)
	@(cd $(C_PATH)/gif; $(MAKE) -s clean) 
	@echo "Application Removed Succesfully"

# install the application
install:
	@echo "Checking for the existence of application "$(TAR_NAME)"....."
	@if test -e $(C_PATH)/$(TAR_NAME); then echo "Application found: [TRUE]"; cp -rf $(C_PATH)/$(TAR_NAME) $(INSTALL_PATH)/; $(MAKE) -s call; \
		else echo "Application found: [FALSE]"; echo "Creating the application $(TAR_NAME"; $(MAKE) -s all; $(MAKE) -s install; \
	fi

# calling the dependencies 
gifhandler.o: handlers.h
	(cd $(C_PATH)/gif;$(MAKE) -s )

call:
	@echo "Application Installled Succesfully"; 
