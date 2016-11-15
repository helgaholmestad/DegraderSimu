
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1
#include "G4GeneralParticleSource.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class DetectorConstruction;

class TH1F;
class TH2D;
//#include "TLegend.h"
#include "TLatex.h"
#include "TCanvas.h"
#include <fstream>

using namespace std;

// -----------------------------------------------------------------------------------------

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction(DetectorConstruction*);    
  virtual ~PrimaryGeneratorAction();
  void GeneratePrimaries(G4Event*);
private:
  G4ParticleGun*           particleGun;
  //G4GeneralParticleSource*  particleGun;
  //pointer a to G4  class
  DetectorConstruction*    Detector;     //pointer to the geometry
  ifstream theFile;
  vector < vector <double> >theData;
  G4int numberOfParticles;
public:
};

// -----------------------------------------------------------------------------------------

#endif


