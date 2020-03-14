################################################################################
# Automatically-generated file. Do not edit!
################################################################################

C_FILES += "..\BSW\mcal_gen\src\EcuM_LCfg.c"
OBJ_FILES += "BSW\mcal_gen\src\EcuM_LCfg.o"
"BSW\mcal_gen\src\EcuM_LCfg.o" : "..\BSW\mcal_gen\src\EcuM_LCfg.c" "BSW\mcal_gen\src\.EcuM_LCfg.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "BSW\mcal_gen\src\.EcuM_LCfg.o.opt"

"BSW\mcal_gen\src\.EcuM_LCfg.o.opt" : .refresh
	@argfile "BSW\mcal_gen\src\.EcuM_LCfg.o.opt" -o "BSW\mcal_gen\src\EcuM_LCfg.o" "..\BSW\mcal_gen\src\EcuM_LCfg.c" -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" -Wa-H"sfr/regtc27x.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -D_TASKING_C_TRICORE_ -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\ASW" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\ecum_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\compiler" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc\TC27xC" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\integration_general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\irq_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\mcu_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\port_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\tricore_general\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\Demo_Aurix" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\inc" --iso=90 --language=+comments,-gcc,-volatile,+strings --uchar --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=4 -g --source -c --dep-file="BSW\mcal_gen\src\.EcuM_LCfg.o.d" -Wc--make-target="BSW\mcal_gen\src\EcuM_LCfg.o"
DEPENDENCY_FILES += "BSW\mcal_gen\src\.EcuM_LCfg.o.d"

C_FILES += "..\BSW\mcal_gen\src\EcuM_PBCfg.c"
OBJ_FILES += "BSW\mcal_gen\src\EcuM_PBCfg.o"
"BSW\mcal_gen\src\EcuM_PBCfg.o" : "..\BSW\mcal_gen\src\EcuM_PBCfg.c" "BSW\mcal_gen\src\.EcuM_PBCfg.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "BSW\mcal_gen\src\.EcuM_PBCfg.o.opt"

"BSW\mcal_gen\src\.EcuM_PBCfg.o.opt" : .refresh
	@argfile "BSW\mcal_gen\src\.EcuM_PBCfg.o.opt" -o "BSW\mcal_gen\src\EcuM_PBCfg.o" "..\BSW\mcal_gen\src\EcuM_PBCfg.c" -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" -Wa-H"sfr/regtc27x.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -D_TASKING_C_TRICORE_ -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\ASW" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\ecum_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\compiler" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc\TC27xC" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\integration_general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\irq_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\mcu_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\port_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\tricore_general\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\Demo_Aurix" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\inc" --iso=90 --language=+comments,-gcc,-volatile,+strings --uchar --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=4 -g --source -c --dep-file="BSW\mcal_gen\src\.EcuM_PBCfg.o.d" -Wc--make-target="BSW\mcal_gen\src\EcuM_PBCfg.o"
DEPENDENCY_FILES += "BSW\mcal_gen\src\.EcuM_PBCfg.o.d"

C_FILES += "..\BSW\mcal_gen\src\Gtm_LCfg.c"
OBJ_FILES += "BSW\mcal_gen\src\Gtm_LCfg.o"
"BSW\mcal_gen\src\Gtm_LCfg.o" : "..\BSW\mcal_gen\src\Gtm_LCfg.c" "BSW\mcal_gen\src\.Gtm_LCfg.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "BSW\mcal_gen\src\.Gtm_LCfg.o.opt"

"BSW\mcal_gen\src\.Gtm_LCfg.o.opt" : .refresh
	@argfile "BSW\mcal_gen\src\.Gtm_LCfg.o.opt" -o "BSW\mcal_gen\src\Gtm_LCfg.o" "..\BSW\mcal_gen\src\Gtm_LCfg.c" -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" -Wa-H"sfr/regtc27x.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -D_TASKING_C_TRICORE_ -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\ASW" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\ecum_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\compiler" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc\TC27xC" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\integration_general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\irq_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\mcu_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\port_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\tricore_general\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\Demo_Aurix" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\inc" --iso=90 --language=+comments,-gcc,-volatile,+strings --uchar --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=4 -g --source -c --dep-file="BSW\mcal_gen\src\.Gtm_LCfg.o.d" -Wc--make-target="BSW\mcal_gen\src\Gtm_LCfg.o"
DEPENDENCY_FILES += "BSW\mcal_gen\src\.Gtm_LCfg.o.d"

C_FILES += "..\BSW\mcal_gen\src\Gtm_PBCfg.c"
OBJ_FILES += "BSW\mcal_gen\src\Gtm_PBCfg.o"
"BSW\mcal_gen\src\Gtm_PBCfg.o" : "..\BSW\mcal_gen\src\Gtm_PBCfg.c" "BSW\mcal_gen\src\.Gtm_PBCfg.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "BSW\mcal_gen\src\.Gtm_PBCfg.o.opt"

"BSW\mcal_gen\src\.Gtm_PBCfg.o.opt" : .refresh
	@argfile "BSW\mcal_gen\src\.Gtm_PBCfg.o.opt" -o "BSW\mcal_gen\src\Gtm_PBCfg.o" "..\BSW\mcal_gen\src\Gtm_PBCfg.c" -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" -Wa-H"sfr/regtc27x.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -D_TASKING_C_TRICORE_ -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\ASW" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\ecum_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\compiler" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc\TC27xC" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\integration_general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\irq_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\mcu_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\port_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\tricore_general\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\Demo_Aurix" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\inc" --iso=90 --language=+comments,-gcc,-volatile,+strings --uchar --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=4 -g --source -c --dep-file="BSW\mcal_gen\src\.Gtm_PBCfg.o.d" -Wc--make-target="BSW\mcal_gen\src\Gtm_PBCfg.o"
DEPENDENCY_FILES += "BSW\mcal_gen\src\.Gtm_PBCfg.o.d"

C_FILES += "..\BSW\mcal_gen\src\Mcu_PBCfg.c"
OBJ_FILES += "BSW\mcal_gen\src\Mcu_PBCfg.o"
"BSW\mcal_gen\src\Mcu_PBCfg.o" : "..\BSW\mcal_gen\src\Mcu_PBCfg.c" "BSW\mcal_gen\src\.Mcu_PBCfg.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "BSW\mcal_gen\src\.Mcu_PBCfg.o.opt"

"BSW\mcal_gen\src\.Mcu_PBCfg.o.opt" : .refresh
	@argfile "BSW\mcal_gen\src\.Mcu_PBCfg.o.opt" -o "BSW\mcal_gen\src\Mcu_PBCfg.o" "..\BSW\mcal_gen\src\Mcu_PBCfg.c" -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" -Wa-H"sfr/regtc27x.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -D_TASKING_C_TRICORE_ -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\ASW" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\ecum_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\compiler" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc\TC27xC" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\integration_general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\irq_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\mcu_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\port_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\tricore_general\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\Demo_Aurix" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\inc" --iso=90 --language=+comments,-gcc,-volatile,+strings --uchar --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=4 -g --source -c --dep-file="BSW\mcal_gen\src\.Mcu_PBCfg.o.d" -Wc--make-target="BSW\mcal_gen\src\Mcu_PBCfg.o"
DEPENDENCY_FILES += "BSW\mcal_gen\src\.Mcu_PBCfg.o.d"

C_FILES += "..\BSW\mcal_gen\src\Port_PBCfg.c"
OBJ_FILES += "BSW\mcal_gen\src\Port_PBCfg.o"
"BSW\mcal_gen\src\Port_PBCfg.o" : "..\BSW\mcal_gen\src\Port_PBCfg.c" "BSW\mcal_gen\src\.Port_PBCfg.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "BSW\mcal_gen\src\.Port_PBCfg.o.opt"

"BSW\mcal_gen\src\.Port_PBCfg.o.opt" : .refresh
	@argfile "BSW\mcal_gen\src\.Port_PBCfg.o.opt" -o "BSW\mcal_gen\src\Port_PBCfg.o" "..\BSW\mcal_gen\src\Port_PBCfg.c" -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" -Wa-H"sfr/regtc27x.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -D_TASKING_C_TRICORE_ -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\ASW" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\ecum_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\compiler" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc\TC27xC" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\integration_general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\irq_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\mcu_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\port_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\tricore_general\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\Demo_Aurix" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\inc" --iso=90 --language=+comments,-gcc,-volatile,+strings --uchar --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=4 -g --source -c --dep-file="BSW\mcal_gen\src\.Port_PBCfg.o.d" -Wc--make-target="BSW\mcal_gen\src\Port_PBCfg.o"
DEPENDENCY_FILES += "BSW\mcal_gen\src\.Port_PBCfg.o.d"


GENERATED_FILES += "BSW\mcal_gen\src\EcuM_LCfg.o" "BSW\mcal_gen\src\.EcuM_LCfg.o.opt" "BSW\mcal_gen\src\.EcuM_LCfg.o.d" "BSW\mcal_gen\src\EcuM_LCfg.src" "BSW\mcal_gen\src\EcuM_LCfg.lst" "BSW\mcal_gen\src\EcuM_PBCfg.o" "BSW\mcal_gen\src\.EcuM_PBCfg.o.opt" "BSW\mcal_gen\src\.EcuM_PBCfg.o.d" "BSW\mcal_gen\src\EcuM_PBCfg.src" "BSW\mcal_gen\src\EcuM_PBCfg.lst" "BSW\mcal_gen\src\Gtm_LCfg.o" "BSW\mcal_gen\src\.Gtm_LCfg.o.opt" "BSW\mcal_gen\src\.Gtm_LCfg.o.d" "BSW\mcal_gen\src\Gtm_LCfg.src" "BSW\mcal_gen\src\Gtm_LCfg.lst" "BSW\mcal_gen\src\Gtm_PBCfg.o" "BSW\mcal_gen\src\.Gtm_PBCfg.o.opt" "BSW\mcal_gen\src\.Gtm_PBCfg.o.d" "BSW\mcal_gen\src\Gtm_PBCfg.src" "BSW\mcal_gen\src\Gtm_PBCfg.lst" "BSW\mcal_gen\src\Mcu_PBCfg.o" "BSW\mcal_gen\src\.Mcu_PBCfg.o.opt" "BSW\mcal_gen\src\.Mcu_PBCfg.o.d" "BSW\mcal_gen\src\Mcu_PBCfg.src" "BSW\mcal_gen\src\Mcu_PBCfg.lst" "BSW\mcal_gen\src\Port_PBCfg.o" "BSW\mcal_gen\src\.Port_PBCfg.o.opt" "BSW\mcal_gen\src\.Port_PBCfg.o.d" "BSW\mcal_gen\src\Port_PBCfg.src" "BSW\mcal_gen\src\Port_PBCfg.lst"
