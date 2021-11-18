#include "G4ios.hh"
#include "MuEventAction.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4UImanager.hh"
#include "G4UnitsTable.hh"
#include "G4UImanager.hh"
#include "MuAnalysisManager.hh"
#include "G4Event.hh"
#include "G4Track.hh"
#include "G4TrackingManager.hh"
#include "G4OpticalPhoton.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"

#include "G4TransportationManager.hh"
#include "G4Navigator.hh"
#include "G4VPhysicalVolume.hh"

#include "MuPMTHit.hh"
#include "MuPMTSD.hh"
#include "PscintHit.hh"
#include "PscintSD.hh"
#include "LxeHit.hh"
#include "LxeSD.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
MuEventAction::MuEventAction()
{
}

MuEventAction::~MuEventAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MuEventAction::BeginOfEventAction(const G4Event* evt)
{
	MuAnalysisManager::getInstance()->BeginOfEvent();
  	MuAnalysisManager::getInstance()->SetEventID(evt->GetEventID());
  
}
void MuEventAction::EndOfEventAction(const G4Event* evt)
{
	int nPhotons = 0;
	std::map<int, int> m_cache_bypmt;
	m_cache_bypmt.clear();
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	G4int scintCollID = SDman->GetCollectionID("PscintInfo");
	G4int pmtCollID = SDman->GetCollectionID("MuPMTInfo");
	G4int LxeCollID = SDman->GetCollectionID("LxeInfo");
	PscintHitsCollection* scintHC = 0;
  	MuPMTHitsCollection* pmtHC = 0;
  	LxeHitsCollection* LxeHC = 0;
	G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
	if (!HCE){
	std::cout<<"No hits collection found." << std::endl;
	}else {
        scintHC = (PscintHitsCollection*)(HCE->GetHC(scintCollID));
	pmtHC = (MuPMTHitsCollection*)(HCE->GetHC(pmtCollID));
        LxeHC = (LxeHitsCollection*)(HCE->GetHC(LxeCollID));
	}
	G4int NbHits = pmtHC->entries();
	//cout<<"G4int NbHits = pmtHC->entries();"<<NbHits<<endl;
	for (G4int i=0;i<NbHits;i++) {
        G4float m_energy = (*pmtHC)[i]->Getenerge();
        double hitTime = (*pmtHC)[i]->GethitTime();
        G4int m_pmtID = (*pmtHC)[i]->GetpmtID();
        m_cache_bypmt[m_pmtID] += 1;
        G4ThreeVector local_pos = (*pmtHC)[i]->GetLocalPos();
        G4float    m_localpos_x = local_pos.x();
        G4float    m_localpos_y = local_pos.y();
        G4float    m_localpos_z = local_pos.z();
	G4ThreeVector local_dir = (*pmtHC)[i]->GetLocalDir();
        G4float    m_localdir_x = local_dir.x();
        G4float    m_localdir_y = local_dir.y();
        G4float    m_localdir_z = local_dir.z();

        G4ThreeVector global_pos = (*pmtHC)[i]->Getglobal();
        G4float    m_globalpos_x = global_pos.x();
        G4float   m_globalpos_y = global_pos.y();
        G4float    m_globalpos_z = global_pos.z();
	if(m_globalpos_x>-15&&m_globalpos_x<1) cout<<m_globalpos_x<<endl;
        MuAnalysisManager::getInstance()->SetpmtID(nPhotons,m_pmtID);
	MuAnalysisManager::getInstance()->Setenergy(nPhotons,m_energy);
        MuAnalysisManager::getInstance()->SethitTime(nPhotons,hitTime);
	//cout<<"m_hitTime "<<hitTime<<endl;
        MuAnalysisManager::getInstance()->SetGlobalPosX(nPhotons, m_globalpos_x);
        MuAnalysisManager::getInstance()->SetGlobalPosY(nPhotons, m_globalpos_y);
        MuAnalysisManager::getInstance()->SetGlobalPosZ(nPhotons, m_globalpos_z);
	MuAnalysisManager::getInstance()->SetLocalX(nPhotons, m_localpos_x);     
        MuAnalysisManager::getInstance()->SetLocalY(nPhotons, m_localpos_y);
        MuAnalysisManager::getInstance()->SetLocalZ(nPhotons, m_localpos_z);
        MuAnalysisManager::getInstance()->SetLocalDirX(nPhotons, m_localdir_x);
        MuAnalysisManager::getInstance()->SetLocalDirY(nPhotons, m_localdir_y);
        MuAnalysisManager::getInstance()->SetLocalDirZ(nPhotons, m_localdir_z);
	nPhotons++;
      }
	int m_npmts_byPMT = 0;
    for (std::map<int,int>::iterator it = m_cache_bypmt.begin();
            it != m_cache_bypmt.end(); ++it) {
        G4int m_PMTID_byPMT = it->first;
        G4int m_nPE_byPMT = it->second;
        MuAnalysisManager::getInstance()->SetnPE_byPMT(m_npmts_byPMT,m_nPE_byPMT);
        MuAnalysisManager::getInstance()->SetPMTID_byPMT(m_npmts_byPMT,m_PMTID_byPMT);
        ++m_npmts_byPMT;
	}
	G4int NHits = scintHC->entries();
	//cout<<"G4int NHits = scintHC->entries(); "<<NHits<<endl;
	G4int MuhitTimes = 0;
        for (G4int j=0;j<NHits;j++){
	G4ThreeVector pos = (*scintHC)[j]->GetMuGlobPos();
        G4float    Muposx = pos.x();
        G4float    Muposy = pos.y();
        G4float    Muposz = pos.z();
	G4ThreeVector momentum = (*scintHC)[j]->GetMuMomentum();
        G4float    Mumomentumx = momentum.x();
        G4float    Mumomentumy = momentum.y();
        G4float    Mumomentumz = momentum.z();
	G4float    Theta = momentum.theta();
	G4float    Phi = momentum.phi();
	MuAnalysisManager::getInstance()->SetMuposx(MuhitTimes,Muposx);
	MuAnalysisManager::getInstance()->SetMuposy(MuhitTimes,Muposy);
	MuAnalysisManager::getInstance()->SetMuposz(MuhitTimes,Muposz);
	MuAnalysisManager::getInstance()->SetMuMomentumx(MuhitTimes,Mumomentumx);
        MuAnalysisManager::getInstance()->SetMuMomentumy(MuhitTimes,Mumomentumy);
        MuAnalysisManager::getInstance()->SetMuMomentumz(MuhitTimes,Mumomentumz);
	MuAnalysisManager::getInstance()->SetMuTheta(MuhitTimes,Theta);
	MuAnalysisManager::getInstance()->SetMuPhi(MuhitTimes,Phi);
	G4int scintid = (*scintHC)[j]->GetPscintID();
	G4int trackid = (*scintHC)[j]->GetTrackID();
	G4int pdg = (*scintHC)[j]->GetPDG();
	MuAnalysisManager::getInstance()->SetPscintID(MuhitTimes,scintid);
	MuAnalysisManager::getInstance()->SettrackID(MuhitTimes,trackid);
	MuAnalysisManager::getInstance()->Setpdg(MuhitTimes,pdg);
	G4double MuGtime = (*scintHC)[j]->GetMuGlobTime();
	G4float muedep = (*scintHC)[j]->GetMuedep();
	G4float muKinE = (*scintHC)[j]->GetMuKinE();
	//cout<<"MuGtime = (*scintHC)[j]->GetMuGlobTime(); "<<MuGtime<<endl;
	MuAnalysisManager::getInstance()->SetMuGlobTime(MuhitTimes,MuGtime);
	MuAnalysisManager::getInstance()->SetMuedep(MuhitTimes,muedep);
	MuAnalysisManager::getInstance()->SetMuKinE(MuhitTimes,muKinE);
	MuhitTimes++;
	}
	
	G4int NHit = LxeHC->entries();
	G4int MuhitTimesLxe = 0;
        for (G4int j=0;j<NHit;j++){
        G4ThreeVector posLxe = (*LxeHC)[j]->GetMuGlobPosLxe();
        G4float    MuposxLxe = posLxe.x();
        G4float    MuposyLxe = posLxe.y();
        G4float    MuposzLxe = posLxe.z();
        G4ThreeVector momentumLxe = (*LxeHC)[j]->GetMuMomentumLxe();
        G4float    MumomentumxLxe = momentumLxe.x();
        G4float    MumomentumyLxe = momentumLxe.y();
        G4float    MumomentumzLxe = momentumLxe.z();
        G4float    ThetaLxe = momentumLxe.theta();
        G4float    PhiLxe = momentumLxe.phi();
        MuAnalysisManager::getInstance()->SetMuposxLxe(MuhitTimesLxe,MuposxLxe);
        MuAnalysisManager::getInstance()->SetMuposyLxe(MuhitTimesLxe,MuposyLxe);
        MuAnalysisManager::getInstance()->SetMuposzLxe(MuhitTimesLxe,MuposzLxe);
        MuAnalysisManager::getInstance()->SetMuMomentumxLxe(MuhitTimesLxe,MumomentumxLxe);
        MuAnalysisManager::getInstance()->SetMuMomentumyLxe(MuhitTimesLxe,MumomentumyLxe);
        MuAnalysisManager::getInstance()->SetMuMomentumzLxe(MuhitTimesLxe,MumomentumzLxe);
        MuAnalysisManager::getInstance()->SetMuThetaLxe(MuhitTimesLxe,ThetaLxe);
        MuAnalysisManager::getInstance()->SetMuPhiLxe(MuhitTimesLxe,PhiLxe);
        G4int Lxeid = (*LxeHC)[j]->GetLxeID();
        G4int trackidLxe = (*LxeHC)[j]->GetTrackIDLxe();
        G4int pdgLxe = (*LxeHC)[j]->GetPDGLxe();
        MuAnalysisManager::getInstance()->SetLxeID(MuhitTimesLxe,Lxeid);
        MuAnalysisManager::getInstance()->SettrackIDLxe(MuhitTimesLxe,trackidLxe);
        MuAnalysisManager::getInstance()->SetpdgLxe(MuhitTimesLxe,pdgLxe);
        G4double MuGtimeLxe = (*LxeHC)[j]->GetMuGlobTimeLxe();
        G4float muedepLxe = (*LxeHC)[j]->GetMuedepLxe();
        G4float muKinELxe = (*LxeHC)[j]->GetMuKinELxe();
	MuAnalysisManager::getInstance()->SetMuGlobTimeLxe(MuhitTimesLxe,MuGtimeLxe);
        MuAnalysisManager::getInstance()->SetMuedepLxe(MuhitTimesLxe,muedepLxe);
        MuAnalysisManager::getInstance()->SetMuKinELxe(MuhitTimesLxe,muKinELxe);
        MuhitTimesLxe++;
	}
	MuAnalysisManager::getInstance()->SetMuhitTimes(MuhitTimes);
	MuAnalysisManager::getInstance()->SetMuhitTimesLxe(MuhitTimesLxe);
        MuAnalysisManager::getInstance()->SetNPhotons(nPhotons);
        MuAnalysisManager::getInstance()->SetnPMTs(m_npmts_byPMT);
        MuAnalysisManager::getInstance()->EndOfEvent();		
}
void MuEventAction::PreUserTrackingAction(const G4Track* /*aTrack*/) {
}
void MuEventAction::PostUserTrackingAction(const G4Track* /*aTrack*/) {
	/*G4TrackingManager* tm = G4EventManager::GetEventManager()
                                            -> GetTrackingManager();
	G4TrackVector* secondaries = tm->GimmeSecondaries();
	G4ThreeVector angleCerenkov;
	if(secondaries)
    	{
	size_t nSeco = secondaries->size();
        if(nSeco>0)
        	{
		for(size_t i=0;i<nSeco;i++)
            		{
				if ((*secondaries)[i]->GetCreatorProcess()
                    and (*secondaries)[i]->GetCreatorProcess()->GetProcessName() == "Cerenkov") 		{
				angleCerenkov = aTrack->GetMomentumDirection();
			G4cout<<angleCerenkov<<G4endl;
				}
	    		}
		}
    	}*/
}
