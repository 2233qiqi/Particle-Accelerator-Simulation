#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
{
    // Constructor implementation can be added here if needed
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{

    G4NistManager *nist = G4NistManager::Instance();

    G4double world_size = 1.0 * m;
    G4Box *world_box = new G4Box("World",
                                 world_size,
                                 world_size,
                                 world_size);

    G4LogicalVolume *world_log = new G4LogicalVolume(world_box,
                                                     nist->FindOrBuildMaterial("G4_Galactic"),
                                                     "WorldLog");


    G4VPhysicalVolume *world_phys = new G4PVPlacement(nullptr,
                                                      G4ThreeVector(),
                                                      world_log,
                                                      "WorldPhys",
                                                      nullptr,
                                                      false,
                                                      0,
                                                      true);

    G4Box *W_tar = new G4Box("Wu_tar",
                             0.5 * m,
                             0.5 * m,
                             0.1 * m);

    G4LogicalVolume *W_tar_log = new G4LogicalVolume(W_tar,
                                                     nist->FindOrBuildMaterial("G4_W"),
                                                     "Wu_tar_log");
    new G4PVPlacement(nullptr,
                      G4ThreeVector(0, 0, 0),
                      W_tar_log,
                      "Wu_tar_phys",
                      world_log,
                      false,
                      0,
                      true);

    return world_phys;
}