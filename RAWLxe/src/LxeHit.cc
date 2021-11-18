#include "LxeHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<LxeHit> LxeHitAllocator;

LxeHit::LxeHit() {}

LxeHit::~LxeHit() {}

LxeHit::LxeHit(const LxeHit& right)
  : G4VHit()
{

  m_LxeID   = right.m_LxeID;
  m_trackIDLxe   = right.m_trackIDLxe;
  m_pdgLxe   = right.m_pdgLxe;
  m_MuGlobPosLxe   = right.m_MuGlobPosLxe;
  m_MuMomentumLxe = right.m_MuMomentumLxe;
  m_MuGlobTimeLxe   = right.m_MuGlobTimeLxe;
  m_MuedepLxe   = right.m_MuedepLxe;
  m_MuKinELxe   = right.m_MuKinELxe;
}

const LxeHit& LxeHit::operator=(const LxeHit& right)
{

  m_LxeID   = right.m_LxeID;
  m_trackIDLxe   = right.m_trackIDLxe;
  m_pdgLxe   = right.m_pdgLxe;
  m_MuGlobPosLxe   = right.m_MuGlobPosLxe;
  m_MuMomentumLxe = right.m_MuMomentumLxe;
  m_MuGlobTimeLxe   = right.m_MuGlobTimeLxe;
  m_MuedepLxe   = right.m_MuedepLxe;
  m_MuKinELxe   = right.m_MuKinELxe;
  return *this;
}

int LxeHit::operator==(const LxeHit& right) const
{
  return (this==&right) ? 1 : 0;
}


