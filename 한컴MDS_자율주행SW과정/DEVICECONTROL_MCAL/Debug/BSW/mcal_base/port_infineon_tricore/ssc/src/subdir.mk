################################################################################
# Automatically-generated file. Do not edit!
################################################################################

C_FILES += "..\BSW\mcal_base\port_infineon_tricore\ssc\src\Port.c"
OBJ_FILES += "BSW\mcal_base\port_infineon_tricore\ssc\src\Port.o"
"BSW\mcal_base\port_infineon_tricore\ssc\src\Port.o" : "..\BSW\mcal_base\port_infineon_tricore\ssc\src\Port.c" "BSW\mcal_base\port_infineon_tricore\ssc\src\.Port.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "BSW\mcal_base\port_infineon_tricore\ssc\src\.Port.o.opt"

"BSW\mcal_base\port_infineon_tricore\ssc\src\.Port.o.opt" : .refresh
	@argfile "BSW\mcal_base\port_infineon_tricore\ssc\src\.Port.o.opt" -o "BSW\mcal_base\port_infineon_tricore\ssc\src\Port.o" "..\BSW\mcal_base\port_infineon_tricore\ssc\src\Port.c" -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" -Wa-H"sfr/regtc27x.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -D_TASKING_C_TRICORE_ -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\ASW" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\ecum_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\compiler" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc\TC27xC" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\integration_general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\irq_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\mcu_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\port_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\tricore_general\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\Demo_Aurix" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\inc" --iso=90 --language=+comments,-gcc,-volatile,+strings --uchar --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=4 -g --source -c --dep-file="BSW\mcal_base\port_infineon_tricore\ssc\src\.Port.o.d" -Wc--make-target="BSW\mcal_base\port_infineon_tricore\ssc\src\Port.o"
DEPENDENCY_FILES += "BSW\mcal_base\port_infineon_tricore\ssc\src\.Port.o.d"


GENERATED_FILES += "BSW\mcal_base\port_infineon_tricore\ssc\src\Port.o" "BSW\mcal_base\port_infineon_tricore\ssc\src\.Port.o.opt" "BSW\mcal_base\port_infineon_tricore\ssc\src\.Port.o.d" "BSW\mcal_base\port_infineon_tricore\ssc\src\Port.src" "BSW\mcal_base\port_infineon_tricore\ssc\src\Port.lst"
