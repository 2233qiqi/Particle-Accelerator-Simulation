#include "RunAction.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"

RunAction::RunAction()
{
  auto analysisManager = G4AnalysisManager::Instance();
  // set printing event number per each 100 events
  G4RunManager::GetRunManager()->SetPrintProgress(1000);
  analysisManager->SetNtupleMerging(true);
  analysisManager->CreateNtuple("Hits", "Reactor Chamber Hits Data");
  analysisManager->CreateNtupleIColumn("TrackID");   // 粒子ID
  analysisManager->CreateNtupleIColumn("ChamberNb"); // 室编号
  analysisManager->CreateNtupleDColumn("Edep");      // 能量沉积(eV)
  analysisManager->CreateNtupleDColumn("PosX");      // X位置(nm)
  analysisManager->CreateNtupleDColumn("PosY");      // Y位置(nm)
  analysisManager->CreateNtupleDColumn("PosZ");      // Z位置(nm)
  analysisManager->CreateNtupleSColumn("Reaction_Name");   // 物理过程名称
  analysisManager->CreateNtupleSColumn("Particle_Name");   // 离子名称
  analysisManager->CreateNtupleDColumn("Charge");   // 电荷
  analysisManager->FinishNtuple();
  // analysisManager->SetNtupleMerging(true);
}

void RunAction::BeginOfRunAction(const G4Run *run)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile("Reaction_hits.root");
  G4cout << "Using " << analysisManager->GetType() << G4endl;
}

void RunAction::EndOfRunAction(const G4Run *run)
{
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  auto analysisManager = G4AnalysisManager::Instance();
  //std::cout << "successful write&close" << std::endl;
  analysisManager->Write();
  analysisManager->CloseFile();
}