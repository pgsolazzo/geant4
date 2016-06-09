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
// $Id: B02ScoringDetectorConstruction.hh,v 1.2 2002/04/19 10:54:26 gcosmo Exp $
// GEANT4 tag $Name: geant4-06-00 $
//

#ifndef B02ScoringDetectorConstruction_hh 
#define B02ScoringDetectorConstruction_hh  B02ScoringDetectorConstruction_hh 

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume; 

class B02ScoringDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  B02ScoringDetectorConstruction(){}
  ~B02ScoringDetectorConstruction(){}

  G4VPhysicalVolume* Construct();
  
};

#endif