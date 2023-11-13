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
SRCDIR = src
OBJDIR = obj
DEPDIR = dep
EXEDIR = bin

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=$(DEPDIR)/%.d)
# UNIX-based OS variables & settings
RM = rm
MKDIR_P = mkdir -p
# Windows OS variables & settings
DEL = rm
WMKDIR = mkdir

EXE = 
DELOBJ = $(wildcard $(OBJDIR)/*.o)
DELDEP = $(wildcard $(DEPDIR)/*.d)
DELEXE = $(wildcard $(EXEDIR)/*$(EXE))

########################################################################
####################### Targets beginning here #########################
########################################################################
# Builds the app
all: color_constancy image_enhancement

# Creates the dependecy rules
$(DEPDIR)/%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:$(DEPDIR)/%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<
# .PHONY: all

color_constancy: $(OBJ)
	$(eval TMP_OBJ := $(filter-out $(wildcard $(OBJDIR)/main_*.o), $(OBJ)) $(OBJDIR)/main_color_constancy.o)
	$(CC) $(CXXFLAGS) -o $(EXEDIR)/main_color_constancy $(TMP_OBJ) $(LDFLAGS)

image_enhancement: $(OBJ)
	$(eval TMP_OBJ := $(filter-out $(wildcard $(OBJDIR)/main_*.o), $(OBJ)) $(OBJDIR)/main_image_enhancement.o)
	$(CC) $(CXXFLAGS) -o $(EXEDIR)/main_image_enhancement $(TMP_OBJ) $(LDFLAGS)

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DELDEP) $(DELEXE)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

####################### Establishing directory for Unix-based OS #########################
.PHONY: dir
dir: 
	$(MKDIR_P) $(OBJDIR) $(DEPDIR) $(EXEDIR)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(DELOBJ) $(DELDEP) $(DELEXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)

####################### Establishing directory for Windows OS #########################
.PHONY: dirw
dirw: 
	$(WMKDIR) $(OBJDIR),$(DEPDIR),$(EXEDIR)