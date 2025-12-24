#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "CADMesh.hh"

#include <cmath>

// --------------------------------------------------------------------

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction() {}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    auto nist = G4NistManager::Instance();

    auto vacuum   = nist->FindOrBuildMaterial("G4_Galactic");
    auto fuelMat = nist->FindOrBuildMaterial("G4_UO2"); 

    G4double worldSize = 10 * m;

    auto solidWorld = new G4Box(
        "World",
        0.5 * worldSize,
        0.5 * worldSize,
        0.5 * worldSize
    );

    auto logicWorld =
        new G4LogicalVolume(solidWorld, vacuum, "World");

    auto physWorld =
        new G4PVPlacement(nullptr, {}, logicWorld,
                          "World", nullptr, false, 0, true);

    auto mesh = CADMesh::TessellatedMesh::FromOBJ("model.obj");
    mesh->SetScale(2000.0);  

    auto solidRod = mesh->GetSolid("FuelRod_2_2");
    if (!solidRod) {
        G4Exception("DetectorConstruction",
                    "MeshNotFound",
                    FatalException,
                    "Missing mesh: FuelRod_2_2");
    }

    auto logicRod =
        new G4LogicalVolume(solidRod, fuelMat, "FuelRod_2_2");

    const G4int nx = 6;
    const G4int ny = 6;

    G4double pitch  = 20.0 * mm;     
    G4double height = 2000.0 * mm;   

    auto solidLattice = new G4Box(
        "Lattice",
        0.5 * nx * pitch,
        0.5 * ny * pitch,
        0.5 * height
    );

    auto logicLattice =
        new G4LogicalVolume(solidLattice, vacuum, "Lattice");

    new G4PVPlacement(
        nullptr,
        {},
        logicLattice,
        "Lattice",
        logicWorld,
        false,
        0,
        true
    );

    const G4double sqrt3 = std::sqrt(3.0);

    G4double x0 = 0.5 * (nx - 1) * pitch;
    G4double y0 = 0.5 * (ny - 1) * pitch * sqrt3 * 0.5;

    G4int copyNo = 0;

    for (G4int iy = 0; iy < ny; ++iy) {
        for (G4int ix = 0; ix < nx; ++ix) {

            G4double x =
                (ix + 0.5 * (iy % 2)) * pitch - x0;

            G4double y =
                iy * pitch * sqrt3 * 0.5 - y0;

            new G4PVPlacement(
                nullptr,
                G4ThreeVector(x, y, 0),
                logicRod,
                "FuelRod",
                logicLattice,
                false,
                copyNo,
                true
            );

            ++copyNo;
        }
    }

    return physWorld;
}
