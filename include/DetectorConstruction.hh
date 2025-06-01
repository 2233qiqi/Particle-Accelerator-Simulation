#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH
#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RotationMatrix.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
private:
    /* data */
public:
    DetectorConstruction (/* args */);
    ~DetectorConstruction() override = default;
    G4VPhysicalVolume* Construct() override;
};






#endif