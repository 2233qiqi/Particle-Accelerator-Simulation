// #include "DetectorConstruction.hh"
// #include "PhysicsList.hh"
// #include "ActionInitialization01.hh"
#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4SteppingVerbose.hh"
#include "G4VisExecutive.hh"
#include "DetectorConstruction.hh"
#include "QBBC.hh"
#include "ActionInitialization.hh"

int main(int argc, char **argv)
{
    G4UIExecutive *ui = nullptr;
    if (argc == 1)
    {
        // If no arguments are provided, create a UI executive
        ui = new G4UIExecutive(argc, argv);
    }

    G4int precision = 4;
    G4SteppingVerbose::UseBestUnit(precision);
    // construct the default run manager
    auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);
    // set mandatory initialization classes
    runManager->SetUserInitialization(new DetectorConstruction);
    auto physicsList = new QBBC;
    physicsList->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList);
    runManager->SetUserInitialization(new ActionInitialization);
    // initialize G4 kernel
    runManager->Initialize();

    // auto visManager = new G4VisExecutive(argc, argv);
    //  Constructors can also take optional arguments:
    //  - a graphics system of choice, eg. "OGL"
    //  - and a verbosity argument - see /vis/verbose guidance.
    auto visManager = new G4VisExecutive(argc, argv, "OGLIQt", "Quiet");
    // auto visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    auto UImanager = G4UImanager::GetUIpointer();

    // Process macro or start UI session
    //
    if (!ui)
    {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }
    else
    {
        // interactive mode
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted
    // in the main() program !

    delete visManager;
    delete runManager;
    return 0;
}