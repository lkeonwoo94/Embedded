################################################################################
# Automatically-generated file. Do not edit!
################################################################################

C_FILES += "..\ASW\core0_main.c"
OBJ_FILES += "ASW\core0_main.o"
"ASW\core0_main.o" : "..\ASW\core0_main.c" "ASW\.core0_main.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "ASW\.core0_main.o.opt"

"ASW\.core0_main.o.opt" : .refresh
	@argfile "ASW\.core0_main.o.opt" -o "ASW\core0_main.o" "..\ASW\core0_main.c" -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" -Wa-H"sfr/regtc27x.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -D_TASKING_C_TRICORE_ -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\ASW" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\ecum_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\compiler" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc\TC27xC" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\integration_general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\irq_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\mcu_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\port_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\tricore_general\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\Demo_Aurix" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\inc" --iso=90 --language=+comments,-gcc,-volatile,+strings --uchar --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=4 -g --source -c --dep-file="ASW\.core0_main.o.d" -Wc--make-target="ASW\core0_main.o"
DEPENDENCY_FILES += "ASW\.core0_main.o.d"


GENERATED_FILES += "ASW\core0_main.o" "ASW\.core0_main.o.opt" "ASW\.core0_main.o.d" "ASW\core0_main.src" "ASW\core0_main.lst"
