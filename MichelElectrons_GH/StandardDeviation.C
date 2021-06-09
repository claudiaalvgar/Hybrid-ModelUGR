{
  //TCanvas*c1=new TCanvas();
  auto c1 = new TCanvas("c1","Title",200,10,700,500);
  c1->SetGrid();
  gStyle->SetOptStat(0);

  //Leemos la informacion de la simulacion y de los PMTs
  TFile *inputMichels= new TFile("output_10000_30MeV_gaus_semi.root","read");


  vector<double>  *X, *Y, *Z, *E;
  //int eventID;


  TTree* treeMichels=(TTree*)inputMichels->Get("ana/tree");

  treeMichels->SetBranchAddress("X",&X);
  treeMichels->SetBranchAddress("Y",&Y);
  treeMichels->SetBranchAddress("Z",&Z);
  treeMichels->SetBranchAddress("E",&E);
  //treeMichels->SetBranchAddress("eventID",&eventID);



  int entriesMichels=treeMichels->GetEntries(); //1000

  //Media posicion x
  TH1F*hx=new TH1F("hx", "", 100,-500,500);
  //Media posicion y
  TH1F*hy=new TH1F("hy", "", 100,-500,500);
  //Media posicion z
  TH1F*hz=new TH1F("hz", "", 100,-500,500);
  //RMS
  //TH2D*histx=new TH2D("hist","",100,0,1000,100,0,60);
  //TH2D*histy=new TH2D("hist","",100,0,1000,100,0,60);
  //TH2D*histz=new TH2D("hist","",100,0,1000,100,0,60);

  TH1F*histx=new TH1F("hist","",100,0,60);
  TH1F*histy=new TH1F("hist","",100,0,60);
  TH1F*histz=new TH1F("hist","",100,0,60);


for(int i=0;i<entriesMichels;i++) //numero de particulas que lanzas son las entries (100)
{
  treeMichels->GetEntry(i); //primer electron de Michel
  cout<<"------Electron numero-----"<<i<<endl;

//Fotones detectados a partir de fotones generados
hx->Reset();
hy->Reset();
hz->Reset();
for(int j=0;j<X->size();j++){

//Para ese electron de michel llenamos el histograma con todas sus posiciones x,y,z
//de las deposiciones de energia y calculamos la media
   hx->Fill(X->at(j),E->at(j));
   hy->Fill(Y->at(j),E->at(j));
   hz->Fill(Z->at(j),E->at(j));

   //cout<<"x= "<<X->at(j)/E->at(j)<<" y= "<<Y->at(j)/E->at(j)<<" z= "<<Z->at(j)/E->at(j)<<endl;
   //cout<<"fotones generados= "<<phot_generated->at(j)<<endl;
}

//Aplicando el corte en 5cm para la desviacion estandar
 //if(hx->GetRMS()>5||hy->GetRMS()>5||hz->GetRMS()>5) continue;
  //sigmaX de ese electron
  double sigmax=hx->GetRMS();
  cout<<"SigmaX= "<<sigmax<<endl;
  //Y
  double sigmay=hy->GetRMS();
  cout<<"SigmaY= "<<sigmay<<endl;
  //Z
  double sigmaz=hz->GetRMS();
  cout<<"SigmaZ= "<<sigmaz<<endl;

   //histx->Fill(i,sigmax);
   //histy->Fill(i,sigmay);
   //histz->Fill(i,sigmaz);
   histx->Fill(sigmax);
   histy->Fill(sigmay);
   histz->Fill(sigmaz);

   }//entries





   histx->SetMarkerStyle(21);
   histy->SetMarkerStyle(21);
   histz->SetMarkerStyle(21);
   histx->SetMarkerColor(1);
   histy->SetMarkerColor(4);
   histz->SetMarkerColor(6);

   histx->SetTitle("E= 30MeV");
   //histx->GetXaxis()->SetTitle("Michel electron event");
   //histx->GetYaxis()->SetTitle("Standard Deviation");
   //histx->GetXaxis()->SetTitle("Standard Deviation (cm)");
   //histx->Draw("");
   //histy->Draw("same");
   //histz->Draw("same");


   TH1* hcx = histx->GetCumulative();
   hcx->GetYaxis()->SetTitle("Cumulative");
   hcx->GetYaxis()->SetRangeUser(0,10000);
   hcx->GetXaxis()->SetTitle("Standard Deviation (cm)");
   hcx->Draw("");
  TLine *lcut7=new TLine(7,0,7,10000);
   lcut7->SetLineColor(kRed);
   lcut7->Draw();


   auto leg = new TLegend(0.1,0.7,0.48,0.9);

     //leg->AddEntry(histx,"#sigmaX","p");
     //leg->AddEntry(histy,"#sigmaY","p");
     //leg->AddEntry(histz,"#sigmaZ","p");
     leg->AddEntry(lcut7,"Cut #sigma=7cm","l");


     leg->Draw();
}
