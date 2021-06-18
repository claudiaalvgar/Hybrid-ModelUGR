//Cortes en distancias (pad1) y numero de fotones (pad2) si el error relativo entre fotones Lite y fotones reconstruidos con el flash
//((hits_flash-hits_g4)/hits_g4) es mayor del 5% sobre el bias
//lo hace para cada rango de ángulos a través de la variable "angle"
//además representa la reconstrucción en las GH para fotones VUV lite (pad3) y fotones VUV reco (pad4)

{
//Dibujar Gaisser-hillas
  TF1 *GH[9];
  double p1[9] = {1.20671, 1.15473, 1.06046, 0.970396, 0.818779, 0.634539, 0.407248, 0.237586, 0.124104};
  double p2[9] = {97.7847, 98.8544, 94.9249, 94.3302, 99.622, 92.3059, 130.988, 60.0004, 0.472002};
  double p3[9] = {11.1932, 10.592, 12.0935, 12.5224, 13.9828, 20.427, 43.0715, 224.988, 197.649};
  double p4[9] = {-1500, -1500, -1500, -1500, -1500, -1500, -700, -150, -40};

  //GH 0
  double params0[4]={p1[0],p2[0],p3[0],p4[0]};
  //Double_t X_mu_0=params0[3];
  //cout<<X_mu_0<<endl;
  //Double_t Normalization=params0[0];
  //cout<<Normalization<<endl;
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




  //TF1*prueba = new TF1("prueba","1.206271*pow((x+1500)/1597.7847,142.74)*TMath::Exp((97.7847-x)/11.1932)",0.,600.);



  //TCanvas*c1=new TCanvas();
  auto *c1 = new TCanvas("c1","Title",200,10,700,500);

  c1->SetGrid();
  gStyle->SetOptStat(0);
  c1->Divide(2,2,0.001,0.001);

//Cambiar este parámetro para ajustar: Rango de angulos para el que se hace el estudio 10-(0,10) 20-(10,20) 30-(20,30) 40-(30,40) 50-(40,50) 60-(50,60) 70-(60,70),80-(70,80), 90-(80,90)
  int angle=90;

  //Inicializamos el array de 9 profiles

TProfile *hprof1 = new TProfile("", "", 60,0,400,"");
TProfile *hprofx1 = new TProfile("", "", 60,0,400,"");


TProfile *hprof2= new TProfile("", "", 60,0,4000,"");
TProfile *hprofx2 = new TProfile("", "", 60,0,4000,"");


TProfile *hprof3= new TProfile("", "", 60,0,600,"");
TProfile *hprofx3 = new TProfile("", "", 60,0,600,"");


TProfile *hprof4= new TProfile("", "", 60,0,600,"");
TProfile *hprofx4= new TProfile("", "", 60,0,600,"");


  //Leemos la informacion de la simulacion y de los PMTs
  //1000 eventos para electrones de 1 MeV y distribución plana
  //TFile *inputMichels= new TFile("output_1000_1MeV_flat_semi.root","read");
  //5000 eventos para electrones de 30MeV y distribución gaussiana
  //TFile *inputMichels= new TFile("output_5000_30MeV_gaus_semi.root","read");
  //10000 eventos para electrones de 30MeV y distribución gaussiana
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


  int entriesMichels=treeMichels->GetEntries(); //2000
  //Cada PMT es una entrada
  int entriesPMTs=treePMTs->GetEntries(); //320
  cout<<"Entradas arbol PMT: "<<entriesPMTs<<endl;

  //Media posicion x
  TH1F*hx=new TH1F("hx", "", 100,-500,500);
  //Media posicion y
  TH1F*hy=new TH1F("hy", "", 100,-500,500);
  //Media posicion z
  TH1F*hz=new TH1F("hz", "", 100,-500,500);


for(int i=0;i<entriesMichels;i++) //numero de particulas que lanzas son las entries (2000 electrones de Michel)
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
   hy->Fill(Y->at(j),E->at(j));
   hz->Fill(Z->at(j),E->at(j));
   phot_gen += phot_generated->at(j);
   Energy += E->at(j);
}
//Si no se generan fotones continua
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
  double xscint=hx->GetMean();
  //Y
  double yscint=hy->GetMean();
  //Z
  double zscint=hz->GetMean();
  cout<<hx->GetRMS()<<" "<<hy->GetRMS()<<" "<<hz->GetRMS()<<endl;
  //Corte para que no tenga en cuenta los electrones que sus posiciones de deposiciones de energía estén
  //separadas más de 7cm
  double MinSpread=7;
  if(hx->GetRMS()>MinSpread||hy->GetRMS()>MinSpread||hz->GetRMS()>MinSpread) continue;
  //cout<<" x media= "<<xscint<<" y= "<<yscint<<" z= "<<zscint<<endl;
  //cout<<"fotones generados totales= "<<phot_gen<<endl;




  //Calculamos la distancia a cada PMT y el numero de fotones detectados en cada PMT para ese punto de centelleo
  for(int j=0;j<entriesPMTs;j++){
    //Cada PMT es una entrada del arbol, tiene 320 entradas:
    treePMTs->GetEntry(j);
    //Sacamos la x e y del PMT
       double xpmt=Xpmt->at(j);
       double ypmt=Ypmt->at(j);
       //Me quedo con los PMTs que estan en la parte de x positiva y que son PMTs y no arapucas
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
      int counter = int(theta/delta_theta);
      // 8" PMT radius
      const double b = 8*2.54/2.;
     // distance form which the model parameters break (empirical value)
      const double d_break = 5*b;//par2
////////////

      if(distance_cm >= d_break) {
      double R_apparent_far = b - par1[counter];
      double geo_factor=2*3.1416 * (1 - sqrt(1 - pow(R_apparent_far/distance_cm,2)));
     //Hasta aquí devuelve el geo_factor
      //Calculamos el numero de fotones detectados tras la corrección geométrica en un pmt
      // Number of hits by geometric acceptance
      double L_abs=2000; //cm
     //numero de fotones depositados en un PMT con la geometria (ángulo solido)
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

       cout<<"histograma: "<<counter<<" theta: "<<theta<<" dist: "<<distance_cm<<" Hitsg4: "<<hits_g4<<endl;
       cout<<"Error: "<<(hits_flash-hits_g4)/hits_g4<<endl;

       //Lleno los histogramas para el rango de ángulos que hemos elegido
       if((theta>=(angle-10))&&(theta<angle)){
       //En funcion de la distancia
       hprof1->Fill(distance_cm,(hits_flash-hits_g4)/hits_g4);
       hprofx1->Fill(distance_cm,distance_cm);
       //En funcion del numero de fotones G4
       hprof2->Fill(hits_flash,(hits_flash-hits_g4)/hits_g4);
       hprofx2->Fill(hits_flash,hits_flash);

       //Gaisser Hillas reco
       hprof3->Fill(distance_cm,(hits_flash/hits_geo)*coseno);
       hprofx3->Fill(distance_cm,distance_cm);

       //gaisser hillas g4
       hprof4->Fill(distance_cm,(hits_g4/hits_geo)*coseno);
       hprofx4->Fill(distance_cm,distance_cm);
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

        cout<<"histograma: "<<counter<<" theta: "<<theta<<" dist: "<<distance_cm<<" Hitsg4: "<<hits_g4<<endl;
        cout<<"Error: "<<(hits_flash-hits_g4)/hits_g4<<endl;

        if((theta>=(angle-10))&&(theta<angle)){
        //En funcion de la distancia
        hprof1->Fill(distance_cm,(hits_flash-hits_g4)/hits_g4);
        hprofx1->Fill(distance_cm,distance_cm);
        //En funcion del numero de fotones G4
        hprof2->Fill(hits_flash,(hits_flash-hits_g4)/hits_g4);
        hprofx2->Fill(hits_flash,hits_g4);

        //Gaisser Hillas reco vuv
        hprof3->Fill(distance_cm,(hits_flash/hits_geo)*coseno);
        hprofx3->Fill(distance_cm,distance_cm);

        //gaisser hillas g4
        hprof4->Fill(distance_cm,(hits_g4/hits_geo)*coseno);
        hprofx4->Fill(distance_cm,distance_cm);
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
//En funcion de la distancia
TGraphErrors *gr1;
//En funcion de Ng4
TGraphErrors *gr2;
//Gaisser Hillas reco vuv
TGraphErrors *gr3;
//Gaisser Hillas  g4 vuv
TGraphErrors *gr4;

//double cut0=5;
//double cut1=20;
//double cutrest=50;

double mean[9]={-0.02987,-0.02901,-0.02702,-0.026,-0.02393,-0.02161,-0.02205,-0.02257,-0.0191};


//En funcion de la distancia
//incializo
double nphotsup1[1], nphotslow1[1];
nphotsup1[0]=1000000;
nphotslow1[0]=10;


//En funcion de la distancia
vector<double> vx1, vy1, vex1, vey1;
  vx1.clear();
  vy1.clear();
  vex1.clear();
  vey1.clear();




TAxis *xaxis1 = hprof1->GetXaxis();
Int_t nbins1 = xaxis1->GetNbins();
for (Int_t bin=0; bin <= nbins1; bin++) {

    //Double_t xcenter = xaxis->GetBinCenter(bin);
    Double_t binentries=hprof1->GetBinEntries(bin);
    if(binentries<1) continue;

    //if(angle==10&&binentries<cut0) continue;
    //if(angle==20&&binentries<cut1) continue;
    //if(angle!=10&&angle!=20&&binentries<cutrest) continue;

    double x_value = hprofx1->GetBinContent(bin);
    double y_value = hprof1->GetBinContent(bin);
    double x_error = hprofx1->GetBinError(bin);
    double y_error = hprof1->GetBinError(bin);
    cout<<"theta: "<<angle<<" binentries "<<binentries<<" Distance: "<<x_value<<" error "<<y_value<<endl;
   if(y_value == 0) continue;


    vx1.push_back(x_value);
    vy1.push_back(y_value);
    vex1.push_back(x_error);
    vey1.push_back(y_error);



    ///////////////////
    //Para cada set de ángulos:
      if(angle==10){double error[2]={mean[0]-0.05,mean[0]+0.05};
        //si el error es mayor del 5%
      if(x_value>150&&(y_value<error[0]||y_value>error[1])){
        double photsup=x_value;

        //Corto en la distancia máxima
        if(photsup<nphotsup1[0]){
          nphotsup1[0]=photsup;
        }
        cout<<"Distance up: "<<nphotsup1[0]<<endl;}

        if(x_value<150&&(y_value<error[0]||y_value>error[1])){
          double photslow=x_value;

          //Corto en la distancia minima
          if(photslow>nphotslow1[0]){
            nphotslow1[0]=photslow;
          }
          cout<<"Distance low: "<<nphotslow1[0]<<endl;}
        }


        if(angle==20){double error[2]={mean[1]-0.05,mean[1]+0.05};
        //si el error es mayor del 5%
      if(x_value>150&&(y_value<error[0]||y_value>error[1])){
        double photsup=x_value;


        if(photsup<nphotsup1[0]){
          nphotsup1[0]=photsup;
        }
        cout<<"Distance up: "<<nphotsup1[0]<<endl;}

        if(x_value<150&&(y_value<error[0]||y_value>error[1])){
          double photslow=x_value;


          if(photslow>nphotslow1[0]){
            nphotslow1[0]=photslow;
          }
          cout<<"Distance low: "<<nphotslow1[0]<<endl;}
        }
        if(angle==30){double error[2]={mean[2]-0.05,mean[2]+0.05};
        //si el error es mayor del 5%
      if(x_value>150&&(y_value<error[0]||y_value>error[1])){
        double photsup=x_value;


        if(photsup<nphotsup1[0]){
          nphotsup1[0]=photsup;
        }
        cout<<"Distance up: "<<nphotsup1[0]<<endl;}

        if(x_value<150&&(y_value<error[0]||y_value>error[1])){
          double photslow=x_value;


          if(photslow>nphotslow1[0]){
            nphotslow1[0]=photslow;
          }
          cout<<"Distance low: "<<nphotslow1[0]<<endl;}
        }
        if(angle==40){double error[2]={mean[3]-0.05,mean[3]+0.05};
          //si el error es mayor del 5%
        if(x_value>150&&(y_value<error[0]||y_value>error[1])){
          double photsup=x_value;


          if(photsup<nphotsup1[0]){
            nphotsup1[0]=photsup;
          }
          cout<<"Distance up: "<<nphotsup1[0]<<endl;}

          if(x_value<150&&(y_value<error[0]||y_value>error[1])){
            double photslow=x_value;


            if(photslow>nphotslow1[0]){
              nphotslow1[0]=photslow;
            }
            cout<<"Distance low: "<<nphotslow1[0]<<endl;}
          }
        if(angle==50){double error[2]={mean[4]-0.05,mean[4]+0.05};
        //si el error es mayor del 5%
      if(x_value>150&&(y_value<error[0]||y_value>error[1])){
        double photsup=x_value;


        if(photsup<nphotsup1[0]){
          nphotsup1[0]=photsup;
        }
        cout<<"Distance up: "<<nphotsup1[0]<<endl;}

        if(x_value<150&&(y_value<error[0]||y_value>error[1])){
          double photslow=x_value;


          if(photslow>nphotslow1[0]){
            nphotslow1[0]=photslow;
          }
          cout<<"Distance low: "<<nphotslow1[0]<<endl;}
        }
        if(angle==60){double error[2]={mean[5]-0.05,mean[5]+0.05};
        //si el error es mayor del 5%
      if(x_value>150&&(y_value<error[0]||y_value>error[1])){
        double photsup=x_value;


        if(photsup<nphotsup1[0]){
          nphotsup1[0]=photsup;
        }
        cout<<"Distance up: "<<nphotsup1[0]<<endl;}

        if(x_value<150&&(y_value<error[0]||y_value>error[1])){
          double photslow=x_value;


          if(photslow>nphotslow1[0]){
            nphotslow1[0]=photslow;
          }
          cout<<"Distance low: "<<nphotslow1[0]<<endl;}
        }
        if(angle==70){double error[2]={mean[6]-0.05,mean[6]+0.05};
        //si el error es mayor del 5%
      if(x_value>150&&(y_value<error[0]||y_value>error[1])){
        double photsup=x_value;


        if(photsup<nphotsup1[0]){
          nphotsup1[0]=photsup;
        }
        cout<<"Distance up: "<<nphotsup1[0]<<endl;}

        if(x_value<150&&(y_value<error[0]||y_value>error[1])){
          double photslow=x_value;


          if(photslow>nphotslow1[0]){
            nphotslow1[0]=photslow;
          }
          cout<<"Distance low: "<<nphotslow1[0]<<endl;}
        }
        if(angle==80){double error[2]={mean[7]-0.05,mean[7]+0.05};
        //si el error es mayor del 5%
      if(x_value>150&&(y_value<error[0]||y_value>error[1])){
        double photsup=x_value;


        if(photsup<nphotsup1[0]){
          nphotsup1[0]=photsup;
        }
        cout<<"Distance up: "<<nphotsup1[0]<<endl;}

        if(x_value<150&&(y_value<error[0]||y_value>error[1])){
          double photslow=x_value;


          if(photslow>nphotslow1[0]){
            nphotslow1[0]=photslow;
          }
          cout<<"Distance low: "<<nphotslow1[0]<<endl;}
        }
        if(angle==90){double error[2]={mean[8]-0.05,mean[8]+0.05};
        //si el error es mayor del 5%
      if(x_value>150&&(y_value<error[0]||y_value>error[1])){
        double photsup=x_value;


        if(photsup<nphotsup1[0]){
          nphotsup1[0]=photsup;
        }
        cout<<"Distance up: "<<nphotsup1[0]<<endl;}

        if(x_value<150&&(y_value<error[0]||y_value>error[1])){
          double photslow=x_value;


          if(photslow>nphotslow1[0]){
            nphotslow1[0]=photslow;
          }
          cout<<"Distance low: "<<nphotslow1[0]<<endl;}
        }



 }


cout<<"-----------------------------------------"<<endl;
 gr1 = new TGraphErrors(vx1.size(), &vx1[0], &vy1[0], 0, &vey1[0]);


//Graficamos (hits_flash-hits_g4)/hits_g4 en funcion de la distancia
c1->cd(1);

double xx1[2]={0,400};
double yy1[2]={-1,0.8};
TGraph *graph1 = new TGraph (2,xx1,yy1);
graph1->GetXaxis()->SetRangeUser(0,400);
graph1->GetYaxis()->SetRangeUser(-1,0.8);
graph1->SetTitle("2000 events of Michel electron E=30MeV");
graph1->GetXaxis()->SetTitle("distance (cm)");
graph1->GetYaxis()->SetTitle("(N_{RecoVUV}-N_{Lite})/N_{Lite}");
graph1->Draw("ap");


  gr1->SetMarkerStyle(21);
  gr1->GetXaxis()->SetRangeUser(0,400);
  gr1->GetYaxis()->SetRangeUser(-1,0.8);
  gr1->GetYaxis()->SetTitle("(N_{RecoVUV}-N_{Lite})/N_{Lite}");
  if(angle==10){gr1->SetMarkerColor(1);}
  if(angle==20){gr1->SetMarkerColor(2);}
  if(angle==30){gr1->SetMarkerColor(3);}
  if(angle==40){gr1->SetMarkerColor(4);}
  if(angle==50){gr1->SetMarkerColor(kOrange-3);}
  if(angle==60){gr1->SetMarkerColor(6);}
  if(angle==70){gr1->SetMarkerColor(7);}
  if(angle==80){gr1->SetMarkerColor(8);}
  if(angle==90){gr1->SetMarkerColor(9);}


gr1->Draw("p");
TLine *lnoerror1=new TLine(0 ,mean[8],400 ,mean[8]);
 lnoerror1->SetLineColor(kBlue);
 lnoerror1->Draw();

  TLine *lcutphotsup1=new TLine(nphotsup1[0] ,-1,nphotsup1[0] ,0.8);
   lcutphotsup1->SetLineColor(kRed);
   lcutphotsup1->Draw();
 std::string up1= ""+std::to_string(nphotsup1[0])+ " cm";
   TLine *lcutphotslow1=new TLine(nphotslow1[0] ,-1,nphotslow1[0] ,0.8);
    lcutphotslow1->SetLineColor(kRed);
   lcutphotslow1->Draw();
 std::string low1= ""+std::to_string(nphotslow1[0])+ " cm";

    auto leg1 = new TLegend(0.1,0.7,0.48,0.9);
    leg1->AddEntry(lcutphotsup1,up1.c_str(),"l");
    leg1->AddEntry(lcutphotslow1,low1.c_str(),"l");
    leg1->Draw();


/////////////////////////////////////////////////////////////////////////////
//En funcion del numero de fotones
//incializo
double nphotsup2[1], nphotslow2[1];
nphotsup2[0]=1000000;
nphotslow2[0]=10;


vector<double> vx2, vy2, vex2, vey2;
//Numero total de fotones detectados en la muestra
double nphotstot2=0;
//Numero de fotones que cortamos en las detecciones
double nphotscut2=0;

  vx2.clear();
  vy2.clear();
  vex2.clear();
  vey2.clear();

TAxis *xaxis2 = hprof2->GetXaxis();
Int_t nbins2 = xaxis2->GetNbins();

for (Int_t bin=0; bin <= nbins2; bin++) {

    //Double_t xcenter = xaxis->GetBinCenter(bin);
    Double_t binentries=hprof2->GetBinEntries(bin);
    if(binentries<1) continue;
    //if(angle==10&&binentries<cut0) continue;
    //if(angle==20&&binentries<cut1) continue;
    //if(angle!=10&&angle!=20&&binentries<cutrest) continue;
    double x_value = hprofx2->GetBinContent(bin);
    double y_value = hprof2->GetBinContent(bin);
    double x_error = hprofx2->GetBinError(bin);
    double y_error = hprof2->GetBinError(bin);
    cout<<"theta: "<<angle<<" binentries "<<binentries<<" Nphots: "<<x_value<<" error "<<y_value<<endl;

   if(y_value == 0) continue;

   nphotstot2+= x_value;

    vx2.push_back(x_value);
    vy2.push_back(y_value);
    vex2.push_back(x_error);
    vey2.push_back(y_error);

///////////////////
    if(angle==10){double error[2]={mean[0]-0.05,mean[0]+0.05};
    //si el error es mayor del 5%
  if(x_value>1000&&(y_value<error[0]||y_value>error[1])){
    double photsup=x_value;
    nphotscut2+= x_value;
    //Corto en el numero más grande de fotones
    if(photsup<nphotsup2[0]){
      nphotsup2[0]=photsup;
    }
    cout<<"N phots up: "<<nphotsup2[0]<<endl;}

    if(x_value<1000&&(y_value<error[0]||y_value>error[1])){
      double photslow=x_value;
      nphotscut2+= x_value;
      //Corto en el numero más pequeño de fotones
      if(photslow>nphotslow2[0]){
        nphotslow2[0]=photslow;
      }
      cout<<"N phots low: "<<nphotslow2[0]<<endl;}
    }


    if(angle==20){double error[2]={mean[1]-0.05,mean[1]+0.05};
    //si el error es mayor del 5%
  if(x_value>1000&&(y_value<error[0]||y_value>error[1])){
    double photsup=x_value;
    nphotscut2+= x_value;
    //Corto en el numero más grande de fotones
    if(photsup<nphotsup2[0]){
      nphotsup2[0]=photsup;
    }
    cout<<"N phots up: "<<nphotsup2[0]<<endl;}

    if(x_value<1000&&(y_value<error[0]||y_value>error[1])){
      double photslow=x_value;
      nphotscut2+= x_value;
      //Corto en el numero más pequeño de fotones
      if(photslow>nphotslow2[0]){
        nphotslow2[0]=photslow;
      }
      cout<<"N phots low: "<<nphotslow2[0]<<endl;}
    }
    if(angle==30){double error[2]={mean[2]-0.05,mean[2]+0.05};
    //si el error es mayor del 5%
  if(x_value>1000&&(y_value<error[0]||y_value>error[1])){
    double photsup=x_value;
    nphotscut2+= x_value;
    //Corto en el numero más grande de fotones
    if(photsup<nphotsup2[0]){
      nphotsup2[0]=photsup;
    }
    cout<<"N phots up: "<<nphotsup2[0]<<endl;}

    if(x_value<1000&&(y_value<error[0]||y_value>error[1])){
      double photslow=x_value;
      nphotscut2+= x_value;
      //Corto en el numero más pequeño de fotones
      if(photslow>nphotslow2[0]){
        nphotslow2[0]=photslow;
      }
      cout<<"N phots low: "<<nphotslow2[0]<<endl;}
    }
    if(angle==40){double error[2]={mean[3]-0.05,mean[3]+0.05};
      //si el error es mayor del 5%
    if(x_value>1000&&(y_value<error[0]||y_value>error[1])){
      double photsup=x_value;
      nphotscut2+= x_value;
      //Corto en el numero más grande de fotones
      if(photsup<nphotsup2[0]){
        nphotsup2[0]=photsup;
      }
      cout<<"N phots up: "<<nphotsup2[0]<<endl;}

      if(x_value<1000&&(y_value<error[0]||y_value>error[1])){
        double photslow=x_value;
        nphotscut2+= x_value;
        //Corto en el numero más pequeño de fotones
        if(photslow>nphotslow2[0]){
          nphotslow2[0]=photslow;
        }
        cout<<"N phots low: "<<nphotslow2[0]<<endl;}
      }
    if(angle==50){double error[2]={mean[4]-0.05,mean[4]+0.05};
    //si el error es mayor del 5%
  if(x_value>1000&&(y_value<error[0]||y_value>error[1])){
    double photsup=x_value;
    nphotscut2+= x_value;
    //Corto en el numero más grande de fotones
    if(photsup<nphotsup2[0]){
      nphotsup2[0]=photsup;
    }
    cout<<"N phots up: "<<nphotsup2[0]<<endl;}

    if(x_value<1000&&(y_value<error[0]||y_value>error[1])){
      double photslow=x_value;
      nphotscut2+= x_value;
      //Corto en el numero más pequeño de fotones
      if(photslow>nphotslow2[0]){
        nphotslow2[0]=photslow;
      }
      cout<<"N phots low: "<<nphotslow2[0]<<endl;}
    }
    if(angle==60){double error[2]={mean[5]-0.05,mean[5]+0.05};
    //si el error es mayor del 5%
  if(x_value>1000&&(y_value<error[0]||y_value>error[1])){
    double photsup=x_value;
    nphotscut2+= x_value;
    //Corto en el numero más grande de fotones
    if(photsup<nphotsup2[0]){
      nphotsup2[0]=photsup;
    }
    cout<<"N phots up: "<<nphotsup2[0]<<endl;}

    if(x_value<1000&&(y_value<error[0]||y_value>error[1])){
      double photslow=x_value;
      nphotscut2+= x_value;
      //Corto en el numero más pequeño de fotones
      if(photslow>nphotslow2[0]){
        nphotslow2[0]=photslow;
      }
      cout<<"N phots low: "<<nphotslow2[0]<<endl;}
    }
    if(angle==70){double error[2]={mean[6]-0.05,mean[6]+0.05};
    //si el error es mayor del 5%
  if(x_value>1000&&(y_value<error[0]||y_value>error[1])){
    double photsup=x_value;
    nphotscut2+= x_value;
    //Corto en el numero más grande de fotones
    if(photsup<nphotsup2[0]){
      nphotsup2[0]=photsup;
    }
    cout<<"N phots up: "<<nphotsup2[0]<<endl;}

    if(x_value<1000&&(y_value<error[0]||y_value>error[1])){
      double photslow=x_value;
      nphotscut2+= x_value;
      //Corto en el numero más pequeño de fotones
      if(photslow>nphotslow2[0]){
        nphotslow2[0]=photslow;
      }
      cout<<"N phots low: "<<nphotslow2[0]<<endl;}
    }
    if(angle==80){double error[2]={mean[7]-0.05,mean[7]+0.05};
    //si el error es mayor del 5%
  if(x_value>1000&&(y_value<error[0]||y_value>error[1])){
    double photsup=x_value;
    nphotscut2+= x_value;
    //Corto en el numero más grande de fotones
    if(photsup<nphotsup2[0]){
      nphotsup2[0]=photsup;
    }
    cout<<"N phots up: "<<nphotsup2[0]<<endl;}

    if(x_value<1000&&(y_value<error[0]||y_value>error[1])){
      double photslow=x_value;
      nphotscut2+= x_value;
      //Corto en el numero más pequeño de fotones
      if(photslow>nphotslow2[0]){
        nphotslow2[0]=photslow;
      }
      cout<<"N phots low: "<<nphotslow2[0]<<endl;}
    }
    if(angle==90){double error[2]={mean[8]-0.05,mean[8]+0.05};
    //si el error es mayor del 5%
  if(x_value>1000&&(y_value<error[0]||y_value>error[1])){
    double photsup=x_value;
    nphotscut2+= x_value;
    //Corto en el numero más grande de fotones
    if(photsup<nphotsup2[0]){
      nphotsup2[0]=photsup;
    }
    cout<<"N phots up: "<<nphotsup2[0]<<endl;}

    if(x_value<1000&&(y_value<error[0]||y_value>error[1])){
      double photslow=x_value;
      nphotscut2+= x_value;
      //Corto en el numero más pequeño de fotones
      if(photslow>nphotslow2[0]){
        nphotslow2[0]=photslow;
      }
      cout<<"N phots low: "<<nphotslow2[0]<<endl;}
    }


 }
cout<<"Fotones totales: "<<nphotstot2<<" Fotones que cortamos (tienen mas de 5% de error): "<<nphotscut2<<endl;
 cout<<"-----------------------------------------"<<endl;

 gr2 = new TGraphErrors(vx2.size(), &vx2[0], &vy2[0], 0, &vey2[0]);




//for(int i=0;i<9;i++)
//{
  //TF1 *f1 = new TF1("f1","0",0,10000);
  //double Chi2= gr2[i]->Chisquare(f1);
  //cout<<"Chi2= "<<Chi2<<endl;

//}
//Graficamos (hits_flash-hits_g4)/hits_g4 en funcion del numero de fotones G4
c1->cd(2);

double xx2[2]={0,4000};
double yy2[2]={-1,0.8};
TGraph *graph2 = new TGraph (2,xx2,yy2);
graph2->GetXaxis()->SetRangeUser(0,4000);
graph2->GetYaxis()->SetRangeUser(-1,0.8);
graph2->SetTitle("2000 events of Michel electron E=30MeV");
graph2->GetXaxis()->SetTitle("N_{RecoVUV}");
graph2->GetYaxis()->SetTitle("(N_{RecoVUV}-N_{Lite})/N_{Lite}");
graph2->Draw("ap");


  gr2->GetXaxis()->SetRangeUser(0,4000);
  gr2->GetYaxis()->SetRangeUser(-1,0.8);
  gr2->GetXaxis()->SetTitle("N_{RecoVUV}");
  gr2->GetYaxis()->SetTitle("(N_{RecoVUV}-N_{Lite})/N_{Lite}");
  gr2->SetMarkerStyle(21);
  if(angle==10){gr2->SetMarkerColor(1);}
  if(angle==20){gr2->SetMarkerColor(2);}
  if(angle==30){gr2->SetMarkerColor(3);}
  if(angle==40){gr2->SetMarkerColor(4);}
  if(angle==50){gr2->SetMarkerColor(kOrange-3);}
  if(angle==60){gr2->SetMarkerColor(6);}
  if(angle==70){gr2->SetMarkerColor(7);}
  if(angle==80){gr2->SetMarkerColor(8);}
  if(angle==90){gr2->SetMarkerColor(9);}
  gr2->Draw("p");


TLine *lnoerror2=new TLine(0 ,mean[8],4000 ,mean[8]);
 lnoerror2->SetLineColor(kBlue);
 lnoerror2->Draw();

 TLine *lcutphotsup2=new TLine(nphotsup2[0] ,-1,nphotsup2[0] ,0.8);
  lcutphotsup2->SetLineColor(kRed);
  lcutphotsup2->Draw();
std::string up2= ""+std::to_string(nphotsup2[0])+ " N_{RecoVUV}";
  TLine *lcutphotslow2=new TLine(nphotslow2[0] ,-1,nphotslow2[0] ,0.8);
   lcutphotslow2->SetLineColor(kRed);
  //lcutphotslow2->Draw();
std::string low2= ""+std::to_string(nphotslow2[0])+ " N_{RecoVUV}";

   auto leg2 = new TLegend(0.1,0.7,0.48,0.9);
   leg2->AddEntry(lcutphotsup2,up2.c_str(),"l");
   //leg2->AddEntry(lcutphotslow2,low2.c_str(),"l");
   leg2->Draw();




/////////////////////////////////////////////////////////////////////////////
//GH


vector<double> vx3, vy3, vex3, vey3;
  vx3.clear();
  vy3.clear();
  vex3.clear();
  vey3.clear();
TAxis *xaxis3 = hprof3->GetXaxis();
Int_t nbins3 = xaxis3->GetNbins();
for (Int_t bin=0; bin <= nbins3; bin++) {

    //Double_t xcenter = xaxis->GetBinCenter(bin);
    Double_t binentries=hprof3->GetBinEntries(bin);
    if(binentries<1) continue;
    //if(angle==20&&binentries<cut1) continue;
    //if(angle!=10&&angle!=20&&binentries<cutrest) continue;
    double x_value = hprofx3->GetBinContent(bin);
    double y_value = hprof3->GetBinContent(bin);
    double x_error = hprofx3->GetBinError(bin);
    double y_error = hprof3->GetBinError(bin);
   if(y_value == 0) continue;
    vx3.push_back(x_value);
    vy3.push_back(y_value);
    vex3.push_back(x_error);
    vey3.push_back(y_error);

 }
cout<<"-----------------------------------------"<<endl;
 gr3 = new TGraphErrors(vx3.size(), &vx3[0], &vy3[0], 0, &vey3[0]);


//Graficamos las gaisser hillas con fotones reco vuv
c1->cd(4);

double xx3[2]={0,600};
double yy3[2]={0,1.5};
TGraph *graph3 = new TGraph (2,xx3,yy3);
graph3->GetXaxis()->SetRangeUser(0,600);
graph3->GetYaxis()->SetRangeUser(0,1.5);
graph3->SetTitle("2000 events of Michel electron E=30MeV");
graph3->GetXaxis()->SetTitle("distance (cm)");
graph3->GetYaxis()->SetTitle("N_{RecoVUV}/N_{#Omega}/cos(#theta)");
graph3->Draw("ap");


  gr3->GetXaxis()->SetRangeUser(0,600);
  gr3->GetYaxis()->SetRangeUser(0,1.5);
  gr3->SetMarkerStyle(21);


  if(angle==10){gr3->SetMarkerColor(1);
    int i=0;
    GH[i]->SetLineColor(1);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr3->Draw("p");
    GH[i]->Draw("same");}
  if(angle==20){gr3->SetMarkerColor(2);
      int i=1;
    GH[i]->SetLineColor(2);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr3->Draw("p");
    GH[i]->Draw("same");}
  if(angle==30){gr3->SetMarkerColor(3);
    int i=2;
    GH[i]->SetLineColor(3);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr3->Draw("p");
    GH[i]->Draw("same");}
  if(angle==40){gr3->SetMarkerColor(4);
      int i=3;
    GH[i]->SetLineColor(4);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr3->Draw("p");
    GH[i]->Draw("same");}
  if(angle==50){gr3->SetMarkerColor(kOrange-3);
      int i=4;
    GH[i]->SetLineColor(kOrange-3);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr3->Draw("p");
    GH[i]->Draw("same");}
  if(angle==60){gr3->SetMarkerColor(6);
      int i=5;
    GH[i]->SetLineColor(6);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr3->Draw("p");
    GH[i]->Draw("same");}
  if(angle==70){gr3->SetMarkerColor(7);
      int i=6;
    GH[i]->SetLineColor(7);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr3->Draw("p");
    GH[i]->Draw("same");}
  if(angle==80){gr3->SetMarkerColor(8);
      int i=7;
    GH[i]->SetLineColor(8);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr3->Draw("p");
    GH[i]->Draw("same");}
  if(angle==90){gr3->SetMarkerColor(9);
      int i=8;
    GH[i]->SetLineColor(9);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr3->Draw("p");
    GH[i]->Draw("same");}





auto leg3 = new TLegend(0.1,0.7,0.48,0.9);
//"lep" para que salga el punto y la linea
//"l" la linea
//"p" el punto
if(angle==10){
std::string angulo= "#theta [0,10] deg";
leg3->AddEntry(gr3,angulo.c_str(),"p");
leg3->Draw();
}
if(angle==20){
std::string angulo= "#theta [10,20] deg";
leg3->AddEntry(gr3,angulo.c_str(),"p");
leg3->Draw();
}
if(angle==30){
std::string angulo= "#theta [20,30] deg";
leg3->AddEntry(gr3,angulo.c_str(),"p");
leg3->Draw();
}

if(angle==40){
std::string angulo= "#theta [30,40] deg";
leg3->AddEntry(gr3,angulo.c_str(),"p");
leg3->Draw();
}

if(angle==50){
std::string angulo= "#theta [40,50] deg";
leg3->AddEntry(gr3,angulo.c_str(),"p");
leg3->Draw();
}

if(angle==60){
std::string angulo= "#theta [50,60] deg";
leg3->AddEntry(gr3,angulo.c_str(),"p");
leg3->Draw();
}

if(angle==70){
std::string angulo= "#theta [60,70] deg";
leg3->AddEntry(gr3,angulo.c_str(),"p");
leg3->Draw();
}

if(angle==80){
std::string angulo= "#theta [70,80] deg";
leg3->AddEntry(gr3,angulo.c_str(),"p");
leg3->Draw();
}

if(angle==90){
std::string angulo= "#theta [80,90] deg";
leg3->AddEntry(gr3,angulo.c_str(),"p");
leg3->Draw();
}




/////////////////////////////////////////////////////////
//GH


vector<double> vx, vy, vex, vey;
  vx.clear();
  vy.clear();
  vex.clear();
  vey.clear();
TAxis *xaxis = hprof4->GetXaxis();
Int_t nbins = xaxis->GetNbins();
for (Int_t bin=0; bin <= nbins; bin++) {

    //Double_t xcenter = xaxis->GetBinCenter(bin);
    Double_t binentries=hprof4->GetBinEntries(bin);
    if(binentries<1) continue;
    //if(angle==10&&binentries<cut0) continue;
    //if(angle==20&&binentries<cut1) continue;
    //if(angle!=10&&angle!=20&&binentries<cutrest) continue;
    double x_value = hprofx4->GetBinContent(bin);
    double y_value = hprof4->GetBinContent(bin);
    double x_error = hprofx4->GetBinError(bin);
    double y_error = hprof4->GetBinError(bin);
   if(y_value == 0) continue;
    vx.push_back(x_value);
    vy.push_back(y_value);
    vex.push_back(x_error);
    vey.push_back(y_error);

 }
cout<<"-----------------------------------------"<<endl;
 gr4 = new TGraphErrors(vx.size(), &vx[0], &vy[0], 0, &vey[0]);




//Graficamos las gaisser hillas con fotones g4 vuv
c1->cd(3);

double xx4[2]={0,600};
double yy4[2]={0,1.5};
TGraph *graph4 = new TGraph (2,xx4,yy4);
graph4->GetXaxis()->SetRangeUser(0,600);
graph4->GetYaxis()->SetRangeUser(0,1.5);
graph4->SetTitle("2000 events of Michel electron E=30MeV");
graph4->GetXaxis()->SetTitle("distance (cm)");
graph4->GetYaxis()->SetTitle("N_{Lite}/N_{#Omega}/cos(#theta)");
graph4->Draw("ap");


  gr4->GetXaxis()->SetRangeUser(0,600);
  gr4->GetYaxis()->SetRangeUser(0,1.5);
  gr4->SetMarkerStyle(21);




  if(angle==10){gr4->SetMarkerColor(1);
    int i=0;
    GH[i]->SetLineColor(1);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr4->Draw("p");
    GH[i]->Draw("same");}
  if(angle==20){gr4->SetMarkerColor(2);
      int i=1;
    GH[i]->SetLineColor(2);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr4->Draw("p");
    GH[i]->Draw("same");}
  if(angle==30){gr4->SetMarkerColor(3);
    int i=2;
    GH[i]->SetLineColor(3);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr4->Draw("p");
    GH[i]->Draw("same");}
  if(angle==40){gr4->SetMarkerColor(4);
      int i=3;
    GH[i]->SetLineColor(4);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr4->Draw("p");
    GH[i]->Draw("same");}
  if(angle==50){gr4->SetMarkerColor(kOrange-3);
      int i=4;
    GH[i]->SetLineColor(kOrange-3);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr4->Draw("p");
    GH[i]->Draw("same");}
  if(angle==60){gr4->SetMarkerColor(6);
      int i=5;
    GH[i]->SetLineColor(6);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr4->Draw("p");
    GH[i]->Draw("same");}
  if(angle==70){gr4->SetMarkerColor(7);
      int i=6;
    GH[i]->SetLineColor(7);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr4->Draw("p");
    GH[i]->Draw("same");}
  if(angle==80){gr4->SetMarkerColor(8);
      int i=7;
    GH[i]->SetLineColor(8);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr4->Draw("p");
    GH[i]->Draw("same");}
  if(angle==90){gr4->SetMarkerColor(9);
      int i=8;
    GH[i]->SetLineColor(9);
    GH[i]->SetLineStyle(kDashed);
    GH[i]->GetXaxis()->SetRangeUser(0,600);
    GH[i]->GetYaxis()->SetRangeUser(0,1.5);
    gr4->Draw("p");
    GH[i]->Draw("same");}





auto leg4 = new TLegend(0.1,0.7,0.48,0.9);
//"lep" para que salga el punto y la linea
//"l" la linea
//"p" el punto

if(angle==10){
std::string angulo= "#theta [0,10] deg";
leg4->AddEntry(gr4,angulo.c_str(),"p");
leg4->Draw();
}
if(angle==20){
std::string angulo= "#theta [10,20] deg";
leg4->AddEntry(gr4,angulo.c_str(),"p");
leg4->Draw();
}
if(angle==30){
std::string angulo= "#theta [20,30] deg";
leg4->AddEntry(gr4,angulo.c_str(),"p");
leg4->Draw();
}

if(angle==40){
std::string angulo= "#theta [30,40] deg";
leg4->AddEntry(gr4,angulo.c_str(),"p");
leg4->Draw();
}

if(angle==50){
std::string angulo= "#theta [40,50] deg";
leg4->AddEntry(gr4,angulo.c_str(),"p");
leg4->Draw();
}

if(angle==60){
std::string angulo= "#theta [50,60] deg";
leg4->AddEntry(gr4,angulo.c_str(),"p");
leg4->Draw();
}

if(angle==70){
std::string angulo= "#theta [60,70] deg";
leg4->AddEntry(gr4,angulo.c_str(),"p");
leg4->Draw();
}

if(angle==80){
std::string angulo= "#theta [70,80] deg";
leg4->AddEntry(gr4,angulo.c_str(),"p");
leg4->Draw();
}

if(angle==90){
std::string angulo= "#theta [80,90] deg";
leg4->AddEntry(gr4,angulo.c_str(),"p");
leg4->Draw();
}




leg4->Draw();

  }
