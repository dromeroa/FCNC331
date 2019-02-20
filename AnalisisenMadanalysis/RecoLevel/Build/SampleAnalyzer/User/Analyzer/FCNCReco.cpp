#include "SampleAnalyzer/User/Analyzer/FCNCReco.h"
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
bool FCNCReco::Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters)
{
  cout << "BEGIN Initialization" << endl;
  // initialize variables, histos

  myHisto1 = new TH1F("myHisto1","NumberofJets",7,-0.5,6.5);
  myHisto2 = new TH1F("myHisto2","NumberofElectrons",7,-0.5,6.5);
  myHisto3 = new TH1F("myHisto3","NumberofSignalElectrons",7,-0.5,6.5);
  myHisto4 = new TH1F("myHisto4","NumberofBtaggedJets",7,-0.5,6.5);
  myHisto5 = new TH1F("myHisto5","NumberofSignalJets",7,-0.5,6.5);
  myHisto6 = new TH1F("myHisto6","MET",60,0.,1000);
  myHisto7 = new TH1F("myHisto7","Wmass",60,0.,600);
  myHisto8 = new TH1F("myHisto8","bjetPT",60,0.,1000);

  cout << "END   Initialization" << endl;
  return true;
}

// -----------------------------------------------------------------------------
// Finalize
// function called one time at the end of the analysis
// -----------------------------------------------------------------------------
void FCNCReco::Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files)
{
  cout << "BEGIN Finalization" << endl;
  // saving histos
  gROOT->SetStyle("Plain");
 
  // Color of the canvas background
  gStyle->SetCanvasColor(0);
 
   // Turning off the border lines of the canvas
   gStyle->SetCanvasBorderMode(0);
 
   // Configuring statistics printing
   gStyle->SetOptStat(111110);
 
 
   TCanvas* myCanvas1 = new TCanvas("myCanvas1","",600,600);
   myHisto1->SetLineWidth(2);
   myHisto1->SetLineColor(kBlue);
   myHisto1->SetFillColor(38);
   myHisto1->GetXaxis()->SetTitle("Number of jets");
   myHisto1->GetYaxis()->SetTitle("Events");
 
   // Drawing histogram
   myHisto1->Draw();
   myCanvas1->SaveAs("Njets.pdf");

    TCanvas* myCanvas2 = new TCanvas("myCanvas2","",600,600);
    myHisto2->SetLineWidth(2);
    myHisto2->SetLineColor(kBlue);
    myHisto2->SetFillColor(38);
    myHisto2->GetXaxis()->SetTitle("Number of Electrons");
    myHisto2->GetYaxis()->SetTitle("Events");
  
   // Drawing histogram
   myHisto2->Draw();
   myCanvas2->SaveAs("NElectrons.pdf");



 TCanvas* myCanvas3 = new TCanvas("myCanvas3","",600,600);
 myHisto3->SetLineWidth(2);
 myHisto3->SetLineColor(kBlue);
 myHisto3->SetFillColor(38);
 myHisto3->GetXaxis()->SetTitle("Number of Signal Electrons");
 myHisto3->GetYaxis()->SetTitle("Events");
      
 // Drawing histogram
 myHisto3->Draw();
 myCanvas3->SaveAs("NSignalElectrons.pdf");


TCanvas* myCanvas4 = new TCanvas("myCanvas4","",600,600);
myHisto4->SetLineWidth(2);
myHisto4->SetLineColor(kBlue);
myHisto4->SetFillColor(38);
myHisto4->GetXaxis()->SetTitle("Number of b-tagged jets");
myHisto4->GetYaxis()->SetTitle("Events");
      
 // Drawing histogram
myHisto4->Draw();
myCanvas4->SaveAs("NBtaggedJets.pdf");


TCanvas* myCanvas5 = new TCanvas("myCanvas5","",600,600);
myHisto5->SetLineWidth(2);
myHisto5->SetLineColor(kBlue);
myHisto5->SetFillColor(38);
myHisto5->GetXaxis()->SetTitle("Number of Signal jets");
myHisto5->GetYaxis()->SetTitle("Events");
      
// Drawing histogram
myHisto5->Draw();
myCanvas5->SaveAs("NSignalJets.pdf");

TCanvas* myCanvas6 = new TCanvas("myCanvas6","",600,600);
myHisto6->SetLineWidth(2);
myHisto6->SetLineColor(kBlue);
myHisto6->SetFillColor(38);
myHisto6->GetXaxis()->SetTitle("MET (GeV)");
myHisto6->GetYaxis()->SetTitle("Events");

// Drawing histogram
myHisto6->Draw();
myCanvas6->SaveAs("MET.pdf");


TCanvas* myCanvas7 = new TCanvas("myCanvas7","",600,600);
myHisto7->SetLineWidth(2);
myHisto7->SetLineColor(kBlue);
myHisto7->SetFillColor(38);
myHisto7->GetXaxis()->SetTitle("W mass");
myHisto7->GetYaxis()->SetTitle("Events");
 
// Drawing histogram
myHisto7->Draw();
myCanvas7->SaveAs("Wmass.pdf");


TCanvas* myCanvas8 = new TCanvas("myCanvas8","",600,600);
myHisto8->SetLineWidth(2);
myHisto8->SetLineColor(kBlue);
myHisto8->SetFillColor(38);
myHisto8->GetXaxis()->SetTitle("b-jet PT");
myHisto8->GetYaxis()->SetTitle("Events");
 
// Drawing histogram
myHisto8->Draw();
myCanvas8->SaveAs("bjetPT.pdf");
 




cout << "END   Finalization" << endl;
}

// -----------------------------------------------------------------------------
// Execute
// function called each time one event is read
// -----------------------------------------------------------------------------
bool FCNCReco::Execute(SampleFormat& sample, const EventFormat& event)
{

  // ***************************************************************************
  // Example of analysis with reconstructed objects
  // Concerned samples : 
  //   - LHCO samples
  //   - LHE/STDHEP/HEPMC samples after applying jet-clustering algorithm
  // ***************************************************************************
  
  // Event weight
//  double myWeight=1.;
//  if (!Configuration().IsNoEventWeight() && event.mc()!=0) myWeight=event.mc()->weight();

//  Manager()->InitializeForNewEvent(myWeight);

  if (event.rec()!=0)
  {
//    cout << "---------------NEW EVENT-------------------" << endl;


    // Aqui comienza el evento


    // El numero de jets
    myHisto1 -> Fill(event.rec()->jets().size());

    myHisto2 -> Fill(event.rec()->electrons().size());


   // Declara los contenedores a ser llenados

   vector<const RecJetFormat*> SignalJets, BtaggedJets;
   vector<const RecLeptonFormat*> SignalLeptons, LooseElectrons;


  // Para los electrons
  for(unsigned int ii=0; ii<event.rec()->electrons().size(); ii++)
  {
     const RecLeptonFormat *myElec = &(event.rec()->electrons()[ii]);
     double eta = std::abs(myElec->eta());
     double pt = myElec->pt();
     double iso_var = PHYSICS->Isol->eflow->sumIsolation(myElec,event.rec(),0.4,0.,IsolationEFlow::ALL_COMPONENTS);

     if((eta>1.44) and (eta<1.57)) continue;
     if(eta>2.5) continue;


     if(iso_var>0.15*pt) continue;

     if (pt>20) SignalLeptons.push_back(myElec);
     if (pt>10) LooseElectrons.push_back(myElec);

  }

   unsigned int ne= SignalLeptons.size();
   myHisto3 -> Fill(ne);

   // Para los jets
   for(unsigned int j=0; j<event.rec()->jets().size(); j++){

       const RecJetFormat *myJet = &(event.rec()->jets()[j]); 
       double eta = std::abs(myJet->eta());
       double pt = myJet->pt();

       if(eta > 5.) continue;


       if(pt>30.) SignalJets.push_back(myJet);
       if(pt>20. && eta<2.5 && myJet->btag())
         BtaggedJets.push_back(myJet); 

    }

   SignalJets = PHYSICS->Isol->JetCleaning(SignalJets,LooseElectrons,0.2);
   BtaggedJets = PHYSICS->Isol->JetCleaning(BtaggedJets,LooseElectrons,0.2);

   unsigned int nb = BtaggedJets.size();
   unsigned int nj = SignalJets.size();

   myHisto4 -> Fill(nb);
   myHisto5 -> Fill(nj);


   MALorentzVector pTm = event.rec()->MET().momentum();
   double MET = pTm.Pt();


  if (SignalLeptons.size()!=0)
  {
     MALorentzVector pW = SignalLeptons[0]->momentum()+ pTm;
     double pWMass = pW.M();
     myHisto7 -> Fill(pWMass);
  }

   myHisto6 -> Fill(MET);


   if (BtaggedJets.size()!=0)
    {
      myHisto8 -> Fill(BtaggedJets[0]->pt());
    }
 


/*
    // Looking through the reconstructed jet collection
    for (MAuint32 i=0;i<event.rec()->jets().size();i++)
    {
      const RecJetFormat& jet = event.rec()->jets()[i];
      cout << "----------------------------------" << endl;
      cout << "Jet" << endl;
      cout << "----------------------------------" << endl;
      cout << "jet: index=" << i+1 
           << " charge=" << jet.charge() << endl;
      cout << "px=" << jet.px()
           << " py=" << jet.py()
           << " pz=" << jet.pz()
           << " e="  << jet.e()
           << " m="  << jet.m() << endl;
      cout << "pt=" << jet.pt() 
           << " eta=" << jet.eta() 
           << " phi=" << jet.phi() << endl;
      cout << "b-tag=" << jet.btag()
           << " true b-tag (before eventual efficiency)=" 
           << jet.true_btag() << endl;
      cout << "EE/HE=" << jet.EEoverHE()
           << " ntracks=" << jet.ntracks() << endl;
      cout << endl;
    }

    // Transverse missing energy (MET)
    cout << "MET pt=" << event.rec()->MET().pt()
         << " phi=" << event.rec()->MET().phi() << endl;
    cout << endl;

    // Transverse missing hadronic energy (MHT)
    cout << "MHT pt=" << event.rec()->MHT().pt()
              << " phi=" << event.rec()->MHT().phi() << endl;
    cout << endl;

    // Total transverse energy (TET)
    cout << "TET=" << event.rec()->TET() << endl;
    cout << endl;

    // Total transverse hadronic energy (THT)
    cout << "THT=" << event.rec()->THT() << endl;
    cout << endl;

  */

  }
  
  return true;
}

