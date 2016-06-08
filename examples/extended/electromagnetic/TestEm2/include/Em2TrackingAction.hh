//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: Em2TrackingAction.hh,v 1.4 2001/10/25 15:12:06 maire Exp $
// GEANT4 tag $Name: geant4-04-00 $
//
//

#ifndef Em2TrackingAction_h
#define Em2TrackingAction_h 1

#include "G4UserTrackingAction.hh"

class Em2RunAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class Em2TrackingAction : public G4UserTrackingAction {

  public:  
    Em2TrackingAction(Em2RunAction*);
   ~Em2TrackingAction() {};
   
    void PostUserTrackingAction(const G4Track*);
    
  private:
    Em2RunAction* Em2Run;  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif