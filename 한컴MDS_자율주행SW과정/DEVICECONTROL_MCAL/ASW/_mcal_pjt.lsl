
// Include the CPU specific .lsl file
// The CPU is specified by the __CPU__ macro
#ifndef __CPU__
# error No CPU defined, please link with -D__CPU__=<cpu>
#endif

#define ISTACK_TC0 8k
#define ISTACK_TC1 8k
#define ISTACK_TC2 8k
#define USTACK_TC0 16k
#define USTACK_TC1 8k
#define USTACK_TC2 8k

#define HSM_RESERVED1_PMU_FLSAH0 0x80018000
#define HSM_RESERVED1_SIZE       16k
#define PMU_PFLASH0 0x80030000
#define PMUECCEDC_SAFETLIB_TVT_RESERVED 0x80090000
#define PMU_SAFETLIB_PFLASHTST_RESERVED (PMUECCEDC_SAFETLIB_TVT_RESERVED+0x100)
#define HSM_RESERVED2_PMU_FLSAH0 0x80060000
#define HSM_RESERVED2_SIZE       128k
#define PMU_PFLASH1 0x80200000
#define CPU0_PMI_PSPR 0x70100100
#define CPU1_PMI_PSPR 0x60100100
#define CPU2_PMI_PSPR 0x50100100
// 100 bytes of DSPR is reserved for sbst_tc0_dspr
#define CPU0_DMI_DSPR 0x70000100
#define CPU0_DMI_DSPR_FLSLOADER 0x70019000
#define CPU1_DMI_DSPR 0x60000100
#define CPU2_DMI_DSPR 0x50000100
#define LMU_SRAM 0xB0000000



#define __QUOTE_ME2(x) #x
#define __QUOTE_ME(x) __QUOTE_ME2(x)
#define CPULSL_FILE __QUOTE_ME(__CPU__.lsl)

#include CPULSL_FILE

// Define default external memory
// These memory definitions can be replaced by the Debug Target Configuration Wizard

#ifndef HAS_ON_CHIP_FLASH       // On-chip flash is located at 0x[8a]0000000
memory xrom_a (tag="External ROM",tag="dtc")
{
        mau = 8;
        size = 1M;
        type = rom;
         map     cached (dest=bus:sri, dest_offset=0x80000000,           size=1M);
         map not_cached (dest=bus:sri, dest_offset=0xa0000000, reserved, size=1M);
}
#endif




/* trap tab is on the reset address of BTV (cached area) */
#define IFXTRAPTAB 0x80000100 /* this is the default address (only cached area) of BTV after reset */

section_layout :vtc:linear
{

  "_lc_u_trap_tab" = (IFXTRAPTAB);
  "_lc_u_trap_tab_tc0" = (IFXTRAPTAB);
  "_lc_u_trap_tab_tc1" = (IFXTRAPTAB+0x0100);
  "_lc_u_trap_tab_tc2" = (IFXTRAPTAB+0x0200);
  "__TC0_PCON2_VALUE"      = 0x00180008 ;
  "__TC0_DCON2_VALUE"      = 0x00700000 ;
  "__TC1_PCON2_VALUE"      = 0x00200010 ;
  "__TC1_DCON2_VALUE"      = 0x00780008 ;
  "__TC2_PCON2_VALUE"      = 0x00200010 ;
  "__TC2_DCON2_VALUE"      = 0x00780008 ;  
  "__SBST_DSPR_BASE_ADDR"  = 0xd0000000 ;
  "__SBST_PSPR_BASE_ADDR"  = 0xc0000000 ;
  "__SBST_CRC_RESULT"      = ("__SBST_DSPR_BASE_ADDR"+0x00FC);  

  

              // trapvector table for CPU0
  group (ordered, contiguous, align = 1<<5, run_addr=(IFXTRAPTAB)+0x0000)
  {
    select ".text.CPU0_TRAP_HANDLER_CODE_ROM";
  }

              // trapvector table for CPU1
  group (ordered, contiguous, align = 1<<5, run_addr=(IFXTRAPTAB)+0x0100)
  {
    select ".text.CPU1_TRAP_HANDLER_CODE_ROM";
  }

              // trapvector table for CPU2
  group (ordered, contiguous, align = 1<<5, run_addr=(IFXTRAPTAB)+0x0200)
  {
    select ".text.CPU2_TRAP_HANDLER_CODE_ROM";
  }

}

section_layout :vtc:linear
{
    
    /* CPU0 DPSR area for STL tests requiring 8-bit variables located to CPU0 DSPR: */
    group CPU0_DSPR_STL_LMUBSS1 (run_addr=mem:mpe:dspr0, align = 1)
    {
        select ".bss.Lmu.CPU0_DSPR_RAM_8BIT";
    }      
	
	/* CPU0 DPSR area for STL tests requiring 32-bit variables located to CPU0 DSPR: */
    group CPU0_DSPR_STL_LMUBSS2 (run_addr=mem:mpe:dspr0, align = 4)
    {
        select ".bss.Lmu.CPU0_DSPR_RAM_32BIT";
    }     
}

section_layout mpe:vtc:linear
{
  "LOC_START_PF0_PATTERNS" = "_lc_gb_PATTERN_PF0";
  "LOC_START_PF1_PATTERNS" = "_lc_gb_PATTERN_PF1";  
  group  (ordered, run_addr=0x80000000)
  {
    select ".rodata.BMD_HDR_CONST_FAR_UNSPECIFIED";
  }
  
  /* PFLASH0 area for PMU ECC/EDC test patterns: */
  group PATTERN_PF0 (align=32, ordered, run_addr=mem:mpe:pflash0/not_cached[0x100000..0x1FFBFF])
  {
    section "PFLASH0_PATTERNS" (size=576,attributes = r, fill = 0x00)
    {
       select ".rodata.MTL_PMU_ECC_EDC_TST_PF0";
    }
  }

  /* PFLASH1 area for PMU ECC/EDC test patterns: */
  group PATTERN_PF1 (align=32, ordered, run_addr=mem:mpe:pflash1/not_cached)
  {
    section "PFLASH1_PATTERNS" (size=576,attributes = r, fill = 0x00)
    {
      select ".rodata.MTL_PMU_ECC_EDC_TST_PF1";
    }  
  }

  group (ordered, run_addr=mem:mpe:pflash0/cached[0x100000..0x1FFBFF])
  {
    select ".rodata*";
  }
  group(ordered, contiguous)
  {
    group(align = 32768)
    {
      select ".text.ifx_opcode_test.asil_b.ISG_800B7000"; 
    }
    group
    {
      select ".text.ifx_opcode_test.asil_b.Main";
      select ".text.ifx_opcode_test.asil_b.Functions";
      select ".text.ifx_opcode_test.asil_b.Kernel_Direct";
      select ".text.ifx_opcode_test.asil_b.TC16E_Direct";
      select ".text.ifx_opcode_test.asil_b.RelocTable";
      select ".text.ifx_opcode_test.asil_b.ISG_800D7000";
      select ".text.ifx_opcode_test.asil_b.TC16P_Main";
      select ".text.ifx_opcode_test.asil_b.TC16P_Direct"; 
    }
  }
}

section_layout :tc0:linear
{
  group  (ordered, run_addr=0x80015000)
  {
    select ".text.Pwm_Demo.Pwm_Channel_0_Notification";
  }
}

section_layout :tc0:linear
{
  group  (ordered, run_addr=0x80015050)
  {
    select "text.Spi_Demo.EepTest_EndOfCmdSeq";
  }
}
section_layout :tc0:linear
{
  group  (ordered, run_addr=0x80015060)
  {
    select ".text.Spi_Demo.EepTest_EndOfStatSeq";
  }
}
section_layout :tc0:linear
{
  group  (ordered, run_addr=0x80015070)
  {
    select ".text.Spi_Demo.EepTest_EndOfDataSeq";
  }
}
section_layout :tc0:linear
{
  group  (ordered, run_addr=0x80015080)
  {
    select ".text.Gpt_Demo.Gpt_NotificationFrgOsm1";
  }
}

section_layout :tc0:linear
{
  group  (ordered, run_addr=0x80015084)
  {
    select ".text.Gpt_Demo.Gpt_NotificationFrlOsm1";
  }
}
section_layout :tc0:linear
{
  group  (ordered, run_addr=0x80015088)
  {
    select ".text.Gpt_Demo.Gpt_NotificationFrlCon2";
  }
}
section_layout :tc0:linear
{
  group  (ordered, run_addr=0x8001508C)
  {
    select ".text.Gpt_Demo.Gpt_NotificationRstOsm1";
  }
}
section_layout :tc0:linear
{
  group  (ordered, run_addr=0x80015090)
  {
    select ".text.Gpt_Demo.Gpt_NotificationRstCon2";
  }
}
section_layout :tc0:linear
{
  group  (ordered, run_addr=0x80015094)
  {
    select ".text.Gpt_Demo.Gpt_NotificationFrgCon2";
  }
}

section_layout mpe:vtc:linear
{
  group  (ordered, run_addr=0x80015200)
  {
    select ".text.FEE_JOBENDNOTIF_CODE";
  }
}

section_layout mpe:vtc:linear
{
  group  (ordered, run_addr=0x80015400)
  {
    select ".text.FEE_JOBERRNOTIF_CODE";
  }
}

section_layout mpe:vtc:linear
{
  group  (ordered, run_addr=0x80015800)
  {
    select ".text.FEE_ILLEGALNOTIF_CODE";
  }
}

section_layout :tc0:linear
{
  group  (ordered, run_addr=0x80015600)
  {
    select ".text.Icu_Demo.Icu_SignalEdgeNotification";
  }
}


section_layout :tc0:linear
{
  group FLS_AC_WRITE (ordered, run_addr = 0x70101100)
  {
    reserved "FLS_AC_WRITE" (alloc_allowed = absolute, size = 200);
  }
}
section_layout :tc0:linear
{
  group FLS_AC_ERASE (ordered, run_addr = 0x701011C8)
  {
    reserved "FLS_AC_ERASE" (alloc_allowed = absolute, size = 200);
  }
}

section_layout :tc0:linear
{
  group FLS_STATE_VAR (ordered, run_addr = 0x70010000)
  {
    reserved "FLS_STATE_VAR" (alloc_allowed = absolute, size = 48);
  }
}

section_layout mpe:vtc:linear
{
  group FLS_AC_ERASE_SOURCE (ordered, contiguous, run_addr=0x80008100)
  {
    select ".text.FLS_AC_ERASE_SOURCE";
  }
}

section_layout mpe:vtc:linear
{
  group FLS_AC_WRITE_SOURCE (ordered, contiguous, run_addr=0x80008300)
  {
    select ".text.FLS_AC_WRITE_SOURCE";
  }
}

section_setup mpe:vtc:linear
{
  modify input (space = mpe:tc0:linear, copy)
  {
    select ".text.FLSLOADERRAMCODE*";
  }
}

section_layout mpe:tc0:linear
{
  group FLSLOADER_CODE ( ordered, run_addr = CPU0_DMI_DSPR_FLSLOADER )
  {
    select ".text.FLSLOADERRAMCODE*";
  }
}




section_layout mpe:vtc:linear
{
  group  (ordered, run_addr=CPU0_PMI_PSPR)
  {
    select ".bss.CPU0_PSPR_RAM_NOINIT";  
  }
}

section_layout mpe:vtc:linear
{
  group  (ordered, run_addr=CPU1_PMI_PSPR)
  {
    select ".bss.CPU1_PSPR_RAM_NOINIT";  
  }
}

section_layout mpe:vtc:linear
{
  group  (ordered, run_addr=CPU2_PMI_PSPR)
  {
    select ".bss.CPU2_PSPR_RAM_NOINIT";
  }
}


// CODE

section_layout mpe:vtc:linear
{
  group HSM_CODE_RESERVE_1 (ordered, contiguous, run_addr = HSM_RESERVED1_PMU_FLSAH0)
  {
    reserved "HSM_CODE_RESERVE_1" (alloc_allowed = absolute, size = HSM_RESERVED1_SIZE);
  }
}

section_layout mpe:vtc:linear
{
  group HSM_CODE_RESERVE_2 (ordered, contiguous, run_addr = HSM_RESERVED2_PMU_FLSAH0)
  {
    reserved "HSM_CODE_RESERVE_2" (alloc_allowed = absolute, size = HSM_RESERVED2_SIZE);
  }
}

section_layout mpe:vtc:linear
{

  "LOC_START_PmuEccEdcTst_tvt_PFLASHCODE" = "_lc_gb_PMUECCEDCTST_TVT_PFLASHCODE";
  "LOC_END_PmuEccEdcTst_tvt_PFLASHCODE" = "_lc_ge_PMUECCEDCTST_TVT_PFLASHCODE";

  "LOC_START_PflashMon_EccEdc_PFLASHCODE" = "_lc_gb_PFLASH_MON_ECCEDC_PFLASHCODE";
  "LOC_END_PflashMon_EccEdc_PFLASHCODE" = "_lc_ge_PFLASH_MON_ECCEDC_PFLASHCODE";

  select ".text.libc.reset";
  group PMUECCEDCTST_TVT_PFLASHCODE ( ordered, load_addr = PMUECCEDC_SAFETLIB_TVT_RESERVED, align=256 )
  {
    section "PMUECCEDCTST_TVT_RAMCODE" (blocksize=4, attributes=r, fill=0x00)
    {
       select "\[.text.PMUECCEDCTST_TVT_RAMCODE*\]";
    }
  }  
  group PFLASH_MON_ECCEDC_PFLASHCODE ( ordered, load_addr = PMU_SAFETLIB_PFLASHTST_RESERVED, align=4 )
  {
    section "PFLASH_MON_ECCEDC_RAMCODE" (blocksize=4, attributes=r, fill=0x00)
    {
       select "\[.text.PFLASH_MON_ECCEDC_RAMCODE*\]";
    }
  }  
  group SHARED_CODE (ordered, run_addr=PMU_PFLASH0)
  {
    section "myoutput" ( size = 320k, attributes = r, fill = 0xFF )
    {
    select ".text.Shared*";
    select ".text*";
    }
  } 
}

section_layout mpe:vtc:linear
{
  group CPU0_PRIVATE_CODE (ordered, run_addr=PMU_PFLASH0)
  {
    select ".text.CPU0.Private*";
  }
}


section_layout mpe:vtc:linear
{
  group CPU1_PRIVATE_CODE (ordered, run_addr=PMU_PFLASH0)
  {
    select ".text.CPU1.Private*";
  }
}

section_layout mpe:vtc:linear
{
  group CPU2_PRIVATE_CODE (ordered, run_addr=PMU_PFLASH0)
  {
    select ".text.CPU2.Private*";
  }
}


//CORE SPECIFIC DATA

section_layout :tc0:linear
{
  group  (ordered, align = 64, attributes=rw, run_addr=(0xd0000000)) 
          reserved "sbst_tc0_dspr" (size = 0x100);                
  group  (ordered, align = 64, attributes=rw, run_addr=(0xc0000000)) 
          reserved "sbst_tc0_pspr" (size = 0x40);                
}

section_layout :tc0:linear
{
  group  (ordered, align = 32, attributes=rw, run_addr=(0x70002000))
            reserved "standby_ram_dspr0" (size = 0x44);   
}

section_layout :tc1:linear
{
  group  (ordered, align = 64, attributes=rw, run_addr=(0xd0000000)) 
          reserved "sbst_tc1_dspr" (size = 0x100);                
  group  (ordered, align = 64, attributes=rw, run_addr=(0xc0000000)) 
          reserved "sbst_tc1_pspr" (size = 0x40);                
}


section_layout :tc2:linear
{
  group  (ordered, align = 64, attributes=rw, run_addr=(0xd0000000)) 
          reserved "sbst_tc2_dspr" (size = 0x100);                
  group  (ordered, align = 64, attributes=rw, run_addr=(0xc0000000)) 
          reserved "sbst_tc2_pspr" (size = 0x40);                
}

section_layout :tc0:linear
{
  group  (ordered, run_addr=0xD0001080)
  {
    select ".data.FLS_RESERVED";
  }
}


section_layout mpe:vtc:linear
{
  group CPU0_PRIVATE_DATA (ordered, run_addr=CPU0_DMI_DSPR)
  {
    select ".bss.CPU0_DSPR_RAM_NOINIT";  
    select ".data.CPU0.Private*";
    select ".zdata.CPU0.Private*";
    select ".zdata*";
    select ".bss.CPU0.Private*";
  }
}

section_layout mpe:vtc:linear
{
  group CPU1_PRIVATE_DATA (ordered, run_addr=CPU1_DMI_DSPR)
  {
    select ".bss.CPU1_DSPR_RAM_NOINIT";  
    select ".data.CPU1.Private*";
    select ".bss.CPU1.Private.*";
  }
}

section_layout mpe:vtc:linear
{
  group CPU2_PRIVATE_DATA (ordered, run_addr=CPU2_DMI_DSPR)
  {
    select ".bss.CPU2_DSPR_RAM_NOINIT";  
    select ".data.CPU2.Private*";
    select ".bss.CPU2.Private*";    
  }
}


section_layout mpe:vtc:abs18
{
  group SHARED_ZBSS (ordered, run_addr=mem:mpe:lmuram/not_cached)
  {
    select ".zbss*";
  }
}

section_layout mpe:vtc:linear
{
  select ".bss.Dma_Demo.ExtBuffer";
  group SHARED_DATA (ordered, run_addr=mem:mpe:lmuram/not_cached)
  {
    select ".bss.LMU_RAM_NOINIT";  
    select ".data*";
    select ".zdata*";
    select ".bss*";
  }
}

/* Added for copytable implementation of PmuEccEdcTst, PFlashMonTst 
and SlFlsErrPtrn functions that are executed from RAM*/
section_setup mpe:vtc:linear
{
  modify input (space = mpe:tc0:linear, copy)
  {
    select ".text.PMUECCEDCTST_TVT_RAMCODE*";
    select ".text.PFLASH_MON_ECCEDC_RAMCODE*";
  }
}

/* Added for copytable implementation of PmuEccEdcTst, PFlashMonTst 
and SlFlsErrPtrn functions that are executed from RAM*/
section_layout mpe:tc0:linear
{

  "LOC_START_PmuEccEdcTst_tvt_RAM_RUNCODE" = "_lc_gb_PMUECCEDCTST_TVT_RUNCODE";
  "LOC_END_PmuEccEdcTst_tvt_RAM_RUNCODE" = "_lc_ge_PMUECCEDCTST_TVT_RUNCODE";

  "LOC_START_PflashMon_EccEdc_RAM_RUNCODE" = "_lc_gb_PFLASH_MON_ECCEDC_RUNCODE";
  "LOC_END_PflashMon_EccEdc_RAM_RUNCODE" = "_lc_ge_PFLASH_MON_ECCEDC_RUNCODE";

  group PMUECCEDCTST_TVT_RUNCODE ( ordered, run_addr = CPU0_PMI_PSPR, align=256 )
  {
    section "PMUECCEDCTST_TVT_RAMCODE" (blocksize=4, attributes=rwx)
    {
       select ".text.PMUECCEDCTST_TVT_RAMCODE*";
    }
  }
  group PFLASH_MON_ECCEDC_RUNCODE ( ordered, run_addr = (CPU0_PMI_PSPR+0x100), align=4 )
  {
    section "PFLASH_MON_ECCEDC_RAMCODE" (blocksize=4, attributes=rwx)
    {
       select ".text.PFLASH_MON_ECCEDC_RAMCODE*";
    }
  }
}

