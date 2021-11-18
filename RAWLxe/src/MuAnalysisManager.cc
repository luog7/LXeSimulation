#include "MuAnalysisManager.hh"
#include "G4UnitsTable.hh"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "Randomize.hh"
#include "MuPMTHit.hh"
#include "MuPMTSD.hh"
#include "PscintHit.hh"
#include "PscintSD.hh"
#include "LxeHit.hh"
#include "LxeSD.hh"
#include "G4EventManager.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "G4UImanager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Navigator.hh"
#include "G4TransportationManager.hh"
#include "G4VPhysicalVolume.hh"
using namespace CLHEP;

MuAnalysisManager* MuAnalysisManager::fManager = 0;

MuAnalysisManager* MuAnalysisManager::getInstance()
{
  	if(!fManager) 
	{
    	fManager = new MuAnalysisManager();
  	}
  	return fManager;
}

void MuAnalysisManager::dispose()
{
  	delete fManager;
  	fManager = 0;
}

MuAnalysisManager::MuAnalysisManager()
{
  	paraTree = 0;
	evtTree = 0;
  	TString outputname="output/";
  	char numstr[100];
  	G4long seed = time(NULL);
  	sprintf(numstr,"%ld",seed);
  	TString NUMstr = numstr;
  	//m_fileName = "Sample"+NUMstr+".root";
  	m_fileName = outputname+ NUMstr +"MuSim_output.root";
}

MuAnalysisManager::~MuAnalysisManager()
{
}

void MuAnalysisManager::bookEventTree()
{
  	paraTree = new TTree("para","Parameters used in Simulation");
	paraTree->Branch("PscintLength",&m_PsL,"Length/F");
	paraTree->Branch("PscintHeight",&m_PsH,"Height/F");
	//paraTree->Branch("TeflonLength",&m_TeL,"Length/F");
  	paraTree->Branch("PscintYield",&m_Yield,"Yield/F");
  	paraTree->Branch("PscintFastTime",&m_pft,"pft/F");
  	paraTree->Branch("PscintSlowTime",&m_pst,"pst/F");
  	paraTree->Branch("PscintRefractiveindex",&m_prd,"prd/F");
  	paraTree->Branch("TeflonRefractiveindex",&m_trd,"trd/F");
  	paraTree->Branch("TeflonReflectivity",&m_trf,"trf/F");
  	paraTree->Branch("TeflonEfficiency",&m_tec,"tec/F");
  	evtTree = new TTree("evt", "evtTreeInfo");
  	evtTree->Branch("evtID", &m_eventID, "evtID/I");
  	evtTree->Branch("nPhotons", &m_nPhotons, "nPhotons/I");
  	evtTree->Branch("energy", m_energy, "energy[nPhotons]/F");
  	evtTree->Branch("hitTime", m_hitTime, "hitTime[nPhotons]/D");
  	evtTree->Branch("pmtID", m_pmtID, "pmtID[nPhotons]/I");
  	//   PMT
  	evtTree->Branch("nPMTs", &m_npmts_byPMT, "nPMTs/I");
  	evtTree->Branch("nPE_byPMT", m_nPE_byPMT, "nPE_byPMT[nPMTs]/I");
  	evtTree->Branch("PMTID_byPMT", m_PMTID_byPMT, "PMTID_byPMT[nPMTs]/I");
////////////////////////////////////////////////////////////////////
  	//   Hit's position
  	evtTree->Branch("LocalPosX", m_localpos_x, "LocalPosX[nPhotons]/F");
  	evtTree->Branch("LocalPosY", m_localpos_y, "LocalPosY[nPhotons]/F");
  	evtTree->Branch("LocalPosZ", m_localpos_z, "LocalPosZ[nPhotons]/F");
  	//   Hit's direction
  	evtTree->Branch("LocalDirX", m_localdir_x, "LocalDirX[nPhotons]/F");
  	evtTree->Branch("LocalDirY", m_localdir_y, "LocalDirY[nPhotons]/F");
  	evtTree->Branch("LocalDirZ", m_localdir_z, "LocalDirZ[nPhotons]/F");
  	//   Hit's Global Position
  	evtTree->Branch("GlobalPosX", m_globalpos_x, "GlobalPosX[nPhotons]/F");
  	evtTree->Branch("GlobalPosY", m_globalpos_y, "GlobalPosY[nPhotons]/F");
  	evtTree->Branch("GlobalPosZ", m_globalpos_z, "GlobalPosZ[nPhotons]/F");
///////////////////////////////////////////////////////////////////////
	//   muon truth info
	MCTruthTree = new TTree("MuMCTruthTree","muon truth info");
  	MCTruthTree->Branch("MuhitTimes", &m_MuhitTimes, "MuhitTimes/I");
  	MCTruthTree->Branch("PscintID",m_PscintID,"PscintID[MuhitTimes]/I");
  	MCTruthTree->Branch("trackID",m_trackID,"trackID[MuhitTimes]/I");
  	MCTruthTree->Branch("pdg",m_pdg,"pdg[MuhitTimes]/I");
  	MCTruthTree->Branch("MuGlobTime",m_MuGlobTime,"MuGlobTime[MuhitTimes]/F");
  	MCTruthTree->Branch("MuposX",m_Mupos_x,"MuposX[MuhitTimes]/F");
  	MCTruthTree->Branch("MuposY",m_Mupos_y,"MuposY[MuhitTimes]/F");
  	MCTruthTree->Branch("MuposZ",m_Mupos_z,"MuposZ[MuhitTimes]/F");
  	MCTruthTree->Branch("MuMomentumX",m_MuMomentum_x,"MuMomentumX[MuhitTimes]/F");
  	MCTruthTree->Branch("MuMomentumY",m_MuMomentum_y,"MuMomentumY[MuhitTimes]/F");
  	MCTruthTree->Branch("MuMomentumZ",m_MuMomentum_z,"MuMomentumZ[MuhitTimes]/F");
  	MCTruthTree->Branch("MuTheta",m_MuTheta,"MuTheta[MuhitTimes]/F");
  	MCTruthTree->Branch("MuPhi",m_MuPhi,"MuPhi[MuhitTimes]/F");
  	MCTruthTree->Branch("Muedep",m_Muedep,"Muedep[MuhitTimes]/F");
  	MCTruthTree->Branch("MuKinE",m_MuKinE,"MuKinE[MuhitTimes]/F");
	////
        MCTruthTree->Branch("MuhitTimesLxe", &m_MuhitTimesLxe, "MuhitTimesLxe/I");
        MCTruthTree->Branch("LxeID",m_LxeID,"LxeID[MuhitTimesLxe]/I");
        MCTruthTree->Branch("trackIDLxe",m_trackIDLxe,"trackIDLxe[MuhitTimesLxe]/I");
        MCTruthTree->Branch("pdgLxe",m_pdgLxe,"pdgLxe[MuhitTimesLxe]/I");
        MCTruthTree->Branch("MuGlobTimeLxe",m_MuGlobTimeLxe,"MuGlobTimeLxe[MuhitTimesLxe]/F");
        MCTruthTree->Branch("MuposXLxe",m_Mupos_xLxe,"MuposXLxe[MuhitTimesLxe]/F");
        MCTruthTree->Branch("MuposYLxe",m_Mupos_yLxe,"MuposYLxe[MuhitTimesLxe]/F");
        MCTruthTree->Branch("MuposZLxe",m_Mupos_zLxe,"MuposZLxe[MuhitTimesLxe]/F");
        MCTruthTree->Branch("MuMomentumXLxe",m_MuMomentum_xLxe,"MuMomentumXLxe[MuhitTimesLxe]/F");
        MCTruthTree->Branch("MuMomentumYLxe",m_MuMomentum_yLxe,"MuMomentumYLxe[MuhitTimesLxe]/F");
        MCTruthTree->Branch("MuMomentumZLxe",m_MuMomentum_zLxe,"MuMomentumZLxe[MuhitTimesLxe]/F");
        MCTruthTree->Branch("MuThetaLxe",m_MuThetaLxe,"MuThetaLxe[MuhitTimesLxe]/F");
        MCTruthTree->Branch("MuPhiLxe",m_MuPhiLxe,"MuPhiLxe[MuhitTimesLxe]/F");
        MCTruthTree->Branch("MuedepLxe",m_MuedepLxe,"MuedepLxe[MuhitTimesLxe]/F");
        MCTruthTree->Branch("MuKinELxe",m_MuKinELxe,"MuKinELxe[MuhitTimesLxe]/F");
}

void MuAnalysisManager::BeginOfRun()
{
	//G4cout << "MuAnalysisManager: Histograms are booked and the run has been started" << G4endl;
	m_PsL = 0;
	m_PsH = 0;
	m_Yield = 0;
	m_pft = 0;
	m_pst = 0;
	m_prd = 0;
	m_trd = 0;
	m_trf = 0;
	m_tec = 0;
  	newfile = new TFile(m_fileName, "recreate");
  	newfile->cd();
  	bookEventTree();
}

void MuAnalysisManager::EndOfRun()
{
  	newfile->cd();
  	paraTree->Fill();
  	paraTree->Write();
  	evtTree->Write();
	MCTruthTree->Write();
  	newfile->Close();
}

void MuAnalysisManager::BeginOfEvent()
{
	m_nPhotons = 0;
  	m_MuhitTimes = 0;
 	m_MuhitTimesLxe = 0;
 	for(int i = 0; i < 20000000; i++) 	
	{
      	m_energy[i] = 0;
      	m_hitTime[i] = 0.;
      	m_pmtID[i] = 0;
      	m_localpos_x[i] = 0.;
      	m_localpos_y[i] = 0.;
      	m_localpos_z[i] = 0.;

      	m_localdir_x[i] = 0.;
      	m_localdir_y[i] = 0.;
      	m_localdir_z[i] = 0.;
      	m_globalpos_x[i] = 0.;
      	m_globalpos_y[i] = 0.;
      	m_globalpos_z[i] = 0.;
	}
	for(int i = 0; i < 20000000; i++)
        {
      	m_PscintID[i]=0;
      	m_trackID[i]=0;
      	m_pdg[i]=0;
	m_MuGlobTime[i]=0;
      	m_Mupos_x[i]=0;
      	m_Mupos_y[i]=0;
      	m_Mupos_z[i]=0;
      	m_MuMomentum_x[i]=0;
      	m_MuMomentum_y[i]=0;
      	m_MuMomentum_z[i]=0;
      	m_MuTheta[i]=0;
      	m_MuPhi[i]=0;
      	m_Muedep[i]=0;
      	m_MuKinE[i]=0;
	
	m_LxeID[i]=0;
        m_trackIDLxe[i]=0;
        m_pdgLxe[i]=0;
        m_MuGlobTimeLxe[i]=0;
        m_Mupos_xLxe[i]=0;
        m_Mupos_yLxe[i]=0;
        m_Mupos_zLxe[i]=0;
        m_MuMomentum_xLxe[i]=0;
        m_MuMomentum_yLxe[i]=0;
        m_MuMomentum_zLxe[i]=0;
        m_MuThetaLxe[i]=0;
        m_MuPhiLxe[i]=0;
        m_MuedepLxe[i]=0;
        m_MuKinELxe[i]=0; 
   	}
 	for(int ii = 0; ii < 20000000; ii++)
	{
      	m_nPE_byPMT[ii]=0.;
      	m_PMTID_byPMT[ii]=0.;
	}
	m_cache_bypmt.clear();  
}

void MuAnalysisManager::EndOfEvent()
{
  	evtTree->Fill();
	MCTruthTree->Fill();
	//G4cout << "MuAnalysisManager:"<< m_nPhotons << G4endl;
}
