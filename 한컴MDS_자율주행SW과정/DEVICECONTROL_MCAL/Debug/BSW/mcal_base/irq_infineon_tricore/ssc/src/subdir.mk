################################################################################
# Automatically-generated file. Do not edit!
################################################################################

C_FILES += "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\AscLin_Irq.c"
OBJ_FILES += "BSW\mcal_base\irq_infineon_tricore\ssc\src\AscLin_Irq.o"
"BSW\mcal_base\irq_infineon_tricore\ssc\src\AscLin_Irq.o" : "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\AscLin_Irq.c" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.AscLin_Irq.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "BSW\mcal_base\irq_infineon_tricore\ssc\src\.AscLin_Irq.o.opt"

"BSW\mcal_base\irq_infineon_tricore\ssc\src\.AscLin_Irq.o.opt" : .refresh
	@argfile "BSW\mcal_base\irq_infineon_tricore\ssc\src\.AscLin_Irq.o.opt" -o "BSW\mcal_base\irq_infineon_tricore\ssc\src\AscLin_Irq.o" "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\AscLin_Irq.c" -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" -Wa-H"sfr/regtc27x.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -D_TASKING_C_TRICORE_ -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\ASW" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\ecum_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\compiler" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc\TC27xC" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\integration_general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\irq_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\mcu_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\port_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\tricore_general\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\Demo_Aurix" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\inc" --iso=90 --language=+comments,-gcc,-volatile,+strings --uchar --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=4 -g --source -c --dep-file="BSW\mcal_base\irq_infineon_tricore\ssc\src\.AscLin_Irq.o.d" -Wc--make-target="BSW\mcal_base\irq_infineon_tricore\ssc\src\AscLin_Irq.o"
DEPENDENCY_FILES += "BSW\mcal_base\irq_infineon_tricore\ssc\src\.AscLin_Irq.o.d"

C_FILES += "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Dma_Irq.c"
OBJ_FILES += "BSW\mcal_base\irq_infineon_tricore\ssc\src\Dma_Irq.o"
"BSW\mcal_base\irq_infineon_tricore\ssc\src\Dma_Irq.o" : "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Dma_Irq.c" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Dma_Irq.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Dma_Irq.o.opt"

"BSW\mcal_base\irq_infineon_tricore\ssc\src\.Dma_Irq.o.opt" : .refresh
	@argfile "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Dma_Irq.o.opt" -o "BSW\mcal_base\irq_infineon_tricore\ssc\src\Dma_Irq.o" "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Dma_Irq.c" -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" -Wa-H"sfr/regtc27x.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -D_TASKING_C_TRICORE_ -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\ASW" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\ecum_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\compiler" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc\TC27xC" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\integration_general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\irq_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\mcu_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\port_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\tricore_general\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\Demo_Aurix" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\inc" --iso=90 --language=+comments,-gcc,-volatile,+strings --uchar --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=4 -g --source -c --dep-file="BSW\mcal_base\irq_infineon_tricore\ssc\src\.Dma_Irq.o.d" -Wc--make-target="BSW\mcal_base\irq_infineon_tricore\ssc\src\Dma_Irq.o"
DEPENDENCY_FILES += "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Dma_Irq.o.d"

C_FILES += "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Gtm_Irq.c"
OBJ_FILES += "BSW\mcal_base\irq_infineon_tricore\ssc\src\Gtm_Irq.o"
"BSW\mcal_base\irq_infineon_tricore\ssc\src\Gtm_Irq.o" : "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Gtm_Irq.c" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Gtm_Irq.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Gtm_Irq.o.opt"

"BSW\mcal_base\irq_infineon_tricore\ssc\src\.Gtm_Irq.o.opt" : .refresh
	@argfile "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Gtm_Irq.o.opt" -o "BSW\mcal_base\irq_infineon_tricore\ssc\src\Gtm_Irq.o" "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Gtm_Irq.c" -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" -Wa-H"sfr/regtc27x.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -D_TASKING_C_TRICORE_ -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\ASW" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\ecum_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\compiler" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc\TC27xC" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\integration_general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\irq_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\mcu_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\port_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\tricore_general\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\Demo_Aurix" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\inc" --iso=90 --language=+comments,-gcc,-volatile,+strings --uchar --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=4 -g --source -c --dep-file="BSW\mcal_base\irq_infineon_tricore\ssc\src\.Gtm_Irq.o.d" -Wc--make-target="BSW\mcal_base\irq_infineon_tricore\ssc\src\Gtm_Irq.o"
DEPENDENCY_FILES += "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Gtm_Irq.o.d"

C_FILES += "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Hsm_Irq.c"
OBJ_FILES += "BSW\mcal_base\irq_infineon_tricore\ssc\src\Hsm_Irq.o"
"BSW\mcal_base\irq_infineon_tricore\ssc\src\Hsm_Irq.o" : "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Hsm_Irq.c" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Hsm_Irq.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Hsm_Irq.o.opt"

"BSW\mcal_base\irq_infineon_tricore\ssc\src\.Hsm_Irq.o.opt" : .refresh
	@argfile "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Hsm_Irq.o.opt" -o "BSW\mcal_base\irq_infineon_tricore\ssc\src\Hsm_Irq.o" "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Hsm_Irq.c" -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" -Wa-H"sfr/regtc27x.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -D_TASKING_C_TRICORE_ -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\ASW" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\ecum_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\compiler" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc\TC27xC" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\integration_general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\irq_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\mcu_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\port_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\tricore_general\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\Demo_Aurix" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\inc" --iso=90 --language=+comments,-gcc,-volatile,+strings --uchar --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=4 -g --source -c --dep-file="BSW\mcal_base\irq_infineon_tricore\ssc\src\.Hsm_Irq.o.d" -Wc--make-target="BSW\mcal_base\irq_infineon_tricore\ssc\src\Hsm_Irq.o"
DEPENDENCY_FILES += "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Hsm_Irq.o.d"

C_FILES += "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Irq.c"
OBJ_FILES += "BSW\mcal_base\irq_infineon_tricore\ssc\src\Irq.o"
"BSW\mcal_base\irq_infineon_tricore\ssc\src\Irq.o" : "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Irq.c" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Irq.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Irq.o.opt"

"BSW\mcal_base\irq_infineon_tricore\ssc\src\.Irq.o.opt" : .refresh
	@argfile "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Irq.o.opt" -o "BSW\mcal_base\irq_infineon_tricore\ssc\src\Irq.o" "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Irq.c" -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" -Wa-H"sfr/regtc27x.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -D_TASKING_C_TRICORE_ -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\ASW" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\ecum_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\compiler" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc\TC27xC" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\integration_general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\irq_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\mcu_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\port_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\tricore_general\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\Demo_Aurix" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\inc" --iso=90 --language=+comments,-gcc,-volatile,+strings --uchar --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=4 -g --source -c --dep-file="BSW\mcal_base\irq_infineon_tricore\ssc\src\.Irq.o.d" -Wc--make-target="BSW\mcal_base\irq_infineon_tricore\ssc\src\Irq.o"
DEPENDENCY_FILES += "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Irq.o.d"

C_FILES += "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Mcal_Trap.c"
OBJ_FILES += "BSW\mcal_base\irq_infineon_tricore\ssc\src\Mcal_Trap.o"
"BSW\mcal_base\irq_infineon_tricore\ssc\src\Mcal_Trap.o" : "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Mcal_Trap.c" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Mcal_Trap.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Mcal_Trap.o.opt"

"BSW\mcal_base\irq_infineon_tricore\ssc\src\.Mcal_Trap.o.opt" : .refresh
	@argfile "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Mcal_Trap.o.opt" -o "BSW\mcal_base\irq_infineon_tricore\ssc\src\Mcal_Trap.o" "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Mcal_Trap.c" -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" -Wa-H"sfr/regtc27x.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -D_TASKING_C_TRICORE_ -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\ASW" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\ecum_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\compiler" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc\TC27xC" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\integration_general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\irq_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\mcu_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\port_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\tricore_general\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\Demo_Aurix" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\inc" --iso=90 --language=+comments,-gcc,-volatile,+strings --uchar --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=4 -g --source -c --dep-file="BSW\mcal_base\irq_infineon_tricore\ssc\src\.Mcal_Trap.o.d" -Wc--make-target="BSW\mcal_base\irq_infineon_tricore\ssc\src\Mcal_Trap.o"
DEPENDENCY_FILES += "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Mcal_Trap.o.d"

C_FILES += "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Stm_Irq.c"
OBJ_FILES += "BSW\mcal_base\irq_infineon_tricore\ssc\src\Stm_Irq.o"
"BSW\mcal_base\irq_infineon_tricore\ssc\src\Stm_Irq.o" : "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Stm_Irq.c" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Stm_Irq.o.opt"
	@echo Compiling ${<F}
	@"${PRODDIR}\bin\cctc" -f "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Stm_Irq.o.opt"

"BSW\mcal_base\irq_infineon_tricore\ssc\src\.Stm_Irq.o.opt" : .refresh
	@argfile "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Stm_Irq.o.opt" -o "BSW\mcal_base\irq_infineon_tricore\ssc\src\Stm_Irq.o" "..\BSW\mcal_base\irq_infineon_tricore\ssc\src\Stm_Irq.c" -Ctc27x --lsl-core=vtc -t -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL" -Wa-H"sfr/regtc27x.def" -Wa-gAHLs --emit-locals=-equ,-symbols -Wa-Ogs -Wa--error-limit=42 -D_TASKING_C_TRICORE_ -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\ASW" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\ecum_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\compiler" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\general\tricore\inc\TC27xC" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\integration_general\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\irq_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\mcu_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\port_infineon_tricore\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_base\tricore_general\ssc\inc" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\Demo_Aurix" -I"C:\Workspace_AURIX\DEVICECONTROL_MCAL\BSW\mcal_gen\inc" --iso=90 --language=+comments,-gcc,-volatile,+strings --uchar --switch=auto --align=0 --default-near-size=8 --default-a0-size=0 --default-a1-size=0 -O0 --tradeoff=4 -g --source -c --dep-file="BSW\mcal_base\irq_infineon_tricore\ssc\src\.Stm_Irq.o.d" -Wc--make-target="BSW\mcal_base\irq_infineon_tricore\ssc\src\Stm_Irq.o"
DEPENDENCY_FILES += "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Stm_Irq.o.d"


GENERATED_FILES += "BSW\mcal_base\irq_infineon_tricore\ssc\src\AscLin_Irq.o" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.AscLin_Irq.o.opt" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.AscLin_Irq.o.d" "BSW\mcal_base\irq_infineon_tricore\ssc\src\AscLin_Irq.src" "BSW\mcal_base\irq_infineon_tricore\ssc\src\AscLin_Irq.lst" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Dma_Irq.o" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Dma_Irq.o.opt" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Dma_Irq.o.d" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Dma_Irq.src" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Dma_Irq.lst" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Gtm_Irq.o" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Gtm_Irq.o.opt" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Gtm_Irq.o.d" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Gtm_Irq.src" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Gtm_Irq.lst" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Hsm_Irq.o" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Hsm_Irq.o.opt" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Hsm_Irq.o.d" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Hsm_Irq.src" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Hsm_Irq.lst" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Irq.o" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Irq.o.opt" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Irq.o.d" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Irq.src" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Irq.lst" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Mcal_Trap.o" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Mcal_Trap.o.opt" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Mcal_Trap.o.d" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Mcal_Trap.src" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Mcal_Trap.lst" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Stm_Irq.o" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Stm_Irq.o.opt" "BSW\mcal_base\irq_infineon_tricore\ssc\src\.Stm_Irq.o.d" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Stm_Irq.src" "BSW\mcal_base\irq_infineon_tricore\ssc\src\Stm_Irq.lst"
