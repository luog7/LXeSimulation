#include "NeutrinoSimPrimaryGeneratorAction.hh"
//#include "NeutrinoPrimaryGeneratorAction.hh"
#include "G4Event.hh"
//#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"
#include "Randomize.hh"
#include "globals.hh"
#include "TSystem.h"
#include "G4String.hh"
#include "TRandom3.h"
#include "TMath.h"
#include "time.h"
#include "G4SystemOfUnits.hh"
NeutrinoSimPrimaryGeneratorAction::NeutrinoSimPrimaryGeneratorAction()
        :       G4VUserPrimaryGeneratorAction(), fGParticleSource()
{
        //particleGun = new NeutrinoPrimaryGeneratorAction();
	fGParticleSource  = new G4GeneralParticleSource();
}

NeutrinoSimPrimaryGeneratorAction::~NeutrinoSimPrimaryGeneratorAction()
{
        delete fGParticleSource;
}

void NeutrinoSimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	fGParticleSource->GeneratePrimaryVertex(anEvent);
}
