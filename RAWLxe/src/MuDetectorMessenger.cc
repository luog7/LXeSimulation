#include "MuDetectorMessenger.hh"
#include "MuDetectorConstruction.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

MuDetectorMessenger::MuDetectorMessenger(MuDetectorConstruction* detector)
 : fMuDetector(detector)
{
  //Setup a command directory for detector controls with guidance
  fDetectorDir = new G4UIdirectory("/Mu/detector/");
  fDetectorDir->SetGuidance("Detector geometry control");

  //Various commands for modifying detector geometry
  fDimensionsCmd =
    new G4UIcmdWith3VectorAndUnit("/Mu/detector/dimensions",this);
  fDimensionsCmd->SetGuidance("Set the dimensions of the detector volume.");
  fDimensionsCmd->SetParameterName("expHall_x","expHall_y","expHall_z",true);
  fDimensionsCmd->SetDefaultUnit("mm");
  fDimensionsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fDimensionsCmd->SetToBeBroadcasted(true);
    
  fPscintLCmd = new G4UIcmdWithADoubleAndUnit("/Mu/detector/PscintL",this);
  fPscintLCmd->SetGuidance("Length of the Plastic scint.");
  fPscintLCmd->SetParameterName("PscintL",true);
  fPscintLCmd->SetDefaultUnit("mm");
  fPscintLCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fPscintLCmd->SetToBeBroadcasted(true);

  fPscintWCmd = new G4UIcmdWithADoubleAndUnit("/Mu/detector/PscintW",this);
  fPscintWCmd->SetGuidance("Width of the Plastic scint .");
  fPscintWCmd->SetParameterName("PscintW",true);
  fPscintWCmd->SetDefaultUnit("mm");
  fPscintWCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fPscintWCmd->SetToBeBroadcasted(true);

  fPscintHCmd = new G4UIcmdWithADoubleAndUnit("/Mu/detector/PscintH",this);
  fPscintHCmd->SetGuidance("Height the Plastic scint .");
  fPscintHCmd->SetParameterName("PscintH",true);
  fPscintHCmd->SetDefaultUnit("mm");
  fPscintHCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fPscintHCmd->SetToBeBroadcasted(true);

  fTeflonLCmd = new G4UIcmdWithADoubleAndUnit("/Mu/detector/TeflonL",this);

  fTeflonLCmd->SetGuidance("Length of the Teflon .");
  fTeflonLCmd->SetParameterName("TeflonL",true);
  fTeflonLCmd->SetDefaultUnit("mm");
  fTeflonLCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fTeflonLCmd->SetToBeBroadcasted(true);

  fTeflonWCmd = new G4UIcmdWithADoubleAndUnit("/Mu/detector/TeflonW",this);
  fTeflonWCmd->SetGuidance("Width of the Teflon .");
  fTeflonWCmd->SetParameterName("TeflonW",true);
  fTeflonWCmd->SetDefaultUnit("mm");
  fTeflonWCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fTeflonWCmd->SetToBeBroadcasted(true);
  fwindowThicknessPMTCmd = new G4UIcmdWithADoubleAndUnit("/Mu/detector/windowThicknessPMT",this);
  fwindowThicknessPMTCmd->SetGuidance("Thickness of the PMT glass .");
  fwindowThicknessPMTCmd->SetParameterName("windowThicknessPMT",true);
  fwindowThicknessPMTCmd->SetDefaultUnit("mm");
  fwindowThicknessPMTCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fwindowThicknessPMTCmd->SetToBeBroadcasted(true);

  frTrunkCmd = new G4UIcmdWithADoubleAndUnit("/Mu/detector/rTrunk",this);
  frTrunkCmd->SetGuidance("Radius of the cylindrical trunk of the PMT .");
  frTrunkCmd->SetParameterName("rTrunk",true);
  frTrunkCmd->SetDefaultUnit("mm");
  frTrunkCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  frTrunkCmd->SetToBeBroadcasted(true);

  faPmtCmd = new G4UIcmdWithADoubleAndUnit
    ("/Mu/detector/aPMT",this);
  faPmtCmd->SetGuidance("Set the Semi-Major axis of the PMTs.");
  faPmtCmd->SetParameterName("aPMT",true);
  faPmtCmd->SetDefaultUnit("mm");
  faPmtCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  faPmtCmd->SetToBeBroadcasted(true);

  fbPmtCmd = new G4UIcmdWithADoubleAndUnit
    ("/Mu/detector/bPMT",this);
  fbPmtCmd->SetGuidance("Set the Semi-Minor axis of the PMTs.");
  fbPmtCmd->SetParameterName("bPMT",true);
  fbPmtCmd->SetDefaultUnit("mm");
  fbPmtCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fbPmtCmd->SetToBeBroadcasted(true);

  fhPmtCmd = new G4UIcmdWithADoubleAndUnit
    ("/Mu/detector/hPMT",this);
  fhPmtCmd->SetGuidance("Set Total height of the PMTs.");
  fhPmtCmd->SetParameterName("hPMT",true);
  fhPmtCmd->SetDefaultUnit("mm");
  fhPmtCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fhPmtCmd->SetToBeBroadcasted(true);
  
  UpdateCmd = new G4UIcmdWithoutParameter("/Mu/detector/update",this);
  UpdateCmd->SetGuidance("Update calorimeter geometry.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
  UpdateCmd->AvailableForStates(G4State_Idle);
 
  fPscintYield = new G4UIcmdWithADouble("/Mu/detector/PscintYield",this);
  fPscintYield->SetGuidance("Set scinitillation yield of Pscint");
  fPscintYield->SetGuidance("Specified in photons/MeV");
  fPscintYield->AvailableForStates(G4State_PreInit,G4State_Idle);
  fPscintYield->SetToBeBroadcasted(true);

  fPscintFastTime = new G4UIcmdWithADouble("/Mu/detector/PscintFastTime",this);
  fPscintFastTime->SetGuidance("Set Pscint fast time constant");
  fPscintFastTime->SetParameterName("PscintFastTime",true);
  fPscintFastTime->AvailableForStates(G4State_PreInit,G4State_Idle);
  fPscintFastTime->SetToBeBroadcasted(true);

  fPscintSlowTime = new G4UIcmdWithADouble("/Mu/detector/PscintSlowTime",this);
  fPscintSlowTime->SetGuidance("Set Pscint slow time constant");
  fPscintSlowTime->SetParameterName("PscintSlowTime",true);
  fPscintSlowTime->AvailableForStates(G4State_PreInit,G4State_Idle);
  fPscintSlowTime->SetToBeBroadcasted(true);
  
  fDefaultsCmd = new G4UIcommand("/Mu/detector/defaults",this);
  fDefaultsCmd->SetGuidance("Set all detector geometry values to defaults.");
  fDefaultsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fDefaultsCmd->SetToBeBroadcasted(true);

  fPscintRindexCmd = new G4UIcmdWithADouble("/Mu/detector/PscintRindex",this);
  fPscintRindexCmd->SetGuidance("Set the refractive index of Pscint");
  fPscintRindexCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fPscintRindexCmd->SetToBeBroadcasted(true);

  fTeflonRindexCmd = new G4UIcmdWithADouble("/Mu/detector/TeflonRindex",this);
  fTeflonRindexCmd->SetGuidance("Set the refractive index of Teflon");
  fTeflonRindexCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fTeflonRindexCmd->SetToBeBroadcasted(true);

  fTeflonReflectCmd = new G4UIcmdWithADouble("/Mu/detector/TeflonReflect",this);
  fTeflonReflectCmd->SetGuidance("Set the reflectivity of Teflon");
  fTeflonReflectCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fTeflonReflectCmd->SetToBeBroadcasted(true);

  fTeflonEfficenCmd = new G4UIcmdWithADouble("/Mu/detector/TeflonEfficen",this);
  fTeflonEfficenCmd->SetGuidance("Set the efficiency of Teflon");
  fTeflonEfficenCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fTeflonEfficenCmd->SetToBeBroadcasted(true);
}

MuDetectorMessenger::~MuDetectorMessenger()
{
  delete fDimensionsCmd;
  delete faPmtCmd;
  delete fbPmtCmd;
  delete fhPmtCmd;
  delete fDetectorDir;
  delete fDefaultsCmd;
  delete fPscintLCmd;
  delete fPscintWCmd;
  delete fPscintHCmd;
  delete fTeflonLCmd;
  delete fTeflonWCmd;
  delete fwindowThicknessPMTCmd;
  delete frTrunkCmd;
  delete fPscintYield;
  delete fPscintFastTime;
  delete fPscintSlowTime;
  delete fPscintRindexCmd;
  delete fTeflonRindexCmd;
  delete fTeflonReflectCmd;
  delete fTeflonEfficenCmd;
  delete UpdateCmd;
}

void MuDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == fDefaultsCmd){
    fMuDetector->SetDefaults();
  }
  else if (command == fDimensionsCmd){
    fMuDetector->SetDimensions(fDimensionsCmd->GetNew3VectorValue(newValue));
  }
  else if (command == fPscintLCmd){
    fMuDetector->SetPscintL(fPscintLCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fPscintWCmd){
    fMuDetector->SetPscintW(fPscintWCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fPscintHCmd){
    fMuDetector->SetPscintH(fPscintHCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fTeflonLCmd){
    fMuDetector->SetTeflonL(fTeflonLCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fTeflonWCmd){
    fMuDetector->SetTeflonW(fTeflonWCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fwindowThicknessPMTCmd){
    fMuDetector->SetwindowThicknessPMT(fwindowThicknessPMTCmd->GetNewDoubleValue(newValue));
  }
  else if (command == frTrunkCmd){
    fMuDetector->SetrTrunk(frTrunkCmd->GetNewDoubleValue(newValue));
  }
  else if (command == faPmtCmd){
    fMuDetector->SetaPMT(faPmtCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fbPmtCmd){
    fMuDetector->SetbPMT(fbPmtCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fhPmtCmd){
    fMuDetector->SethPMT(fhPmtCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fPscintYield){
    fMuDetector->SetPscintYield(fPscintYield->GetNewDoubleValue(newValue));
  }
  else if (command == fPscintFastTime){
    fMuDetector->SetPscintFastTime(fPscintFastTime->GetNewDoubleValue(newValue));
  }
  else if (command == fPscintSlowTime){
    fMuDetector->SetPscintSlowTime(fPscintSlowTime->GetNewDoubleValue(newValue));
  }
  else if (command == fPscintRindexCmd){
    fMuDetector->SetPscintRindex(fPscintRindexCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fTeflonRindexCmd){
    fMuDetector->SetTeflonRindex(fTeflonRindexCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fTeflonReflectCmd){
    fMuDetector->SetTeflonReflect(fTeflonReflectCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fTeflonEfficenCmd){
    fMuDetector->SetTeflonEfficen(fTeflonEfficenCmd->GetNewDoubleValue(newValue));
  }
  else if( command == UpdateCmd )
   { fMuDetector->UpdateGeometry(); }
}
