#ifndef MuDetectorConstruction_H
#define MuDetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Box;
class G4Sphere;
class G4Tubs;
class G4SubtractionSolid;
#include "G4Material.hh"
#include "MuDetectorMessenger.hh"
#include "G4OpticalSurface.hh"
#include "G4VUserDetectorConstruction.hh"
#include "MuPMTSD.hh"
#include "PscintSD.hh"
#include "G4Cache.hh"
#include "LxeSD.hh"
class MuDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    MuDetectorConstruction(G4String input,G4bool gdml);
    G4String input_gdml;
    G4bool isgdml;
    virtual ~MuDetectorConstruction();
    virtual void ConstructSDandField();

    virtual G4VPhysicalVolume* Construct();
    //Functions to modify the geometry
    void SetDimensions(G4ThreeVector );
    void SetPscintL(G4double );
    void SetPscintW(G4double );
    void SetPscintH(G4double );
    void SetTeflonL(G4double );
    void SetTeflonW(G4double );
    void SetwindowThicknessPMT(G4double );
    void SetrTrunk(G4double );
    void SetaPMT(G4double );
    void SetbPMT(G4double );
    void SethPMT(G4double );
    //Functions to modify the para
    void SetPscintYield(G4double );
    void SetPscintFastTime(G4double );
    void SetPscintSlowTime(G4double );
    void SetPscintRindex(G4double );
    void SetTeflonRindex(G4double );
    void SetTeflonReflect(G4double );
    void SetTeflonEfficen(G4double );
    void SetDefaults();
    //Functions to get simulation inf
    G4double GetPscintH() const {return PscintH; };
    G4double GetPscintW() const {return PscintW; };
    G4double GetPscintL() const {return PscintL; };

    G4double GetTeflonL() const {return TeflonL; };
    G4double GetTeflonW() const {return TeflonW; };

    G4double GetPMTHeight() const {return hPMT; };
    G4double GetPMTMajor() const {return aPMT; };
    G4double GetPMTMinor() const {return bPMT; };

    G4double GetWorldX() const {return expHall_x; };
    G4double GetWorldY() const {return expHall_y; };
    G4double GetWorldZ() const {return expHall_z; };
    
    G4double GetPscintYield() const {return Pscintyield; };
    G4double GetPscintFastTime() const {return PscintFT; };
    G4double GetPscintSlowTime() const {return PscintST; };
    G4double GetPscintRindex() const {return Pscintrindex; };
    G4double GetTeflonRindex() const {return Teflonrindex; };
    G4double GetTeflonReflect() const {return Teflonreflect; };
    G4double GetTeflonEfficen() const {return Teflonefficen; };

    G4double GetPscintMass() const {return PscintMass; };
    //Update Geometry
    void UpdateGeometry();

  private:
    	//Detector Dimensions
        G4double expHall_x;
        G4double expHall_y;
        G4double expHall_z;

	//Teflon & Pscint
        G4double TeflonL;
	G4double TeflonW;
        G4double PscintH;
        G4double PscintW;
        G4double PscintL;
	//Fiber
	G4double FiberD;
	//PMT
        G4double windowThicknessPMT;
        G4double aPMT;
        G4double bPMT;
        G4double hPMT;
        G4double rTrunk;
	//Pscint & Teflon parameter
	G4double Pscintyield;
        G4double PscintFT;
        G4double PscintST;
        G4double Pscintrindex;
        G4double Teflonrindex;
        G4double Teflonreflect;
        G4double Teflonefficen;
	//Material
	G4Material* Air;
	G4Material* teflon;
	G4Material* LAB;
	G4Material* Aluminum;
	G4Material* fPMMA;
        G4Material* fPethylene1;
        G4Material* fPethylene2;
        G4Material* fPstyrene;
	G4Material* fLXe;
	G4Material* fPb;
	G4Material* fCu;
	G4Material* ssteel;
	//OpticalSurface
	G4OpticalSurface* photocath_opsurf;
	G4OpticalSurface* TeflonSurface;
	//Construct
        MuDetectorMessenger* fDetectorMessenger;
        G4VPhysicalVolume* ConstructDetector();
	void DefineMaterials();

        G4double PscintMass;
	//MaterialPropertiesTable
	G4MaterialPropertiesTable* Tef_mt;
        G4MaterialPropertiesTable* MPTscint;
	G4MaterialPropertiesTable* cathmetal_mt;
  	G4MaterialPropertiesTable* fLXe_mt;
	// Solid volumes
	G4Box* experimentalHall_box;
	G4Box* TX_box;
	G4Box* FiberX_Tubs;
	G4Tubs* TeflonX_boxall;
	G4SubtractionSolid* TeflonX_box;
	G4Box* PscintX_box;
	
        G4Box* TY_box;
        G4Tubs* FiberY_Tubs;
        G4Tubs* TeflonY_boxall;
        G4SubtractionSolid* TeflonY_box;
        G4Box* PscintY_box;
	G4Tubs* fPhotocath;
  	// Logical volumes
	G4LogicalVolume* experimentalHall_log;
	G4LogicalVolume*  Pscint_log;
	G4LogicalVolume*  pmt_wall_log;
	G4LogicalVolume*  vac_wall_log;
	G4LogicalVolume*  Fiber_log;
	G4LogicalVolume*  fPhotocath_log;
	G4LogicalVolume* shell_log;
	G4LogicalVolume* Teflon_log;
  	G4LogicalVolume* Lab_log1;
	G4LogicalVolume* Lab_log2;
	// Physical volumes
	G4VPhysicalVolume* experimentalHall_phys;
	G4VPhysicalVolume* Teflon_phys;
	G4VPhysicalVolume* Fiber_phys;
	G4VPhysicalVolume* Pscint_phys;
	G4VPhysicalVolume* fPhotocath_phys;
	G4VPhysicalVolume* shell_phys;
	G4VPhysicalVolume* Lxe_phys;
	G4VPhysicalVolume* Lab_phys1;
	G4VPhysicalVolume* Lab_phys2;
	//Sensitive Detectors
	G4Cache<PscintSD*> fScint_SD;
	G4Cache<MuPMTSD*> fPmt_SD;
	G4Cache<LxeSD*> fLxe_SD;
};
#endif

