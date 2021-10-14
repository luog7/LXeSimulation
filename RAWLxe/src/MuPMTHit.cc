#include "MuPMTHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<MuPMTHit> MuPMTHitAllocator;

MuPMTHit::MuPMTHit() {}

MuPMTHit::~MuPMTHit() {}

MuPMTHit::MuPMTHit(const MuPMTHit& right)
  : G4VHit()
{
  m_pmtID=right.m_pmtID;
  m_LocalPos=right.m_LocalPos;
  m_LocalDir=right.m_LocalDir;
  m_time=right.m_time;
  m_globalPos=right.m_globalPos;
  m_energy=right.m_energy;
}
const MuPMTHit& MuPMTHit::operator=(const MuPMTHit& right)
{
 m_pmtID=right.m_pmtID;
  m_LocalPos=right.m_LocalPos;
  m_LocalDir=right.m_LocalDir;
  m_time=right.m_time;
  m_globalPos=right.m_globalPos;
  m_energy=right.m_energy;
  return *this;
}
int MuPMTHit::operator==(const MuPMTHit& right) const
{
  return (this==&right) ? 1 : 0;
}



