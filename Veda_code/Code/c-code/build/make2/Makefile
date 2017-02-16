###############################################################################################
# This makefile demonstrates the creation of a simple makefile with multiple targets          #
# Team	 : Veda                                                                               #
# Version: 1.0										      ################################################################################################


# The makefiles creation consists of creating the targets and the rules for achieving the
# targets. The syntax of creating the targets and rules are as follows
# <target-name>: <dependencies>
#	<rules for creating the target> 

# if we don't want to display the background of makefile, we need to simply add "@" before the # command in the makefile.

# target=app(creating the application)
app: ui.c gifhandler.o handlers.h
	gcc -o app ui.c gifhandler.o
	@echo "Application Created Succesfully"

# target=clean(removing the existing one)
clean:
	rm gifhandler.o app
	@echo "Application Removed Succesfully"

# target=creation of gifhandler.o
gifhandler.o:
	gcc -c gifhandler.c
	@echo "gifhandler.o created succesully"
