# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=socken - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to socken - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "socken - Win32 Release" && "$(CFG)" != "socken - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "socken.mak" CFG="socken - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "socken - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "socken - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "socken - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "socken - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\socken.exe"

CLEAN : 
	-@erase "$(INTDIR)\async.obj"
	-@erase "$(INTDIR)\Setup.obj"
	-@erase "$(INTDIR)\sock.obj"
	-@erase "$(INTDIR)\socken.obj"
	-@erase "$(INTDIR)\socken.pch"
	-@erase "$(INTDIR)\socken.res"
	-@erase "$(INTDIR)\sockenDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\talky2Dlg.obj"
	-@erase "$(OUTDIR)\socken.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/socken.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c\
 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/socken.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/socken.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 wsock32.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=wsock32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/socken.pdb" /machine:I386 /out:"$(OUTDIR)/socken.exe" 
LINK32_OBJS= \
	"$(INTDIR)\async.obj" \
	"$(INTDIR)\Setup.obj" \
	"$(INTDIR)\sock.obj" \
	"$(INTDIR)\socken.obj" \
	"$(INTDIR)\socken.res" \
	"$(INTDIR)\sockenDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\talky2Dlg.obj"

"$(OUTDIR)\socken.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "socken - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\socken.exe" "$(OUTDIR)\socken.bsc"

CLEAN : 
	-@erase "$(INTDIR)\async.obj"
	-@erase "$(INTDIR)\async.sbr"
	-@erase "$(INTDIR)\Setup.obj"
	-@erase "$(INTDIR)\Setup.sbr"
	-@erase "$(INTDIR)\sock.obj"
	-@erase "$(INTDIR)\sock.sbr"
	-@erase "$(INTDIR)\socken.obj"
	-@erase "$(INTDIR)\socken.pch"
	-@erase "$(INTDIR)\socken.res"
	-@erase "$(INTDIR)\socken.sbr"
	-@erase "$(INTDIR)\sockenDlg.obj"
	-@erase "$(INTDIR)\sockenDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\talky2Dlg.obj"
	-@erase "$(INTDIR)\talky2Dlg.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\socken.bsc"
	-@erase "$(OUTDIR)\socken.exe"
	-@erase "$(OUTDIR)\socken.ilk"
	-@erase "$(OUTDIR)\socken.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/socken.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/socken.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/socken.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\async.sbr" \
	"$(INTDIR)\Setup.sbr" \
	"$(INTDIR)\sock.sbr" \
	"$(INTDIR)\socken.sbr" \
	"$(INTDIR)\sockenDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\talky2Dlg.sbr"

"$(OUTDIR)\socken.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 wsock32.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=wsock32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/socken.pdb" /debug /machine:I386 /out:"$(OUTDIR)/socken.exe" 
LINK32_OBJS= \
	"$(INTDIR)\async.obj" \
	"$(INTDIR)\Setup.obj" \
	"$(INTDIR)\sock.obj" \
	"$(INTDIR)\socken.obj" \
	"$(INTDIR)\socken.res" \
	"$(INTDIR)\sockenDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\talky2Dlg.obj"

"$(OUTDIR)\socken.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "socken - Win32 Release"
# Name "socken - Win32 Debug"

!IF  "$(CFG)" == "socken - Win32 Release"

!ELSEIF  "$(CFG)" == "socken - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\sockenDlg.cpp
DEP_CPP_SOCKE=\
	".\Sock.h"\
	".\socken.h"\
	".\sockenDlg.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "socken - Win32 Release"


"$(INTDIR)\sockenDlg.obj" : $(SOURCE) $(DEP_CPP_SOCKE) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"


!ELSEIF  "$(CFG)" == "socken - Win32 Debug"


"$(INTDIR)\sockenDlg.obj" : $(SOURCE) $(DEP_CPP_SOCKE) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"

"$(INTDIR)\sockenDlg.sbr" : $(SOURCE) $(DEP_CPP_SOCKE) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "socken - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/socken.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\socken.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "socken - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/socken.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\socken.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\socken.rc

"$(INTDIR)\socken.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\socken.cpp
DEP_CPP_SOCKEN=\
	".\Setup.h"\
	".\Sock.h"\
	".\socken.h"\
	".\sockenDlg.h"\
	".\StdAfx.h"\
	".\talky2Dlg.h"\
	

!IF  "$(CFG)" == "socken - Win32 Release"


"$(INTDIR)\socken.obj" : $(SOURCE) $(DEP_CPP_SOCKEN) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"


!ELSEIF  "$(CFG)" == "socken - Win32 Debug"


"$(INTDIR)\socken.obj" : $(SOURCE) $(DEP_CPP_SOCKEN) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"

"$(INTDIR)\socken.sbr" : $(SOURCE) $(DEP_CPP_SOCKEN) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\async.cpp
DEP_CPP_ASYNC=\
	".\async.h"\
	".\Sock.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "socken - Win32 Release"


"$(INTDIR)\async.obj" : $(SOURCE) $(DEP_CPP_ASYNC) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"


!ELSEIF  "$(CFG)" == "socken - Win32 Debug"


"$(INTDIR)\async.obj" : $(SOURCE) $(DEP_CPP_ASYNC) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"

"$(INTDIR)\async.sbr" : $(SOURCE) $(DEP_CPP_ASYNC) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\sock.cpp
DEP_CPP_SOCK_=\
	".\async.h"\
	".\Sock.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "socken - Win32 Release"


"$(INTDIR)\sock.obj" : $(SOURCE) $(DEP_CPP_SOCK_) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"


!ELSEIF  "$(CFG)" == "socken - Win32 Debug"


"$(INTDIR)\sock.obj" : $(SOURCE) $(DEP_CPP_SOCK_) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"

"$(INTDIR)\sock.sbr" : $(SOURCE) $(DEP_CPP_SOCK_) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\talky2Dlg.cpp
DEP_CPP_TALKY=\
	".\Sock.h"\
	".\StdAfx.h"\
	".\talky2Dlg.h"\
	

!IF  "$(CFG)" == "socken - Win32 Release"


"$(INTDIR)\talky2Dlg.obj" : $(SOURCE) $(DEP_CPP_TALKY) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"


!ELSEIF  "$(CFG)" == "socken - Win32 Debug"


"$(INTDIR)\talky2Dlg.obj" : $(SOURCE) $(DEP_CPP_TALKY) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"

"$(INTDIR)\talky2Dlg.sbr" : $(SOURCE) $(DEP_CPP_TALKY) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Setup.cpp
DEP_CPP_SETUP=\
	".\Setup.h"\
	".\socken.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "socken - Win32 Release"


"$(INTDIR)\Setup.obj" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"


!ELSEIF  "$(CFG)" == "socken - Win32 Debug"


"$(INTDIR)\Setup.obj" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"

"$(INTDIR)\Setup.sbr" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"\
 "$(INTDIR)\socken.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
