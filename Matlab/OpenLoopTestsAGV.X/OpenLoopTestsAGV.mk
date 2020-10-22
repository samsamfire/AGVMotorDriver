#
# File: MCHP_dsPIC.tmf
#
#--------------------------------------------------------------
#   Embedded Coder for Microchip dsPIC30/dsPIC33/PIC24 family. |
#   Generate .c and .h files from your Matlab/simulink model   |
#   and compile the diagram to .hex / .elf or .coff file that  |
#   can be downloaded directly into the microcontroller        |
#                                                              |
#      The Microchip name PIC, dsPIC, and MPLAB are            |
#      registered trademarks of Microchip Technology Inc.      |
#      MATLAB, Simulink, and Real-Time Workshop are            |
#      registered trademarks of The MathWorks, Inc.            |
#                                                              |
#--------------------------------------------------------------
#------------------------ Macros read by make_rtw ------------------------------
MAKECMD          = "D:/Programs/Matlab/bin/win64/gmake"
SHELL            = cmd
#HOST             = PC
HOST            = ANY
BUILD            = yes
BUILD_SUCCESS    = +++ Created
SYS_TARGET_FILE  = MCHP_dsPIC_stf.tlc
MAKEFILE_FILESEP = /
#---------------------- Tokens expanded by make_rtw ----------------------------
#
# The following tokens, when wrapped with "|>" and "<|" are expanded by the
# Real-Time Workshop build procedure.
#
MODEL                   = OpenLoopTestsAGV
MODULES                 = MCHP_ADC1_Interrupt.c MCHP_UART1_Rx_Interrupt.c MCHP_UART1_Tx.Interrupt.c OpenLoopTestsAGV_data.c OpenLoopTestsAGV_main.c fonctionsAGV.c can1.c ecan1.c dma.c
#MODULES_OBJ            = MCHP_ADC1_Interrupt.obj MCHP_UART1_Rx_Interrupt.obj MCHP_UART1_Tx.Interrupt.obj OpenLoopTestsAGV_data.obj OpenLoopTestsAGV_main.obj fonctionsAGV.obj can1.obj ecan1.obj dma.obj 
MAKEFILE                = OpenLoopTestsAGV.mk
MATLAB_ROOT             = D:/Programs/Matlab
ALT_MATLAB_ROOT         = D:/Programs/Matlab
MASTER_ANCHOR_DIR       = 
START_DIR               = D:/Projet_Smart_Factory/AGV_Driver/Matlab
S_FUNCTIONS             = 
S_FUNCTIONS_LIB         = 
NUMST                   = 6
NCSTATES                = 0
COMPUTER                = PCWIN64
BUILDARGS               =  GENERATE_ASAP2=0 MCHP_AUTO_FLASH=1 MCHP_MULTITHREAD_COMPILATION=1 LinkWithMaster=0 ISPROTECTINGMODEL=NOTPROTECTING OPTS="-mdfp=D:\Programs\Microchip\mplabx\packs\Microchip\dsPIC33E-GM-GP-MC-GU-MU_DFP\1.2.58\xc16"
MULTITASKING            = 1
INTEGER_CODE            = 0
MAT_FILE                = 0
ONESTEPFCN              = 1
TERMFCN                 = 0
B_ERTSFCN               = 0
MEXEXT                  = mexw64
EXT_MODE                = 0
TMW_EXTMODE_TESTING     = 0
EXTMODE_TRANSPORT       = 0
EXTMODE_STATIC          = 0
EXTMODE_STATIC_SIZE     = 500
MULTI_INSTANCE_CODE     = 0
TGT_FCN_LIB             = None
SHARED_SRC              = 
SHARED_SRC_DIR          = 
SHARED_BIN_DIR          = 
SHARED_LIB              = 
GEN_SAMPLE_MAIN         = 0
TARGET_LANG_EXT         = c
PORTABLE_WORDSIZES      = 0
SHRLIBTARGET            = 0
OPTIMIZATION_FLAGS      = 
ADDITIONAL_LDFLAGS      =  -mdfp=D:\Programs\Microchip\mplabx\packs\Microchip\dsPIC33E-GM-GP-MC-GU-MU_DFP\1.2.58\xc16
MAKEFILEBUILDER_TGT     = 0
STANDALONE_SUPPRESS_EXE = 0

#--------------------------- Model and reference models -----------------------
MODELREFS                 = 
MODELLIB                  = 
MODELREF_LINK_LIBS        = 
MODELREF_LINK_RSPFILE     = OpenLoopTestsAGV_ref.rsp
MODELREF_INC_PATH         = 
# warning: .. is different from MAtlab 2013a version (pointing to a folder beyong)
RELATIVE_PATH_TO_ANCHOR   = ..
MODELREF_TARGET_TYPE       = NONE



#-- In the case when directory name contains space ---
ifneq ($(MATLAB_ROOT),$(ALT_MATLAB_ROOT))
	MATLAB_ROOT := $(ALT_MATLAB_ROOT)
endif
# if MATLAB_ROOT has space (for system with no 8.3 compatibility mode, then any requirement of code from the matlab folder will fail to compile. That is the case for PIL or External Mode for ex.)


#-----------------------------  tool specification settings -----------------

AssemblyListing = 0
ProduceHexOutput = 1

GCC1    = xc16-gcc.exe
AR1     = xc16-ar
BIN2HEX1 = xc16-bin2hex
OBJDUMP1 = xc16-objdump

GCCPATH	= C:/PROGRA~1/MICROC~1/xc16/v1.60/bin
ifeq ($(strip $(GCCPATH)),)
	CC   = $(GCC1)
	CPP  = $(GCC1)
	LD   = $(GCC1)
	AR   = $(AR1) -r -omf=$(OMF)
	BIN2HEX = $(BIN2HEX1)
	OBJDUMP = $(OBJDUMP1)	
else
	CC   = "$(GCCPATH)/$(GCC1)"
	CPP  = "$(GCCPATH)/$(GCC1)"
	LD   = "$(GCCPATH)/$(GCC1)"
	AR   = "$(GCCPATH)/$(AR1)" -r -omf=$(OMF)
	BIN2HEX = "$(GCCPATH)/$(BIN2HEX1)"
	OBJDUMP = "$(GCCPATH)/$(OBJDUMP1)"		
endif

# slave1_image
SECONDARYIMAGE = 

# ifeq ($(HOST),PC)
DEL = del /Q
# else
# DEL = rm -rf
# endif

#------------------------------ Others dsPIC blockset parameters --------------
EXTMODE_DATA_UPLOAD = 0
OMF   	        = elf

OPTIM_GCC 		=  -O1 -mno-eds-warn -msmall-data
LDFLAGS 		= -t,--report-mem,-Map=info.map,-cref,-lq-dsp,--memorysummary,memoryfile.xml
LINKER_SCRIPT 	= "p33EP256MC502.gld"
PIC_LIB 		= 
PIC_INCLUDES 	= 
PIC_REF 		= 33EP256MC502

#-- always add one space just before -Xlinker solve possible ambiguity while using -Wl flag. Solve problem when LDFLAGS starts with -Xlinker (old style)
LDFLAGS := $(subst -Xlinker, -Xlinker,$(LDFLAGS))


MCPU  			   = -mcpu=$(PIC_REF)
PROGRAM_FILE_EXT   = .$(subst coff,cof,$(OMF))

T_LINKER_SCRIPT = -omf=$(OMF) -Wl,--script=$(LINKER_SCRIPT)

LDLIBPIC = $(PIC_LIB)


CC_OPTS 		= $(MCPU) -omf=$(OMF) $(OPTIM_GCC) $(OPTS)

ifeq ($(INTEGER_CODE),1)
	CC_OPTS 		+= -DINTEGER_CODE=1
endif

OBJ_EXT =.o
CCOUTPUTFLAG = -o

#----------------------------- External mode -----------------------------------
# added OPTS: from make file call, define MemUnit_T=uint8_T and MEM_UNIT_BYTES=, usefull for PIL or external mode
# EXTMODE_DISABLESIGNALMONITORING EXTMODE_DISABLE_ARGS_PROCESSING  MULTITASKING
# -DEXTMODE_DISABLESIGNALMONITORING=1

ifeq ($(EXT_MODE),1)
	#---Compiler and Linker settings---
	ifeq ($(MULTITASKING),1)
		LDFLAGS += -Wl,--wrap,_SetParam
	endif

	CC_OPTS += -DEXT_MODE=1 -DMODEL=$(MODEL) -DNUMST=$(NUMST)  -DEXTMODE_DISABLEPRINTF=1 -DEXTMODE_DISABLE_ARGS_PROCESSING=1
	ifeq ($(EXTMODE_DATA_UPLOAD),0)
		CC_OPTS 		+= -DEXTMODE_DISABLESIGNALMONITORING=1
	endif

	#---required files---

	#external mode sources
	EXT_SRC  = ext_svr.c updown.c ext_work.c rtiostream_interface.c

	# static memory management (optional)
	ifeq ($(EXTMODE_STATIC),1)
	  EXT_SRC += mem_mgr.c
	  CC_OPTS +=  -DEXTMODE_STATIC=1 -DEXTMODE_STATIC_SIZE=$(EXTMODE_STATIC_SIZE)
	endif

endif

#------------------------------ parameter controlled from simulink ----------------



# Keep following line, help the Matlab programming tool to find the programmer.
# Additional info : PICREF{33EP256MC502} PROGRAMMER{}

#------------------------------ Include Path -----------------------------------
#
MATLAB_INCLUDES = \
	-I"$(MATLAB_ROOT)/rtw/c/ert" \
	-I"$(MATLAB_ROOT)/extern/include" \
	-I"$(MATLAB_ROOT)/simulink/include" \
	-I"$(MATLAB_ROOT)/rtw/c/src" \
	-I"$(MATLAB_ROOT)/rtw/c/src/ext_mode/common"

# Additional includes
#
ADD_INCLUDES = \
	-I"$(START_DIR)" \
	-I"$(START_DIR)/OpenLoopTestsAGV.X" \
	-I"$(START_DIR)/Mplab_generated_code/ECAN1" \
	-I"$(MATLAB_ROOT)/extern/include" \
	-I"$(MATLAB_ROOT)/simulink/include" \
	-I"$(MATLAB_ROOT)/rtw/c/src" \
	-I"$(MATLAB_ROOT)/rtw/c/src/ext_mode/common" \
	-I"$(MATLAB_ROOT)/rtw/c/ert" \



SHARED_INCLUDES =
ifneq ($(SHARED_SRC_DIR),)
SHARED_INCLUDES = -I"$(SHARED_SRC_DIR)"
endif

INCLUDES = -I. -I"$(RELATIVE_PATH_TO_ANCHOR)" $(MATLAB_INCLUDES) $(ADD_INCLUDES) \
			 $(PIC_INCLUDES) $(MODELREF_INC_PATH) \
			 $(SHARED_INCLUDES)

#-------------------------------- C Flags --------------------------------------
# General User Options

# New : to support Continuous States ? find in "Upgrading from V3.2.1 or V3.2"
CPP_REQ_DEFINES = -DMODEL=$(MODEL) -DNUMST=$(NUMST) -DNCSTATES=$(NCSTATES) \
		  -DMAT_FILE=$(MAT_FILE) -DINTEGER_CODE=$(INTEGER_CODE) \
		  -DONESTEPFCN=$(ONESTEPFCN) -DTERMFCN=$(TERMFCN) \
		  -DHAVESTDIO -DMULTI_INSTANCE_CODE=$(MULTI_INSTANCE_CODE) \
		  -DCLASSIC_INTERFACE=$(CLASSIC_INTERFACE)\
		  -DADD_MDL_NAME_TO_GLOBALS=$(ADD_MDL_NAME_TO_GLOBALS)

CFLAGS    =$(CC_OPTS)  $(INCLUDES)
CPPFLAGS = $(CC_OPTS)  $(INCLUDES)

LIBS =










#-------------------------------- Target application --------------------------------------
# Define the target file

ifeq ($(MODELREF_TARGET_TYPE), NONE)
	ifeq ($(MAKEFILEBUILDER_TGT), 0)
		ifeq ($(STANDALONE_SUPPRESS_EXE), 1)
			# Build object code only for top level model (preliminary step for building
			# PIL application)		
			BUILD_MODE=pil_prebuild
			PRODUCT=ObjectModules			
			BUILD_PRODUCT_TYPE = object modules

			# BUILD_MODE= pil_prebuild
			# PRODUCT = $(MODELLIB)
			# BUILD_PRODUCT_TYPE = library		

		else
			# Building executable for real-time deployment
			BUILD_MODE=real_time
			# remove MODELLIB from linker
			# MODELLIB =
			PRODUCT = $(MODEL)$(PROGRAM_FILE_EXT)
			BUILD_PRODUCT_TYPE = executable
		endif
	else
		# Building executable for deployment as PIL application (non-real-time
		# simulation)
		BUILD_MODE= pil_application
		PRODUCT = $(MODEL)$(PROGRAM_FILE_EXT)
		BUILD_PRODUCT_TYPE = executable
	endif
else
	# Building a library for a referenced model
	BUILD_MODE = model_reference
	PRODUCT = $(MODELLIB)
	BUILD_PRODUCT_TYPE = library
endif

#----------------------------- Source Files ------------------------------------

# add assembly source file from root folder, generated by Code Replacement Library and others
#ASM_OPTIM_SRCS = 
#
#ASM_OPTIM_SRCS += $(wildcard $(START_DIR)/*.s) 
#ASM_OPTIM_SRCS += $(wildcard $(START_DIR)/OpenLoopTestsAGV.X/*.s) 
#ASM_OPTIM_SRCS += $(wildcard $(START_DIR)/Mplab_generated_code/ECAN1/*.s) 
#ASM_OPTIM_SRCS += $(wildcard $(MATLAB_ROOT)/extern/include/*.s) 
#ASM_OPTIM_SRCS += $(wildcard $(MATLAB_ROOT)/simulink/include/*.s) 
#ASM_OPTIM_SRCS += $(wildcard $(MATLAB_ROOT)/rtw/c/src/*.s) 
#ASM_OPTIM_SRCS += $(wildcard $(MATLAB_ROOT)/rtw/c/src/ext_mode/common/*.s) 
#ASM_OPTIM_SRCS += $(wildcard $(MATLAB_ROOT)/rtw/c/ert/*.s) 

#ASM_OPTIM_SRCS = $(wildcard *.s)
#    # for instrumented code
#ASM_OPTIM_SRCS = $(wildcard ../*.s) 

SRCS = $(S_FUNCTIONS)
#SRCS += $(ASM_OPTIM_SRCS)

ifeq ($(BUILD_MODE), pil_prebuild)
  SRCS += $(MODULES) $(MODEL).$(TARGET_LANG_EXT) $(EXT_SRC)
endif

ifeq ($(BUILD_MODE), pil_application)
  SRCS += $(TARGET_SRCS)
  PREBUILT_SRCS      = $(MODULES)
  PREBUILT_OBJS      = $(addsuffix $(OBJ_EXT), $(basename $(PREBUILT_SRCS)))
endif

ifeq ($(BUILD_MODE), real_time)
  SRCS += $(MODULES) $(MODEL).$(TARGET_LANG_EXT) $(EXT_SRC)
  SRCS += $(TARGET_SRCS)
endif

ifeq ($(BUILD_MODE), model_reference)
  SRCS += $(MODULES)
endif

USER_SRCS =
USER_OBJS       = $(addsuffix $(OBJ_EXT), $(basename $(USER_SRCS)))
LOCAL_USER_OBJS = $(notdir $(USER_OBJS))

OBJS      = $(addsuffix $(OBJ_EXT), $(basename $(SRCS))) $(USER_OBJS)
LINK_OBJS = $(addsuffix $(OBJ_EXT), $(basename $(SRCS))) $(LOCAL_USER_OBJS) $(PREBUILT_OBJS)

LIBS += $(S_FUNCTIONS_LIB)

#wildcard does not support slash, must be replaced with backslash at least for SHARED_SRC
SHARED_SRC := $(subst \,/,$(SHARED_SRC))
#SHARED_SRC_DIR := $(subst \,/,$(SHARED_SRC_DIR))
#SHARED_BIN_DIR := $(subst \,/,$(SHARED_BIN_DIR))
#SHARED_LIB := $(subst \,/,$(SHARED_LIB))

SHARED_SRC := $(wildcard $(SHARED_SRC))
SHARED_OBJS = $(addsuffix $(OBJ_EXT), $(basename $(SHARED_SRC)))

#-------------- Default target -----------
TARGETS = $(PRODUCT)

all: $(TARGETS)

# Need a rule to generate the build success string if product was already up to date
.PHONY : all
all : $(PRODUCT)
	-@echo ### Created $(PRODUCT) successfully (or it was already up to date)

#----------------------------- Dependencies ------------------------------------

$(OBJS) : $(MAKEFILE) rtw_proj.tmw

$(SHARED_LIB) : $(SHARED_OBJS)
	-@echo ### Creating $@
	$(AR) $@ $(SHARED_OBJS)
	-@echo ### $@ Created



##-------------------------- Support for building modules ----------------------
ifeq ($(BUILD_MODE), pil_prebuild)
$(PRODUCT) : $(OBJS) $(SHARED_LIB)
	-@echo ### BUILD_MODE $(BUILD_MODE)
	-@echo ### Created $(PRODUCT)
endif


ifeq ($(BUILD_MODE), model_reference)
$(PRODUCT) : $(OBJS) $(SHARED_LIB) $(LIBS)
	-@echo ### BUILD_MODE $(BUILD_MODE)
	-@echo ### Creating library ...
	$(AR) $(PRODUCT) $(OBJS)
	-@echo "$(BUILD_SUCCESS) $(BUILD_PRODUCT_TYPE): $@"
endif


ifeq ($(BUILD_MODE), pil_application)
$(PRODUCT) : $(PREBUILT_OBJS) $(OBJS) $(MODELLIB) $(MODELREF_LINK_LIBS) $(SHARED_LIB) $(LIBS)
	-@echo ### BUILD_MODE $(BUILD_MODE)
	$(LD) $(MCPU) $^ $(LDLIBPIC) -o $(MODEL)$(PROGRAM_FILE_EXT) $(T_LINKER_SCRIPT),$(LDFLAGS)
	-@echo "$(BUILD_SUCCESS) $(BUILD_PRODUCT_TYPE): $@  [$(PIC_REF)]"
ifeq ($(ProduceHexOutput),1)
	$(BIN2HEX) -omf=$(OMF) $(PRODUCT)
	-@echo "+++ Converted $(MODEL)$(PROGRAM_FILE_EXT) to $(MODEL).hex"
endif
ifeq ($(AssemblyListing),1)
	$(OBJDUMP) -omf=$(OMF) -S -f -Msymbolic $(PRODUCT) > $(MODEL).lst
		-@echo "+++ Created Assembly list file $(MODEL).lst"
endif
endif

ifeq ($(BUILD_MODE), real_time)
#$(MODEL)$(PROGRAM_FILE_EXT) : $(OBJS) $(MODELREF_LINK_LIBS) $(SHARED_LIB) $(LIBS)
$(PRODUCT) : $(OBJS) $(MODELREF_LINK_LIBS) $(SHARED_LIB) $(LIBS)
	-@echo ### BUILD_MODE $(BUILD_MODE)
	$(LD) $(MCPU) $(LINK_OBJS) $(MODELREF_LINK_LIBS) $(SHARED_LIB) $(LIBS) $(SYSLIBS) $(LDLIBPIC) -o $(MODEL)$(PROGRAM_FILE_EXT) $(T_LINKER_SCRIPT),$(LDFLAGS)
	-@echo $(BUILD_SUCCESS) $(BUILD_PRODUCT_TYPE): $@
ifeq ($(ProduceHexOutput),1)
	$(BIN2HEX) -omf=$(OMF) $(PRODUCT)
	-@echo "+++ Converted $(PRODUCT) to $(MODEL).hex"
endif
ifeq ($(AssemblyListing),1)
	$(OBJDUMP) -omf=$(OMF) -S -f -Msymbolic $(PRODUCT) > $(MODEL).lst
		-@echo "+++ Created Assembly list file $(MODEL).lst"
endif
ifneq ($(strip $(SECONDARYIMAGE)),)
	-@echo ### Write secondary core Image and header to integrate in Main core project.
ifeq (,$(wildcard $(SECONDARYIMAGE)/.*))
	mkdir $(SECONDARYIMAGE)
endif
ifneq (,$(wildcard Secondary_FuseConfig.h))
	copy /Y Secondary_FuseConfig.h $(SECONDARYIMAGE)
endif
	$(BIN2HEX) $(PRODUCT) --image $(SECONDARYIMAGE)/$(SECONDARYIMAGE)
	-@echo "+++ Created secondary core Image $(SECONDARYIMAGE).s and $(SECONDARYIMAGE).h header definition file"
endif
endif



ifeq ($(OMF),elf)
ifeq (,$(wildcard $(MODEL).cof))	# if file exist
else
	$(DEL) $(MODEL).cof
endif
endif

ifeq ($(OMF),coff)
ifeq (,$(wildcard $(MODEL).elf))		# if file exist
else
	$(DEL) $(MODEL).elf
endif
endif

ifeq ($(ProduceHexOutput),0)
ifeq (,$(wildcard $(MODEL).hex))	# if file exist
else
	$(DEL) $(MODEL).hex
endif
endif

ifeq ($(AssemblyListing),0)
ifeq (,$(wildcard $(MODEL).lst))		# if file exist
else
	$(DEL) $(MODEL).lst
endif
endif



mem_mgr.o : $(MATLAB_ROOT)/rtw/c/src/ext_mode/common/mem_mgr.c
	$(CC) -c -fno-strict-aliasing $(CFLAGS) $< $(CCOUTPUTFLAG) $@

%$(OBJ_EXT) : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	-@echo Compiling: $<
	$(CC) -c $(CFLAGS) $< $(CCOUTPUTFLAG) $@

%$(OBJ_EXT) : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	-@echo Compiling: $<
	$(CC) -c $(CPPFLAGS) $< $(CCOUTPUTFLAG) $@

%$(OBJ_EXT) : $(RELATIVE_PATH_TO_ANCHOR)/%.s
	-@echo Compiling: $<
	$(CC) -c -mcpu=$(PIC_REF) $< -Wa,-g $(CCOUTPUTFLAG) $@

%$(OBJ_EXT) : %.c
	-@echo Compiling: $<
	$(CC) -c $(CFLAGS) $< $(CCOUTPUTFLAG) $@

%$(OBJ_EXT) : %.cpp
	-@echo Compiling: $<
	$(CC) -c $(CPPFLAGS) $< $(CCOUTPUTFLAG) $@

%$(OBJ_EXT) : %.s
	-@echo Compiling: $<
	$(CC) -c -mcpu=$(PIC_REF) $< -Wa,-g $(CCOUTPUTFLAG) $@

%$(OBJ_EXT) : $(START_DIR)/Mplab_generated_code/ECAN1/%.c
	-@echo Compiling: $<
	$(CC) -c $(CFLAGS) $< $(CCOUTPUTFLAG) $@

%$(OBJ_EXT) : $(MATLAB_ROOT)/rtw/c/src/%.c
	-@echo Compiling: $<
	$(CC) -c $(CFLAGS) $< $(CCOUTPUTFLAG) $@

%$(OBJ_EXT) : $(MATLAB_ROOT)/simulink/src/%.c
	-@echo Compiling: $<
	$(CC) -c $(CFLAGS) $< $(CCOUTPUTFLAG) $@



%$(OBJ_EXT) : $(START_DIR)/Mplab_generated_code/ECAN1/%.cpp
	-@echo Compiling: $<
	$(CC) -c $(CPPFLAGS) $< $(CCOUTPUTFLAG) $@

%$(OBJ_EXT) : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	-@echo Compiling: $<
	$(CC) -c $(CPPFLAGS) $< $(CCOUTPUTFLAG) $@

%$(OBJ_EXT) : $(MATLAB_ROOT)/simulink/src/%.cpp
	-@echo Compiling: $<
	$(CC) -c $(CPPFLAGS) $< $(CCOUTPUTFLAG) $@



%$(OBJ_EXT) : $(START_DIR)/Mplab_generated_code/ECAN1/%.s
	-@echo Compiling: $<
	$(CC) -c -mcpu=$(PIC_REF) $< -Wa,-g $(CCOUTPUTFLAG) $@

%$(OBJ_EXT) : $(MATLAB_ROOT)/rtw/c/src/%.s
	-@echo Compiling: $<
	$(CC) -c -mcpu=$(PIC_REF) $< -Wa,-g $(CCOUTPUTFLAG) $@

%$(OBJ_EXT) : $(MATLAB_ROOT)/simulink/src/%.s
	-@echo Compiling: $<
	$(CC) -c -mcpu=$(PIC_REF) $< -Wa,-g $(CCOUTPUTFLAG) $@


