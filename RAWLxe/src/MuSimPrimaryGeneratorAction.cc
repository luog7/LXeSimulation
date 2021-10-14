#include "MuSimPrimaryGeneratorAction.hh"
//#include "MuPrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
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
MuSimPrimaryGeneratorAction::MuSimPrimaryGeneratorAction(G4String gen)
        :       G4VUserPrimaryGeneratorAction(), gun(gen)
{
        //particleGun = new MuPrimaryGeneratorAction();
        //fGun = new MuCosmicSpecturm();
	start = 0.01;
	end = 4000;
	verbose = false;
	er = G4UniformRand();
	G4int n_particle = 1;
	particleGun  = new G4ParticleGun(n_particle);
	fGun  = new G4ParticleGun(n_particle);
	particleTable = G4ParticleTable::GetParticleTable();
	if(er<=0.5)
        {
                particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="mu+"));
        	fGun->SetParticleDefinition(particleTable->FindParticle(particleName="mu-"));
	}
        else
        {
                particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="mu-"));
        	fGun->SetParticleDefinition(particleTable->FindParticle(particleName="mu+"));
	}
	Energy = 1000*MeV;
	particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0.5,-1));
	particleGun->SetParticleEnergy(Energy);
	particleGun->SetParticlePosition(G4ThreeVector(-50*mm,-50*mm,310*mm));
}

Double_t MuSimPrimaryGeneratorAction::distribution(Double_t* x,Double_t* p)
{
        Double_t E=p[0];
        Double_t costheta=x[0];
        Double_t val=0.14*TMath::Power(E,-2.7)*(1./(1.+1.1*E*costheta/115)+0.054/(1+1.1*E*costheta/850));
        return val;
}

MuSimPrimaryGeneratorAction::~MuSimPrimaryGeneratorAction()
{
        delete particleGun;
        delete fGun;
}

void MuSimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
        if(gun=="gps")
        {
                // For GPS generator
                G4cout<<"GPS generator used!"<<G4endl;
		//Energy = 1000*MeV;
		//particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0.5,-1));
  		particleGun->SetParticleEnergy(Energy);
  		//particleGun->SetParticlePosition(G4ThreeVector(-50*mm,-50*mm,310*mm));
  		G4cout << "Particle Energy: " << Energy << G4endl;		
                particleGun->GeneratePrimaryVertex(anEvent);
        }
	else if(gun=="muon")
        {
                // For cosmic ray muon generator
                G4cout<<"Cosmic ray muon generator used!"<<G4endl;
		f1 = new TF1("f1",distribution,0.25,1.,1);
		xlogmin = TMath::Log(start);
        	xlogmax = TMath::Log(end);
		nbins = 300;
		dlogx = (xlogmax-xlogmin)/(nbins);
        	xbins = new Double_t[nbins+1];
        	for(Int_t i=0; i<=nbins; i++)
        	{
        	xlog = xlogmin+i*dlogx;
        	xbins[i] = TMath::Power(10, xlog);
        	}
		E = new TH1D("","",800,0.01,4000);
	        Dist = new TH1D("","",nbins, xbins);
        	for(int ih=0;ih<4000;ih++){
	        f1->SetParameter(0,0.01+1*ih);
       		double content = f1->Integral(0.25,1);
        	E->SetBinContent(ih,content);
        	}
        	for(int ii=0;ii<5000000;ii++){
        	double energy = E->GetRandom();
        	Dist->Fill(energy);
        	}
        	Energy = Dist->GetRandom();
       		G4cout << "Particle Energy: " << Energy << G4endl;
		Energy = Energy*GeV;
        	G4double poscenter = 3*G4UniformRand();
        	G4double posPM = G4UniformRand();
        	double posX=0,posY=0,posZ=0;
        	double setPosP = 1071/2.,setPosM = -1071/2.;
		if(poscenter<=1) {if(posPM<=0.5) posX = setPosM;else posX = setPosP;}
        	if(poscenter>1&&poscenter<=2) {if(posPM<=0.5) posY = setPosM;else posY = setPosP;}
        	if(poscenter>2&&poscenter<=3) {if(posPM<=0.5) posZ = setPosM;else posZ = setPosP;}

        	double dirX = 1,dirY=1,dirZ=1;
        	/*if(posX==setPosM&&posY==0&&posZ==0) {dirX = 1;dirY = 1.9*G4UniformRand()-0.95;dirZ = 1.9*G4UniformRand()-0.95;}
        	if(posX==setPosP&&posY==0&&posZ==0) {dirX = -1;dirY = 1.9*G4UniformRand()-0.95;dirZ = 1.9*G4UniformRand()-0.95;}
        	if(posX==0&&posY==setPosM&&posZ==0) {dirY = 1;dirX = 1.9*G4UniformRand()-0.95;dirZ = 1.9*G4UniformRand()-0.95;}
        	if(posX==0&&posY==setPosP&&posZ==0) {dirY = -1;dirX = 1.9*G4UniformRand()-0.95;dirZ = 1.9*G4UniformRand()-0.95;}
		if(posX==0&&posY==0&&posZ==setPosM) {dirZ = 1;dirY = 1.9*G4UniformRand()-0.95;dirX = 1.9*G4UniformRand()-0.95;}
        	if(posX==0&&posY==0&&posZ==setPosP) {dirZ = -1;dirY = 1.9*G4UniformRand()-0.95;dirX = 1.9*G4UniformRand()-0.95;}
		*/
		dirZ = -1;dirY = 1.9*G4UniformRand()-0.95;dirX = 1.9*G4UniformRand()-0.95;
        	fGun->SetParticleEnergy(Energy);
		//fGun->SetParticlePosition(G4ThreeVector(posX*mm,posY*mm,posZ*mm));
        	fGun->SetParticlePosition(G4ThreeVector(0*mm,0*mm,setPosP*mm));	
		fGun->SetParticleMomentumDirection(G4ThreeVector(dirX,dirY,dirZ));
                fGun->GeneratePrimaryVertex(anEvent);
        }

}
