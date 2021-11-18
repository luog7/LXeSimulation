#ifndef LxeSD_h 
#define LxeSD_h 1
#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "LxeHit.hh"

class LxeSD : public G4VSensitiveDetector
{

  public:
      LxeSD(G4String name);
      ~LxeSD();

      void Initialize(G4HCofThisEvent*HCE);
      G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
      void EndOfEvent(G4HCofThisEvent*HCE);

  private:
      LxeHitsCollection* LxeCollection;
//////////////////////////////////////////////////////////////
      int get_Lxeid(G4Track*);
/////////////////////////////////////////////////////////////
      bool iftrig;
};

#endif

