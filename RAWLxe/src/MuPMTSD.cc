#include "MuPMTSD.hh"
#include "MuPMTHit.hh"
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
#include "MuAnalysisManager.hh"
#include "G4OpticalPhoton.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
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
#include <cassert>
#include <map>
#include "G4PhysicalConstants.hh"
MuPMTSD::MuPMTSD( G4String name )
  : G4VSensitiveDetector(name)
{
  	PMTCollection=NULL;
  	collectionName.insert("MuPMTInfo");
}

MuPMTSD::~MuPMTSD()
{
}

void MuPMTSD::Initialize(G4HCofThisEvent* HCE){
  	PMTCollection = new MuPMTHitsCollection(SensitiveDetectorName,collectionName[0]);
  	//A way to keep all the hits of this event in one place if needed
  	static G4int HCID = -1;
  	if(HCID<0)
	{
    	HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  	}
  	HCE->AddHitsCollection( HCID, PMTCollection );
}

G4bool MuPMTSD::ProcessHits(G4Step* aStep,G4TouchableHistory* ){
	if (aStep == NULL) return false;
	G4double edep = aStep->GetTotalEnergyDeposit();
	if(edep==0.) return false;
	G4Track* fTrack = aStep->GetTrack();
	//if(fTrack->GetDefinition() != G4Neutron::Neutron()) return false;
	if(fTrack->GetDefinition() != G4MuonMinus::MuonMinus() && fTrack->GetDefinition() != G4MuonPlus::MuonPlus() ) return false;
	//G4cout<<"G4Mu    "<<fTrack->GetDefinition()->GetPDGEncoding()<<endl;
	//####################################################################
	//####################################################################
	/*G4ThreeVector momentum(0,0,-1);
	G4ThreeVector angleCerenkov;
	if(fTrack->GetCreatorProcess()->GetProcessName()=="Cerenkov" && fTrack->GetParentID() == 1){
	angleCerenkov = fTrack->GetMomentumDirection();
	double AngleCerenkov = momentum.angle(angleCerenkov);
                G4cout<<AngleCerenkov/twopi*360<<G4endl;}
	*/
	//std::cout<<fTrack->GetCreatorProcess()->GetProcessName()<<std::endl;
	//####################################################################
	//####################################################################
	int PMTid = get_pmtid(fTrack);
	G4float Pedep = aStep->GetTotalEnergyDeposit();
	G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint* postStepPoint = aStep->GetPostStepPoint();
	const G4AffineTransform& trans = fTrack->GetTouchable()->GetHistory()->GetTopTransform();
	G4double time = postStepPoint->GetGlobalTime();
	//cout<<"time: "<<time<<endl;
	const G4ThreeVector& global_pos = preStepPoint->GetPosition();
	//const G4ThreeVector& global_pos = postStepPoint->GetPosition();
	G4ThreeVector local_pos = trans.TransformPoint(global_pos);
	G4ThreeVector local_dir = trans.TransformAxis(fTrack->GetMomentum());
	local_dir = local_dir.unit();
	MuPMTHit* hit = new MuPMTHit();
	hit->SetpmtID(PMTid);
	hit->SetLocalPos(local_pos);
	hit->SetLocalDir(local_dir);
	//hit->SethitTime( fTrack->GetGlobalTime() );
	hit->SethitTime(time);
	hit->Setglobal(global_pos);
	hit->Setenerge(Pedep);
	PMTCollection->insert(hit);
	return true;
}

void MuPMTSD::EndOfEvent(G4HCofThisEvent* ) {}

int MuPMTSD::get_pmtid(G4Track *track) {

        int ipmt= -1;
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
                ipmt= touch->GetReplicaNumber(id+idid-1);
                break;
            }
        }
        if (ipmt < 0) {
            G4Exception(" could not find envelope -- where am I !?!", // issue
                    "", //Error Code
                    FatalException, // severity
                    "");
        }
    }
        return ipmt;
}


