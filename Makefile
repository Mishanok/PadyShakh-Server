#Compiler and Linker
export CC          := g++

#The Target Binary Program
TARGET             := PadyShakh_server_main

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR             := src
LOG_DIR            := var
export BUILDDIR    := $(shell pwd)/obj
export TARGETDIR   := bin
export OBJEXT      := o

#Flags, Libraries and Includes
export CFLAGS      := -fopenmp -g -c
export LIB         := -fopenmp -lm -Wall
export INCLUDE     := -I$(shell pwd)/$(SRCDIR)

SOURCES            := main config-manager
OBJECTS            := $(patsubst %,$(BUILDDIR)/%.$(OBJEXT),$(SOURCES))

#Defauilt Make
all: resources $(TARGET)

#Remake
remake: cleaner all

#Copy Resources from Resources Directory to Target Directory
resources: directories
	@echo $(OBJECTS)

#Make the Directories
directories: clean
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(LOG_DIR)

#Clean only Objecst
clean:
	@$(RM) -rf $(BUILDDIR)

#Full Clean, Objects and Binaries
cleaner: clean
	@$(RM) -rf $(TARGETDIR)

#Link
$(TARGET): $(OBJECTS)
	$(CC) $(LIB) -o $(TARGETDIR)/$@ $^
	@echo Bin is ready!

#Compile
$(BUILDDIR)/%.$(OBJEXT):# $(SRCDIR)/*/%.cpp $(SRCDIR)/*/%.h
	@$(MAKE) -C $(SRCDIR)/$*

#Non-File Targets
.PHONY: all remake clean cleaner resources
