#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
//#include "TLegend.h"
#include "TColor.h"
#include "TLatex.h"
#include "globals.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <iostream>
#include <cmath>
#include "G4GeneralParticleSource.hh"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

//#include "CLHEP/Random/RandGauss.h"
//#include "/Applications/geant4.9.6.p02/source/externals/clhep/include/CLHEP/Random/RandLandau.h" //(include this before method definition)

// -----------------------------------------------------------------------------------------

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction* DC)
  :Detector(DC)
{
  numberOfParticles=0;
  G4String particleName = "anti_proton";
  //  G4String particleName = "proton";
  //G4String particleName = "geantino";
  theFile.open("../Antiprotons-output/particles_hit_collimator.txt",std::ios_base::in);
  //std::string line;
  vector <double> theLine;
  G4double d;
  int counter=0;
  while (theFile>>d){
    if(counter/9==1){
      theData.push_back(theLine);
      counter=0;
      theLine.clear();
      numberOfParticles+=1;
    }
    counter++;
    theLine.push_back(d);
     //std::istringstream linestream(line);
    //std::string word;
    // while (  linestream >> word){
    //   G4cout<<"hva er her "<<word<<G4endl;
    //   theWords.push_back(word);
    // }
    // G4cout<<line<<G4endl;
    // theData.push_back(theWords);
  }
  
  
  //G4String particleName = "pi-";
  G4int n_particle = 1;
  particleGun  = new G4ParticleGun(n_particle);
  //particleGun  = new G4GeneralParticleSource();
  G4cout<<"list  source "<<endl;
  //particleGun->ListSource();
  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);		
  particleGun->SetParticleDefinition(particle);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{ 
  delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
  //set energy and stuff
 
  //particleGun->SetParticleEnergy(2.3*MeV);
  particleGun->SetParticlePosition(G4ThreeVector(-3.5*cm,0,0));
  // //particleGun->SetParticleMomentumDirection(G4ThreeVector(theData[eventNumber][6],theData[eventNumber][4],theData[eventNumber][8]));
  // //particleGun->SetParticlePosition(G4ThreeVector(,0,10*cm));
  particleGun->SetParticleMomentumDirection(G4ThreeVector(1,0,0));
  particleGun->GeneratePrimaryVertex(anEvent);
   
}

