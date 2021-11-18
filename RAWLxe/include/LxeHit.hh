#ifndef LxeHit_h 
#define LxeHit_h 1
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
class LxeHit : public G4VHit
{
public:

  LxeHit();
  ~LxeHit();
  LxeHit(const LxeHit&);
  const LxeHit& operator=(const LxeHit&);
  int operator==(const LxeHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);
public:
  void SetLxeID (G4int LxeID) {m_LxeID = LxeID;}
  void SetTrackIDLxe    (G4int trackLxe)      { m_trackIDLxe = trackLxe; }
  void SetPDGLxe    (G4int pdgLxe)      { m_pdgLxe = pdgLxe; }
  void SetMuGlobPosLxe (G4ThreeVector MuGlobPosLxe)   {m_MuGlobPosLxe = MuGlobPosLxe;}
  void SetMuGlobTimeLxe (G4float MuGlobTimeLxe)   {m_MuGlobTimeLxe = MuGlobTimeLxe;}
  void SetMuedepLxe    (G4float MuedepLxe)      { m_MuedepLxe = MuedepLxe; }
  void SetMuKinELxe (G4float MuKinELxe)	{m_MuKinELxe = MuKinELxe;}
  void SetMuMomentumLxe (G4ThreeVector MuMomentumLxe) {m_MuMomentumLxe = MuMomentumLxe;}
  
  G4int GetLxeID()	{return m_LxeID;}
  G4int GetTrackIDLxe()       {return m_trackIDLxe;}
  G4int GetPDGLxe()	{return m_pdgLxe;}
  G4ThreeVector GetMuGlobPosLxe()	{return m_MuGlobPosLxe;}
  G4ThreeVector GetMuMomentumLxe() {return m_MuMomentumLxe;}
  G4float GetMuGlobTimeLxe()	{return m_MuGlobTimeLxe;}
  G4float GetMuedepLxe()	{return m_MuedepLxe;}
  G4float GetMuKinELxe()	{return m_MuKinELxe;}
private:
  G4int         m_LxeID;
  G4int         m_trackIDLxe;
  G4int         m_pdgLxe;
  G4ThreeVector m_MuGlobPosLxe;
  G4ThreeVector m_MuMomentumLxe;
  G4float	m_MuGlobTimeLxe;
  G4float	m_MuedepLxe;
  G4float	m_MuKinELxe;
};

typedef G4THitsCollection<LxeHit> LxeHitsCollection;

extern G4Allocator<LxeHit> LxeHitAllocator;

inline void* LxeHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) LxeHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void LxeHit::operator delete(void *aHit)
{
  LxeHitAllocator.FreeSingle((LxeHit*) aHit);
}


#endif

