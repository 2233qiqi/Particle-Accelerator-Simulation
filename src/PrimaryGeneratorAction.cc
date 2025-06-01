#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    // Create a particle gun with one particle
    fParticleGun = new G4ParticleGun(1);
    
    // Set the particle type to gamma
    fParticleGun->SetParticleDefinition(G4Proton::Definition());
 
    // Set the initial energy of the particle
    fParticleGun->SetParticleEnergy(1.0 * MeV);
    
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1)); // Set the momentum direction along the z-axis
    // Set the initial position of the particle
    //fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, 0));
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  G4double size = 8*cm;
  G4double x0 = size  * (G4UniformRand() - 0.5);
  G4double y0 = size  * (G4UniformRand() - 0.5);
  G4double z0 = -50*cm;

  fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, z0));

  fParticleGun->GeneratePrimaryVertex(event);
}