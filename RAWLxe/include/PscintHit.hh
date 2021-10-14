#ifndef PscintHit_h 
#define PscintHit_h 1
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
class PscintHit : public G4VHit
{
public:

  PscintHit();
  ~PscintHit();
  PscintHit(const PscintHit&);
  const PscintHit& operator=(const PscintHit&);
  int operator==(const PscintHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);
public:
  void SetPscintID (G4int PscintID) {m_PscintID = PscintID;}
  void SetTrackID    (G4int track)      { m_trackID = track; }
  void SetPDG    (G4int pdg)      { m_pdg = pdg; }
  void SetMuGlobPos (G4ThreeVector MuGlobPos)   {m_MuGlobPos = MuGlobPos;}
  void SetMuGlobTime (G4float MuGlobTime)   {m_MuGlobTime = MuGlobTime;}
  void SetMuedep    (G4float Muedep)      { m_Muedep = Muedep; }
  void SetMuKinE (G4float MuKinE)	{m_MuKinE = MuKinE;}
  void SetMuMomentum (G4ThreeVector MuMomentum) {m_MuMomentum = MuMomentum;}
  
  G4int GetPscintID()	{return m_PscintID;}
  G4int GetTrackID()       {return m_trackID;}
  G4int GetPDG()	{return m_pdg;}
  G4ThreeVector GetMuGlobPos()	{return m_MuGlobPos;}
  G4ThreeVector GetMuMomentum() {return m_MuMomentum;}
  G4float GetMuGlobTime()	{return m_MuGlobTime;}
  G4float GetMuedep()	{return m_Muedep;}
  G4float GetMuKinE()	{return m_MuKinE;}
private:
  G4int         m_PscintID;
  G4int         m_trackID;
  G4int         m_pdg;
  G4ThreeVector m_MuGlobPos;
  G4ThreeVector m_MuMomentum;
  G4float	m_MuGlobTime;
  G4float	m_Muedep;
  G4float	m_MuKinE;
};

typedef G4THitsCollection<PscintHit> PscintHitsCollection;

extern G4Allocator<PscintHit> PscintHitAllocator;

inline void* PscintHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) PscintHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void PscintHit::operator delete(void *aHit)
{
  PscintHitAllocator.FreeSingle((PscintHit*) aHit);
}


#endif

