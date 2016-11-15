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
//
#include "AntiPTestCellParameterisation.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4VPhysicalVolume.hh"
#include "globals.hh"
#include "G4UnitsTable.hh"



AntiPTestCellParameterisation::AntiPTestCellParameterisation()
{
  // Initialise.Her lages det vektorer med posisjonen midt i cellen. 
  for(G4int i=0; i<256*256; i++) {
    G4int column = i / 256;
    G4int row = i % 256;
    xCell.push_back((row-128)*0.055*mm + 27.5*um);
    yCell.push_back((column-128)*0.055*mm + 27.5*um);
  }
}

AntiPTestCellParameterisation::~AntiPTestCellParameterisation() {}

void AntiPTestCellParameterisation::ComputeTransformation(const G4int copyNo,G4VPhysicalVolume *physVol) const
{
 
  physVol->SetTranslation(G4ThreeVector(0*cm,yCell[copyNo],xCell[copyNo]));
}

