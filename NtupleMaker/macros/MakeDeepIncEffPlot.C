// Use this macro to make a cutflow after running an analyzer on your data.
// It's necessary that the analyzer is run on the data because it implments a
// correction to the NtupleMaker HLT decisions.
//
// to run this macro, open root
// root -l
// load the macro
// .L macros/MakeCutflowFromOuttree()
// and then execute it on the file you made with the analyzer
// .x MakeCutflowFromOuttree("filename.root")
//

void MakeDeepIncEffPlot(char* filename, int key) {

    TFile *_file0 = TFile::Open(filename);

    TTree* tree = (TTree*)_file0->Get("outTree");

    double nEvents = tree->Draw("nEvents", "nEvents>0", "goff");

    std::cout << nEvents << '\t' << "nEvents" << '\n' << std::endl;

    TH1::SetDefaultSumw2();

    TCanvas *c1 = new TCanvas("c1", "", 600, 400);
    gStyle->SetOptStat(kFALSE);

    // TCut for full selection and then missing each part
    // t1, t2, j1, j2, mjj (all in GeV)
    // 30, 30, 120, 45, 700 (full offline)
    // --, 30, 120, 45, 700 // key = 0
    // 30, --, 120, 45, 700 // key = 1
    // 30, 30, --,  45, 700 // key = 2
    // 30, 30, 120, --, 700 // key = 3
    // 30, 30, 120, 45, --- // key = 4
    // 30, 30, ---, --, 700 // key = 5

    TCut viable = "viableTaus>0 && viableJets>0";
    TCut passHLT = "passDeepInclusiveVBFHLT>0";
    TCut matchHLT = "passDeepInclusiveVBFHLT>0 && matchedHLTJets>0 && matchedHLTTaus>0"; 
    TCut fullOffline = "t1_ptAOD>=30 && t2_ptAOD>=30 && j1_ptAOD>=120 && j2_ptAOD>=45 && mjjAOD>=700";

    TCut misst1pt = "t1_ptAOD>= 0 && t2_ptAOD>=30 && j1_ptAOD>=120 && j2_ptAOD>=45 && mjjAOD>=700";
    //TCut misst1pt = "t1_ptAOD>= 0 && t2_ptAOD>=50 && j1_ptAOD>=45 && j2_ptAOD>=45 && mjjAOD>=800";
    TCut misst2pt = "t1_ptAOD>=30 && t2_ptAOD>= 0 && j1_ptAOD>=120 && j2_ptAOD>=45 && mjjAOD>=700";
    TCut missj1pt = "t1_ptAOD>=30 && t2_ptAOD>=30 && j1_ptAOD>= 0 && j2_ptAOD>=45 && mjjAOD>=700";
    TCut missj2pt = "t1_ptAOD>=30 && t2_ptAOD>=30 && j1_ptAOD>=120 && j2_ptAOD>= 0 && mjjAOD>=700";
    TCut missMjj  = "t1_ptAOD>=30 && t2_ptAOD>=30 && j1_ptAOD>=120 && j2_ptAOD>=45 && mjjAOD>=  0";
    
    TCut missjets = "t1_ptAOD>=30 && t2_ptAOD>=30 && j1_ptAOD>= 0 && j2_ptAOD>= 0 && mjjAOD>=700"; // lets us get a better look at j1_pt
  
    double numCount;
    double demCount;
 
    if (key == 0) {
      const Int_t NBINS = 10;
      Double_t edges[NBINS + 1] = {0.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 200.0};
      TH1F* h_t1TOnum = new TH1F("h_t1TOnum", "", NBINS, edges); // t1TOnum is t1_pt Turn-On Numerator
      TH1F* h_t1TOdem = new TH1F("h_t1TOdem", "", NBINS, edges);
      TH1F* h_t1TOratio = new TH1F("h_t1TOratio", "", NBINS, edges);

      tree->Draw("t1_ptAOD >> h_t1TOnum", viable && misst1pt && passHLT, "goff");
      tree->Draw("t1_ptAOD >> h_t1TOdem", viable && misst1pt, "goff");
      numCount = tree->Draw("t1_ptAOD >> h_t1TOnum", viable && misst1pt && passHLT, "goff");
      demCount = tree->Draw("t1_ptAOD >> h_t1TOdem", viable && misst1pt, "goff");
      std::cout << numCount << '\t' << "numerator Events" << std::endl;
      std::cout << demCount << '\t' << "denominator Events" << std::endl;

      h_t1TOratio = (TH1F*)h_t1TOnum->Clone();
      h_t1TOratio->Divide(h_t1TOdem);

      h_t1TOratio->SetTitle("t1_pt Turn-On Plot");
      h_t1TOratio->Draw("E");
      h_t1TOratio->GetYaxis()->SetRangeUser(0.,1.1);

      c1->Print("t1_pt_HLT_turnon.png", "png");
    }
   
    if (key == 1) {
      const Int_t NBINS = 8;
      Double_t edges[NBINS + 1] = {0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 150.0};
      TH1F* h_t2TOnum = new TH1F("h_t2TOnum", "", NBINS, edges); // t2TOnum is t2_pt Turn-On Numerator
      TH1F* h_t2TOdem = new TH1F("h_t2TOdem", "", NBINS, edges);
      TH1F* h_t2TOratio = new TH1F("h_t2TOratio", "", NBINS, edges);

      tree->Draw("t2_ptAOD >> h_t2TOnum", viable && misst2pt && passHLT, "goff");
      tree->Draw("t2_ptAOD >> h_t2TOdem", viable && misst2pt, "goff");
      numCount = tree->Draw("t2_ptAOD >> h_t2TOnum", viable && misst2pt && passHLT, "goff");
      demCount = tree->Draw("t2_ptAOD >> h_t2TOdem", viable && misst2pt, "goff");
      std::cout << numCount << '\t' << "numerator Events" << std::endl;
      std::cout << demCount << '\t' << "denominator Events" << std::endl;

      h_t2TOratio = (TH1F*)h_t2TOnum->Clone();
      h_t2TOratio->Divide(h_t2TOdem);

      h_t2TOratio->SetTitle("t2_pt Turn-On Plot");
      h_t2TOratio->Draw("E");
      h_t2TOratio->GetYaxis()->SetRangeUser(0.,1.1);

      c1->Print("t2_pt_HLT_turnon.png", "png");
    }

    if (key == 2) {
      const Int_t NBINS = 11;
      Double_t edges[NBINS + 1] = {0.0, 20.0, 40.0, 60.0, 80.0, 100.0, 120.0, 140.0, 160.0, 180.0, 200.0, 300.0};
      TH1F* h_j1TOnum = new TH1F("h_j1TOnum", "", NBINS, edges); // j1TOnum is j1_pt Turn-On Numerator
      TH1F* h_j1TOdem = new TH1F("h_j1TOdem", "", NBINS, edges);
      TH1F* h_j1TOratio = new TH1F("h_j1TOratio", "", NBINS, edges);

      tree->Draw("j1_ptAOD >> h_j1TOnum", viable && missj1pt && passHLT, "goff");
      tree->Draw("j1_ptAOD >> h_j1TOdem", viable && missj1pt, "goff");
      numCount = tree->Draw("j1_ptAOD >> h_j1TOnum", viable && missj1pt && passHLT, "goff");
      demCount = tree->Draw("j1_ptAOD >> h_j1TOdem", viable && missj1pt, "goff");
      std::cout << numCount << '\t' << "numerator Events" << std::endl;
      std::cout << demCount << '\t' << "denominator Events" << std::endl;

      h_j1TOratio = (TH1F*)h_j1TOnum->Clone();
      h_j1TOratio->Divide(h_j1TOdem);

      h_j1TOratio->SetTitle("j1_pt Turn-On Plot");
      h_j1TOratio->Draw("E");
      h_j1TOratio->GetYaxis()->SetRangeUser(0.,1.1);

      c1->Print("j1_pt_HLT_turnon.png", "png");
    }

    if (key == 3) {
      const Int_t NBINS = 10;
      Double_t edges[NBINS+1] = {0.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 200.0};
      TH1F* h_j2TOnum = new TH1F("h_j2TOnum", "", NBINS, edges); // j2TOnum is j2_pt Turn-On Numerator
      TH1F* h_j2TOdem = new TH1F("h_j2TOdem", "", NBINS, edges);
      TH1F* h_j2TOratio = new TH1F("h_j2TOratio", "", NBINS, edges);

      tree->Draw("j2_ptAOD >> h_j2TOnum", viable && missj2pt && passHLT, "goff");
      tree->Draw("j2_ptAOD >> h_j2TOdem", viable && missj2pt, "goff");
      numCount = tree->Draw("j2_ptAOD >> h_j2TOnum", viable && missj2pt && passHLT, "goff");
      demCount = tree->Draw("j2_ptAOD >> h_j2TOdem", viable && missj2pt, "goff");
      std::cout << numCount << '\t' << "numerator Events" << std::endl;
      std::cout << demCount << '\t' << "denominator Events" << std::endl;

      h_j2TOratio = (TH1F*)h_j2TOnum->Clone();
      h_j2TOratio->Divide(h_j2TOdem);

      h_j2TOratio->SetTitle("j2_pt Turn-On Plot");
      h_j2TOratio->Draw("E");
      h_j2TOratio->GetYaxis()->SetRangeUser(0.,1.1);

      c1->Print("j2_pt_HLT_turnon.png", "png");
    }

    if (key == 4) {
      const Int_t NBINS = 10;
      Double_t edges[NBINS+1] = {0.0, 200.0, 300.0, 400.0, 500.0, 600.0, 700.0, 1000.0, 1500.0, 2000.0, 3000.0};
      TH1F* h_mjjTOnum = new TH1F("h_mjjTOnum", "", NBINS, edges); // mjjTOnum is mjj_pt Turn-On Numerator
      TH1F* h_mjjTOdem = new TH1F("h_mjjTOdem", "", NBINS, edges);
      TH1F* h_mjjTOratio = new TH1F("h_mjjTOratio", "", NBINS, edges);

      tree->Draw("mjjAOD >> h_mjjTOnum", viable && missMjj && passHLT, "goff");
      tree->Draw("mjjAOD >> h_mjjTOdem", viable && missMjj, "goff");
      numCount = tree->Draw("mjjAOD >> h_mjjTOnum", viable && missMjj && passHLT, "goff");
      demCount = tree->Draw("mjjAOD >> h_mjjTOdem", viable && missMjj, "goff");
      std::cout << numCount << '\t' << "numerator Events" << std::endl;
      std::cout << demCount << '\t' << "denominator Events" << std::endl;
 

      h_mjjTOratio = (TH1F*)h_mjjTOnum->Clone();
      h_mjjTOratio->Divide(h_mjjTOdem);

      h_mjjTOratio->SetTitle("mjj_pt Turn-On Plot");
      h_mjjTOratio->Draw("E");
      h_mjjTOratio->GetYaxis()->SetRangeUser(0.,1.1);

      c1->Print("mjj_HLT_turnon.png", "png");
    }

    if (key == 5) {
      const Int_t NBINS = 11;
      Double_t edges[NBINS+1] = {0.0, 20.0, 40.0, 60.0, 80.0, 100.0, 120.0, 140.0, 160.0, 180.0, 200.0, 300.0};
      TH1F* h_j1TOnum = new TH1F("h_j1TOnum", "", NBINS, edges); // j1TOnum is j1_pt Turn-On Numerator
      TH1F* h_j1TOdem = new TH1F("h_j1TOdem", "", NBINS, edges);
      TH1F* h_j1TOratio = new TH1F("h_j1TOratio", "", NBINS, edges);

      tree->Draw("j1_ptAOD >> h_j1TOnum", viable && missjets && passHLT, "goff");
      tree->Draw("j1_ptAOD >> h_j1TOdem", viable && missjets, "goff");
      numCount = tree->Draw("j1_ptAOD >> h_j1TOnum", viable && missjets && passHLT, "goff");
      demCount = tree->Draw("j1_ptAOD >> h_j1TOdem", viable && missjets, "goff");
      std::cout << numCount << '\t' << "numerator Events" << std::endl;
      std::cout << demCount << '\t' << "denominator Events" << std::endl;

      h_j1TOratio = (TH1F*)h_j1TOnum->Clone();
      h_j1TOratio->Divide(h_j1TOdem);

      h_j1TOratio->SetTitle("j1 pt Turn-On no j2 pt Plot");
      h_j1TOratio->Draw("E");
      h_j1TOratio->GetYaxis()->SetRangeUser(0.,1.1);

      c1->Print("odd_HLT_turnon.png", "png");
    }


}
