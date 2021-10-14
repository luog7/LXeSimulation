#ifndef PscintSD_h 
#define PscintSD_h 1
#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "PscintHit.hh"

class PscintSD : public G4VSensitiveDetector
{

  public:
      PscintSD(G4String name);
      ~PscintSD();

      void Initialize(G4HCofThisEvent*HCE);
      G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
      void EndOfEvent(G4HCofThisEvent*HCE);

  private:
      PscintHitsCollection* PscintCollection;
//////////////////////////////////////////////////////////////
      int get_Pscintid(G4Track*);
/////////////////////////////////////////////////////////////
      bool iftrig;
};

#endif

