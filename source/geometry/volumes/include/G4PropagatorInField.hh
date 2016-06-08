// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4PropagatorInField.hh,v 1.5 1999/07/27 20:56:12 japost Exp $
// GEANT4 tag $Name: geant4-00-01-patch1 $
//
// 
// ------------------------------------------------------------------------
//	GEANT 4  include file implementation
//
//	For information related to this code contact:
//	CERN, IT Division (formely CN), ASD group
// ------------------------------------------------------------------------
// 
//  This class performs the navigation/propagation of a particle/track 
//  in a magnetic field. The field is in general non-uniform.
//    For the calculation of the path, it relies on the class G4MagTr.
//
//  class G4PropagatorInField 
//      Methods:
//        ComputeStep(..)
//        CalculateStepTimeAndAccuracy(..) 
//        LocateIntersectionPoint(..)
//
// 25.10.96 John Apostolakis,  design and implementation 
// 25.03.97 John Apostolakis,  adaptation for G4Transportation and cleanup
// ------------------------------------------------------------------------
#ifndef G4PropagatorInField_hh 
#define G4PropagatorInField_hh  1

#include "globals.hh"
#include "G4FieldTrack.hh"
// #include "G4VPhysicalVolume.hh"
// class  G4VPhysicalVolume;

#include "G4Navigator.hh"
#include "G4ChordFinder.hh"

#include "G4FieldManager.hh"

// #include "G4MagIntegratorDriver.hh"

class G4PropagatorInField {

 public:
   //  To create an object, must have an object that calculates the Curved 
   //  paths and also must know the value of the maximum displacement allowed
   //

   G4PropagatorInField( G4Navigator    *theNavigator, 
			G4FieldManager *detectorFieldMgr);

   G4PropagatorInField( G4Navigator   *theNavigator );
  ~G4PropagatorInField(){};

   // Compute the next geometric Step
   //
   G4double ComputeStep(G4FieldTrack  &pFieldTrack,
			G4double pCurrentProposedStepLength,
			G4double       &pNewSafety, 
			G4VPhysicalVolume *pPhysVol=0 );

   G4double ComputeStep(const G4ThreeVector &pGlobalPoint,
		        const G4ThreeVector &pCurveTangent,    // Unit vector
		              G4double pCurrentProposedStepLength,
			      G4double       &pNewSafety, 
                       	      G4VPhysicalVolume *pPhysVol=0 );
                                        // Current Volume (to check)

   // Return the state after the Step
   // 
   G4ThreeVector  EndPosition();       
   G4ThreeVector  EndMomentumDir();
   G4bool         IsParticleLooping();

   //   The accuracy of finding an intersection
   //
   G4double  DeltaIntersection(); 

   //   The accuracy of a single Step
   //
   G4double  DeltaOneStep();

   //   The ratio   DeltaOneStep()/h_current_step
   //
   G4double  GetEpsilonStep();  // Relative accuracy for current Step (Calc.)
   void      SetEpsilonStep(G4double newEps);

   void SetChargeMomentumMass( G4double Charge,         // in e+ units
			       G4double Momentum,       // in Geant4 units
			       G4double pMass);  

   G4ChordFinder* GetChordFinder();
   // void        SetChordFinder(G4ChordFinder* newCF);  // Not yet relevant

   G4int  SetVerboseLevel( G4int Verbose ){ return fVerboseLevel=Verbose; }
   G4int  Verbose(){ return fVerboseLevel; }

                                   //   Accuracies:
   G4double  GetDeltaIntersection();   //   for boundary intersection
   G4double  GetDeltaOneStep();        //   for one tracking/physics step
                                    
   // Sets both accuracies,
   //    maintaining a particular ratio Delta Interaction / OneStep )
   void    SetAccuraciesWithDeltaOneStep(G4double deltaOneStep);  

   // A maximum for the number of steps that a (looping) particle can take
   G4int   GetMaxLoopCount();
   void    SetMaxLoopCount(G4int new_max);

   //   Print Method - useful mostly for debugging this class
   //
   void printStatus( 
                  const G4FieldTrack&  StartFT,
		  const G4FieldTrack&  CurrentFT, 
                  G4double             requestStep, 
                  G4double             safety,
                  G4int                Step, 
                  G4VPhysicalVolume*   startVolume);

   //  The Field Manager of the Detector
   // 
   // void  SetGlobalFieldMgr( G4FieldManager *detectorFieldMgr );
   G4FieldTrack    GetEndState() { return End_PointAndTangent; }

 private:
   // If such an intersection exists, this function 
   // calculate the intersection point of the true path of the particle 
   // with the surface of the current volume (or of one of its daughters). 
   //  (Should use lateral displacement as measure of convergence). 
   //
   G4bool LocateIntersectionPoint( 
	    const  G4FieldTrack&       CurveStartPointTangent,  //  A
	    const  G4FieldTrack&       CurveEndPointTangent,    //  B
	    const  G4ThreeVector&     TrialPoint,              //  E
		   G4FieldTrack&       IntersectPointTangent);  // Output


  //  DATA Members
  // ----------------------------------------------------------------------
 private:

   // The  Field Manager of the whole Detector
   // 
   G4FieldManager *fDetectorFieldMgr; 

   G4Navigator   *fNavigator;

   //  STATE information
   // ------------------

   G4double    fEpsilonStep;  // Relative accuracy for current Step (Calc.)

   // End point storage:
   //
   G4FieldTrack    End_PointAndTangent;

   G4bool      fParticleIsLooping;

   //  For debuging purposes
   G4int  fVerboseLevel;

   //  Values for the required accuracies
   //
   G4double  fDelta_One_Step_Value;      //  for one tracking/physics step
   G4double  fDelta_Intersection_Val;    //  for boundary intersection

   //  Their default values ...  (set in G4PropagatemagField.cc)
   //
   static const G4double  fDefault_Delta_One_Step_Value;   // = 0.25 * mm;
   static const G4double  fDefault_Delta_Intersection_Val; // = 0.1 * mm;

   G4int  fmax_loop_count;

   //  Variables to keep track of "abnormal" case - which causes loop
   G4int     fNoZeroStep;                //  Counter of zeroStep
   G4int     fThresholdNo_ZeroSteps;    //  Threshold: above this - action
                       // G4double  fMidPoint_CurveLen_of_LastAttempt= -1;
   G4double  fFull_CurveLen_of_LastAttempt; 
   G4double  fLast_ProposedStepLength; 
}; // End of class G4PropagatorInField {

//  Defines the constructor.
//
#include "G4PropagatorInField.icc"

#endif 
// End of   "#ifndef G4PropagatorInField_hh"