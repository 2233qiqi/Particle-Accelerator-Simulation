#ifndef REACTORHIT_HH
#define REACTORHIT_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4Allocator.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"

class ReactorHit : public G4VHit
{
public:
  ReactorHit() = default;
  ReactorHit(const ReactorHit &) = default;
  ~ReactorHit() override = default;

  // operators
  ReactorHit &operator=(const ReactorHit &) = default;
  G4bool operator==(const ReactorHit &) const;

  inline void *operator new(size_t);
  inline void operator delete(void *);

  // methods from base class
  void Draw() override;
  void Print() override;

  // Set methods
  void SetTrackID(G4int track) { fTrackID = track; };
  void SetChamberNb(G4int chamb) { fChamberNb = chamb; };
  void SetEdep(G4double de) { fEdep = de; };
  void SetPos(G4ThreeVector xyz) { fPos = xyz; };
  void SetReactorName(G4String reactorName) { fReactorName = reactorName; };
  void SetCharge(G4double charge) { fCharge = charge; };
  void SetParticleName(G4String particle_name) { fparticle_name = particle_name; };
  // Get methods
  G4int GetTrackID() const { return fTrackID; };
  G4int GetChamberNb() const { return fChamberNb; };
  G4double GetEdep() const { return fEdep; };
  G4ThreeVector GetPos() const { return fPos; };
  G4String GetReactorName() const { return fReactorName; };
  G4double GetCharge() const { return fCharge; };
  G4String GetParticleName() const { return fparticle_name; };
private:
  G4int fTrackID = -1;
  G4int fChamberNb = -1;
  G4double fEdep = 0.;
  G4ThreeVector fPos;
  G4String fReactorName = "Unknown Reactor";
  G4double fCharge = 0.; // 电荷
  G4String fparticle_name = "Unknown Particle"; // 反应产物的粒子名称
};

using ReactorHitsCollection = G4THitsCollection<ReactorHit>;

extern G4ThreadLocal G4Allocator<ReactorHit> *ReactorHitAllocator;

inline void *ReactorHit::operator new(size_t)
{
  if (!ReactorHitAllocator)
    ReactorHitAllocator = new G4Allocator<ReactorHit>;
  return (void *)ReactorHitAllocator->MallocSingle();
}

inline void ReactorHit::operator delete(void *hit)
{
  ReactorHitAllocator->FreeSingle((ReactorHit *)hit);
}

#endif