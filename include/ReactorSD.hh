#ifndef  REACTORSD_HH
#define  REACTORSD_HH
#include "G4VSensitiveDetector.hh"
#include "G4THitsCollection.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "ReactorHit.hh"

class ReactorSD : public G4VSensitiveDetector
{

public:
    ReactorSD(const G4String& name, const G4String& hitsCollectionName);
    ~ReactorSD()override = default;
    // methods from base class
    void Initialize(G4HCofThisEvent* hitCollection) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
    void EndOfEvent(G4HCofThisEvent* hitCollection) override;

private:
ReactorHitsCollection* fHitsCollection = nullptr;
};




#endif // REACTORSD_HH