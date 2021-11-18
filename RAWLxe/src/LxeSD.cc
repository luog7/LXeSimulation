#include "LxeSD.hh"
#include "LxeHit.hh"
#include "G4ParticleTypes.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4HCofThisEvent.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4LossTableManager.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4OpticalPhoton.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
#include <cassert>
#include "Randomize.hh"
#include "G4Allocator.hh"
#include "G4Alpha.hh"
#include "G4DataInterpolation.hh"
#include <G4OpticalPhoton.hh>
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4Step.hh"
#include <G4MuonPlus.hh>
#include <G4MuonMinus.hh>
#include <sstream>
#include <map>
#include "globals.hh"
#include "TSystem.h"
#include "G4PhysicalConstants.hh"
#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"
LxeSD::LxeSD( G4String name )
  : G4VSensitiveDetector(name)
{
  	LxeCollection=NULL; 
  	collectionName.insert("LxeInfo");
}

LxeSD::~LxeSD()
{
}

void LxeSD::Initialize(G4HCofThisEvent* HCE){
  	LxeCollection = new LxeHitsCollection(SensitiveDetectorName,collectionName[0]);
  	//A way to keep all the hits of this event in one place if needed
  	static G4int HCID = -1;
  	if(HCID<0)
	{
    	HCID = GetCollectionID(0);
  	}
  	HCE->AddHitsCollection( HCID, LxeCollection );
}

G4bool LxeSD::ProcessHits(G4Step* aStep,G4TouchableHistory* ){
  	if (aStep == NULL) return false;
  	G4double edep = aStep->GetTotalEnergyDeposit();
  	//if(edep==0.) return false; //No edep so dont count as hit
	G4Track* fTrack = aStep->GetTrack();
	G4ParticleDefinition* particle = fTrack->GetDefinition();
	G4String pname = particle->GetParticleName();
  	//G4StepPoint* PrePoint = aStep->GetPreStepPoint();
  	//G4StepPoint* PostPoint = aStep->GetPostStepPoint();
  	//G4int copyN = PrePoint->GetTouchableHandle()->GetCopyNumber();
  	//G4Material* material =  fTrack->GetMaterial();
  	//G4Material* material_post;
  	//material = aStep->GetPreStepPoint()->GetMaterial();
  	//material_post = aStep->GetPostStepPoint()->GetMaterial();
  	//G4String procName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  	//G4ThreeVector momentum(0.5,0.5,-1);
  	//if(fTrack->GetTrackID()==1){G4ThreeVector momentum = fTrack->GetMomentumDirection();std::cout<<momentum<<std::endl;}
  	//if(fTrack->GetParentID()==1&&fTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {G4ThreeVector momentump = fTrack->GetMomentumDirection();double angle2 = momentum.angle(momentump);std::cout<<angle2/twopi*360<<std::endl;}//std::cout<<aStep->GetPostStepPoint()->GetGlobalTime()<<std::endl;
  	//if(fTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()){std::cout<<"TrackID ="<<fTrack->GetTrackID()<<"\t"<<"matername ="<<material->GetName()<<"\t"<<"copyN ="<<copyN<<std::endl;std::cout<<"pname ="<<pname<<"\t"<< "procName ="<<procName<<std::endl;}
	//if(fTrack->GetDefinition() != G4MuonMinus::MuonMinus() && fTrack->GetDefinition() != G4MuonPlus::MuonPlus() ) return false;
	//if(fTrack->GetDefinition() != G4Neutron::NeutronDefinition() || aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()!="hadElastic") return false;
	if(fTrack->GetDefinition() != G4Neutron::NeutronDefinition() || aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()!="nCapture") return false;
	G4cout<<"wa! neutron in HDPE "<<fTrack->GetCreatorProcess()->GetProcessName()<<G4endl;
	//if(fTrack->GetDefinition() != G4Neutron::NeutronDefinition()) return false;
	//std::cout<<"TrackID ="<<fTrack->GetTrackID()<<"\t"<<"matername ="<<material->GetName()<<"\t"<<"copyN ="<<copyN<<std::endl;std::cout<<"pname ="<<pname<<"\t"<< "procName ="<<procName<<std::endl;
	//###########################################################
        /*G4ThreeVector momentum(0,0,-1);
        G4ThreeVector angleCerenkov;
        if(fTrack->GetCreatorProcess()->GetProcessName()=="Cerenkov" && fTrack->GetParentID() == 1){
        angleCerenkov = fTrack->GetMomentumDirection();
        double AngleCerenkov = momentum.angle(angleCerenkov);
                G4cout<<AngleCerenkov/twopi*360<<G4endl;}*/
        //###########################################################

	int Lxeid = get_Lxeid(fTrack);
	G4float muedep = aStep->GetTotalEnergyDeposit();
	G4StepPoint* thePrePoint = aStep->GetPreStepPoint();G4ThreeVector pos = thePrePoint->GetPosition();
	//G4StepPoint* thePostPoint = aStep->GetPostStepPoint();G4ThreeVector pos = thePostPoint->GetPosition();
  	G4ThreeVector momentum = fTrack->GetMomentumDirection();
	//G4cout<<momentum.theta()<<G4endl;
	//G4cout<<momentum.phi()<<G4endl;
	//G4cout<<momentum.x()<<G4endl;
	//G4cout<<momentum.y()<<G4endl;
	//G4cout<<momentum.z()<<G4endl;
	//pos/=2.;
	//G4cout<<fTrack->GetKineticEnergy()/GeV<<G4endl;
	G4float time = aStep->GetPostStepPoint()->GetGlobalTime();
	LxeHit* xeHit = new LxeHit();
	xeHit->SetLxeID(Lxeid);
	xeHit->SetTrackIDLxe(fTrack->GetTrackID());
	xeHit->SetPDGLxe(fTrack->GetDefinition()->GetPDGEncoding());
	xeHit->SetMuGlobPosLxe(pos);
	xeHit->SetMuGlobTimeLxe(time);
	xeHit->SetMuedepLxe(muedep);
	xeHit->SetMuKinELxe(fTrack->GetKineticEnergy()/MeV);
	xeHit->SetMuMomentumLxe(momentum);
	LxeCollection->insert(xeHit);
//}
	return true;
}

void LxeSD::EndOfEvent(G4HCofThisEvent* ) {}

int LxeSD::get_Lxeid(G4Track *track) {

        int Lxeid= -1;
        {
        const G4VTouchable* touch= track->GetTouchable();
        int nd= touch->GetHistoryDepth();
        int id=0;
        for (id=0; id<nd; id++) {
            if (touch->GetVolume(id)==track->GetVolume()) {
                int idid=1;
                G4VPhysicalVolume* tmp_pv=NULL;
                for (idid=1; idid < (nd-id); ++idid) {
                    tmp_pv = touch->GetVolume(id+idid);

                    G4LogicalVolume* mother_vol = tmp_pv->GetLogicalVolume();
                    G4LogicalVolume* daughter_vol = touch->GetVolume(id+idid-1)->GetLogicalVolume();
                    int no_daugh = mother_vol -> GetNoDaughters();
                    if (no_daugh > 1) {
                        int count = 0;
                        for (int i=0; (count<2) &&(i < no_daugh); ++i) {
                            if (daughter_vol->GetName()
                                    ==mother_vol->GetDaughter(i)->GetLogicalVolume()->GetName()) {
                                ++count;
                            }
                        }
                        if (count > 1) {
                            break;
                        }
                    }
                    // continue to find
                }
                Lxeid= touch->GetReplicaNumber(id+idid-1);
                break;
            }
        }
        if (Lxeid < 0) {
            G4Exception(" could not find envelope -- where am I !?!", // issue
                    "", //Error Code
                    FatalException, // severity
                    "");
        }
    }
        return Lxeid;
}

