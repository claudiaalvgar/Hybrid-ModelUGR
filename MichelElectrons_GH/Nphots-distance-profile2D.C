//Pad 1
//Representa en un profile 2D el error relativo entre fotones VUV lite (g4) y reco (digitalizados) en función del numero de
//fotones detectados (y) y la distancia (x)
//Pad 2
//Cada graph representa un rango de ángulos de 10º y se representan en función del numero de
//fotones detectados (y) y la distancia al PMT (x)


{

  //TCanvas*c1=new TCanvas(); (const char* name, const char* title, Int_t wtopx, Int_t wtopy, Int_t ww, Int_t wh)
  //wtopx,wtopy are the pixel coordinates of the top left corner of
  //the canvas (if wtopx < 0) the menubar is not shown)
  //ww is the canvas size in pixels along X
  //wh is the canvas size in pixels along Y

  auto *c1 = new TCanvas("c1","Title",500,100,1250,450);

  c1->SetGrid();
  gStyle->SetOptStat(0);
  c1->Divide(2,1,0.001,0.001);

//Tprofile(name, title, nx (bines en x),xlow,xup,ny (bines en y),ylow,yup,zlow,zup,option="")
   auto hprof2d  = new TProfile2D("hprof2d","Profile of pz versus px and py",60,0,600,60,-200,22000,-40,40);

   TProfile *hprofx= new TProfile("", "", 60,0,600);
   TProfile *hprofy= new TProfile("", "", 60,-200,22000);

   vector<double> x0, y0, x1, y1, x2, y2,x3, y3,x4, y4,x5, y5,x6, y6,x7, y7,x8, y8;
   x0.clear();
   y0.clear();
   x1.clear();
   y1.clear();
   x2.clear();
   y2.clear();
   x3.clear();
   y3.clear();
   x4.clear();
   y4.clear();
   x5.clear();
   y5.clear();
   x6.clear();
   y6.clear();
   x7.clear();
   y7.clear();
   x8.clear();
   y8.clear();


  TFile *inputMichels= new TFile("analysisOutputVUV_run1-1_subrun1-2.root","read");

  TFile *inputPMTs= new TFile("PMTs.root","read");

  //Leemos la energia depositada en cada step, las posiciones x,y,z y los fotones generados (phot_generated).
  //Leemos flash_pe_vuv: fotones detectados vuv con la digitalizacion y phot_detected son los fotones detectados sin la digitalización (g4)
  vector<double> *E, *phot_generated, *X, *Y, *Z, *flash_pe_vuv, *phot_detected;

//Para los PMTs leemos de un .root el número del canal optico (numpmt) y la posición x,y,z de ese PMT
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
  cout<<"Entradas arbol PMT: "<<entriesPMTs<<endl;

  //Media posicion x
  TH1F*hx=new TH1F("hx", "", 100,-500,500);
  //Media posicion y
  TH1F*hy=new TH1F("hy", "", 100,-500,500);
  //Media posicion z
  TH1F*hz=new TH1F("hz", "", 100,-500,500);

for(int i=0;i<entriesMichels;i++) //numero de particulas que lanzas son las entries (100)
{
  treeMichels->GetEntry(i); //primer electron de Michel


  //cout<<"------Electron numero-----"<<i<<endl;
  //Inicializamos el numero de fotones generados para electron a 0
  double phot_gen=0;
  double Energy=0;

  hx->Reset();
  hy->Reset();
  hz->Reset();
//Fotones detectados a partir de fotones generados
for(int j=0;j<X->size();j++){
//Para ese electron de michel llenamos el histograma con todas sus posiciones x,y,z, pesadas por la energía
//h->Fill(variable,peso=w);
//de las deposiciones de energia y calculamos la media

   hx->Fill(X->at(j),E->at(j));
   //if(i==53){cout<<"x= "<<X->at(j)<<endl;}
   hy->Fill(Y->at(j),E->at(j));
   hz->Fill(Z->at(j),E->at(j));
   phot_gen += phot_generated->at(j);
   Energy += E->at(j);

}
if(phot_gen==0) continue;
  //X de ese electron
  //double xscint=hx->GetMean()/Energy;
  double xscint=hx->GetMean();
  //Y
  //double yscint=hy->GetMean()/Energy;
  double yscint=hy->GetMean();
  //Z
  //double zscint=hz->GetMean()/Energy;
  double zscint=hz->GetMean();
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
       //distancia del punto de centelleo al centro del PMT
       double distance_cm=sqrt(pow(xscint-xpmt,2)+pow(yscint-ypmt,2)+pow(zscint-zpmt,2));
       //coseno (usando la distancia a la parte de abajo del PMT)
       double coseno= sqrt(pow(xscint-xpmt,2))/distance_cm;
       //angulo theta en grados
       double theta=acos(coseno)*180./3.1416;
       //Calculamos el angulo sólido
       /////Añado
       // this function calculates the solid angle of a semi-sphere of radius b,
       // as a correction to the analytic formula of the on-axix solid angle,
       // as we move off-axis an angle theta. We have used 9-angular bins
       // with delta_theta width.
       // par0 = Radius correction close
      // par1 = Radius correction far
      // par2 = breaking distance betwween "close" and "far"
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

       hprof2d->Fill(distance_cm,hits_g4,(hits_flash-hits_g4)/hits_g4,1);
       hprofx->Fill(distance_cm,distance_cm);
       hprofy->Fill(hits_g4,hits_g4);
       //Guardamos los valores para los angulos onaxis y el resto de ángulos
       if((0<=theta)&&(theta<10)){x0.push_back(distance_cm);
                    y0.push_back(hits_g4);}
       if((10<=theta)&&(theta<20)){x1.push_back(distance_cm);
                    y1.push_back(hits_g4);}
       if((20<=theta)&&(theta<30)){x2.push_back(distance_cm);
                    y2.push_back(hits_g4);}
       if((30<=theta)&&(theta<40)){x3.push_back(distance_cm);
                    y3.push_back(hits_g4);}
       if((40<=theta)&&(theta<50)){x4.push_back(distance_cm);
                     y4.push_back(hits_g4);}
       if((50<=theta)&&(theta<60)){x5.push_back(distance_cm);
                     y5.push_back(hits_g4);}
       if((60<=theta)&&(theta<70)){x6.push_back(distance_cm);
                     y6.push_back(hits_g4);}
       if((70<=theta)&&(theta<80)){x7.push_back(distance_cm);
                     y7.push_back(hits_g4);}
       if((80<=theta)&&(theta<90)){x8.push_back(distance_cm);
                     y8.push_back(hits_g4);}


          }
       }//for chanopt
     }
///////////////
    else {
      double R_apparent_close = b - par0[counter];
      double geo_factor=(2*3.1416 * (1 - sqrt(1 - pow(R_apparent_close/distance_cm,2))));
      //Hasta aquí devuelve el geo_factor que es la corrección por ángulo sólido
       //Calculamos el numero de fotones detectados tras la corrección geométrica en un pmt
       // Number of hits by geometric acceptance
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
        hprof2d->Fill(distance_cm,hits_g4,(hits_flash-hits_g4)/hits_g4,1);
        hprofx->Fill(distance_cm,distance_cm);
        hprofy->Fill(hits_g4,hits_g4);

        //Guardamos los valores para los angulos onaxis y el resto de ángulos
        if((0<=theta)&&(theta<10)){x0.push_back(distance_cm);
                     y0.push_back(hits_g4);}
        if((10<=theta)&&(theta<20)){x1.push_back(distance_cm);
                     y1.push_back(hits_g4);}
        if((20<=theta)&&(theta<30)){x2.push_back(distance_cm);
                     y2.push_back(hits_g4);}
        if((30<=theta)&&(theta<40)){x3.push_back(distance_cm);
                     y3.push_back(hits_g4);}
        if((40<=theta)&&(theta<50)){x4.push_back(distance_cm);
                      y4.push_back(hits_g4);}
        if((50<=theta)&&(theta<60)){x5.push_back(distance_cm);
                      y5.push_back(hits_g4);}
        if((60<=theta)&&(theta<70)){x6.push_back(distance_cm);
                      y6.push_back(hits_g4);}
        if((70<=theta)&&(theta<80)){x7.push_back(distance_cm);
                      y7.push_back(hits_g4);}
        if((80<=theta)&&(theta<90)){x8.push_back(distance_cm);
                      y8.push_back(hits_g4);}

            }
         }//for chanopt
      }

///////////Añado

         }//if xpmt>0
     }//for numpmt

}//for entriesMichels

TAxis *xaxis = hprof2d->GetXaxis();
TAxis *yaxis = hprof2d->GetYaxis();
Int_t nbinsx = xaxis->GetNbins();
Int_t nbinsy = yaxis->GetNbins();
cout<<"nbinsx= "<<nbinsx<<endl;
cout<<"nbinsy= "<<nbinsy<<endl;
for (Int_t binx=0; binx <= nbinsx; binx++) {
     for (Int_t biny=0; biny <= nbinsy; biny++) {

    double value = hprof2d->GetBinContent(binx,biny);
    double valuex=hprofx->GetBinContent(binx);
    double valuey=hprofy->GetBinContent(biny);
    //if(value==0) continue;
    cout<<"x= "<<valuex<<" y= "<<valuey<<" Bin value: "<<value<<endl;
  }

  }

c1->cd(1);
hprof2d->Draw("colz");

hprof2d->SetTitle("(N_{RecoVUV}-N_{Lite})/N_{Lite}");
hprof2d->GetXaxis()->SetTitle("distance (cm)");
hprof2d->GetYaxis()->SetTitle("N_{Lite}");


c1->cd(2);
double xx1[2]={0,600};
double yy1[2]={-200,22000};
TGraph *graph1 = new TGraph (2,xx1,yy1);
graph1->GetXaxis()->SetRangeUser(0,600);
graph1->GetYaxis()->SetRangeUser(-200,22000);
graph1->SetTitle("All angles");
graph1->GetXaxis()->SetTitle("distance (cm)");
graph1->GetYaxis()->SetTitle("N_{Lite}");
graph1->Draw("ap");

TGraph* gr0 = new TGraph(x0.size(),&x0[0],&y0[0]);
TGraph* gr1 = new TGraph(x1.size(),&x1[0],&y1[0]);
TGraph* gr2 = new TGraph(x2.size(),&x2[0],&y2[0]);
TGraph* gr3 = new TGraph(x3.size(),&x3[0],&y3[0]);
TGraph* gr4 = new TGraph(x4.size(),&x4[0],&y4[0]);
TGraph* gr5 = new TGraph(x5.size(),&x5[0],&y5[0]);
TGraph* gr6 = new TGraph(x6.size(),&x6[0],&y6[0]);
TGraph* gr7 = new TGraph(x7.size(),&x7[0],&y7[0]);
TGraph* gr8 = new TGraph(x8.size(),&x8[0],&y8[0]);



gr2->Draw("p*");
gr3->Draw("p*");
gr4->Draw("p*");
gr5->Draw("p*");
gr6->Draw("p*");
gr7->Draw("p*");
gr8->Draw("p*");
gr1->Draw("p*");
gr0->Draw("p*");

gr0->SetMarkerColor(1);
gr1->SetMarkerColor(2);
gr2->SetMarkerColor(3);
gr3->SetMarkerColor(4);
gr4->SetMarkerColor(5);
gr5->SetMarkerColor(6);
gr6->SetMarkerColor(7);
gr7->SetMarkerColor(8);
gr8->SetMarkerColor(9);


auto leg = new TLegend(0.1,0.7,0.48,0.9);
leg->AddEntry(gr0,"#theta [0,10] deg","p");
leg->AddEntry(gr1,"#theta [10,20] deg","p");
leg->AddEntry(gr2,"#theta [20,30] deg","p");
leg->AddEntry(gr3,"#theta [30,40] deg","p");
leg->AddEntry(gr4,"#theta [40,50] deg","p");
leg->AddEntry(gr5,"#theta [50,60] deg","p");
leg->AddEntry(gr6,"#theta [60,70] deg","p");
leg->AddEntry(gr7,"#theta [70,80] deg","p");
leg->AddEntry(gr8,"#theta [80,90] deg","p");

leg->Draw();


  }
