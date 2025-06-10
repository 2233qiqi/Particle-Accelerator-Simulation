#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  // Create a particle gun with one particle
  fParticleGun = new G4ParticleGun(1);

  // Set the particle type to electron
  auto particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition *particle = particleTable->FindParticle("e-"); // "e-" is the name for electron in Geant4
  fParticleGun->SetParticleDefinition(particle);                      // You can change this to any particle type you want, e.g., "proton", "gamma", etc.

  // Set the initial energy of the particle
  fParticleGun->SetParticleEnergy(10 * keV);

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 1, 0)); // Set the momentum direction along the z-axis
                                                                      // Set the initial position of the particle
                                                                      // fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, 0));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
  // G4double size = 1*cm;
  G4double x0 = -9 * cm;
  G4double y0 = 0 * cm;
  G4double z0 = -2.3 * cm;

  fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, z0));

  fParticleGun->GeneratePrimaryVertex(event);
}