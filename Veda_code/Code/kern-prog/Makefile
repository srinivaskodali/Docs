
#MAKEFLAGS = -rR --no-print-directory
MAKEFLAGS += --include-dir=$(PWD)


.PHONY : all clean

all  : $(PWD)/Script_Dir $(PWD)/Script_Obj one

$(PWD)/Script_Dir : ;
include $(PWD)/Script_Dir

$(PWD)/Script_Obj : ;
include $(PWD)/Script_Obj


one:
	@for dir in $(SUBDIRS); do \
		$(MAKE) --directory=$$dir;  \
	done
clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) --directory=$$dir clean;\
	done


