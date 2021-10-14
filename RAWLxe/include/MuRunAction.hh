#ifndef MuRunAction_h
#define MuRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class MuDetectorConstruction;
class G4Run;
#include "G4TransportationManager.hh"
#include "G4Navigator.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"

class MuRunAction : public G4UserRunAction
{
  public:
    MuRunAction(MuDetectorConstruction*);
   ~MuRunAction();
   void outGDML();
  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
  private:
    MuDetectorConstruction* fDetector;
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

