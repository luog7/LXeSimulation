#ifndef MuPMTHit_h
#define MuPMTHit_h 1
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class MuPMTHit : public G4VHit
{
public:

  MuPMTHit();
  ~MuPMTHit();
  MuPMTHit(const MuPMTHit&);
  const MuPMTHit& operator=(const MuPMTHit&);
  int operator==(const MuPMTHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);
public:
  void SetpmtID (G4int pmtid)     {m_pmtID = pmtid; };
  void SetLocalPos(G4ThreeVector LocalPos) {m_LocalPos = LocalPos;};
  void SetLocalDir(G4ThreeVector LocalDir) {m_LocalDir = LocalDir;};
  void SethitTime  (G4double time)      { m_time = time; };
  void Setglobal(G4ThreeVector gloP) {m_globalPos=gloP;}
  void Setenerge(G4float ene){m_energy = ene;}
  G4int GetpmtID()    {return m_pmtID;};
  G4ThreeVector GetLocalPos() {return m_LocalPos;};
  G4ThreeVector GetLocalDir() {return m_LocalDir;};
  G4float Getenerge() {return m_energy;}
  G4ThreeVector Getglobal() {return m_globalPos;}
  G4float GethitTime()       { return m_time; };
private:
  G4int         m_pmtID;
  G4ThreeVector m_LocalPos;
  G4ThreeVector m_LocalDir;
  G4double      m_time;
  G4ThreeVector m_globalPos;
  G4float       m_energy;
};

typedef G4THitsCollection<MuPMTHit> MuPMTHitsCollection;

extern G4Allocator<MuPMTHit> MuPMTHitAllocator;

inline void* MuPMTHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) MuPMTHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void MuPMTHit::operator delete(void *aHit)
{
  MuPMTHitAllocator.FreeSingle((MuPMTHit*) aHit);
}


#endif

