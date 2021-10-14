#ifndef MuActionInitializer_h
#define MuActionInitializer_h 1

#include "G4VUserActionInitialization.hh"
#include "globals.hh"
#include "MuDetectorConstruction.hh"
class MuDetectorConstruction;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class MuActionInitializer : public G4VUserActionInitialization
{
public:

  MuActionInitializer(MuDetectorConstruction*, G4String gen);
  ~MuActionInitializer(){;};

  void Build() const;
  void BuildForMaster() const;
private:
  MuDetectorConstruction* fDetector;
  G4String gun;
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

