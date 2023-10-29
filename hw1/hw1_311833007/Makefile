########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = 

# Makefile settings - Can be customized.
APPNAME = main
EXT = .cpp
SRCDIR = .
OBJDIR = obj
DEPDIR = dep
EXEDIR = bin

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=$(DEPDIR)/%.d)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)
# Windows OS variables & settings
DEL = rm
EXE = .exe
MKDIR_P = mkdir -p
WDELOBJ = $(wildcard $(OBJDIR)/*.o)
WDELDEP = $(wildcard $(DEPDIR)/*.d)
WDELEXE = $(wildcard $(EXEDIR)/*$(EXE))

########################################################################
####################### Targets beginning here #########################
########################################################################
# Builds the app
all: scaling quan flip

scaling: $(OBJ)
	$(eval TMP_OBJ := $(filter-out $(wildcard $(OBJDIR)/main_*.o), $(OBJ)) $(OBJDIR)/main_scaling.o)
	$(CC) $(CXXFLAGS) -o $(EXEDIR)/main_scaling $(TMP_OBJ) $(LDFLAGS)

quan: $(OBJ)
	$(eval TMP_OBJ := $(filter-out $(wildcard $(OBJDIR)/main_*.o), $(OBJ)) $(OBJDIR)/main_quan.o)
	$(CC) $(CXXFLAGS) -o $(EXEDIR)/main_quan $(TMP_OBJ) $(LDFLAGS)

flip: $(OBJ)
	$(eval TMP_OBJ := $(filter-out $(wildcard $(OBJDIR)/main_*.o), $(OBJ)) $(OBJDIR)/main_flip.o)
	$(CC) $(CXXFLAGS) -o $(EXEDIR)/main_flip $(TMP_OBJ) $(LDFLAGS)

# Creates the dependecy rules
$(DEPDIR)/%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:$(DEPDIR)/%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(WDELDEP) $(WDELEXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)

####################### Establishing directory #########################
.PHONY: directories
directories: $(OBJDIR) $(DEPDIR) $(EXEDIR)

$(OBJDIR):
	$(MKDIR_P) $(OBJDIR)

$(DEPDIR):
	$(MKDIR_P) $(DEPDIR)

$(EXEDIR):
	$(MKDIR_P) $(EXEDIR)