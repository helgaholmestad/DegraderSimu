//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: EventAction.cc,v 1.1 2010/10/18 15:56:17 maire Exp $
// GEANT4 tag $Name: geant4-09-04 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "EventAction.hh"
#include "AntiPHit.hh"
#include "G4DigiManager.hh"
#include "analysis.hh"
#include "RunAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include <iomanip>

#include <iostream>
#include <fstream>

using namespace std;

//------------------------------------------------------------------------------

EventAction::EventAction(RunAction* run)
:runAct(run),printModulo(1)
{

  // G4DigiManager * fDM = G4DigiManager::GetDMpointer();
  // MyExpDetDigitizer * myDM = new MyExpDetDigitizer( "MyMod", "AntiPCollection", "MyDigit" );
  // fDM->AddNewModule(myDM);
}

//------------------------------------------------------------------------------

EventAction::~EventAction()
{
}

//------------------------------------------------------------------------------

void EventAction::BeginOfEventAction(const G4Event* evt)
{  
  
	
}

//------------------------------------------------------------------------------

void EventAction::EndOfEventAction(const G4Event* event)
{
  analysis::GetInstance()->writePerEvent(event);
  
}

//------------------------------------------------------------------------------