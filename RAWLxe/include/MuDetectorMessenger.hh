#ifndef MuDetectorMessenger_h
#define MuDetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class MuDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcommand;
class G4UIcmdWithABool;
class G4UIcmdWithADouble;
class G4UIcmdWithoutParameter;

class MuDetectorMessenger: public G4UImessenger
{
  public:

    MuDetectorMessenger(MuDetectorConstruction*);
    virtual ~MuDetectorMessenger();
    virtual void SetNewValue(G4UIcommand*, G4String);

  private:

    MuDetectorConstruction*      fMuDetector;
    G4UIdirectory*               fDetectorDir;
    G4UIcmdWith3VectorAndUnit*   fDimensionsCmd;
    G4UIcmdWithADoubleAndUnit*   fPscintLCmd;
    G4UIcmdWithADoubleAndUnit*   fPscintWCmd;
    G4UIcmdWithADoubleAndUnit*   fPscintHCmd;
    G4UIcmdWithADoubleAndUnit*   fTeflonLCmd;
    G4UIcmdWithADoubleAndUnit*   fTeflonWCmd;
    G4UIcmdWithADoubleAndUnit*   fwindowThicknessPMTCmd;
    G4UIcmdWithADoubleAndUnit*   frTrunkCmd;
    G4UIcmdWithADoubleAndUnit*   faPmtCmd;
    G4UIcmdWithADoubleAndUnit*   fbPmtCmd;
    G4UIcmdWithADoubleAndUnit*   fhPmtCmd;
    G4UIcommand*                 fDefaultsCmd;
    G4UIcmdWithADouble*          fPscintYield;
    G4UIcmdWithADouble*   	 fPscintFastTime;
    G4UIcmdWithADouble*   	 fPscintSlowTime;
    G4UIcmdWithADouble*          fPscintRindexCmd;
    G4UIcmdWithADouble*          fTeflonRindexCmd;
    G4UIcmdWithADouble*          fTeflonReflectCmd;
    G4UIcmdWithADouble*          fTeflonEfficenCmd;
    G4UIcmdWithoutParameter*     UpdateCmd;
};

#endif

