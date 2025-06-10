#include "EventAction.hh"

#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4ios.hh"
#include "ReactorHit.hh"
#include "G4SDManager.hh"
#include "ReactorSD.hh"

EventAction::EventAction(const RunAction *run) {}

void EventAction::BeginOfEventAction(const G4Event *) {}

void EventAction::EndOfEventAction(const G4Event *event)
{
  // get number of stored trajectories

  /*G4TrajectoryContainer *trajectoryContainer = event->GetTrajectoryContainer();
  std::size_t n_trajectories = 0;
  if (trajectoryContainer)
    n_trajectories = trajectoryContainer->entries();

  // periodic printing


  if (eventID < 100 || eventID % 100 == 0)
  {
    G4cout << ">>> Event: " << eventID << G4endl;
    if (trajectoryContainer)
    {
      G4cout << "    " << n_trajectories << " trajectories stored in this event." << G4endl;
    }
    G4VHitsCollection *hc = event->GetHCofThisEvent()->GetHC(0);
    G4cout << "    " << hc->GetSize() << " hits stored in this event" << G4endl;
  }
  G4int eventID = event->GetEventID();

  auto analysisManager = G4AnalysisManager::Instance();
  // 获取Hits Collection（假设已通过SD注册）
  auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID("ReactorHitsCollection");
  auto hitsHC = dynamic_cast<ReactorHitsCollection *>(event->GetHCofThisEvent()->GetHC(hcID));

  if (hitsHC)
  {
    for (size_t i = 0; i < hitsHC->entries(); i++)
    {
      auto hit = (*hitsHC)[i];
      analysisManager->FillNtupleIColumn(0, hit->GetTrackID());
      analysisManager->FillNtupleIColumn(1, hit->GetChamberNb());
      analysisManager->FillNtupleDColumn(2, hit->GetEdep());
      analysisManager->FillNtupleDColumn(3, hit->GetPos().x());
      analysisManager->FillNtupleDColumn(4, hit->GetPos().y());
      analysisManager->FillNtupleDColumn(5, hit->GetPos().z());
      analysisManager->FillNtupleSColumn(6, hit->GetReactorName());
      analysisManager->AddNtupleRow();
    }
  }
  std::cout << "EventAction: EndOfEventAction called for event " << eventID << std::endl;*/
}
