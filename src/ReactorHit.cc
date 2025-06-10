#include "ReactorHit.hh"

#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<ReactorHit> *ReactorHitAllocator = nullptr;

G4bool ReactorHit::operator==(const ReactorHit &right) const
{
  return (this == &right) ? true : false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ReactorHit::Draw()
{
  G4VVisManager *pVVisManager = G4VVisManager::GetConcreteInstance();
  if (pVVisManager)
  {
    G4Circle circle(fPos);
    circle.SetScreenSize(4.);
    circle.SetFillStyle(G4Circle::filled);
    G4VisAttributes attribs(G4Colour::Red());
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ReactorHit::Print()
{
  G4cout << "  trackID: " << fTrackID << " chamberNb: " << fChamberNb << " Edep: " << std::setw(7)
         << G4BestUnit(fEdep, "Energy") << " Position: " << std::setw(10)
         << G4BestUnit(fPos, "Length") << " Reaction Name :" << std::setw(10) << fReactorName << std::setw(10) 
         <<" Particle_Name :"<< fparticle_name<<std::setw(10)<<" Charge :"<< fCharge<<std::setw(10)<<G4endl;
}
