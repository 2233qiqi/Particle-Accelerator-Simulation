#ifndef EMField_h
#define EMField_h 1

#include "G4ElectroMagneticField.hh"
#include "G4TransportationManager.hh"

class EMField
#ifndef STANDALONE
 : public G4ElectroMagneticField
#endif

{  
  public:

    explicit EMField();
  
    void  GetFieldValue( const  double Point[4], double *Bfield ) const;
		       
    G4bool DoesFieldChangeEnergy() const {return true;}
};
#endif
