#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4String.hh"
#include "TROOT.h"
#include "TH1F.h"
#include "TH1D.h"
#include <vector>
#include "TF2.h"
#include "TF1.h"
#include "G4GeneralParticleSource.hh"
class G4GeneralParticleSource;
//class G4ParticleGun;
class G4Event;
class NeutrinoSimPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    NeutrinoSimPrimaryGeneratorAction();
    ~NeutrinoSimPrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);
  private:
    G4GeneralParticleSource *fGParticleSource;
};

