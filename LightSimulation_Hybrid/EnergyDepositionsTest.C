//Representa en las direcciones X Y Z las energías depositadas por un muón
//dentro y fuera del volumen activo y además representa los límites del
//volumen activo en cada una de las dimensiones

{

  //Leemos el archivo .root, version 21
  //TFile *input= new TFile("output_muonX.root","read");
  //TFile *input= new TFile("output_muonY.root","read");
  //TFile *input= new TFile("output_muonZ.root","read");

  //Leemos el archivo .root, version 22_02 con la geometria nowires
  //TFile *input= new TFile("outputmuonX_v22_02.root","read");
  //TFile *input= new TFile("outputmuonY_v22_02.root","read");
  //TFile *input= new TFile("outputmuonZ_v22_02.root","read");

  //Leemos el archivo .root, version 22_02 con wires (tiene el argon gas)
  //TFile *input= new TFile("muonX_v22_wires.root","read");
  //TFile *input= new TFile("muonY_v22_wires.root","read");
  TFile *input= new TFile("muonZ_v22_wires.root","read");

  //Declaro las dos columnas del fichero
  //dEdx son E y E1 nphot/dx son P y P1
  vector<double> *Z;
  vector<double> *E;
  vector<double> *Z1;
  vector<double> *E1;

  //Leemos el TTree
  TTree* tree1=(TTree*)input->Get("ana/tree");

  //Semi

  tree1->SetBranchAddress("E", &E);
  //tree1->SetBranchAddress("X", &X);
  //tree1->SetBranchAddress("Y", &Y);
  tree1->SetBranchAddress("Z", &Z);
  //Lib
  tree1->SetBranchAddress("E1", &E1);
  //tree1->SetBranchAddress("X1", &X1);
  //tree1->SetBranchAddress("Y1", &Y1);
  tree1->SetBranchAddress("Z1", &Z1);


  int entries=tree1->GetEntries();
  cout<<entries<<endl;
  //Para plotearlo en un graph
  const Int_t ns = 1000000;
  const Int_t nl = 1000000;
  //Double_t x[ns], e[ns];
  //Double_t x1[nl], e1[nl];
  //Double_t y[ns], e[ns];
  //Double_t y1[nl], e1[nl];
  Double_t z[ns], e[ns];
  Double_t z1[nl], e1[nl];

  int counter=0;

  for(int i=0;i<entries;i++)
  {

    tree1->GetEntry(i);


  for (Int_t j=0;j<E->size();j++) {
    z[j] = Z->at(j);
    e[j] = E->at(j);
    counter=counter+1;


  }


  for (Int_t j=0;j<E1->size();j++) {
    //para que no haga deposiciones de energía en el argon gas
    //if (Y1->at(j)>244.38) continue;
    z1[j] = Z1->at(j);
    e1[j] = E1->at(j);
    //if(y1[j]>244.38){
      //cout<<y1[j]<<endl;
    //}
  }

}

Double_t activemin=0;
Double_t activemax=0;

for(int i=0;i<counter;i++){
  if(z[i]>activemax){
    activemax=z[i];
  }
  if(z[i]<activemin){
    activemin=z[i];
  }
}
cout<<"Active max: "<<activemax;
cout<<"Active min: "<<activemin;

  //TGraph* grs = new TGraph(ns,x,e);
  //TGraph* grs = new TGraph(ns,y,e);
  TGraph* grs = new TGraph(ns,z,e);


  //TGraph* grl = new TGraph(nl,x1,e1);
  //TGraph* grl = new TGraph(nl,y1,e1);
  TGraph* grl = new TGraph(nl,z1,e1);



   auto mg = new TMultiGraph();

   grs->SetMarkerStyle(7);
   grs->SetMarkerColor(kViolet-2);

   grl->SetMarkerStyle(7);
   grl->SetMarkerColor(kGray+1);

   mg->Add( grs );
   mg->Add( grl );


   //mg->SetTitle("X direction 5 GeV Muon=(-260,100,250)cm Hybrid Model");
   //mg->SetTitle("Y direction 5 GeV Muon=(100,270,250)cm Hybrid Model");
   mg->SetTitle("Z direction 5 GeV Muon=(100,100,-56)cm Hybrid Model");
   mg->GetXaxis()->SetTitle("Z (cm)");
   mg->GetYaxis()->SetTitle("E (MeV)");
   mg->GetYaxis()->SetRangeUser(0,0.5);
   mg->Draw("AP");


//Cryostat boundaries x
//TLine *lcryomin=new TLine(-259.98 ,0,-259.98 ,0.5);
 //lcryomin->SetLineColor(kBlue);
 //lcryomin->Draw();

 //TLine *lcryomax=new TLine(259.98 ,0,259.98 ,0.5);
  //lcryomax->SetLineColor(kBlue);
  //lcryomax->Draw();

  //Cryostat boundaries y
  //TLine *lcryomin=new TLine(-271.53 ,0,-271.53 ,0.5);
   //lcryomin->SetLineColor(kBlue);
   //lcryomin->Draw();

  //TLine *lcryomax=new TLine(244.38 ,0,244.38 ,0.5);
    //lcryomax->SetLineColor(kBlue);
    //lcryomax->Draw();


//Cryostat boundaries z
   TLine *lcryomin=new TLine(-55.4 ,0,-55.4 ,0.5);
    lcryomin->SetLineColor(kBlue);
    lcryomin->Draw();

    TLine *lcryomax=new TLine(647.3 ,0,647.3 ,0.5);
     lcryomax->SetLineColor(kBlue);
     lcryomax->Draw();

    TLine *lactivemin=new TLine(activemin,0,activemin,0.5);
     lactivemin->SetLineColor(kBlue);
     lactivemin->Draw();

     TLine *lactivemax=new TLine(activemax,0,activemax,0.5);
      lactivemax->SetLineColor(kBlue);
      lactivemax->Draw();


       //TLine *l2=new TLine(215.5,0,215.5,0.5);
        //l2->SetLineColor(kBlue);
        //l2->Draw();



  }
