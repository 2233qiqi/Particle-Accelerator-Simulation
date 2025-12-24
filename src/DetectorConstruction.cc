#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "CADMesh.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{
}
DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
auto nist = G4NistManager::Instance();

auto vacuum = nist->FindOrBuildMaterial("G4_Galactic");
auto aluminum = nist->FindOrBuildMaterial("G4_AL");
auto iron = nist->FindOrBuildMaterial("G4_Fe");


G4double WorldSize = 10 * m;

auto SolidWorld =new G4Box("World", WorldSize, WorldSize, WorldSize);
auto LogicalWorld =new G4LogicalVolume(SolidWorld,vacuum,"World");
auto PhysicalWorld =new G4PVPlacement(NULL,{},LogicalWorld,"World",NULL,false,0);

auto mesh =CADMesh::TessellatedMesh::FromOBJ("Model.obj");
mesh->SetScale(1000.0);
G4String meshName[] = {
    "Vacuum_Tube",
    "RF_Cavity",
    "Focusing_Magnet_1",
    "Focusing_Magnet_2"
};
G4Material *materials[]={
    aluminum,
    aluminum,
    iron,
    iron
};

    for (G4int i = 0; i < 4; i++) {

        auto solid = mesh->GetSolid(meshName[i]);

        auto logic =
            new G4LogicalVolume(solid,
                                materials[i],
                                meshName[i]);

        new G4PVPlacement(
            nullptr,
            G4ThreeVector(),
            logic,
            meshName[i],
            LogicalWorld,
            false,
            i,
            true
        );
    }



return PhysicalWorld;
}
