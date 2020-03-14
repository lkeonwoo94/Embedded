//________________________________________________________________________
//                      Integrator920T Specific Information
//________________________________________________________________________ 

How Do I Configure a MetroTRK Remote Debugger Connection?
--------------------------------------------------------
If there is no remote connection set up for the MetroTRK:
Select Preferences from the Edit pull-down menu to open the IDE pref panels.
Select Remote Connections from the Debugger pref panels.  Click Add.
Give your new connection a name and select ARM - MetroTRK for the Debugger.
Select the Serial Port that your Integrator board is connected to and 
configure the other settings to match the Integrator's hardware.  See ARM's 
Integrator920T documentation for more info on these settings.  Click OK to 
close the New Connection window.

If there is a remote connection set up for the MetroTRK:
Select Preferences from the Edit pull-down menu to open the IDE pref panels.
Select the Remote Connections from the Debugger pref panels.  Select the 
remote connection set up for the MetroTRK and hit Change to access the 
connection window.  From there you can reconfigure any of the settings you
wish.
Note: At Present the METROTRK is not Available for Integrator Target.

How Do I Configure a Multi-ICE Remote Debugger Connection?
---------------------------------------------------------
If there is no remote connection set up for the Multi-ICE:
Select Preferences from the Edit pull-down menu to open the IDE pref panels.
Select the Remote Connections from the Debugger pref panels.  Click Add.
Give your new connection a name and select ARM RDI for the Debugger.
Click Browse and browse to the Multi-ICE.dll in your ARM Multi-ICE 
installation***.  Click Configure.  This will bring up ARM's Multi-ICE Setup 
window.  Follow the directions to configure your connection.  When you've
saved your configuration file, click OK to close the New Connection window.

If there is a remote connection set up for the RDI:
Select Preferences from the Edit pull-down menu to open the IDE pref panels.
Select the Remote Connections from the Debugger pref panels.  Select the 
remote connection set up for the Multi-ICE and hit Change to access the 
connection window.  From there you can select Configure to reconfigure 
your connection.

***Note: The Multi-ICE is not included in the CodeWarrior installation,
and must be purchased separately.

Configure ARM Debugger Settings Preference Panel when Multi-ICE is used
-----------------------------------------------------------------------

By default, no initialization file is selected by the stationery. But,
the targets require this file to initialize the memory system on the
integrator920t board.

Check the "Use Target Initialization File"
Browse to the <install>\ARM_EABI_Support\Initialization_Files folder.

pick up the init file for this board

--------------------------------------------------
Debugging ROM Debug  & Rom Release Stationery:
-------------------------------------------------
While Debugging ROM Stationery Pl. ensure that the following options in the "ARM Debugger Setting Panel" Under 'Program Download options'
for both 'Initial Launch' & 'Successive Runs' are  unchecked.
//'Executable', 'Constant Data','Initialized Data',& 'Uninitialized Data'.

ROM Startup stationery -- When ROM target is chosen 
====================================================================

Standalone Application for ARM Integrator Board

This simple application blinks LED D7(Green) and D9(Red) after booting 
the board standalone. 

The application also demonstrates exception handling (Entry and Exit) 
====================================================================

====================================================================
MEMORY MAP OF INTEGRATOR:
	
MEMORY MAP:

The user Flash starts at 0x24000000 and goes to 0x25ffffff
 
DIP SWITCH S1 SETTINGS

Set the Switch S1-1 and S1-4 to the OFF position. 
Set the Switch S1-2 and S1-3 to the ON position
     
====================================================================

Target Integrator_ROM_A_BE_D and Integrator_ROM_A_BE:

These targets creates a S-Record file, which could be put into the 
application flash area on the board by the CW flash programmer.

Refer to the readme.txt at

{CodeWarrior}\Bin\Plugins\Support\Flash_Programmer\ARM_EABI\readme.txt

to program the flash on Integrator board. 

Notes: 

-The targeted flash needs to be first erased before programming.

-For ROM debugging ensure that the MultiICE is configured to reset board at startup

-Since the ROM executable is linked at 0x24000000, the offset setting in flash programmer
 should be unchecked or alternately set to 0x0

When the ROM image has been written into the flash, the board can 
boot standalone.

Switch OFF power to the Board. 

Remove JTAG cable from the board.

Switch On power to the board.

=====================================================================

The application runs in three stages:

- First stage blinks LED D7 five times at power on / reset.

- Second stage demonstrates successfull exception entry by blinking
  LED D9 five times under SWI.

- Third and final stage demonstrates successful exception exit by blinking 
  both D7 and D9 five times.
  

To appreciate exception handling, you can comment out the "swi 0x776655;"
statement, recompile and program the executable in Flash. This time the 
second stage will be skipped.
=====================================================================


//------------------------------------------------------------------------
//	General Overview
//------------------------------------------------------------------------

This project stationery is designed to get you up and running
quickly with CodeWarrior for ARM.  This includes stationery for debugging 
on the DragonBall MX1 and MX-Lite via the MetroTRK and the Multi-ICE.
There are other stationery set up for debugging with the Virtio, as well as
on the Integrator920T and Evaluator7T boards via the MetroTRK and Multi-ICE. 

The project has Five targets:  RAM Debug, RAM Rel,ROM Debug,Rom Release and Build All.
The Debug & Release targets are almost identical, but are 
set to build at different compiler optimizations, Minimum(0) & Most(1) 
respectively.  The Build All target has been included for 
your convenience and simply builds all of the other targets.

//------------------------------------------------------------------------
//	Getting Started
//------------------------------------------------------------------------

Most of the target settings are already configured for you, but you
will need to configure the debugger settings.  Once you have a project 
created from this stationery, open the Edit pull-down menu and select
Debug Settings... (Alt+F7). Select the Remote Debugging pref panel from 
the left column.  If want to debug via the MetroTRK, select the Connection 
that you've set up in the IDE Preferences for Remote Debugging via the 
MetroTRK.  Otherwise, select the Connection that you've set up for Remote 
Debugging via the Multi-ICE.  We recommend that you make sure the project 
is working properly before you begin adding your own code.  Select Make 
and then Debug from the Project pull-down menu****.  If everything is working 
properly, the debugger window should come up and be stopped at main().  If 
there is a problem, please consult the Targeting_ARM_Systems.pdf for more 
information on debugging via the MetroTRK, or consult ARM's Multi-ICE 
documentation.

****Note: When debugging via the Multi-ICE, remember to launch the Multi-ICE 
server before launching the CW debugger.  If you've installed ARM's 
Multi-ICE software, you should be able to access the Multi-ICE server 
through your Startup menu.  Alternatively, execute Multi-ICEServer.exe in
your ARM Multi-ICE installation.  You may also reconfigure your CW 
Multi-ICE Remote Debugger Connection, which will bring up a Failed to 
Connect window that will ask whether you want to launch the Multi-ICE 
server.

//------------------------------------------------------------------------
//	Adding your own code
//------------------------------------------------------------------------

Once everything is working as expected, you can begin adding your own code
to the project.  Keep in mind that we provide this as an example of how to
get up and running quickly with CodeWarrior.  Feel free to modify any of 
the source provided. 


//------------------------------------------------------------------------
//	Contacting Metrowerks
//------------------------------------------------------------------------

For bug reports, technical questions, and suggestions, please use the
forms in the Release Notes folder on the CD, and send them to:

emb_support@metrowerks.com        : For bug reports.
cw_suggestion@metrowerks.com      : For suggestions.


