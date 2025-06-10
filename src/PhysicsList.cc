#include "PhysicsList.hh"

#include "G4ComptonScattering.hh"
#include "G4EmBuilder.hh"
#include "G4GammaConversion.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleTypes.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4PhysicsListHelper.hh"
#include "G4ProcessManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eIonisation.hh"
#include "G4eMultipleScattering.hh"
#include "G4eplusAnnihilation.hh"


PhysicsList::PhysicsList()
{
  defaultCutValue = 1.0 * mm;
}



void PhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program.
  G4EmBuilder::ConstructMinimalEmSet();
}


void PhysicsList::ConstructProcess()
{
  AddTransportation();
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

  auto particleIterator = GetParticleIterator();
  particleIterator->reset();
  while ((*particleIterator)()) {
    G4ParticleDefinition* particle = particleIterator->value();
    G4String particleName = particle->GetParticleName();

    if (particleName == "gamma") {
      ph->RegisterProcess(new G4PhotoElectricEffect, particle);
      ph->RegisterProcess(new G4ComptonScattering, particle);
      ph->RegisterProcess(new G4GammaConversion, particle);
    }
    else if (particleName == "e-") {
      ph->RegisterProcess(new G4eMultipleScattering, particle);
      ph->RegisterProcess(new G4eIonisation, particle);
      ph->RegisterProcess(new G4eBremsstrahlung, particle);
    }
    else if (particleName == "e+") {
      ph->RegisterProcess(new G4eMultipleScattering, particle);
      ph->RegisterProcess(new G4eIonisation, particle);
      ph->RegisterProcess(new G4eBremsstrahlung, particle);
      ph->RegisterProcess(new G4eplusAnnihilation, particle);
    }
  }
}

