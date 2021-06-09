//Programa que calcula la calibración geométrica del modelo semianalítico para SBND
//Se representan las GH teóricas para intervalos de ángulos [0º,10º], [10,20].....[80,90]
//Input: fichero .root con 2000 electrones Michel
//Calcula NfotonesrecoVUV/Nfotonesgeom para cada Michel en función de la distancia del electrón a cada PMT
//la poscion de cada Michel se calcula como la media de las posiciones de las deposiciones de energía para ese electrón
//pesadas por la energía depositada. Las posiciones de los PMT se leen de un .root
//Objetivo: ver si se recuperan las curvas GH, donde NfotonesRecoVUV son los fotones VUV detectados proporcionados
//por la simulación a nivel detsim OpFlash
//y Nfotonesgeom los fotones generados multiplicados por la corrección geométrica (ángulo sólido)

{
//Dibujar Gaisser-hillas
  TF1 *GH[9];
  double p1[9] = {1.20671, 1.15473, 1.06046, 0.970396, 0.818779, 0.634539, 0.407248, 0.237586, 0.124104};
  double p2[9] = {97.7847, 98.8544, 94.9249, 94.3302, 99.622, 92.3059, 130.988, 60.0004, 0.472002};
  double p3[9] = {11.1932, 10.592, 12.0935, 12.5224, 13.9828, 20.427, 43.0715, 224.988, 197.649};
  double p4[9] = {-1500, -1500, -1500, -1500, -1500, -1500, -700, -150, -40};

  //GH 0
  double params0[4]={p1[0],p2[0],p3[0],p4[0]};
  Double_t Diff0=params0[1]-params0[3];

  GH[0] =  new TF1("GH0","[0]*TMath::Exp(([1]-x)/[2])*[3]*pow((x-[4])/[5],[5]/[2])",0.,600.);
  GH[0]->SetParameters(1,params0[1],params0[2],params0[0],params0[3],Diff0);
  //GH 1
  double params1[4]={p1[1],p2[1],p3[1],p4[1]};
  Double_t Diff1=params1[1]-params1[3];

  GH[1] =  new TF1("GH1","[0]*TMath::Exp(([1]-x)/[2])*[3]*pow((x-[4])/[5],[5]/[2])",0.,600.);
  GH[1]->SetParameters(1,params1[1],params1[2],params1[0],params1[3],Diff1);

  //GH 2
  double params2[4]={p1[2],p2[2],p3[2],p4[2]};
  Double_t Diff2=params2[1]-params2[3];

  GH[2] =  new TF1("GH2","[0]*TMath::Exp(([1]-x)/[2])*[3]*pow((x-[4])/[5],[5]/[2])",0.,600.);
  GH[2]->SetParameters(1,params2[1],params2[2],params2[0],params2[3],Diff2);

  //GH 3
  double params3[4]={p1[3],p2[3],p3[3],p4[3]};
  Double_t Diff3=params3[1]-params3[3];

  GH[3] =  new TF1("GH3","[0]*TMath::Exp(([1]-x)/[2])*[3]*pow((x-[4])/[5],[5]/[2])",0.,600.);
  GH[3]->SetParameters(1,params3[1],params3[2],params3[0],params3[3],Diff3);

  //GH 4
  double params4[4]={p1[4],p2[4],p3[4],p4[4]};
  Double_t Diff4=params4[1]-params4[3];

  GH[4] =  new TF1("GH4","[0]*TMath::Exp(([1]-x)/[2])*[3]*pow((x-[4])/[5],[5]/[2])",0.,600.);
  GH[4]->SetParameters(1,params4[1],params4[2],params4[0],params4[3],Diff4);

  //GH 5
  double params5[4]={p1[5],p2[5],p3[5],p4[5]};
  Double_t Diff5=params5[1]-params5[3];

  GH[5] =  new TF1("GH5","[0]*TMath::Exp(([1]-x)/[2])*[3]*pow((x-[4])/[5],[5]/[2])",0.,600.);
  GH[5]->SetParameters(1,params5[1],params5[2],params5[0],params5[3],Diff5);

  //GH 6
  double params6[4]={p1[6],p2[6],p3[6],p4[6]};
  Double_t Diff6=params6[1]-params6[3];

  GH[6] =  new TF1("GH6","[0]*TMath::Exp(([1]-x)/[2])*[3]*pow((x-[4])/[5],[5]/[2])",0.,600.);
  GH[6]->SetParameters(1,params6[1],params6[2],params6[0],params6[3],Diff6);

  //GH 7
  double params7[4]={p1[7],p2[7],p3[7],p4[7]};
  Double_t Diff7=params7[1]-params7[3];

  GH[7] =  new TF1("GH7","[0]*TMath::Exp(([1]-x)/[2])*[3]*pow((x-[4])/[5],[5]/[2])",0.,600.);
  GH[7]->SetParameters(1,params7[1],params7[2],params7[0],params7[3],Diff7);

  //GH 8
  double params8[4]={p1[8],p2[8],p3[8],p4[8]};
  Double_t Diff8=params8[1]-params8[3];

  GH[8] =  new TF1("GH8","[0]*TMath::Exp(([1]-x)/[2])*[3]*pow((x-[4])/[5],[5]/[2])",0.,600.);
  GH[8]->SetParameters(1,params8[1],params8[2],params8[0],params8[3],Diff8);



  //TCanvas*c1=new TCanvas();
  auto c1 = new TCanvas("c1","Title",200,10,700,500);

  //c1->SetGrid();
  //gStyle->SetOptStat(0);


  //Inicializamos el array de 9 profiles
  TProfile *hprof[9];
  TProfile *hprofx[9];
for(int j=0; j<9; j++) {
  hprof[j] = new TProfile("", "", 24,0,600,"");
  hprofx[j] = new TProfile("", "", 24,0,600,"");
}

  TFile *inputMichels= new TFile("analysisOutputVUV_run1-1_subrun1-2.root","read");
  //.root con el número de cada PMT, y la posicion x, y, z
  TFile *inputPMTs= new TFile("PMTs.root","read");


  vector<double> *E, *phot_generated, *X, *Y, *Z, *flash_pe_vuv;
  //vector<int> *chanopt, *chanoptref;

  vector<double> *numpmt, *Xpmt, *Ypmt, *Zpmt;
  //double numpmt, Xpmt, Ypmt, Zpmt;

  TTree* treeMichels=(TTree*)inputMichels->Get("ana/tree");
  TTree* treePMTs=(TTree*)inputPMTs->Get("treepmt");

  treeMichels->SetBranchAddress("E",&E);
  treeMichels->SetBranchAddress("phot_generated",&phot_generated);
  treeMichels->SetBranchAddress("X",&X);
  treeMichels->SetBranchAddress("Y",&Y);
  treeMichels->SetBranchAddress("Z",&Z);
  //treeMichels->SetBranchAddress("phot_detected",&phot_detected);
  //treeMichels->SetBranchAddress("phot_detectedref",&phot_detectedref);
  //Ahora el canal optico coincide con las posiciones del vector flash_pe_v
  treeMichels->SetBranchAddress("flash_pe_vuv",&flash_pe_vuv);
  //treeMichels->SetBranchAddress("chanopt",&chanopt);
  //treeMichels->SetBranchAddress("chanoptref",&chanoptref);

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

for(int i=0;i<entriesMichels;i++) //numero de particulas que lanzas son las entries (2000 MIchels)
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
//Para ese electron de michel llenamos el histograma con todas sus posiciones x,y,z, pesadas por la energía
//h->Fill(variable,peso=w);
//de las deposiciones de energia y calculamos la media

   hx->Fill(X->at(j),E->at(j));
   //if(i==53){cout<<"x= "<<X->at(j)<<endl;}
   hy->Fill(Y->at(j),E->at(j));
   hz->Fill(Z->at(j),E->at(j));
   phot_gen += phot_generated->at(j);
   Energy += E->at(j);

   //cout<<"x= "<<X->at(j)/E->at(j)<<" y= "<<Y->at(j)/E->at(j)<<" z= "<<Z->at(j)/E->at(j)<<endl;
   //cout<<"fotones generados= "<<phot_generated->at(j)<<endl;
}
if(phot_gen==0) continue;
cout<<"fotones generados para el electrón= "<<phot_gen<<endl;


//Esto es para que saque los histogramas de arriba de uno en uno, hay que darle doble click
//para ir cerrándolos

//TCanvas *canvas0 = new TCanvas("canvas0", "graph draw options",200,200,500,400);
//hx->SetTitle("x positions for 1 Michel electron");
//hx->GetXaxis()->SetTitle("x");
//hx->Draw();
//canvas0->Update();
//canvas0->Modified();
//canvas0->WaitPrimitive();


  //X de ese electron
  //double xscint=hx->GetMean()/Energy;
  double xscint=hx->GetMean();
  //Y
  //double yscint=hy->GetMean()/Energy;
  double yscint=hy->GetMean();
  //Z
  //double zscint=hz->GetMean()/Energy;
  double zscint=hz->GetMean();
  cout<<hx->GetRMS()<<" "<<hy->GetRMS()<<" "<<hz->GetRMS()<<endl;
  //Corte para que no tenga en cuenta los electrones que sus posiciones de deposiciones de energía estén
  //separadas más de 5cm
  double MinSpread=7;
  if(hx->GetRMS()>MinSpread||hy->GetRMS()>MinSpread||hz->GetRMS()>MinSpread) continue;
  //cout<<" x media= "<<xscint<<" y= "<<yscint<<" z= "<<zscint<<endl;
  //cout<<"fotones generados totales= "<<phot_gen<<endl;




  //Calculamos la distancia de esa posición del Michel a cada PMT y el numero de fotones detectados en cada PMT para ese punto de centelleo
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
       cout<<"Canal optico: "<<chanpmt<<endl;


       cout<<"Posicion: "<<xpmt<<" "<<ypmt<<" "<<zpmt<<endl;
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
        //indica el rango de ángulos: counter=0 [0,10º], counter=1 [10,20º]...
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
    cout<<"Fotones detectados geom: "<<hits_geo<<endl;
   //numero de fotones detectados en ese PMT por simulación
   for(int k=0;k<flash_pe_vuv->size();k++){
     //Ahora el canal optico coincide con la posicion del vector de flashes
     double chan=k;
     if(chan==chanpmt)
     {
       //cout<<"Canal en el que se han calculado los fot geom: "<<chanpmt<<endl;
       //cout<<"Canal en el que se han calculado los fot sim: "<<chan<<endl;
       double hits_simulation= flash_pe_vuv->at(k);
       cout<<"Fotones detectados sim: "<<hits_simulation<<endl;
       //hprof[counter]->Fill(distance_cm,(hits_simulation/0.03)/hits_geo/cos(theta));
       //if(counter==0){
       cout<<"hits_simulation: "<<hits_simulation<<" hits_geo: "<<hits_geo<<" theta: "<<theta<<" coseno: "<<coseno<<endl;
       //Cortes de calidad para seleccionar los fotones
       if(hits_simulation==0) continue;
       if((counter==0)&&((hits_simulation<23)||(hits_simulation>2000))) continue; //onaxis
       if((counter==0)&&((distance_cm<79)||(distance_cm>218))) continue;

       if((counter==1)&&(hits_simulation>2000)) continue;
       if((counter==1)&&((distance_cm<77)||(distance_cm>225))) continue;

       if((counter==2)&&((hits_simulation<23)||(hits_simulation>2000))) continue;
       if((counter==2)&&((distance_cm<77)||(distance_cm>244))) continue;

       if((counter==3)&&((hits_simulation<20)||(hits_simulation>2000))) continue;
       if((counter==3)&&((distance_cm<78)||(distance_cm>263))) continue;

       if((counter==4)&&(hits_simulation>2000)) continue;
       if((counter==4)&&((distance_cm<71)||(distance_cm>310))) continue;

       if((counter==5)&&(hits_simulation>2000)) continue;
       if((counter==5)&&((distance_cm<64)||(distance_cm>343))) continue;

       if((counter==6)&&(hits_simulation>2000)) continue;
       if((counter==6)&&((distance_cm<51)||(distance_cm>389))) continue;

       if((counter==7)&&(hits_simulation>2000)) continue;
       if((counter==7)&&((distance_cm<50)||(distance_cm>389))) continue;

       if((counter==8)&&(hits_simulation>1000)) continue;
       if((counter==8)&&((distance_cm<111)||(distance_cm>303))) continue;



       hprof[counter]->Fill(distance_cm,(hits_simulation/hits_geo)*coseno);
       hprofx[counter]->Fill(distance_cm,distance_cm);

       cout<<"Distancia: "<<distance_cm<<" hits: "<<(hits_simulation/hits_geo)*coseno<<endl;
       cout<<"histograma: "<<counter<<" theta: "<<theta<<endl;
       cout<<"---------------------------"<<endl;
     //}//if counter
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
      cout<<"Fotones detectados geom: "<<hits_geo<<endl;
     //numero de fotones detectados en ese PMT por simulación
     for(int k=0;k<flash_pe_vuv->size();k++){
      double chan=k;
      if(chan==chanpmt)
      {

        //cout<<"Canal en el que se han calculado los fot geom: "<<chanpmt<<endl;
        //cout<<"Canal en el que se han calculado los fot sim: "<<chan<<endl;
        double hits_simulation= flash_pe_vuv->at(k);
        cout<<"Fotones detectados sim: "<<hits_simulation<<endl;
        //hprof[counter]->Fill(distance_cm,(hits_simulation/0.03)/hits_geo/cos(theta));
        //if(counter==0){
        cout<<"hits_simulation: "<<hits_simulation<<" hits_geo: "<<hits_geo<<" theta: "<<theta<<" coseno: "<<coseno<<endl;
        cout<<"Distancia: "<<distance_cm<<" hits: "<<(hits_simulation/hits_geo)*coseno<<" "<<endl;

        if(hits_simulation==0) continue;
         //Cortes de calidad para seleccionar los fotones
        if((counter==0)&&((hits_simulation<23)||(hits_simulation>2000))) continue; //onaxis
        if((counter==0)&&((distance_cm<79)||(distance_cm>218))) continue;

        if((counter==1)&&(hits_simulation>2000)) continue;
        if((counter==1)&&((distance_cm<77)||(distance_cm>225))) continue;

        if((counter==2)&&((hits_simulation<23)||(hits_simulation>2000))) continue;
        if((counter==2)&&((distance_cm<77)||(distance_cm>244))) continue;

        if((counter==3)&&((hits_simulation<20)||(hits_simulation>2000))) continue;
        if((counter==3)&&((distance_cm<78)||(distance_cm>263))) continue;

        if((counter==4)&&(hits_simulation>2000)) continue;
        if((counter==4)&&((distance_cm<71)||(distance_cm>310))) continue;

        if((counter==5)&&(hits_simulation>2000)) continue;
        if((counter==5)&&((distance_cm<64)||(distance_cm>343))) continue;

        if((counter==6)&&(hits_simulation>2000)) continue;
        if((counter==6)&&((distance_cm<51)||(distance_cm>389))) continue;

       if((counter==7)&&(hits_simulation>2000)) continue;
       if((counter==7)&&((distance_cm<50)||(distance_cm>389))) continue;

       if((counter==8)&&(hits_simulation>1000)) continue;
       if((counter==8)&&((distance_cm<111)||(distance_cm>303))) continue;

        hprof[counter]->Fill(distance_cm,(hits_simulation/hits_geo)*coseno);
        hprofx[counter]->Fill(distance_cm,distance_cm);
        cout<<"histograma: "<<counter<<" theta: "<<theta<<endl;
        cout<<"---------------------------"<<endl;
      //}//if counter
            }
         }//for chanopt
      }

///////////Añado

         }//if xpmt>0
     }//for numpmt

}//for entriesMichels

cut0=1;
cut1=1;
cut2=1;
cut3=1;
cut4=1;
cut5=1;
cut6=1;
cut7=1;
cut8=1;


TGraphErrors *gr[9];


for(int i=0;i<9;i++){
vector<double> vx, vy, vex, vey;
  vx.clear();
  vy.clear();
  vex.clear();
  vey.clear();
TAxis *xaxis = hprof[i]->GetXaxis();
Int_t nbins = xaxis->GetNbins();
cout<<"nbins= "<<nbins<<endl;
for (Int_t bin=0; bin <= nbins; bin++) {

    //Double_t xcenter = xaxis->GetBinCenter(bin);
    Double_t binentries=hprof[i]->GetBinEntries(bin);
    //if(binentries<1) continue;
    //if(binentries<10) continue;
    if((i==0)&&binentries<cut0) continue;
    if((i==1)&&binentries<cut1) continue;
    if((i==2)&&binentries<cut2) continue;
    if((i==3)&&binentries<cut3) continue;
    if((i==4)&&binentries<cut4) continue;
    if((i==5)&&binentries<cut5) continue;
    if((i==6)&&binentries<cut6) continue;
    if((i==7)&&binentries<cut7) continue;
    if((i==8)&&binentries<cut8) continue;

    cout<<"Entradas del bin: "<<binentries<<endl;
    double x_value = hprofx[i]->GetBinContent(bin);
    double y_value = hprof[i]->GetBinContent(bin);
    double x_error = hprofx[i]->GetBinError(bin);
    double y_error = hprof[i]->GetBinError(bin);
   if(y_value == 0) continue;
   //if(y_value > 2) continue;

   cout<<"histograma: "<<i<<" x= "<<x_value<<" y= "<<y_value<<" yerror= "<<y_error<<endl;
    vx.push_back(x_value);
    //vy.push_back(y_value+0.03*y_value);
    vy.push_back(y_value);
    vex.push_back(x_error);
    vey.push_back(y_error);
 }

 gr[i] = new TGraphErrors(vx.size(), &vx[0], &vy[0], 0, &vey[0]);

}



double xx[2]={0,600};
double yy[2]={0,1.5};
TGraph *graph = new TGraph (2,xx,yy);
graph->GetXaxis()->SetRangeUser(0,600);
graph->GetYaxis()->SetRangeUser(0,1.5);
graph->SetTitle("2000 events of Michel electron E=30MeV");
graph->GetXaxis()->SetTitle("distance (cm)");
graph->GetYaxis()->SetTitle("N_{RecoVUV}/N_{#Omega}/cos(#theta)");
graph->Draw("ap");

gr[0]->SetMarkerStyle(21);
gr[0]->SetMarkerColor(1);
gr[0]->GetXaxis()->SetRangeUser(0,600);
gr[0]->GetYaxis()->SetRangeUser(0,1.5);
gr[0]->GetXaxis()->SetTitle("distance (cm)");
gr[0]->GetYaxis()->SetTitle("N_{RecoVUV}/N_{#Omega}/cos(#theta)");
gr[0]->Draw("p");

GH[0]->SetLineColor(1);
GH[0]->SetLineStyle(kDashed);
GH[0]->GetXaxis()->SetRangeUser(0,600);
GH[0]->GetYaxis()->SetRangeUser(0,1.5);
GH[0]->Draw("same");

for(int i=1;i<9;i++)
{
  gr[i]->SetMarkerStyle(21);
  gr[i]->SetMarkerColor(i+1);
  gr[i]->Draw("p");

  GH[i]->SetLineColor(i+1);
  GH[i]->SetLineStyle(kDashed);
  GH[i]->Draw("same");
}

//prueba chicuadrado
//for(int i=0;i<9;i++)
//{
  //TF1 *f1 = new TF1("f1","0",0,10000);
  //double Chi2= gr[i]->Chisquare(GH[i]);
  //cout<<"hist= "<<i<<" Chi2= "<<Chi2<<endl;

//}
///////////////////////////////
//double Chi2[9];

//for(int i=0;i<9;i++)
//{
    //Chi2[i]=0;
//}

//La W es para que no tenga en cuenta las barras de error del
//gr[0]->Fit("GH0","W");
//Chi2[0]= gr[0]->GetFunction("GH0")->GetChisquare();
//cout<<"hist= "<<0<<" Chi2= "<<Chi2[0]<<endl;

//gr[1]->Fit("GH1","W");
//Chi2[1]= gr[1]->GetFunction("GH1")->GetChisquare();
//cout<<"hist= "<<1<<" Chi2= "<<Chi2[1]<<endl;

//gr[2]->Fit("GH2","W");
//Chi2[2]= gr[2]->GetFunction("GH2")->GetChisquare();
//cout<<"hist= "<<2<<" Chi2= "<<Chi2[2]<<endl;

//gr[3]->Fit("GH3","W");
//Chi2[3]= gr[3]->GetFunction("GH3")->GetChisquare();
//cout<<"hist= "<<3<<" Chi2= "<<Chi2[3]<<endl;

//gr[4]->Fit("GH4","W");
//Chi2[4]= gr[4]->GetFunction("GH4")->GetChisquare();
//cout<<"hist= "<<4<<" Chi2= "<<Chi2[4]<<endl;

//gr[5]->Fit("GH5","W");
//Chi2[5]= gr[5]->GetFunction("GH5")->GetChisquare();
//cout<<"hist= "<<5<<" Chi2= "<<Chi2[5]<<endl;

//gr[6]->Fit("GH6","W");
//Chi2[6]= gr[6]->GetFunction("GH6")->GetChisquare();
//cout<<"hist= "<<6<<" Chi2= "<<Chi2[6]<<endl;

//gr[7]->Fit("GH7","W");
//Chi2[7]= gr[7]->GetFunction("GH7")->GetChisquare();
//cout<<"hist= "<<7<<" Chi2= "<<Chi2[7]<<endl;

//gr[8]->Fit("GH8","W");
//Chi2[8]= gr[8]->GetFunction("GH8")->GetChisquare();
//cout<<"hist= "<<8<<" Chi2= "<<Chi2[8]<<endl;

//leyenda
auto leg = new TLegend(0.1,0.7,0.48,0.9);
//"lep" para que salga el punto y la linea
//"l" la linea
//"p" el punto
  leg->AddEntry(gr[0],"#theta [0,10] deg","p");
  leg->AddEntry(gr[1],"#theta [10,20] deg","p");
  leg->AddEntry(gr[2],"#theta [20,30] deg","p");
  leg->AddEntry(gr[3],"#theta [30,40] deg","p");
  leg->AddEntry(gr[4],"#theta [40,50] deg","p");
  leg->AddEntry(gr[5],"#theta [50,60] deg","p");
  leg->AddEntry(gr[6],"#theta [60,70] deg","p");
  leg->AddEntry(gr[7],"#theta [70,80] deg","p");
  leg->AddEntry(gr[8],"#theta [80,90] deg","p");


leg->Draw();

  }
