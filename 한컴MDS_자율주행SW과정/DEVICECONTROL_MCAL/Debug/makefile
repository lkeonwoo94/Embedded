################################################################################
# Automatically-generated file. Do not edit!
################################################################################

PROJ 	= DEVICECONTROL_MCAL
PRODDIR = C:\Program Files (x86)\TASKING\TriCore v4.2r2\ctc

-include "..\makefile.init"

all :

-include "subdir.mk"
-include "ASW\subdir.mk"
-include "BSW\mcal_base\ecum_infineon_tricore\ssc\src\subdir.mk"
-include "BSW\mcal_base\integration_general\src\subdir.mk"
-include "BSW\mcal_base\irq_infineon_tricore\ssc\src\subdir.mk"
-include "BSW\mcal_base\mcu_infineon_tricore\ssc\src\subdir.mk"
-include "BSW\mcal_base\port_infineon_tricore\ssc\src\subdir.mk"
-include "BSW\mcal_base\tricore_general\ssc\src\subdir.mk"
-include "BSW\mcal_gen\src\subdir.mk"
-include "..\makefile.defs"

PCP_FILES :=
EXT_LIBRARIES =

all : "DEVICECONTROL_MCAL.elf"

"DEVICECONTROL_MCAL.elf" : $(OBJ_FILES) $(EXT_LIBRARIES) ".DEVICECONTROL_MCAL.elf.opt"
	@echo Linking to ${@F}
	@"${PRODDIR}\bin\cctc" -f ".DEVICECONTROL_MCAL.elf.opt"

".DEVICECONTROL_MCAL.elf.opt" : .refresh
	@argfile ".DEVICECONTROL_MCAL.elf.opt" -o "DEVICECONTROL_MCAL.elf" $(OBJ_FILES) $(EXT_LIBRARIES) $(PCP_FILES)  -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" "../ASW/_mcal_pjt.lsl" -Wl-OtxycL --no-map-file -Wl--map-file="${PROJ}.mapxml":XML -Wl-mcrfiklSmNOduQ -Wl--error-limit=42 -g -Wl--dep-file=".DEVICECONTROL_MCAL.elf.d" -Wl--make-target="DEVICECONTROL_MCAL.elf"
DEPENDENCY_FILES += ".DEVICECONTROL_MCAL.elf.d"
-include $(DEPENDENCY_FILES)

$(EXT_LIBRARIES) : .dummy

GENERATED_FILES += "DEVICECONTROL_MCAL.elf" "DEVICECONTROL_MCAL*.sre" "DEVICECONTROL_MCAL*.hex" "DEVICECONTROL_MCAL.map*" "DEVICECONTROL_MCAL.mdf" ".DEVICECONTROL_MCAL.elf.opt" ".DEVICECONTROL_MCAL.elf.d"
-include "..\makefile.targets"


clean : ".clean.opt"
	@echo Cleaning
	@"${PRODDIR}\bin\rm" -f -m ".clean.opt"

".clean.opt" : .refresh
	@argfile ".clean.opt" $(GENERATED_FILES) $(OPTIONAL_FILES)

GENERATED_FILES += ".clean.opt"
OPTIONAL_FILES +=  "*.pre" "*.lst" "*.p.o" "*.p.a"


.PHONY : .dummy .refresh
