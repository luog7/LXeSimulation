#ifndef MuPMTSD_h
#define MuPMTSD_h 1
#include "MuPMTHit.hh"
#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
class MuPMTSD : public G4VSensitiveDetector
{

  public:
      MuPMTSD(G4String name);
      ~MuPMTSD();

      void Initialize(G4HCofThisEvent*HCE);
      G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
      void EndOfEvent(G4HCofThisEvent*HCE);

  private:
      MuPMTHitsCollection* PMTCollection;
//////////////////////////////////////////////////////////////
      int get_pmtid(G4Track*);
/////////////////////////////////////////////////////////////
      bool iftrig;
};

#endif

