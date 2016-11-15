//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
// $Id:$
//
// Jane Tinslay - adapted from A01 example
// Tatsumi Koi   Minor modifications for McGill Univ.  tutorial
// W. Takase     Minor modifications for Geant4 tutorial 2010
//
#include "AntiPSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"    
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "globals.hh"
#include "G4UnitsTable.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include <iostream>
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"
////

using namespace std;
AntiPSD::AntiPSD(const G4String& name)
  :G4VSensitiveDetector(name)
{
  collectionName.insert("AntiPCollection");
  fHitsCollectionID = -1;
}

AntiPSD::~AntiPSD() {}


//G4HCofThisEvent stores all hits in one event
void AntiPSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent)
{
  //lager en collection for hvert event. 
  fHitsCollection =new AntiPHitsCollection(SensitiveDetectorName, collectionName[0]);
  //ID er -1 ved starten ogsa blir den null. 
  if(fHitsCollectionID < 0){fHitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);}
  // Add collection to the event
  hitsCollectionOfThisEvent->AddHitsCollection(fHitsCollectionID, fHitsCollection);
}

G4bool AntiPSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  G4Track* theTrack = aStep->GetTrack();
  G4ParticleDefinition* particleType = theTrack->GetDefinition();
  G4int particleID = particleType->GetPDGEncoding();
  G4String particleName = particleType->GetParticleName();	
 // Get energy deposited in this step
  G4double depositedEnergy = aStep->GetTotalEnergyDeposit()-aStep->GetNonIonizingEnergyDeposit();
  G4double kineticEnergy=theTrack->GetKineticEnergy();
  //we don't do any more if there is noe energy deposit
  //if ( depositedEnergy == 0 ) return true;
  // Get touchable for volume information.
  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  //G4StepPoint* postStepPoint = aStep->GetPostStepPoint();
  const G4ThreeVector& hitPos = preStepPoint->GetPosition();  
  const G4ThreeVector& momentumDirection =preStepPoint->GetMomentumDirection();
  G4TouchableHistory* theTouchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
  AntiPHit* aHit = 0;
  G4int isLast= aStep->IsLastStepInVolume();
  //Copy number is the number for the pixel  
  G4int copyNo = theTouchable->GetReplicaNumber(0);           // Copy number of volume.  
  aHit = new AntiPHit(copyNo);  // Create a Hit object.
  //add different varibles to the hit objekt
  aHit->SetHitPosition(hitPos);
  aHit->SetMomentumDirection(momentumDirection);
  aHit->SetIsBoundry(isLast);
  aHit->AddDepositedEnergy(depositedEnergy);                  // Set energy deposit to the Hit object.

  // Set position of prestep point to the Hit object. 
  aHit->SetParticleID(particleID);
  aHit->SetParticleName(particleName);
  aHit->SetHitTrack(theTrack);
  aHit->SetCopyNumber(theTrack->GetVolume()->GetCopyNo());
  aHit->SetMyParticleEnergy(kineticEnergy);
  //Stores this hit to the hits collection of this event                                                                                     
  fHitsCollection->insert(aHit);// Store (insert) the Hit object to hit collection container.
  const G4VProcess * theProcess=theTrack->GetCreatorProcess();
  if(theProcess==NULL){
    G4cout<<"er null"<<G4endl;
  }
  //G4String process=theProcess->GetProcessName();
    //G4cout<<process<<G4endl;
  return true;
}

void AntiPSD::EndOfEvent(G4HCofThisEvent*) {}
