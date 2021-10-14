#include "PscintHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<PscintHit> PscintHitAllocator;

PscintHit::PscintHit() {}

PscintHit::~PscintHit() {}

PscintHit::PscintHit(const PscintHit& right)
  : G4VHit()
{

  m_PscintID   = right.m_PscintID;
  m_trackID   = right.m_trackID;
  m_pdg   = right.m_pdg;
  m_MuGlobPos   = right.m_MuGlobPos;
  m_MuMomentum = right.m_MuMomentum;
  m_MuGlobTime   = right.m_MuGlobTime;
  m_Muedep   = right.m_Muedep;
  m_MuKinE   = right.m_MuKinE;
}

const PscintHit& PscintHit::operator=(const PscintHit& right)
{

  m_PscintID   = right.m_PscintID;
  m_trackID   = right.m_trackID;
  m_pdg   = right.m_pdg;
  m_MuGlobPos   = right.m_MuGlobPos;
  m_MuMomentum = right.m_MuMomentum;
  m_MuGlobTime   = right.m_MuGlobTime;
  m_Muedep   = right.m_Muedep;
  m_MuKinE   = right.m_MuKinE;
  return *this;
}

int PscintHit::operator==(const PscintHit& right) const
{
  return (this==&right) ? 1 : 0;
}


