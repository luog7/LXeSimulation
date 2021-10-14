#include "MuActionInitializer.hh"
#include "NeutrinoSimPrimaryGeneratorAction.hh"
//#include "MuSimPrimaryGeneratorAction.hh"
#include "MuRunAction.hh"
#include "MuEventAction.hh"
#include "MuStackingAction.hh"
#include "MuDetectorConstruction.hh"
#include "G4GeneralParticleSource.hh"
MuActionInitializer::MuActionInitializer(MuDetectorConstruction* det,G4String gen) :
  G4VUserActionInitialization(), fDetector(det),gun(gen)
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MuActionInitializer::Build() const
{
  //SetUserAction(new MuSimPrimaryGeneratorAction(gun));
  SetUserAction(new NeutrinoSimPrimaryGeneratorAction());
  SetUserAction(new MuRunAction(fDetector));
  SetUserAction(new MuEventAction());
//  SetUserAction(new MuSteppingAction());
  SetUserAction(new MuStackingAction());

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MuActionInitializer::BuildForMaster() const
{
  //Run action in the master
  SetUserAction(new MuRunAction(fDetector));
}


