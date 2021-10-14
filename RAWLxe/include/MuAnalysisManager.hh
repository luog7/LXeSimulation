#ifndef MuAnalysisManager_h
#define MuAnalysisManager_h 1

#include "globals.hh"
#include "G4Track.hh"
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "TObjString.h"
#include <string>
#include "G4ThreeVector.hh"
#include "G4UserRunAction.hh"
using namespace std;

class G4Track;
class MuAnalysisManager
{
public:
  static MuAnalysisManager* getInstance();
  static void dispose();

  void bookEventTree();
  void BeginOfRun();
  void EndOfRun();
  void BeginOfEvent();
  void EndOfEvent();
  void setFileName(TString i) { m_fileName = i; }
  //para
  void SetPsL(Float_t i) {m_PsL = i;}
  void SetPsH(Float_t i) {m_PsH = i;}
  void SetTeL(Float_t i) {m_TeL = i;}
  //void SetTeH(Float_t i) {m_TeH = i;}
  void Setpy(Float_t i) { m_Yield = i; }
  void Setpst(Float_t i) { m_pst = i; }
  void Setpft(Float_t i) {m_pft = i; }
  void Setprd(Float_t i) {m_prd = i; }
  void Settrd(Float_t i) {m_trd = i; }
  void Settrf(Float_t i) {m_trf = i; }
  void Settec(Float_t i) {m_tec = i; }
  //event
  ////////////////////////////////////////////////////////
  void SetpmtID(Int_t i,Int_t j) {m_pmtID[i] = j;}
  void SetnPMTs(Int_t j){m_npmts_byPMT=j;}
  void SetnPE_byPMT(Int_t i,Int_t j){m_nPE_byPMT[i]=j;}
  void SetPMTID_byPMT(Int_t i,Int_t j){m_PMTID_byPMT[i]=j;}
  void SetLocalX(Int_t i,Float_t j) {m_localpos_x[i] = j;}
  void SetLocalY(Int_t i,Float_t j) {m_localpos_y[i] = j;}
  void SetLocalZ(Int_t i,Float_t j) {m_localpos_z[i] = j;}
  void SetLocalDirX(Int_t i,Float_t j) {m_localdir_x[i] = j;}
  void SetLocalDirY(Int_t i,Float_t j) {m_localdir_y[i] = j;}
  void SetLocalDirZ(Int_t i,Float_t j) {m_localdir_z[i] = j;}
  void SetEventID(Int_t i) { m_eventID = i; }
  void SetNPhotons(Int_t i) { m_nPhotons = i; }
  void Setenergy(Int_t i, Float_t j){m_energy[i]=j;}
  void SethitTime(Int_t i, Double_t j) { m_hitTime[i] = j;}
  void SetGlobalPosX(Int_t i,Float_t j) {m_globalpos_x[i] = j;}
  void SetGlobalPosY(Int_t i,Float_t j) {m_globalpos_y[i] = j;}
  void SetGlobalPosZ(Int_t i,Float_t j) {m_globalpos_z[i] = j;}
  //truth
  void SetMuedep(Int_t i, Float_t j){m_Muedep[i]=j;}
  void SetMuKinE(Int_t i, Float_t j){m_MuKinE[i]=j;}
  void SetMuGlobTime(Int_t i, Double_t j) { m_MuGlobTime[i] = j;}
  void SetMuposx(Int_t i,Float_t j) {m_Mupos_x[i] = j;}
  void SetMuposy(Int_t i,Float_t j) {m_Mupos_y[i] = j;}
  void SetMuposz(Int_t i,Float_t j) {m_Mupos_z[i] = j;}
  void SetMuMomentumx(Int_t i,Float_t j) {m_MuMomentum_x[i] = j;}
  void SetMuMomentumy(Int_t i,Float_t j) {m_MuMomentum_y[i] = j;}
  void SetMuMomentumz(Int_t i,Float_t j) {m_MuMomentum_z[i] = j;}
  void SetPscintID(Int_t i,Int_t j) {m_PscintID[i] = j;}
  void SetMuTheta(Int_t i,Float_t j) {m_MuTheta[i] = j;}
  void SetMuPhi(Int_t i,Float_t j) {m_MuPhi[i] = j;}
  void SettrackID(Int_t i,Int_t j) {m_trackID[i] = j;}
  void Setpdg(Int_t i,Int_t j) {m_pdg[i] = j;}
  void SetMuhitTimes(Int_t i) { m_MuhitTimes = i; }
public:
  static MuAnalysisManager* fManager;
  TFile* newfile;
  G4String m_fileName;
//////////////////////////////////////////
  TTree* paraTree;
  
  Float_t m_PsL;
  Float_t m_PsH;
  Float_t m_TeL;

  Float_t m_Yield;
  Float_t m_pst;
  Float_t m_pft;
  Float_t m_prd;
  Float_t m_trd;
  Float_t m_trf;
  Float_t m_tec;
/////////////////////////////////////////////
  TTree* evtTree;
  
  Int_t m_eventID;
  Int_t m_nPhotons;
  Int_t m_pmtID[20000000];
  Double_t m_hitTime[20000000];
  Float_t m_energy[20000000];
  Int_t m_npmts_byPMT;
  Int_t m_nPE_byPMT[2880000];
  Int_t m_PMTID_byPMT[2880000];
  Float_t m_globalpos_x[20000000];
  Float_t m_globalpos_y[20000000];
  Float_t m_globalpos_z[20000000];
  Float_t m_localpos_x[20000000];
  Float_t m_localpos_y[20000000];
  Float_t m_localpos_z[20000000];
  Float_t m_localdir_x[20000000];
  Float_t m_localdir_y[20000000];
  Float_t m_localdir_z[20000000];
  G4ThreeVector m_photonPos;
  std::map<int, int> m_cache_bypmt;
//////////////////////////////////////////////
  TTree* MCTruthTree;
  Int_t m_MuhitTimes;
  Int_t m_PscintID[20000000];
  Int_t m_trackID[20000000];
  Int_t m_pdg[20000000];
  Float_t m_MuGlobTime[20000000];
  Float_t m_Mupos_x[20000000];
  Float_t m_Mupos_y[20000000];
  Float_t m_Mupos_z[20000000];
  Float_t m_MuMomentum_x[20000000];
  Float_t m_MuMomentum_y[20000000];
  Float_t m_MuMomentum_z[20000000];
  Float_t m_MuTheta[20000000];
  Float_t m_MuPhi[20000000];
  Float_t m_Muedep[20000000];
  Float_t m_MuKinE[20000000];
//////////////////////////////////////////////
  
  private:
  MuAnalysisManager();
  ~MuAnalysisManager();
};
#endif

