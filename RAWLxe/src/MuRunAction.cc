#include "MuRunAction.hh"
#include "MuAnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "MuDetectorConstruction.hh"
#include "G4TransportationManager.hh"
#include "G4Navigator.hh"
#include "G4VPhysicalVolume.hh"
MuRunAction::MuRunAction(MuDetectorConstruction* detector)
 : G4UserRunAction(), fDetector(detector)
{
  // set printing event number per each 100 events
  G4RunManager::GetRunManager()->SetPrintProgress(5000);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

MuRunAction::~MuRunAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MuRunAction::BeginOfRunAction(const G4Run* aRun)
{
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  // Creation of the analysis manager
  MuAnalysisManager* analysis = MuAnalysisManager::getInstance();
  analysis->BeginOfRun();


  G4int RunN = aRun->GetRunID();
  if ( RunN % 10000 == 0 )
    //G4cout << "### Run : " << RunN << G4endl;

#ifdef G4VIS_USE
  if (G4VVisManager::GetConcreteInstance())
    {
      G4UImanager* UI = G4UImanager::GetUIpointer();
      UI->ApplyCommand("/vis/clear/view");
      UI->ApplyCommand("/vis/draw/current");
    }
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void MuRunAction::EndOfRunAction(const G4Run* )
{
  // Get the analysis manager
  MuAnalysisManager* analysis = MuAnalysisManager::getInstance();
  /*G4cout<<fDetector->GetPscintYield()<<G4endl;
  G4cout<<fDetector->GetPscintFastTime()<<G4endl;
  G4cout<<fDetector->GetPscintSlowTime()<<G4endl;
  G4cout<<fDetector->GetPscintRindex()<<G4endl;
  G4cout<<fDetector->GetTeflonRindex()<<G4endl;
  G4cout<<fDetector->GetTeflonReflect()<<G4endl;
  G4cout<<fDetector->GetTeflonEfficen()<<G4endl;*/
  
  MuAnalysisManager::getInstance()->SetPsH(fDetector->GetPscintH());
  MuAnalysisManager::getInstance()->SetPsL(fDetector->GetPscintL());
  //MuAnalysisManager::getInstance()->SetTeL(fDetector->GetTeflonL());
  MuAnalysisManager::getInstance()->Setpy(fDetector->GetPscintYield());
  MuAnalysisManager::getInstance()->Setpft(fDetector->GetPscintFastTime());
  MuAnalysisManager::getInstance()->Setpst(fDetector->GetPscintSlowTime());
  MuAnalysisManager::getInstance()->Setprd(fDetector->GetPscintRindex());
  MuAnalysisManager::getInstance()->Settrd(fDetector->GetTeflonRindex());
  MuAnalysisManager::getInstance()->Settrf(fDetector->GetTeflonReflect());
  MuAnalysisManager::getInstance()->Settec(fDetector->GetTeflonEfficen());  
  analysis->EndOfRun();
  //////////////out gdml file//////////////
  //outGDML();
  /////////////////////////////////////////
#ifdef G4VIS_USE
  if (G4VVisManager::GetConcreteInstance())
G4UImanager::GetUIpointer()->ApplyCommand("/vis/show/view");
#endif
}
/*void MuRunAction::outGDML(){
  G4Navigator* gNavigator =
        G4TransportationManager::GetTransportationManager()
        ->GetNavigatorForTracking();
        G4VPhysicalVolume* pworld = gNavigator->GetWorldVolume();
        G4LogicalVolume* lworld = pworld->GetLogicalVolume();
        G4GDMLParser parser;
        std::string name="output/";
        std::string m_filename = name + "Detector.gdml";
        parser.Write(m_filename, lworld, true);
}*/
