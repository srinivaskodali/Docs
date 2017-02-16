
MAKEFLAGS = -rR --no-print-directory
MAKEFLAGS += --include-dir=$(PWD)


.PHONY : all clean

all  : $(PWD)/Script_Obj $(PWD)/Script_Dir one

$(PWD)/Script_Obj : ;
include $(PWD)/Script_Obj

$(PWD)/Script_Dir : ;
include $(PWD)/Script_Dir

one:
	@for dir in $(SUBDIRS); do \
		$(MAKE) --directory=$$dir;  \
	done
clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) --directory=$$dir clean;\
	done


