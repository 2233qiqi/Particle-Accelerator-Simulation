#include "ReactorSD.hh"
#include "G4VProcess.hh"
#include "G4Ions.hh"
#include "G4AnalysisManager.hh"

ReactorSD::ReactorSD(const G4String &name, const G4String &hitsCollectionName) : G4VSensitiveDetector(name)
{
  collectionName.insert(hitsCollectionName);
}

void ReactorSD::Initialize(G4HCofThisEvent *hce)
{
  // Create hits collection

  fHitsCollection = new ReactorHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce

  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  // hce->AddHitsCollection(hcID, fHitsCollection);
}

G4bool ReactorSD::ProcessHits(G4Step *step, G4TouchableHistory *)
{
  // energy deposit
  G4double edep = step->GetTotalEnergyDeposit();

  if (edep == 0.)
    return false;

  auto newHit = new ReactorHit();

  newHit->SetTrackID(step->GetTrack()->GetTrackID());
  newHit->SetChamberNb(step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber());
  newHit->SetEdep(edep);
  newHit->SetPos(step->GetPostStepPoint()->GetPosition());
  newHit->SetReactorName(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());


  const G4ParticleDefinition *particle = step->GetTrack()->GetDefinition();
  newHit->SetParticleName(particle->GetParticleName());
  G4double charge = particle->GetPDGCharge(); // 基本电荷单位（如+2e)
  newHit->SetCharge(charge);

  fHitsCollection->insert(newHit);

  // newHit->Print();

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ReactorSD::EndOfEvent(G4HCofThisEvent *)
{
  // if ( verboseLevel> 1) {
  std::size_t nofHits = fHitsCollection->entries();
  G4cout << G4endl << "-------->Hits Collection: in this event they are " << nofHits
         << " hits in the tracker chambers: " << G4endl;
  for (std::size_t i = 0; i < nofHits; i++)
  {
    (*fHitsCollection)[i]->Print();
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleIColumn(0, (*fHitsCollection)[i]->GetTrackID());
    analysisManager->FillNtupleIColumn(1, (*fHitsCollection)[i]->GetChamberNb());
    analysisManager->FillNtupleDColumn(2, (*fHitsCollection)[i]->GetEdep());
    analysisManager->FillNtupleDColumn(3, (*fHitsCollection)[i]->GetPos().x());
    analysisManager->FillNtupleDColumn(4, (*fHitsCollection)[i]->GetPos().y());
    analysisManager->FillNtupleDColumn(5, (*fHitsCollection)[i]->GetPos().z());
    analysisManager->FillNtupleSColumn(6, (*fHitsCollection)[i]->GetReactorName());
    analysisManager->FillNtupleSColumn(7, (*fHitsCollection)[i]->GetParticleName());
    analysisManager->FillNtupleDColumn(8, (*fHitsCollection)[i]->GetCharge());
    analysisManager->AddNtupleRow();
  }
}
