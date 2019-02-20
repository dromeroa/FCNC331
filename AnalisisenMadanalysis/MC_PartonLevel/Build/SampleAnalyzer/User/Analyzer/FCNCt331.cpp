#include "SampleAnalyzer/User/Analyzer/FCNCt331.h"
#include <iostream>
#include <TH1.h>
#include "TGraph.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <ios>
#include <iosfwd>


using namespace MA5;
using namespace std;

// -----------------------------------------------------------------------------
// Initialize
// function called one time at the beginning of the analysis
// -----------------------------------------------------------------------------
bool FCNCt331::Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters)
{
  cout << "BEGIN Initialization" << endl;

  myHisto1 = new TH1F("myHisto1","Wmass",80,0,250);

  myHisto2 = new TH1F("myHisto2","ZPmass",80,0,5000);

  myHisto3 = new TH1F("myHisto3","AntibquarkPT",80,0,3000);

  myHisto4 = new TH1F("myHisto4","CquarkPT",80,0,3000);

  // initialize variables, histos
  cout << "END   Initialization" << endl;
  return true;
}

// -----------------------------------------------------------------------------
// Finalize
// function called one time at the end of the analysis
// -----------------------------------------------------------------------------
void FCNCt331::Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files)
{
  cout << "BEGIN Finalization" << endl;

gROOT->SetStyle("Plain");
 
// Color of the canvas background
gStyle->SetCanvasColor(0);
 
// Turning off the border lines of the canvas
gStyle->SetCanvasBorderMode(0);
 
// Configuring statistics printing
gStyle->SetOptStat(111110);
 
 
TCanvas* myCanvas1 = new TCanvas("myCanvas1","myCanvas1",800,600);
myHisto1->SetLineWidth(2);
myHisto1->SetLineColor(kBlue+1);
myHisto1->SetFillColor(38);
myHisto1->GetXaxis()->SetTitle("M_{W}");
myHisto1->GetYaxis()->SetTitle("Events");
 
// Drawing histogram
myHisto1->Draw();
       
// Saving plot
myCanvas1->SaveAs("Wmass.pdf");
 

TCanvas* myCanvas2 = new TCanvas("myCanvas2","myCanvas2",800,600);
myHisto2->SetLineWidth(2);
myHisto2->SetLineColor(kRed+1);
myHisto2->SetFillColor(46);
myHisto2->GetXaxis()->SetTitle("M_{Z'}");
myHisto2->GetYaxis()->SetTitle("Events");

// Drawing histogram
myHisto2->Draw();
  
// Saving plot
myCanvas2->SaveAs("ZPmass.pdf");

TCanvas* myCanvas3 = new TCanvas("myCanvas3","myCanvas3",800,600);
myHisto3->SetLineWidth(2);
myHisto3->SetLineColor(kBlue+1);
myHisto3->SetFillColor(38);
myHisto3->GetXaxis()->SetTitle("b-quark p_{T}");
myHisto3->GetYaxis()->SetTitle("Events");
  
//Drawing histogram
myHisto3->Draw();
  
// Saving plot
myCanvas3->SaveAs("bquarkPT.pdf");



TCanvas* myCanvas4 = new TCanvas("myCanvas4","myCanvas4",800,600);
myHisto4->SetLineWidth(2);
myHisto4->SetLineColor(kBlue+1);
myHisto4->SetFillColor(38);
myHisto4->GetXaxis()->SetTitle("c-quark p_{T}");
myHisto4->GetYaxis()->SetTitle("Events");
  
 // Drawing histogram
 myHisto4->Draw();
  
 // Saving plot
 myCanvas4->SaveAs("cquarkPT.pdf");






  // saving histos
  cout << "END   Finalization" << endl;
}

// -----------------------------------------------------------------------------
// Execute
// function called each time one event is read
// -----------------------------------------------------------------------------
bool FCNCt331::Execute(SampleFormat& sample, const EventFormat& event)
{
  // ***************************************************************************
  // Example of analysis with generated particles
  // Concerned samples : LHE/STDHEP/HEPMC
  // ***************************************************************************


    if (event.mc()!=0){
  
   //cout << "---------------NEW EVENT-------------------" << endl;
   // Define the vectors to store the particles
   std::vector<const MCParticleFormat*> FinalElectrons;
   std::vector<const MCParticleFormat*> FinalAntineutrinos;
   std::vector<const MCParticleFormat*> FinalAntibquark;
   std::vector<const MCParticleFormat*> FinalCquark;

   for(unsigned int i=0; i<event.mc()->particles().size(); i++){
            const MCParticleFormat* prt = &event.mc()->particles()[i];
            if(prt->pdgid() == 11) {
               if((PHYSICS->Id->IsFinalState(prt)) == true)
                  FinalElectrons.push_back(prt);
             }
      }


   for(unsigned int i=0; i<event.mc()->particles().size(); i++){
              const MCParticleFormat* prt = &event.mc()->particles()[i];
              if(prt->pdgid()== -12) {
                  if((PHYSICS->Id->IsFinalState(prt)) == true)
                  FinalAntineutrinos.push_back(prt);
               }
          }    


   for(unsigned int i=0; i<event.mc()->particles().size(); i++){
              const MCParticleFormat* prt = &event.mc()->particles()[i];
              if(prt->pdgid() == -5) {
                 if((PHYSICS->Id->IsFinalState(prt)) == true)
                    FinalAntibquark.push_back(prt);
               }
        }


   for(unsigned int i=0; i<event.mc()->particles().size(); i++){
               const MCParticleFormat* prt = &event.mc()->particles()[i];
               if(prt->pdgid() == 4) {
                  if((PHYSICS->Id->IsFinalState(prt)) == true)
                     FinalCquark.push_back(prt);
                }
         }



  if (!(FinalElectrons.empty() && FinalAntineutrinos.empty() && FinalAntibquark.empty() && FinalCquark.empty()  )){

  MALorentzVector pW = FinalElectrons[0]->momentum() + FinalAntineutrinos[0]->momentum();

  MALorentzVector pZP = pW + FinalAntibquark[0]->momentum() + FinalCquark[0]->momentum();


  double Wmass = pW.M();

  double ZPmass = pZP.M();

  double AntibqurakPT = FinalAntibquark[0]->pt();

  double CquarkPT = FinalCquark[0]->pt();


  myHisto1 -> Fill(Wmass);

  myHisto2 -> Fill(ZPmass);

  myHisto3 -> Fill(AntibqurakPT);

  myHisto4 -> Fill(CquarkPT);


  }





   }



  return true;
}

