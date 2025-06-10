#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "FTFP_BERT.hh"
// 或高精度选项（推荐）
#include "G4EmStandardPhysics_option4.hh"

class PhysicsList: public G4VModularPhysicsList {
public:
    PhysicsList();
    ~PhysicsList() override = default;
private:
    void ConstructParticle();
    void ConstructProcess();
};
#endif
