// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4OpenInventorWin32.cc,v 1.3 1999/05/10 15:39:01 johna Exp $
// GEANT4 tag $Name: geant4-00-01 $
//
// OpenInventor graphics system factory.

#ifdef G4VIS_BUILD_OIWIN32_DRIVER

#include <Inventor/Xt/SoXt.h>

#include "G4OpenInventorWin32.hh"

#include "G4OpenInventorSceneHandler.hh"
#include "G4OpenInventorViewer.hh"

#include "G4Win32.hh"

G4OpenInventorWin32::G4OpenInventorWin32 ()
:G4OpenInventor("OpenInventorWin32","OIWIN32",G4VGraphicsSystem::threeD)
{
  SetInteractorManager (G4Win32::getInstance());
  GetInteractorManager () -> RemoveDispatcher((G4DispatchFunction)G4Win32::dispatchWin32Event);  
  GetInteractorManager () -> AddDispatcher   ((G4DispatchFunction)SoXt::dispatchEvent);

  Widget toplevel = (Widget)GetInteractorManager()->GetMainInteractor();

  SoXt::init(toplevel);

  InitHEPVis();
}

G4OpenInventorWin32::~G4OpenInventorWin32 () {}

#endif