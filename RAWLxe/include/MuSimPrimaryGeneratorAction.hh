#ifndef MuSimPrimaryGeneratorAction_h
#define MuSimPrimaryGeneratorAction_h 1

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

class G4ParticleGun;
class G4Event;
class MuSimPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    MuSimPrimaryGeneratorAction(G4String gen);
    ~MuSimPrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);

  private:
        G4String gun;
        G4ParticleGun* fGun;
	G4ParticleGun* particleGun;
	G4ParticleTable* particleTable;
	G4String particleName;
	G4double er;
  private:
        TF1* f1;
	G4long seed;
    	bool verbose;
	double Energy;
	Double_t start;
	Double_t end;
	Double_t xlogmin;
	Double_t xlogmax;
	Int_t nbins;
	Double_t dlogx;
	Double_t* xbins;
	Double_t xlog;
	TH1D* E;
	TH1D* Dist;
  private:
        static Double_t distribution(Double_t* x,Double_t* par);
};

#endif

