========================================================================
    Sample code for extending Movie Maker 2.0's special effects
========================================================================

This is the sample project for creating 2D and 3D transitions and effects for Windows Movie Maker 2.0.  
Using the project, Microsoft Visual Studio.Net, and the DirectX Transform SDK, you can create new special effects.  

The sample code included demostrates how to create a Blue Adjust effect and a new 3D transition called Melt.  

The package contains a Visual Studio.Net C++ project MMSTFX and a series of XML files 
which describe effects and transitions.  Some of the XML files are extensions of 
existing Movie Maker special effects and some are completely new.  The new ones require 
that a DLL be compiled by building the C++ project.

When compiling this sample be sure to add the DXMedia SDK's include directory i.e. "C:\DXMedia\Include" to your Visual C++'s include path.

To try out the new sample transitions and effects, create the "AddOnTFX" directory in Movie Maker's "Shared" install directory i.e. "C:\Program files\Movie Maker\Shared\AddOnTFX" and copy to it the XML files from the "XML" directory in this sample i.e. "C:\MMSTFX\XML\*.xml".  
Register the enclosed DLL "MMSTFX.dll" in the sample's "Bin" directory i.e. from the command line: "regsvr32 c:\MMSTFX\Bin\MMSTFX.dll."
Run Movie Maker and look for the new transitions and effects.


========================================================================
    XML files
========================================================================

These files should be placed in Movie Maker's add on special effects directory
which is called "AddOnTFX" and is located under Movie Maker's install Shared directory.
	ie. "C:\Program Files\Movie Maker\Shared\AddOnTFX".
This directory does not exist by default and should be created and the XML files copied in.


AlternatePageCurls.xml -	Two extensions of Movie Maker's existing Page Curl transforms.
							Sets alternate the starting corners for the page curl.

SuperBlur.xml - Extension of Movie Maker's existing Blur effect.  

SuperBrightness.xml - Extensions on Movie Maker's existing Brightness, Increase and Decrease effects.

WhirldwindDown.xml - Extension of Movie Maker's existing Whirlwind transition.


BlueAdjust.xml -	New effect to adjust amount of Blue in video.  The amount of blue added is 
					determined by the value Blue PARAM in the XML file.  This effects uses the
					CMMSpecialEffect object to alter the color balance in the video.
					Requires MMSTFX DLL to be built.
					
Melt.xml -	New 3D transition.  This XML file sets MeltIntensity which determines the amount of 
			melting which occurs before the first video slides away revealing the second video.
			Requires MMSTFX DLL to be built.
				 

========================================================================
    WIN32 DLL : MMSTFX Project Overview
========================================================================

MMSTFX.vcproj
    This is the main project file for this VC++ sample project.  Provides basic 2D image 
    processing through the DX Transform SDK and a simple 3D engine using Direct3D 7.
    
MMSTFX.idl
	Definition for IMMSampleTFX, the interface used for both the sample Blue Adjust 
	effect (CMMSampleEffect) and the Melt transition (CMMSampleTransition).  Note sharing a
	single interface is purely for convenience and brievity of the sample code, a DXT may 
	use any interface which inherits from IDXEffect.

MMSTFX.cpp
 	Main module source file for DLL.  Defines ATL _Module object, object map entries for 
 	COM objects, and DLL entry points supplied by this DLL.

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file named MMSTFX.pch and a precompiled
    types file named StdAfx.obj.  Miscellaneous classes and methods also are defined here.

MMSpecialEffectDXT.h, MMSpecialEffectDXT.cpp
	Contains two sample DXT's (DirectX Transforms) one effect CMMSampleEffect and
	one transition CMMSampleTransition, both built from a common base class CMMSpecialEffectDXT.
	
	CMMSpecialEffectDXT is a COM object which inherits from a base class CDXBaseNTo1 provided by
	the DXTransform SDK for creating video effects and transitions.  CMMSpecialEffectDXT handles
	communication and memory buffer manipulation between Movie Maker and the 
	class CMMSpecialEffect which implements the graphics portion the effect or transition.
	In this sample, CMMSpecialEffectDXT creates and stores a CMMSpecialEffect-based object in the 
	FinalConstruct() handlers of CMMSampleEffect and CMMSampleTransition.
	
MMSpecialEffect.h, MMSpecialEffect.cpp
	Contains the class CMMSpecialEffect for performing simple image processing effects as color, 
	brightness, and constrast adjustments on an input video buffer.  The sample effect Blue Adjust 
	uses this class to adjust the amount of blue in the video.
	
	CMMSpecialEffect is a base class.  By overriding the Initlize(), Execute() and Terminate() 
	methods	entirly new effects and transitions may be created.

3DSpecialEffect.h, 3DSpecialEffect.cpp
	Defines the classes CMM3DSpecialEffect, CSimple3DSpecialEffect, and CVideoPlane.
	
	CMM3DSpecialEffect inherits from CMMSpecialEffect and implements basic Direct3D functionality
	to create texture objects from the input video buffer(s) and a rendering target surface 
	directly on the output video buffer.  It declares methods to simplify which may be overridden:
	CreateScene, ReleaseScene, RenderScene, CreateSurfaces, RestoreSurfaces, ReleaseSurfaces.  
	Note that this class does not render anything, it is inherited by CSimple3DSpecialEffect 
	for this purpose.
	
	CSimple3DSpecialEffect inherits from CMM3DSpecialEffect and performs rendering.  Creates one or 
	two 3D plane(s) depending on if this if an effect or transition.  The planes are aligned to 
	the XZ plane, are 2 wide by 2 units high, and sit directly in front of the virtual camera.  
	The Melt sample transition uses this class by sliding the first video plane down the screen 
	revealing the second video plane behind it.
	
Frametimer.h, Frametimer.cpp
	Defines precision timer class.  Used to determine elapsed time in CMM3DSpecialEffect.	

/////////////////////////////////////////////////////////////////////////////
AppWizard has created the following resources:

MMSTFX.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.
    
MMSpecialEffectDXT1.rgs, MMSpecialEffectDXT2.rgs
	Registry entries to define CMMSampleEffect and CMMSampleTransition as 
	


/////////////////////////////////////////////////////////////////////////////
