#include "analysis.hh"
#include "AntiPHit.hh"
#include "DetectorConstruction.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4DigiManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "TStyle.h"
#include <iostream>
#include <sstream>
#include "TCanvas.h"
#include "TrackingAction.hh"
#include "TPaveText.h"
using namespace std;
analysis* analysis::singleton = 0;

//Constructor: it initializes parameters
analysis::analysis(){;
}
void analysis::makeHistograms(){
  //G4cout<<"input i analyse "<<input<<G4endl;
  numberOfAntiprotons=0;
  //const char* thickness=(const char*)input;
  //string filename="../../makeDifferentPlots/histoTuning"+string(input)+"um.root";
  string filename="files/Degrader.txt";
  string histoFileName="files/histoDegraderum.root";
  //file=new TFile("../../makeDifferentPlots/histoXum.root","RECREATE");
  file=new TFile(histoFileName.c_str(),"RECREATE");
  energyHisto=new TH1D("energy","energy",100000,0,2000);
  outfile.open(filename.c_str(),std::ios::trunc);
  totalMomentum=0;
}

void analysis::writePerEvent(const G4Event* event){
  G4cout<<"event ID"<<event->GetEventID()<<G4endl;
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4int AntiPCollectionID = SDman->GetCollectionID("AntiPCollection");
  G4HCofThisEvent * HCE=event->GetHCofThisEvent();
  AntiPHitsCollection* hc=0;
  hc=(AntiPHitsCollection*)(HCE->GetHC(AntiPCollectionID));
  
  if(hc==NULL){
    G4cout<<"NULL"<<G4endl;
  }
 
  G4int nEntries = hc->entries();
  //outfile <<"eventID"<<event->GetEventID()<<"\n";
  //    
    
    for(G4int itr  = 0 ; itr < nEntries ; itr++) {
      if((*hc)[itr]->GetParticleName()=="anti_proton"){
	if ((*hc)[itr]->GetMyParticleEnergy()/keV<10 and (*hc)[itr]->GetMyParticleEnergy()/keV>0 and (*hc)[itr]->GetMyMomentumDirection().x()>0.99){
	  numberOfAntiprotons+=1;
	}
	numberOfAntiprotons+=1;
	energyHisto->Fill((*hc)[itr]->GetMyParticleEnergy()/keV);
	//outfile<<"copyNumber "<<(*hc)[itr]->GetCopyNumber()<<"  "<<(*hc)[itr]->GetParticleName()<<"  "<<(*hc)[itr]->GetMyParticleEnergy()/keV<<"  "<<(*hc)[itr]->GetHitPosition().x()/cm<<"  "<<(*hc)[itr]->GetHitPosition().y()/cm<<"  "<<(*hc)[itr]->GetHitPosition().z()/cm<<"  "<<(*hc)[itr]->GetMyMomentumDirection().x()<<"  "<<(*hc)[itr]->GetMyMomentumDirection().y()<<"  "<<(*hc)[itr]->GetMyMomentumDirection().z()<<"\n";;
	cout<<(*hc)[itr]->GetMyParticleEnergy()/keV<<"  "<<(*hc)[itr]->GetHitPosition().x()/cm<<"  "<<(*hc)[itr]->GetHitPosition().y()/cm<<"  "<<(*hc)[itr]->GetHitPosition().z()/cm<<"  "<<(*hc)[itr]->GetMyMomentumDirection().x()<<"  "<<(*hc)[itr]->GetMyMomentumDirection().y()<<"  "<<(*hc)[itr]->GetMyMomentumDirection().z()<<endl;
	outfile<<(*hc)[itr]->GetMyParticleEnergy()/keV<<"  "<<(*hc)[itr]->GetHitPosition().x()/cm<<"  "<<(*hc)[itr]->GetHitPosition().y()/cm<<"  "<<(*hc)[itr]->GetHitPosition().z()/cm<<"  "<<(*hc)[itr]->GetMyMomentumDirection().x()<<"  "<<(*hc)[itr]->GetMyMomentumDirection().y()<<"  "<<(*hc)[itr]->GetMyMomentumDirection().z()<<"\n";;
	totalMomentum+=(*hc)[itr]->GetMyMomentumDirection().x();
	
	//outfile<<(*hc)[itr]->GetMyParticleEnergy()/MeV<<"  "<<(*hc)[itr]->GetMyMomentumDirection().x()<<"  "<<(*hc)[itr]->GetMyMomentumDirection().y()<<"  "<<(*hc)[itr]->GetMyMomentumDirection().z()<<"\n";
      }
    }
    //energyHisto->Write();
  }  
void analysis::writeHistograms(){
  energyHisto->Write();
  file->Write();
  outfile.close();
  G4cout<<" mean energy "<<energyHisto->GetMean()<<G4endl;
  G4cout<<" mean momentum "<<totalMomentum/numberOfAntiprotons<<endl;


  
  //histFile->Write();
  // histFile->Close();
}

