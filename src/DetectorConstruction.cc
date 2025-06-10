#include "DetectorConstruction.hh"
#include "ReactorHit.hh"
#include "ReactorSD.hh"

#include "G4MagIntegratorDriver.hh"
#include "G4AutoDelete.hh"
#include "G4TMagFieldEquation.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4MagIntegratorStepper.hh" // 步进器
#include "G4ClassicalRK4.hh"         // 经典的龙格-库塔方法
#include "G4HelixExplicitEuler.hh"   // 螺旋线显式欧拉法
#include "G4HelixImplicitEuler.hh"   // 螺旋线隐式欧拉法
#include "G4HelixSimpleRunge.hh"     // 螺旋线简单龙格法
#include "G4CashKarpRKF45.hh"        // Cash-Karp龙格-库塔法
#include "G4SimpleRunge.hh"          // 简单的龙格法
#include "G4IntegrationDriver.hh"    // 积分驱动器
#include "G4ChordFinder.hh"          // 和弦查找器
#include "G4EqMagElectricField.hh"   // 电磁场方程

DetectorConstruction::DetectorConstruction()
{
    // Constructor implementation can be added here if needed
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{

    G4NistManager *nist = G4NistManager::Instance();

    G4Element *elSi = new G4Element("Nickel", "Ni", 28, 58.6934 * g / mole);
    G4Element *elO = new G4Element("Oxygen", "O", 8, 15.999 * g / mole);
    G4Element *elC = new G4Element("Carbon", "C", 6, 12.000 * g / mole);
    G4Isotope *isoC12 = new G4Isotope("C12", 6, 12, 12.0000 * g / mole);
    G4Isotope *isoC14 = new G4Isotope("C14", 6, 14, 14.000 * g / mole);

    // 碳化硅
    G4Material *SiC = new G4Material("SiliconCarbide", 3.21 * g / cm3, 2);
    SiC->AddElement(elSi, 1);
    SiC->AddElement(elC, 1);

    // 二氧化碳
    // pv=nRT
    G4double T = 300 * kelvin;                     // 温度
    G4double P = 0.01 * pascal;                    // 压力
    G4double CO2_density = 1.76 * 1e-10 * g / cm3; // 二氧化碳密度
    // std::cout << "CO2_density:" << CO2_density << std::endl; // 二氧化碳密度
    G4State state = kStateGas; // 二氧化碳状态
    G4Element *elMixC = new G4Element("MixCarbon", "C", 2);
    elMixC->AddIsotope(isoC12, 80. * perCent);
    elMixC->AddIsotope(isoC14, 20. * perCent);
    G4Material *MixCo2 = new G4Material("carbon dioxide", CO2_density, 2, kStateGas, T, P);
    MixCo2->AddElement(elMixC, 1);
    MixCo2->AddElement(elO, 2);

    G4double MixCo2_thikness = 20 * cm;
    // G4int Step = 1;
    // G4double unitWidth = MixCo2_thikness / Step;

    G4double world_size = MixCo2_thikness * 2;
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

    /*for (G4int copyNo = 0; copyNo < Step; copyNo++)
    {
        auto chamber = new G4Box("Chamber_soild", unitWidth / 2, 5 * cm / 2, 5 * cm / 2); // 半宽度=1 µm
        G4double Xposition = copyNo * unitWidth;                                          // 中心间距=2 µm
        fLogicChamber.push_back(new G4LogicalVolume(chamber, MixCo2, "Chamber_LV"));
        new G4PVPlacement(nullptr, G4ThreeVector(Xposition, 0, 0), fLogicChamber.back(), "Chamber_PV", world_log, false, copyNo, true);
    }*/
    auto chamber = new G4Box("Chamber_soild", MixCo2_thikness / 2, 5 * cm / 2, 5 * cm / 2); // 半宽度=1 µm
    // G4double Xposition = copyNo * MixCo2_thikness;                                          // 中心间距=2 µm
    auto fLogicChamber = new G4LogicalVolume(chamber, MixCo2, "Chamber_LV");
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 0), fLogicChamber, "Chamber_PV", world_log, false, true);

    G4cout << *(G4Material::GetMaterialTable()) << G4endl;

    fFieldLogicalVolume = fLogicChamber;
    //G4VisAttributes *fieldVis = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.5));
    //fieldVis->SetForceSolid(true); // 强制实体渲染（可选）
    //fFieldLogicalVolume->SetVisAttributes(fieldVis);
    return world_phys;
}

void DetectorConstruction::ConstructSDandField()
{
    G4String reactorChamberSDname = "/ReactorChamberSD";
    auto reactorSD = new ReactorSD(reactorChamberSDname, "ReactorHitsCollection");
    G4SDManager::GetSDMpointer()->AddNewDetector(reactorSD);
    // Setting trackerSD to all logical volumes with the same name
    // of "Chamber_LV".
    SetSensitiveDetector("Chamber_LV", reactorSD, true);

    EMField *field = new EMField();
    G4AutoDelete::Register(field);

    G4EqMagElectricField *fEquation = new G4EqMagElectricField(field);
    G4MagIntegratorStepper *fStepper = new G4ClassicalRK4(fEquation, 8);
    G4FieldManager *fFieldMgr =
        //G4TransportationManager::GetTransportationManager()->GetFieldManager();
        new G4FieldManager();

    // Relaxed
    G4MagInt_Driver *fIntgrDriver =
        new G4MagInt_Driver(1 * mm, fStepper, fStepper->GetNumberOfVariables());

    G4ChordFinder *fChordFinder = new G4ChordFinder(fIntgrDriver);
    fFieldMgr->SetChordFinder(fChordFinder);
    fFieldMgr->SetDetectorField(field);
    fFieldLogicalVolume->SetFieldManager(fFieldMgr, true);
    G4AutoDelete::Register(fFieldMgr);
}