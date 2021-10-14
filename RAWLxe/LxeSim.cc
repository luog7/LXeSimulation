//#include "Physics.hh"			//现在用的物理过程
#include "MuDetectorConstruction.hh"
#include "MuActionInitializer.hh"
#include "MuRunAction.hh"
#include "MuEventAction.hh"
#include "MuAnalysisManager.hh"
#include "Randomize.hh"
#include "time.h"
#include <G4VUserPhysicsList.hh>
#include "DMXPhysicsList.hh" 		//自己写的物理过程
//#ifdef G4MULTITHREADED
//#include "G4MTRunManager.hh"		//多线条运行,339服务器不支持，跟操作系统有关系。
//#else
#include "G4RunManager.hh"
//#endif
#include "G4UImanager.hh"
#include "G4StepLimiterPhysics.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif
//..............................##################............................
namespace {
        void PrintUsage() {
		G4cerr << " Usage: " << G4endl;
		G4cerr << " LxeSim [-m macro ] [-ifinputGDML(Yes|No)] [-g gdml] [-gen ChooseGenerator(gps|muon)]" << G4endl;
	}
}

int main(int argc,char** argv)
{
  if ( argc > 10 ) {
                PrintUsage();
                return 1;
        }  
  G4String macro;
  G4String gdml = "../DetectorStructure/Detector.gdml";
  G4bool isgdml = false;
  G4String gun = "muon";
  for ( G4int i=1; i<argc; i=i+2 )
  {
	if(G4String(argv[i]) == "-m") macro = argv[i+1];
	else if ( G4String(argv[i]) == "-g" )
                {
                        G4String name = argv[i+1];
                        gdml = "../DetectorStructure/"+name+".gdml";
                }
	 else if ( G4String(argv[i]) == "-ifinputGDML" )
                {
			G4String Switch = argv[i+1];
			if (Switch == "Yes" ) isgdml = true;
                        else if  (Switch == "No" ) isgdml = false;
			else
                        {
                                PrintUsage();
                                return 1;
                        }

              	}
	else if (G4String(argv[i]) == "-gen")
                {
                        gun = argv[i+1];
                }
	else
	{
		PrintUsage();
                return 1;
	}
  }
/*
  G4MTRunManager* runManager = new G4MTRunManager;
*/
  G4RunManager* runManager = new G4RunManager;
  // Mandatory user initialization classes
  MuDetectorConstruction* Detector = new MuDetectorConstruction(gdml,isgdml);
  runManager->SetUserInitialization(Detector);
//#######################现在模拟用的物理过程#############
  /*G4VUserPhysicsList* muonPhy = new Physics();
  runManager->SetUserInitialization(muonPhy);
  */
//########################################################
 //%%%%%%%%%%%%%%%%%%%%%%手写的物理过程%%%%%%%%%%%%%%%%%%%%
  runManager->SetUserInitialization(new DMXPhysicsList);
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  // User action initialization
  runManager->SetUserInitialization(new MuActionInitializer(Detector,gun));
/*
  MuPrimaryGeneratorGun2* gen_action = new MuPrimaryGeneratorGun2();
  runManager->SetUserAction(gen_action);
  runManager->SetUserAction(new MuRunAction);
  runManager->SetUserAction(new MuEventAction);
*/
  // Initialize G4 kernel
  runManager->Initialize();
  // Visualization manager construction
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  // Get the pointer to the User Interface manager
  G4UIExecutive* ui = 0;
  // Choose the Random engine
  //G4Random::setTheEngine(new CLHEP::RanecuEngine);
  //Random Seed
  G4long seed = time(NULL);
  CLHEP::HepRandom::setTheSeed(seed);
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if ( macro.size() ) {
    // execute an argument macro file if exist
    G4String command = "/control/execute ";
    //G4String fileName = argv[1];
    //UImanager->ApplyCommand(command+fileName);
    UImanager->ApplyCommand(command+macro);
  }
  else {
    ui = new G4UIExecutive(argc, argv);
    UImanager->ApplyCommand("/control/execute macro/init_vis.mac");
    //UImanager->ApplyCommand("/control/execute macro/ChangeGometry.mac");
    /*
      if (ui->IsGUI()) {
         UImanager->ApplyCommand("/control/execute macro/gui.mac");
    }
    */
    // start interactive session
    ui->SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
    
