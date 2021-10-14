#ifndef MuEventAction_h
#define MuEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4Track.hh"
class MuEventActionMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class MuEventAction : public G4UserEventAction
{
  public:
    MuEventAction();
   ~MuEventAction();

  public:
    void BeginOfEventAction(const G4Event* anEvent);
    void EndOfEventAction(const G4Event* anEvent);
    
    // Tracking Action
    virtual void PreUserTrackingAction(const G4Track* aTrack);
    virtual void PostUserTrackingAction(const G4Track* aTrack);

};

#endif


