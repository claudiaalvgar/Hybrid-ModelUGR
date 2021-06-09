{


  //TCanvas*c1=new TCanvas();
  auto *c1 = new TCanvas("c1","Title",200,10,700,500);

  c1->SetGrid();
  //gStyle->SetOptStat(0);
  c1->Divide(2,2,0.001,0.001);


  TH1F* histerror = new TH1F("histerror","",100,-0.4,0.4);

  vector<double> distance, photsreco, e;
  distance.clear();
  e.clear();
  photsreco.clear();

  TFile *inputMichels= new TFile("analysisOutputVUV_run1-1_subrun1-2.root","read");


  TFile *inputPMTs= new TFile("PMTs.root","read");


  vector<double> *E, *phot_generated, *X, *Y, *Z, *flash_pe_vuv, *phot_detected;


  vector<double> *numpmt, *Xpmt, *Ypmt, *Zpmt;

  TTree* treeMichels=(TTree*)inputMichels->Get("ana/tree");
  TTree* treePMTs=(TTree*)inputPMTs->Get("treepmt");

  treeMichels->SetBranchAddress("E",&E);
  treeMichels->SetBranchAddress("phot_generated",&phot_generated);
  treeMichels->SetBranchAddress("X",&X);
  treeMichels->SetBranchAddress("Y",&Y);
  treeMichels->SetBranchAddress("Z",&Z);
  treeMichels->SetBranchAddress("phot_detected",&phot_detected);
  treeMichels->SetBranchAddress("flash_pe_vuv",&flash_pe_vuv);



  treePMTs->SetBranchAddress("numpmt",&numpmt);
  treePMTs->SetBranchAddress("Xpmt",&Xpmt);
  treePMTs->SetBranchAddress("Ypmt",&Ypmt);
  treePMTs->SetBranchAddress("Zpmt",&Zpmt);


  int entriesMichels=treeMichels->GetEntries(); //1000
  //Cada PMT es una entrada
  int entriesPMTs=treePMTs->GetEntries(); //320

  //Cambiar este parámetro para ajustar: Rango de angulos para el que se hace el estudio 10-(0,10) 20-(10,20) 30-(20,30) 40-(30,40) 50-(40,50) 60-(50,60) 70-(60,70),80-(70,80), 90-(80,90)
  angle=50;


  //Media posicion x
  TH1F*hx=new TH1F("hx", "", 100,-500,500);
  //Media posicion y
  TH1F*hy=new TH1F("hy", "", 100,-500,500);
  //Media posicion z
  TH1F*hz=new TH1F("hz", "", 100,-500,500);

for(int i=0;i<entriesMichels;i++) //numero de particulas que lanzas son las entries (100)
{
  treeMichels->GetEntry(i); //primer electron de Michel


  cout<<"------Electron numero-----"<<i<<endl;
  //Inicializamos el numero de fotones generados para electron a 0
  double phot_gen=0;
  double Energy=0;

  hx->Reset();
  hy->Reset();
  hz->Reset();
//Fotones detectados a partir de fotones generados
for(int j=0;j<X->size();j++){

   hx->Fill(X->at(j),E->at(j));
   hy->Fill(Y->at(j),E->at(j));
   hz->Fill(Z->at(j),E->at(j));
   phot_gen += phot_generated->at(j);
   Energy += E->at(j);
}
if(phot_gen==0) continue;

  //double xscint=hx->GetMean()/Energy;
  double xscint=hx->GetMean();
  //Y
  //double yscint=hy->GetMean()/Energy;
  double yscint=hy->GetMean();
  //Z
  //double zscint=hz->GetMean()/Energy;
  double zscint=hz->GetMean();
  //cout<<hx->GetRMS()<<" "<<hy->GetRMS()<<" "<<hz->GetRMS()<<endl;
  //Corte para que no tenga en cuenta los electrones que sus posiciones de deposiciones de energía estén
  //separadas más de 5cm
  double MinSpread=7;
  if(hx->GetRMS()>MinSpread||hy->GetRMS()>MinSpread||hz->GetRMS()>MinSpread) continue;
  //cout<<" x media= "<<xscint<<" y= "<<yscint<<" z= "<<zscint<<endl;
  //cout<<"fotones generados totales= "<<phot_gen<<endl;

  //Calculamos la distancia a cada PMT y el numero de fotones detectados en cada PMT para ese punto de centelleo
  for(int j=0;j<entriesPMTs;j++){
    //Cada PMT es una entrada del arbol, tiene 320 entradas:
      treePMTs->GetEntry(j);
       double xpmt=Xpmt->at(j);
       double ypmt=Ypmt->at(j);
       //Me quedo con los PMTs que estan en la parte de x positiva y que son PMT y no arapucas
       if(xpmt==211.465&&ypmt!=0&&ypmt!=130&&ypmt!=-130)
       {

       double zpmt=Zpmt->at(j);
       double chanpmt=numpmt->at(j);
       //cout<<"Canal optico: "<<chanpmt<<endl;


       //cout<<"Posicion: "<<xpmt<<" "<<ypmt<<" "<<zpmt<<endl;
       //distancia del punto de centelleo al centro del PMT
       double distance_cm=sqrt(pow(xscint-xpmt,2)+pow(yscint-ypmt,2)+pow(zscint-zpmt,2));
       //coseno (usando la distancia a la parte de abajo del PMT)
       double coseno= sqrt(pow(xscint-xpmt,2))/distance_cm;
       //angulo theta en grados
       double theta=acos(coseno)*180./3.1416;
      double par0[9] = {0., 0., 0., 0., 0., 0.597542, 1.00872, 1.46993, 2.04221};
      double par1[9] = {0, 0, 0.19569, 0.300449, 0.555598, 0.854939, 1.39166, 2.19141, 2.57732};
      const double delta_theta = 10.;
      int counter = int(theta/delta_theta);
      // 8" PMT radius
      const double b = 8*2.54/2.;
     // distance form which the model parameters break (empirical value)
      const double d_break = 5*b;//par2
////////////

      if(distance_cm >= d_break) {
      double R_apparent_far = b - par1[counter];
      double geo_factor=2*3.1416 * (1 - sqrt(1 - pow(R_apparent_far/distance_cm,2)));
     //Hasta aquí devuelve el geo_factor que es la corrección por ángulo sólido
      //Calculamos el numero de fotones detectados tras la corrección geométrica en un pmt
      // Number of hits by geometric acceptance
      double L_abs=2000; //cm
     //numero de fotones depositados en un PMT por geometria

    double hits_geo = exp(-1.*distance_cm/L_abs)*gRandom->Poisson(phot_gen * geo_factor/(4*3.1416));
    if(hits_geo==0) continue;
   //numero de fotones detectados en ese PMT por simulación
   for(int k=0;k<flash_pe_vuv->size();k++){
     //Ahora el canal optico coincide con la posicion del vector de flashes
     double chanflash=k;

     if(chanflash==chanpmt)
     {

       double hits_flash= flash_pe_vuv->at(k);
       double hits_g4= phot_detected->at(k);

       if(hits_flash==0) continue;
       if(hits_g4==0) continue;

    if((theta>=(angle-10))&&(theta<angle)){
       histerror->Fill((hits_flash-hits_g4)/hits_g4);
       distance.push_back(distance_cm);
       photsreco.push_back(hits_flash);
       e.push_back((hits_flash-hits_g4)/hits_g4);
     }

       cout<<"---------------------------"<<endl;
     //}//if counter
          }
       }//for chanopt
     }
///////////////
    else {
      double R_apparent_close = b - par0[counter];
      double geo_factor=(2*3.1416 * (1 - sqrt(1 - pow(R_apparent_close/distance_cm,2))));
      double L_abs=2000; //cm
      //numero de fotones depositados en un PMT por geometria

      double hits_geo = exp(-1.*distance_cm/L_abs)*gRandom->Poisson(phot_gen * geo_factor/(4*3.1416));
      if(hits_geo==0) continue;
     //numero de fotones detectados en ese PMT por simulación
     for(int k=0;k<flash_pe_vuv->size();k++){

       double chanflash=k;

       if(chanflash==chanpmt)
      {
        double hits_flash= flash_pe_vuv->at(k);
        double hits_g4= phot_detected->at(k);

        if(hits_flash==0) continue;
        if(hits_g4==0) continue;

     if((theta>=(angle-10))&&(theta<angle)){
        histerror->Fill((hits_flash-hits_g4)/hits_g4);
        distance.push_back(distance_cm);
        photsreco.push_back(hits_flash);
        e.push_back((hits_flash-hits_g4)/hits_g4);
      }


        cout<<"---------------------------"<<endl;
      //}//if counter
            }
         }//for chanopt
      }

///////////Añado

         }//if xpmt>0
     }//for numpmt

}//for entriesMichels
c1->cd(1);
TGraph *gdistance = new TGraph (distance.size(),&distance[0],&e[0]);

if(angle==10){ string title= "Angle [0,10] deg";
gdistance->SetTitle(title.c_str());}
if(angle==20){ string title= "Angle [10,20] deg";
gdistance->SetTitle(title.c_str());}
if(angle==30){ string title= "Angle [20,30] deg";
gdistance->SetTitle(title.c_str());}
if(angle==40){ string title= "Angle [30,40] deg";
gdistance->SetTitle(title.c_str());}
if(angle==50){ string title= "Angle [40,50] deg";
gdistance->SetTitle(title.c_str());}
if(angle==60){ string title= "Angle [50,60] deg";
gdistance->SetTitle(title.c_str());}
if(angle==70){ string title= "Angle [60,70] deg";
gdistance->SetTitle(title.c_str());}
if(angle==80){ string title= "Angle [70,80] deg";
gdistance->SetTitle(title.c_str());}
if(angle==90){ string title= "Angle [80,90] deg";
gdistance->SetTitle(title.c_str());}

gdistance->GetXaxis()->SetRangeUser(0,600);
gdistance->GetYaxis()->SetRangeUser(-1,1);
gdistance->SetMarkerStyle(7);
gdistance->GetXaxis()->SetTitle("distance (cm)");
gdistance->GetYaxis()->SetTitle("(N_{RecoVUV}-N_{Lite})/N_{Lite}");
gdistance->Draw("ap");

c1->cd(2);
TGraph *gnphotsreco = new TGraph (photsreco.size(),&photsreco[0],&e[0]);

gnphotsreco->GetXaxis()->SetRangeUser(0,12000);
gnphotsreco->GetYaxis()->SetRangeUser(-1,1);
gnphotsreco->SetMarkerStyle(7);
gnphotsreco->SetTitle("");
gnphotsreco->GetXaxis()->SetTitle("N_{RecoVUV}");
gnphotsreco->GetYaxis()->SetTitle("(N_{RecoVUV}-N_{Lite})/N_{Lite}");
gnphotsreco->Draw("ap");

c1->cd(3);

TGraph *gscatter = new TGraph (photsreco.size(),&distance[0],&photsreco[0]);

gscatter->GetXaxis()->SetRangeUser(0,600);
gscatter->GetYaxis()->SetRangeUser(0,12000);
gscatter->SetMarkerStyle(7);
gscatter->SetTitle("Scatter plot");
gscatter->GetXaxis()->SetTitle("distance (cm)");
gscatter->GetYaxis()->SetTitle("N_{RecoVUV}");
gscatter->Draw("ap");


c1->cd(4);
histerror->Draw();
histerror->SetTitle("Cut 1#sigma");
histerror->GetXaxis()->SetTitle("(N_{RecoVUV}-N_{Lite})/N_{Lite}");
double mean= histerror->GetMean();
double numdeviation=histerror->GetRMS();


double plussigma=mean+numdeviation;
std::string splussigma= ""+std::to_string(plussigma);
double minussigma=mean-numdeviation;
std::string sminussigma= ""+std::to_string(minussigma);

if(angle==10){
histerror->GetYaxis()->SetRangeUser(0,100);
TLine *lcutphotsup=new TLine(plussigma,0,plussigma,100);
 lcutphotsup->SetLineColor(kRed);
 lcutphotsup->Draw();

 TLine *lcutphotslow=new TLine(minussigma,0,minussigma,100);
  lcutphotslow->SetLineColor(kRed);
  lcutphotslow->Draw();

  auto leg = new TLegend(0.1,0.7,0.48,0.9);
  leg->AddEntry(lcutphotsup,splussigma.c_str(),"l");
  leg->AddEntry(lcutphotslow,sminussigma.c_str(),"l");
  leg->Draw();
}

if(angle==20){
histerror->GetYaxis()->SetRangeUser(0,150);
TLine *lcutphotsup=new TLine(plussigma,0,plussigma,150);
 lcutphotsup->SetLineColor(kRed);
 lcutphotsup->Draw();

 TLine *lcutphotslow=new TLine(minussigma,0,minussigma,150);
  lcutphotslow->SetLineColor(kRed);
  lcutphotslow->Draw();

  auto leg = new TLegend(0.1,0.7,0.48,0.9);
  leg->AddEntry(lcutphotsup,splussigma.c_str(),"l");
  leg->AddEntry(lcutphotslow,sminussigma.c_str(),"l");
  leg->Draw();
}




if(angle==30){
histerror->GetYaxis()->SetRangeUser(0,200);
TLine *lcutphotsup=new TLine(plussigma,0,plussigma,200);
 lcutphotsup->SetLineColor(kRed);
 lcutphotsup->Draw();

 TLine *lcutphotslow=new TLine(minussigma,0,minussigma,200);
  lcutphotslow->SetLineColor(kRed);
  lcutphotslow->Draw();

  auto leg = new TLegend(0.1,0.7,0.48,0.9);
  leg->AddEntry(lcutphotsup,splussigma.c_str(),"l");
  leg->AddEntry(lcutphotslow,sminussigma.c_str(),"l");
  leg->Draw();
}

if(angle==40){
histerror->GetYaxis()->SetRangeUser(0,300);
TLine *lcutphotsup=new TLine(plussigma,0,plussigma,300);
 lcutphotsup->SetLineColor(kRed);
 lcutphotsup->Draw();

 TLine *lcutphotslow=new TLine(minussigma,0,minussigma,300);
  lcutphotslow->SetLineColor(kRed);
  lcutphotslow->Draw();

  auto leg = new TLegend(0.1,0.7,0.48,0.9);
  leg->AddEntry(lcutphotsup,splussigma.c_str(),"l");
  leg->AddEntry(lcutphotslow,sminussigma.c_str(),"l");
  leg->Draw();
}

if((angle==50)||(angle==60)||(angle==70)||(angle==80)){
histerror->GetYaxis()->SetRangeUser(0,500);
TLine *lcutphotsup=new TLine(plussigma,0,plussigma,500);
 lcutphotsup->SetLineColor(kRed);
 lcutphotsup->Draw();

 TLine *lcutphotslow=new TLine(minussigma,0,minussigma,500);
  lcutphotslow->SetLineColor(kRed);
  lcutphotslow->Draw();

  auto leg = new TLegend(0.1,0.7,0.48,0.9);
  leg->AddEntry(lcutphotsup,splussigma.c_str(),"l");
  leg->AddEntry(lcutphotslow,sminussigma.c_str(),"l");
  leg->Draw();
}





if(angle==90){
histerror->GetYaxis()->SetRangeUser(0,150);
TLine *lcutphotsup=new TLine(plussigma,0,plussigma,150);
 lcutphotsup->SetLineColor(kRed);
 lcutphotsup->Draw();

 TLine *lcutphotslow=new TLine(minussigma,0,minussigma,150);
  lcutphotslow->SetLineColor(kRed);
  lcutphotslow->Draw();

  auto leg = new TLegend(0.1,0.7,0.48,0.9);
  leg->AddEntry(lcutphotsup,splussigma.c_str(),"l");
  leg->AddEntry(lcutphotslow,sminussigma.c_str(),"l");
  leg->Draw();
}




  }
