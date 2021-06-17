//Lanzamiento de 50 crossing muon en las posiciones x= 20,40,60,80,100,120,140,160,175,185
//195,204,212,220,228,236,244,252 cm del detector SBND. Hay un .root para cada posición.

//pad 1
//
//Eje X: distancia en x (cm)
//Eje Y: Número de fotones generados (#PE)
//Para cada 50 crossing muons (en cada en cada una de las posiciones) se calcula la media de las posiciones (punto en el eje x)
//Para cada 50 crossing muons se calcula la suma de fotones generados para la luz ultravioleta (VUV) y la luz reflejada (VIS)
//multiplicado por 0.03 para tener en cuenta el prescale (punto del eje y)
//Este cálculo se hace usando el LArQL Model, que tiene en cuenta los "escaping electrons" que no se recombinan a bajo campo electrico
//y por tanto sus efectos serán visibles en el non-active volume (userecomb.root) y sin este modelo (norecomb.root).

//pad 2
//Se representa el error relativo del numero de fotones entre ambos modelos (usando LArQL y sin usarlo)


{
  //TCanvas*c1=new TCanvas();
  TCanvas *c1 = new TCanvas("c1","Title",200,10,700,600);
  c1->SetGrid();
TPad *pad1 = new TPad("pad1","pad1",0,0.33,1,1);
TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.33);
pad1->SetBottomMargin(0.1);
pad1->SetGrid();
pad1->SetBorderMode(0);
pad2->SetTopMargin(0.1);
pad2->SetBottomMargin(0.1);
pad2->SetBorderMode(0);
pad2->SetGrid();
pad1->Draw();
pad2->Draw();
  gStyle->SetOptStat(0);

  //Leemos los archivos hibrido LArQL .root
  TFile *inputs20= new TFile("output_hib_20_userecomb.root","read");
  TFile *inputs40= new TFile("output_hib_40_userecomb.root","read");
  TFile *inputs60= new TFile("output_hib_60_userecomb.root","read");
  TFile *inputs80= new TFile("output_hib_80_userecomb.root","read");
  TFile *inputs100= new TFile("output_hib_100_userecomb.root","read");
  TFile *inputs120= new TFile("output_hib_120_userecomb.root","read");
  TFile *inputs140= new TFile("output_hib_140_userecomb.root","read");
  TFile *inputs160= new TFile("output_hib_160_userecomb.root","read");
  TFile *inputs175= new TFile("output_hib_175_userecomb.root","read");
  TFile *inputs185= new TFile("output_hib_185_userecomb.root","read");
  TFile *inputs195= new TFile("output_hib_195_userecomb.root","read");
  TFile *inputs204= new TFile("output_hib_204_userecomb.root","read");
  TFile *inputs212= new TFile("output_hib_212_userecomb.root","read");
  TFile *inputs220= new TFile("output_hib_220_userecomb.root","read");
  TFile *inputs228= new TFile("output_hib_228_userecomb.root","read");
  TFile *inputs236= new TFile("output_hib_236_userecomb.root","read");
  TFile *inputs244= new TFile("output_hib_244_userecomb.root","read");
  TFile *inputs252= new TFile("output_hib_252_userecomb.root","read");




//Leemos los archivos hibrido sin LArQL .root
TFile *inputh20= new TFile("output_hib_20_norecomb.root","read");
TFile *inputh40= new TFile("output_hib_40_norecomb.root","read");
TFile *inputh60= new TFile("output_hib_60_norecomb.root","read");
TFile *inputh80= new TFile("output_hib_80_norecomb.root","read");
TFile *inputh100= new TFile("output_hib_100_norecomb.root","read");
TFile *inputh120= new TFile("output_hib_120_norecomb.root","read");
TFile *inputh140= new TFile("output_hib_140_norecomb.root","read");
TFile *inputh160= new TFile("output_hib_160_norecomb.root","read");
TFile *inputh175= new TFile("output_hib_175_norecomb.root","read");
TFile *inputh185= new TFile("output_hib_185_norecomb.root","read");
TFile *inputh195= new TFile("output_hib_195_norecomb.root","read");
TFile *inputh204= new TFile("output_hib_204_norecomb.root","read");
TFile *inputh212= new TFile("output_hib_212_norecomb.root","read");
TFile *inputh220= new TFile("output_hib_220_norecomb.root","read");
TFile *inputh228= new TFile("output_hib_228_norecomb.root","read");
TFile *inputh236= new TFile("output_hib_236_norecomb.root","read");
TFile *inputh244= new TFile("output_hib_244_norecomb.root","read");
TFile *inputh252= new TFile("output_hib_252_norecomb.root","read");





  //Declaro las dos columnas del fichero

   //Pos X
   vector<double> *Xss20, *Xss40, *Xss60, *Xss80, *Xss100, *Xss120,*Xss140,*Xss160,*Xss175,*Xss185, *Xss195,*Xss204,*Xss212,*Xss220,*Xss228,*Xss236,*Xss244,*Xss252;
   vector<double> *Xsl20, *Xsl40, *Xsl60, *Xsl80, *Xsl100, *Xsl120,*Xsl140,*Xsl160,*Xsl175,*Xsl185,*Xsl195,*Xsl204,*Xsl212,*Xsl220,*Xsl228,*Xsl236,*Xsl244,*Xsl252;


   vector<double> *Xhs20, *Xhs40, *Xhs60, *Xhs80, *Xhs100, *Xhs120,*Xhs140,*Xhs160,*Xhs175,*Xhs185, *Xhs195,*Xhs204,*Xhs212,*Xhs220,*Xhs228,*Xhs236,*Xhs244,*Xhs252;
   vector<double> *Xhl20, *Xhl40, *Xhl60, *Xhl80, *Xhl100, *Xhl120,*Xhl140,*Xhl160,*Xhl175,*Xhl185,*Xhl195,*Xhl204,*Xhl212,*Xhl220,*Xhl228,*Xhl236,*Xhl244,*Xhl252;

   //VUV (fotones directos)

   vector<double> *VUVss20, *VUVss40, *VUVss60, *VUVss80, *VUVss100, *VUVss120,*VUVss140,*VUVss160,*VUVss175,*VUVss185,*VUVss195,*VUVss204,*VUVss212,*VUVss220,*VUVss228,*VUVss236,*VUVss244,*VUVss252;
   vector<double> *VUVsl20, *VUVsl40, *VUVsl60, *VUVsl80, *VUVsl100, *VUVsl120,*VUVsl140,*VUVsl160,*VUVsl175,*VUVsl185,*VUVsl195,*VUVsl204,*VUVsl212,*VUVsl220,*VUVsl228,*VUVsl236,*VUVsl244,*VUVsl252;

   vector<double> *VUVhs20, *VUVhs40, *VUVhs60, *VUVhs80, *VUVhs100, *VUVhs120,*VUVhs140,*VUVhs160,*VUVhs175,*VUVhs185,*VUVhs195,*VUVhs204,*VUVhs212,*VUVhs220,*VUVhs228,*VUVhs236,*VUVhs244,*VUVhs252;
   vector<double> *VUVhl20, *VUVhl40, *VUVhl60, *VUVhl80, *VUVhl100, *VUVhl120,*VUVhl140,*VUVhl160,*VUVhl175,*VUVhl185,*VUVhl195,*VUVhl204,*VUVhl212,*VUVhl220,*VUVhl228,*VUVhl236,*VUVhl244,*VUVhl252;

   //VIS (fotones reflejados)
   vector<double> *VISss20, *VISss40, *VISss60, *VISss80, *VISss100, *VISss120,*VISss140,*VISss160,*VISss175, *VISss185,*VISss195,*VISss204,*VISss212, *VISss220, *VISss228, *VISss236,*VISss244, *VISss252;
   vector<double> *VISsl20, *VISsl40, *VISsl60, *VISsl80, *VISsl100, *VISsl120,*VISsl140,*VISsl160,*VISsl175, *VISsl185,*VISsl195,*VISsl204,*VISsl212, *VISsl220, *VISsl228, *VISsl236,*VISsl244, *VISsl252;

   vector<double> *VIShs20, *VIShs40, *VIShs60, *VIShs80, *VIShs100, *VIShs120,*VIShs140,*VIShs160,*VIShs175, *VIShs185,*VIShs195,*VIShs204,*VIShs212, *VIShs220, *VIShs228, *VIShs236,*VIShs244, *VIShs252;
   vector<double> *VIShl20, *VIShl40, *VIShl60, *VIShl80, *VIShl100, *VIShl120,*VIShl140,*VIShl160,*VIShl175, *VIShl185,*VIShl195,*VIShl204,*VIShl212, *VIShl220, *VIShl228, *VIShl236,*VIShl244, *VIShl252;


  //Leemos los TTree
  TTree* trees20=(TTree*)inputs20->Get("ana/tree");
  TTree* trees40=(TTree*)inputs40->Get("ana/tree");
  TTree* trees60=(TTree*)inputs60->Get("ana/tree");
  TTree* trees80=(TTree*)inputs80->Get("ana/tree");
  TTree* trees100=(TTree*)inputs100->Get("ana/tree");
  TTree* trees120=(TTree*)inputs120->Get("ana/tree");
  TTree* trees140=(TTree*)inputs140->Get("ana/tree");
  TTree* trees160=(TTree*)inputs160->Get("ana/tree");
  TTree* trees175=(TTree*)inputs175->Get("ana/tree");
  TTree* trees185=(TTree*)inputs185->Get("ana/tree");
  TTree* trees195=(TTree*)inputs195->Get("ana/tree");
  TTree* trees204=(TTree*)inputs204->Get("ana/tree");
  TTree* trees212=(TTree*)inputs212->Get("ana/tree");
  TTree* trees220=(TTree*)inputs220->Get("ana/tree");
  TTree* trees228=(TTree*)inputs228->Get("ana/tree");
  TTree* trees236=(TTree*)inputs236->Get("ana/tree");
  TTree* trees244=(TTree*)inputs244->Get("ana/tree");
  TTree* trees252=(TTree*)inputs252->Get("ana/tree");


//Notación: las variables con un 1 al final se han calculado con la librería óptica
//y por tanto son fuera del volumen activo. Las variables que no tienen 1 se han calculado
//usando el modelo semianalitico y por tanto son dentro del volumen activo
//Para el nombre de la variable, si lleva una s al inicio es con LArQL y si lleva una h al inicio es sin LArQL
//si lleva una s es con el semianalítico y si lleva una l es con la librería.
//Por ejemplo Xss20 quiere decir que son las posiciones de los 50 muones, lanzados en x=20cm usando LArQL con el modelo semianalítico
//(es decir las posiciones dentro del volumen activo), mientras que Xsl20 es lo mismo pero las posiciones de fuera del volumen
//activo (usando la libreria)
  trees20->SetBranchAddress("X",&Xss20);
  trees20->SetBranchAddress("X1",&Xsl20);
  trees20->SetBranchAddress("phot_detected",&VUVss20);
  trees20->SetBranchAddress("phot_detected1",&VUVsl20);
  trees20->SetBranchAddress("phot_detectedref",&VISss20);
  trees20->SetBranchAddress("phot_detectedref1",&VISsl20);


  trees40->SetBranchAddress("X",&Xss40);
  trees40->SetBranchAddress("X1",&Xsl40);
  trees40->SetBranchAddress("phot_detected",&VUVss40);
  trees40->SetBranchAddress("phot_detected1",&VUVsl40);
  trees40->SetBranchAddress("phot_detectedref",&VISss40);
  trees40->SetBranchAddress("phot_detectedref1",&VISsl40);


  trees60->SetBranchAddress("X",&Xss60);
  trees60->SetBranchAddress("X1",&Xsl60);
  trees60->SetBranchAddress("phot_detected",&VUVss60);
  trees60->SetBranchAddress("phot_detected1",&VUVsl60);
  trees60->SetBranchAddress("phot_detectedref",&VISss60);
  trees60->SetBranchAddress("phot_detectedref1",&VISsl60);


  trees80->SetBranchAddress("X",&Xss80);
  trees80->SetBranchAddress("X1",&Xsl80);
  trees80->SetBranchAddress("phot_detected",&VUVss80);
  trees80->SetBranchAddress("phot_detected1",&VUVsl80);
  trees80->SetBranchAddress("phot_detectedref",&VISss80);
  trees80->SetBranchAddress("phot_detectedref1",&VISsl80);


  trees100->SetBranchAddress("X",&Xss100);
  trees100->SetBranchAddress("X1",&Xsl100);
  trees100->SetBranchAddress("phot_detected",&VUVss100);
  trees100->SetBranchAddress("phot_detected1",&VUVsl100);
  trees100->SetBranchAddress("phot_detectedref",&VISss100);
  trees100->SetBranchAddress("phot_detectedref1",&VISsl100);


  trees120->SetBranchAddress("X",&Xss120);
  trees120->SetBranchAddress("X1",&Xsl120);
  trees120->SetBranchAddress("phot_detected",&VUVss120);
  trees120->SetBranchAddress("phot_detected1",&VUVsl120);
  trees120->SetBranchAddress("phot_detectedref",&VISss120);
  trees120->SetBranchAddress("phot_detectedref1",&VISsl120);


  trees140->SetBranchAddress("X",&Xss140);
  trees140->SetBranchAddress("X1",&Xsl140);
  trees140->SetBranchAddress("phot_detected",&VUVss140);
  trees140->SetBranchAddress("phot_detected1",&VUVsl140);
  trees140->SetBranchAddress("phot_detectedref",&VISss140);
  trees140->SetBranchAddress("phot_detectedref1",&VISsl140);


  trees160->SetBranchAddress("X",&Xss160);
  trees160->SetBranchAddress("X1",&Xsl160);
  trees160->SetBranchAddress("phot_detected",&VUVss160);
  trees160->SetBranchAddress("phot_detected1",&VUVsl160);
  trees160->SetBranchAddress("phot_detectedref",&VISss160);
  trees160->SetBranchAddress("phot_detectedref1",&VISsl160);


  trees175->SetBranchAddress("X",&Xss175);
  trees175->SetBranchAddress("X1",&Xsl175);
  trees175->SetBranchAddress("phot_detected",&VUVss175);
  trees175->SetBranchAddress("phot_detected1",&VUVsl175);
  trees175->SetBranchAddress("phot_detectedref",&VISss175);
  trees175->SetBranchAddress("phot_detectedref1",&VISsl175);


  trees185->SetBranchAddress("X",&Xss185);
  trees185->SetBranchAddress("X1",&Xsl185);
  trees185->SetBranchAddress("phot_detected",&VUVss185);
  trees185->SetBranchAddress("phot_detected1",&VUVsl185);
  trees185->SetBranchAddress("phot_detectedref",&VISss185);
  trees185->SetBranchAddress("phot_detectedref1",&VISsl185);


  trees195->SetBranchAddress("X",&Xss195);
  trees195->SetBranchAddress("X1",&Xsl195);
  trees195->SetBranchAddress("phot_detected",&VUVss195);
  trees195->SetBranchAddress("phot_detected1",&VUVsl195);
  trees195->SetBranchAddress("phot_detectedref",&VISss195);
  trees195->SetBranchAddress("phot_detectedref1",&VISsl195);


  trees204->SetBranchAddress("X",&Xss204);
  trees204->SetBranchAddress("X1",&Xsl204);
  trees204->SetBranchAddress("phot_detected",&VUVss204);
  trees204->SetBranchAddress("phot_detected1",&VUVsl204);
  trees204->SetBranchAddress("phot_detectedref",&VISss204);
  trees204->SetBranchAddress("phot_detectedref1",&VISsl204);


  trees212->SetBranchAddress("X",&Xss212);
  trees212->SetBranchAddress("X1",&Xsl212);
  trees212->SetBranchAddress("phot_detected",&VUVss212);
  trees212->SetBranchAddress("phot_detected1",&VUVsl212);
  trees212->SetBranchAddress("phot_detectedref",&VISss212);
  trees212->SetBranchAddress("phot_detectedref1",&VISsl212);



  trees220->SetBranchAddress("X",&Xss220);
  trees220->SetBranchAddress("X1",&Xsl220);
  trees220->SetBranchAddress("phot_detected",&VUVss220);
  trees220->SetBranchAddress("phot_detected1",&VUVsl220);
  trees220->SetBranchAddress("phot_detectedref",&VISss220);
  trees220->SetBranchAddress("phot_detectedref1",&VISsl220);


  trees228->SetBranchAddress("X",&Xss228);
  trees228->SetBranchAddress("X1",&Xsl228);
  trees228->SetBranchAddress("phot_detected",&VUVss228);
  trees228->SetBranchAddress("phot_detected1",&VUVsl228);
  trees228->SetBranchAddress("phot_detectedref",&VISss228);
  trees228->SetBranchAddress("phot_detectedref1",&VISsl228);


  trees236->SetBranchAddress("X",&Xss236);
  trees236->SetBranchAddress("X1",&Xsl236);
  trees236->SetBranchAddress("phot_detected",&VUVss236);
  trees236->SetBranchAddress("phot_detected1",&VUVsl236);
  trees236->SetBranchAddress("phot_detectedref",&VISss236);
  trees236->SetBranchAddress("phot_detectedref1",&VISsl236);


  trees244->SetBranchAddress("X",&Xss244);
  trees244->SetBranchAddress("X1",&Xsl244);
  trees244->SetBranchAddress("phot_detected",&VUVss244);
  trees244->SetBranchAddress("phot_detected1",&VUVsl244);
  trees244->SetBranchAddress("phot_detectedref",&VISss244);
  trees244->SetBranchAddress("phot_detectedref1",&VISsl244);

  trees252->SetBranchAddress("X",&Xss252);
  trees252->SetBranchAddress("X1",&Xsl252);
  trees252->SetBranchAddress("phot_detected",&VUVss252);
  trees252->SetBranchAddress("phot_detected1",&VUVsl252);
  trees252->SetBranchAddress("phot_detectedref",&VISss252);
  trees252->SetBranchAddress("phot_detectedref1",&VISsl252);



  //Leemos los TTree
  TTree* treeh20=(TTree*)inputh20->Get("ana/tree");
  TTree* treeh40=(TTree*)inputh40->Get("ana/tree");
  TTree* treeh60=(TTree*)inputh60->Get("ana/tree");
  TTree* treeh80=(TTree*)inputh80->Get("ana/tree");
  TTree* treeh100=(TTree*)inputh100->Get("ana/tree");
  TTree* treeh120=(TTree*)inputh120->Get("ana/tree");
  TTree* treeh140=(TTree*)inputh140->Get("ana/tree");
  TTree* treeh160=(TTree*)inputh160->Get("ana/tree");
  TTree* treeh175=(TTree*)inputh175->Get("ana/tree");
  TTree* treeh185=(TTree*)inputh185->Get("ana/tree");
  TTree* treeh195=(TTree*)inputh195->Get("ana/tree");
  TTree* treeh204=(TTree*)inputh204->Get("ana/tree");
  TTree* treeh212=(TTree*)inputh212->Get("ana/tree");
  TTree* treeh220=(TTree*)inputh220->Get("ana/tree");
  TTree* treeh228=(TTree*)inputh228->Get("ana/tree");
  TTree* treeh236=(TTree*)inputh236->Get("ana/tree");
  TTree* treeh244=(TTree*)inputh244->Get("ana/tree");
  TTree* treeh252=(TTree*)inputh252->Get("ana/tree");



  treeh20->SetBranchAddress("X",&Xhs20);
  treeh20->SetBranchAddress("X1",&Xhl20);
  treeh20->SetBranchAddress("phot_detected",&VUVhs20);
  treeh20->SetBranchAddress("phot_detected1",&VUVhl20);
  treeh20->SetBranchAddress("phot_detectedref",&VIShs20);
  treeh20->SetBranchAddress("phot_detectedref1",&VIShl20);


  treeh40->SetBranchAddress("X",&Xhs40);
  treeh40->SetBranchAddress("X1",&Xhl40);
  treeh40->SetBranchAddress("phot_detected",&VUVhs40);
  treeh40->SetBranchAddress("phot_detected1",&VUVhl40);
  treeh40->SetBranchAddress("phot_detectedref",&VIShs40);
  treeh40->SetBranchAddress("phot_detectedref1",&VIShl40);


  treeh60->SetBranchAddress("X",&Xhs60);
  treeh60->SetBranchAddress("X1",&Xhl60);
  treeh60->SetBranchAddress("phot_detected",&VUVhs60);
  treeh60->SetBranchAddress("phot_detected1",&VUVhl60);
  treeh60->SetBranchAddress("phot_detectedref",&VIShs60);
  treeh60->SetBranchAddress("phot_detectedref1",&VIShl60);


  treeh80->SetBranchAddress("X",&Xhs80);
  treeh80->SetBranchAddress("X1",&Xhl80);
  treeh80->SetBranchAddress("phot_detected",&VUVhs80);
  treeh80->SetBranchAddress("phot_detected1",&VUVhl80);
  treeh80->SetBranchAddress("phot_detectedref",&VIShs80);
  treeh80->SetBranchAddress("phot_detectedref1",&VIShl80);


  treeh100->SetBranchAddress("X",&Xhs100);
  treeh100->SetBranchAddress("X1",&Xhl100);
  treeh100->SetBranchAddress("phot_detected",&VUVhs100);
  treeh100->SetBranchAddress("phot_detected1",&VUVhl100);
  treeh100->SetBranchAddress("phot_detectedref",&VIShs100);
  treeh100->SetBranchAddress("phot_detectedref1",&VIShl100);


  treeh120->SetBranchAddress("X",&Xhs120);
  treeh120->SetBranchAddress("X1",&Xhl120);
  treeh120->SetBranchAddress("phot_detected",&VUVhs120);
  treeh120->SetBranchAddress("phot_detected1",&VUVhl120);
  treeh120->SetBranchAddress("phot_detectedref",&VIShs120);
  treeh120->SetBranchAddress("phot_detectedref1",&VIShl120);


  treeh140->SetBranchAddress("X",&Xhs140);
  treeh140->SetBranchAddress("X1",&Xhl140);
  treeh140->SetBranchAddress("phot_detected",&VUVhs140);
  treeh140->SetBranchAddress("phot_detected1",&VUVhl140);
  treeh140->SetBranchAddress("phot_detectedref",&VIShs140);
  treeh140->SetBranchAddress("phot_detectedref1",&VIShl140);


  treeh160->SetBranchAddress("X",&Xhs160);
  treeh160->SetBranchAddress("X1",&Xhl160);
  treeh160->SetBranchAddress("phot_detected",&VUVhs160);
  treeh160->SetBranchAddress("phot_detected1",&VUVhl160);
  treeh160->SetBranchAddress("phot_detectedref",&VIShs160);
  treeh160->SetBranchAddress("phot_detectedref1",&VIShl160);


  treeh175->SetBranchAddress("X",&Xhs175);
  treeh175->SetBranchAddress("X1",&Xhl175);
  treeh175->SetBranchAddress("phot_detected",&VUVhs175);
  treeh175->SetBranchAddress("phot_detected1",&VUVhl175);
  treeh175->SetBranchAddress("phot_detectedref",&VIShs175);
  treeh175->SetBranchAddress("phot_detectedref1",&VIShl175);


  treeh185->SetBranchAddress("X",&Xhs185);
  treeh185->SetBranchAddress("X1",&Xhl185);
  treeh185->SetBranchAddress("phot_detected",&VUVhs185);
  treeh185->SetBranchAddress("phot_detected1",&VUVhl185);
  treeh185->SetBranchAddress("phot_detectedref",&VIShs185);
  treeh185->SetBranchAddress("phot_detectedref1",&VIShl185);


  treeh195->SetBranchAddress("X",&Xhs195);
  treeh195->SetBranchAddress("X1",&Xhl195);
  treeh195->SetBranchAddress("phot_detected",&VUVhs195);
  treeh195->SetBranchAddress("phot_detected1",&VUVhl195);
  treeh195->SetBranchAddress("phot_detectedref",&VIShs195);
  treeh195->SetBranchAddress("phot_detectedref1",&VIShl195);


  treeh204->SetBranchAddress("X",&Xhs204);
  treeh204->SetBranchAddress("X1",&Xhl204);
  treeh204->SetBranchAddress("phot_detected",&VUVhs204);
  treeh204->SetBranchAddress("phot_detected1",&VUVhl204);
  treeh204->SetBranchAddress("phot_detectedref",&VIShs204);
  treeh204->SetBranchAddress("phot_detectedref1",&VIShl204);


  treeh212->SetBranchAddress("X",&Xhs212);
  treeh212->SetBranchAddress("X1",&Xhl212);
  treeh212->SetBranchAddress("phot_detected",&VUVhs212);
  treeh212->SetBranchAddress("phot_detected1",&VUVhl212);
  treeh212->SetBranchAddress("phot_detectedref",&VIShs212);
  treeh212->SetBranchAddress("phot_detectedref1",&VIShl212);



  treeh220->SetBranchAddress("X",&Xhs220);
  treeh220->SetBranchAddress("X1",&Xhl220);
  treeh220->SetBranchAddress("phot_detected",&VUVhs220);
  treeh220->SetBranchAddress("phot_detected1",&VUVhl220);
  treeh220->SetBranchAddress("phot_detectedref",&VIShs220);
  treeh220->SetBranchAddress("phot_detectedref1",&VIShl220);


  treeh228->SetBranchAddress("X",&Xhs228);
  treeh228->SetBranchAddress("X1",&Xhl228);
  treeh228->SetBranchAddress("phot_detected",&VUVhs228);
  treeh228->SetBranchAddress("phot_detected1",&VUVhl228);
  treeh228->SetBranchAddress("phot_detectedref",&VIShs228);
  treeh228->SetBranchAddress("phot_detectedref1",&VIShl228);


  treeh236->SetBranchAddress("X",&Xhs236);
  treeh236->SetBranchAddress("X1",&Xhl236);
  treeh236->SetBranchAddress("phot_detected",&VUVhs236);
  treeh236->SetBranchAddress("phot_detected1",&VUVhl236);
  treeh236->SetBranchAddress("phot_detectedref",&VIShs236);
  treeh236->SetBranchAddress("phot_detectedref1",&VIShl236);


  treeh244->SetBranchAddress("X",&Xhs244);
  treeh244->SetBranchAddress("X1",&Xhl244);
  treeh244->SetBranchAddress("phot_detected",&VUVhs244);
  treeh244->SetBranchAddress("phot_detected1",&VUVhl244);
  treeh244->SetBranchAddress("phot_detectedref",&VIShs244);
  treeh244->SetBranchAddress("phot_detectedref1",&VIShl244);


  treeh252->SetBranchAddress("X",&Xhs252);
  treeh252->SetBranchAddress("X1",&Xhl252);
  treeh252->SetBranchAddress("phot_detected",&VUVhs252);
  treeh252->SetBranchAddress("phot_detected1",&VUVhl252);
  treeh252->SetBranchAddress("phot_detectedref",&VIShs252);
  treeh252->SetBranchAddress("phot_detectedref1",&VIShl252);




  //Ver las entradas que tienen los TTree
  //hibrido LArQL
  int entriess20=trees20->GetEntries();
  int entriess40=trees40->GetEntries();
  int entriess60=trees60->GetEntries();
  int entriess80=trees80->GetEntries();
  int entriess100=trees100->GetEntries();
  int entriess120=trees120->GetEntries();
  int entriess140=trees140->GetEntries();
  int entriess160=trees160->GetEntries();
  int entriess175=trees175->GetEntries();
  int entriess185=trees185->GetEntries();
  int entriess195=trees195->GetEntries();
  int entriess204=trees204->GetEntries();
  int entriess212=trees212->GetEntries();
  int entriess220=trees220->GetEntries();
  int entriess228=trees228->GetEntries();
  int entriess236=trees236->GetEntries();
  int entriess244=trees244->GetEntries();
  int entriess252=trees252->GetEntries();


  //hibrido sin LArQL
  int entriesh20=treeh20->GetEntries();
  int entriesh40=treeh40->GetEntries();
  int entriesh60=treeh60->GetEntries();
  int entriesh80=treeh80->GetEntries();
  int entriesh100=treeh100->GetEntries();
  int entriesh120=treeh120->GetEntries();
  int entriesh140=treeh140->GetEntries();
  int entriesh160=treeh160->GetEntries();
  int entriesh175=treeh175->GetEntries();
  int entriesh185=treeh185->GetEntries();
  int entriesh195=treeh195->GetEntries();
  int entriesh204=treeh204->GetEntries();
  int entriesh212=treeh212->GetEntries();
  int entriesh220=treeh220->GetEntries();
  int entriesh228=treeh228->GetEntries();
  int entriesh236=treeh236->GetEntries();
  int entriesh244=treeh244->GetEntries();
  int entriesh252=treeh252->GetEntries();


//numero de puntos en cada graph
 const Int_t ns = 18;
 const Int_t nh = 18;
//Almacenamos los puntos y los errores del graph en vectores
   Double_t xs[ns], xh[nh], ys[ns], yh[nh], ysvis[ns],yhvis[nh];
   Double_t exs[ns], exh[nh],eys[ns], eyh[nh], eysvis[ns], eyhvis[nh];





//Hibrido usando UseModLarqlRecomb=true/////////////////////////////////////////////////////////////////////////////////////////////
cout<<"-----Hibrido usando UseModLarqlRecomb=true-----"<<endl;
//Para las x
TH1F*hsx20=new TH1F("hsx20", "", 100,0,300);
//Para las y VUV
TH1F*hsy20=new TH1F("hsy20", "", 100,0,10000000);
//Para las y VIS
TH1F*hsyvis20=new TH1F("hsyvis20", "", 100,0,10000000);
for(int i=0;i<entriess20;i++) //50 veces
{
  trees20->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss20->size();j++){
    hsx20->Fill(Xss20->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl20->size();j++){
    hsx20->Fill(Xsl20->at(j)); //llena todas las x de los 50 muones
  }



  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;


  //fotones detectados en los coated
  for(int j=0;j<VUVss20->size();j++){
     VUV+= VUVss20->at(j);
  }
  for(int j=0;j<VUVsl20->size();j++){
     VUV1+= VUVsl20->at(j);
  }
  hsy20->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss20->size();j++){
     VIS+= VISss20->at(j);
  }
  for(int j=0;j<VISsl20->size();j++){
     VIS1+= VISsl20->at(j);
  }
  hsyvis20->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[0] = hsx20->GetMean();
 exs[0]= hsx20->GetRMS();
//punto y del graph final con su error
ys[0]= hsy20->GetMean();
eys[0]= hsy20->GetRMS();

ysvis[0]=hsyvis20->GetMean();
eyhvis[0]=hsyvis20->GetRMS();

cout<<xs[0]<<" "<<ys[0]<<endl;



/////////////////////////////
TH1F*hsx40=new TH1F("hsx40", "", 100,0,300);
TH1F*hsy40=new TH1F("hsy40", "", 100,0,10000000);
TH1F*hsyvis40=new TH1F("hsyvis40", "", 100,0,10000000);
for(int i=0;i<entriess40;i++) //50 veces
{
  trees40->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss40->size();j++){
    //X = Xs20->at(j);
    hsx40->Fill(Xss40->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl40->size();j++){
    //X = Xs20->at(j);
    hsx40->Fill(Xsl40->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;


  //fotones detectados en los coated
  for(int j=0;j<VUVss40->size();j++){
     VUV+= VUVss40->at(j);
  }
  for(int j=0;j<VUVsl40->size();j++){
     VUV1+= VUVsl40->at(j);
  }
  hsy40->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss40->size();j++){
     VIS+= VISss40->at(j);
  }
  for(int j=0;j<VISsl40->size();j++){
     VIS1+= VISsl40->at(j);
  }
  hsyvis40->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[1] = hsx40->GetMean();
 exs[1]= hsx40->GetRMS();
//punto y del graph final con su error
ys[1]= hsy40->GetMean();
eys[1]= hsy40->GetRMS();

ysvis[1]=hsyvis40->GetMean();
eyhvis[1]=hsyvis40->GetRMS();

cout<<xs[1]<<" "<<ys[1]<<endl;

/////////////////////////////
TH1F*hsx60=new TH1F("hsx60", "", 100,0,300);
TH1F*hsy60=new TH1F("hsy60", "", 100,0,10000000);
TH1F*hsyvis60=new TH1F("hsyvis60", "", 100,0,10000000);
for(int i=0;i<entriess60;i++) //50 veces
{
  trees60->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss60->size();j++){
    //X = Xs20->at(j);
    hsx60->Fill(Xss60->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl60->size();j++){
    //X = Xs20->at(j);
    hsx60->Fill(Xsl60->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;


  //fotones detectados en los coated
  for(int j=0;j<VUVss60->size();j++){
     VUV+= VUVss60->at(j);
  }
  for(int j=0;j<VUVsl60->size();j++){
     VUV1+= VUVsl60->at(j);
  }
  hsy60->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss60->size();j++){
     VIS+= VISss60->at(j);
  }
  for(int j=0;j<VISsl60->size();j++){
     VIS1+= VISsl60->at(j);
  }
  hsyvis60->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[2] = hsx60->GetMean();
 exs[2]= hsx60->GetRMS();
//punto y del graph final con su error
ys[2]= hsy60->GetMean();
eys[2]= hsy60->GetRMS();

ysvis[2]=hsyvis60->GetMean();
eyhvis[2]=hsyvis60->GetRMS();

cout<<xs[2]<<" "<<ys[2]<<endl;
/////////////////////////////
TH1F*hsx80=new TH1F("hsx80", "", 100,0,300);
TH1F*hsy80=new TH1F("hsy80", "", 100,0,10000000);
TH1F*hsyvis80=new TH1F("hsyvis80", "", 100,0,10000000);
for(int i=0;i<entriess80;i++) //50 veces
{
  trees80->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss80->size();j++){
    //X = Xs20->at(j);
    hsx80->Fill(Xss80->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl80->size();j++){
    //X = Xs20->at(j);
    hsx80->Fill(Xsl80->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;


  //fotones detectados en los coated
  for(int j=0;j<VUVss80->size();j++){
     VUV+= VUVss80->at(j);
  }
  for(int j=0;j<VUVsl80->size();j++){
     VUV1+= VUVsl80->at(j);
  }
  hsy80->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss80->size();j++){
     VIS+= VISss80->at(j);
  }
  for(int j=0;j<VISsl80->size();j++){
     VIS1+= VISsl80->at(j);
  }
  hsyvis80->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[3] = hsx80->GetMean();
 exs[3]= hsx80->GetRMS();
//punto y del graph final con su error
ys[3]= hsy80->GetMean();
eys[3]= hsy80->GetRMS();

ysvis[3]=hsyvis80->GetMean();
eyhvis[3]=hsyvis80->GetRMS();

cout<<xs[3]<<" "<<ys[3]<<endl;
/////////////////////////////
TH1F*hsx100=new TH1F("hsx100", "", 100,0,300);
TH1F*hsy100=new TH1F("hsy100", "", 100,0,10000000);
TH1F*hsyvis100=new TH1F("hsyvis100", "", 100,0,10000000);
for(int i=0;i<entriess100;i++) //50 veces
{
  trees100->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss100->size();j++){
    //X = Xs20->at(j);
    hsx100->Fill(Xss100->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl100->size();j++){
    //X = Xs20->at(j);
    hsx100->Fill(Xsl100->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVss100->size();j++){
     VUV+= VUVss100->at(j);
  }
  for(int j=0;j<VUVsl100->size();j++){
     VUV1+= VUVsl100->at(j);
  }
  hsy100->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss100->size();j++){
     VIS+= VISss100->at(j);
  }
  for(int j=0;j<VISsl100->size();j++){
     VIS1+= VISsl100->at(j);
  }
  hsyvis100->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[4] = hsx100->GetMean();
 exs[4]= hsx100->GetRMS();
//punto y del graph final con su error
ys[4]= hsy100->GetMean();
eys[4]= hsy100->GetRMS();

ysvis[4]=hsyvis100->GetMean();
eyhvis[4]=hsyvis100->GetRMS();

cout<<xs[4]<<" "<<ys[4]<<endl;

/////////////////////////////
TH1F*hsx120=new TH1F("hsx120", "", 100,0,300);
TH1F*hsy120=new TH1F("hsy120", "", 100,0,10000000);
TH1F*hsyvis120=new TH1F("hsyvis120", "", 100,0,10000000);
for(int i=0;i<entriess120;i++) //50 veces
{
  trees120->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss120->size();j++){
    //X = Xs20->at(j);
    hsx120->Fill(Xss120->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl120->size();j++){
    //X = Xs20->at(j);
    hsx120->Fill(Xsl120->at(j)); //llena todas las x de los 50 muones
  }

  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;


  //fotones detectados en los coated
  for(int j=0;j<VUVss120->size();j++){
     VUV+= VUVss120->at(j);
  }
  for(int j=0;j<VUVsl120->size();j++){
     VUV1+= VUVsl120->at(j);
  }
  hsy120->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss120->size();j++){
     VIS+= VISss120->at(j);
  }
  for(int j=0;j<VISsl120->size();j++){
     VIS1+= VISsl120->at(j);
  }
  hsyvis120->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[5] = hsx120->GetMean();
 exs[5]= hsx120->GetRMS();
//punto y del graph final con su error
ys[5]= hsy120->GetMean();
eys[5]= hsy120->GetRMS();

ysvis[5]=hsyvis120->GetMean();
eyhvis[5]=hsyvis120->GetRMS();

cout<<xs[5]<<" "<<ys[5]<<endl;
/////////////////////////////
TH1F*hsx140=new TH1F("hsx140", "", 100,0,300);
TH1F*hsy140=new TH1F("hsy140", "", 100,0,10000000);
TH1F*hsyvis140=new TH1F("hsyvis140", "", 100,0,10000000);
for(int i=0;i<entriess140;i++) //50 veces
{
  trees140->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss140->size();j++){
    //X = Xs20->at(j);
    hsx140->Fill(Xss140->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl140->size();j++){
    //X = Xs20->at(j);
    hsx140->Fill(Xsl140->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;


  //fotones detectados en los coated
  for(int j=0;j<VUVss140->size();j++){
     VUV+= VUVss140->at(j);
  }
  for(int j=0;j<VUVsl140->size();j++){
     VUV1+= VUVsl140->at(j);
  }
  hsy140->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss140->size();j++){
     VIS+= VISss140->at(j);
  }
  for(int j=0;j<VISsl140->size();j++){
     VIS1+= VISsl140->at(j);
  }
  hsyvis140->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[6] = hsx140->GetMean();
 exs[6]= hsx140->GetRMS();
//punto y del graph final con su error
ys[6]= hsy140->GetMean();
eys[6]= hsy140->GetRMS();

ysvis[6]=hsyvis140->GetMean();
eyhvis[6]=hsyvis140->GetRMS();

cout<<xs[6]<<" "<<ys[6]<<endl;

/////////////////////////////
TH1F*hsx160=new TH1F("hsx160", "", 100,0,300);
TH1F*hsy160=new TH1F("hsy160", "", 100,0,10000000);
TH1F*hsyvis160=new TH1F("hsyvis160", "", 100,0,10000000);
for(int i=0;i<entriess160;i++) //50 veces
{
  trees160->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss160->size();j++){
    //X = Xs20->at(j);
    hsx160->Fill(Xss160->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl160->size();j++){
    //X = Xs20->at(j);
    hsx160->Fill(Xsl160->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVss160->size();j++){
     VUV+= VUVss160->at(j);
  }
  for(int j=0;j<VUVsl160->size();j++){
     VUV1+= VUVsl160->at(j);
  }
  hsy160->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss160->size();j++){
     VIS+= VISss160->at(j);
  }
  for(int j=0;j<VISsl160->size();j++){
     VIS1+= VISsl160->at(j);
  }
  hsyvis160->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[7] = hsx160->GetMean();
 exs[7]= hsx160->GetRMS();
//punto y del graph final con su error
ys[7]= hsy160->GetMean();
eys[7]= hsy160->GetRMS();

ysvis[7]=hsyvis160->GetMean();
eyhvis[7]=hsyvis160->GetRMS();

cout<<xs[7]<<" "<<ys[7]<<endl;
/////////////////////////////
TH1F*hsx175=new TH1F("hsx175", "", 100,0,300);
TH1F*hsy175=new TH1F("hsy175", "", 100,0,10000000);
TH1F*hsyvis175=new TH1F("hsyvis175", "", 100,0,10000000);
for(int i=0;i<entriess175;i++) //50 veces
{
  trees175->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss175->size();j++){
    //X = Xs20->at(j);
    hsx175->Fill(Xss175->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl175->size();j++){
    //X = Xs20->at(j);
    hsx175->Fill(Xsl175->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;


  //fotones detectados en los coated
  for(int j=0;j<VUVss175->size();j++){
     VUV+= VUVss175->at(j);
  }
  for(int j=0;j<VUVsl175->size();j++){
     VUV1+= VUVsl175->at(j);
  }
  hsy175->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss175->size();j++){
     VIS+= VISss175->at(j);
  }
  for(int j=0;j<VISsl175->size();j++){
     VIS1+= VISsl175->at(j);
  }
  hsyvis175->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[8] = hsx175->GetMean();
 exs[8]= hsx175->GetRMS();
//punto y del graph final con su error
ys[8]= hsy175->GetMean();
eys[8]= hsy175->GetRMS();

ysvis[8]=hsyvis175->GetMean();
eyhvis[8]=hsyvis175->GetRMS();

cout<<xs[8]<<" "<<ys[8]<<endl;
/////////////////////////////
TH1F*hsx185=new TH1F("hsx185", "", 100,0,300);
TH1F*hsy185=new TH1F("hsy185", "", 100,0,10000000);
TH1F*hsyvis185=new TH1F("hsyvis185", "", 100,0,10000000);
for(int i=0;i<entriess185;i++) //50 veces
{
  trees185->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss185->size();j++){
    //X = Xs20->at(j);
    hsx185->Fill(Xss185->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl185->size();j++){
    //X = Xs20->at(j);
    hsx185->Fill(Xsl185->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;


  //fotones detectados en los coated
  for(int j=0;j<VUVss185->size();j++){
     VUV+= VUVss185->at(j);
  }
  for(int j=0;j<VUVsl185->size();j++){
     VUV1+= VUVsl185->at(j);
  }
  hsy185->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss185->size();j++){
     VIS+= VISss185->at(j);
  }
  for(int j=0;j<VISsl185->size();j++){
     VIS1+= VISsl185->at(j);
  }
  hsyvis185->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[9] = hsx185->GetMean();
 exs[9]= hsx185->GetRMS();
//punto y del graph final con su error
ys[9]= hsy185->GetMean();
eys[9]= hsy185->GetRMS();

ysvis[9]=hsyvis185->GetMean();
eyhvis[9]=hsyvis185->GetRMS();

cout<<xs[9]<<" "<<ys[9]<<endl;
/////////////////////////////
TH1F*hsx195=new TH1F("hsx195", "", 100,0,300);
TH1F*hsy195=new TH1F("hsy195", "", 100,0,10000000);
TH1F*hsyvis195=new TH1F("hsyvis195", "", 100,0,10000000);
for(int i=0;i<entriess195;i++) //50 veces
{
  trees195->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss195->size();j++){
    //X = Xs20->at(j);
    hsx195->Fill(Xss195->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl195->size();j++){
    //X = Xs20->at(j);
    hsx195->Fill(Xsl195->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVss195->size();j++){
     VUV+= VUVss195->at(j);
  }
  for(int j=0;j<VUVsl195->size();j++){
     VUV1+= VUVsl195->at(j);
  }
  hsy195->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss195->size();j++){
     VIS+= VISss195->at(j);
  }
  for(int j=0;j<VISsl195->size();j++){
     VIS1+= VISsl195->at(j);
  }
  hsyvis195->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[10] = hsx195->GetMean();
 exs[10]= hsx195->GetRMS();
//punto y del graph final con su error
ys[10]= hsy195->GetMean();
eys[10]= hsy195->GetRMS();

ysvis[10]=hsyvis195->GetMean();
eyhvis[10]=hsyvis195->GetRMS();

cout<<xs[10]<<" "<<ys[10]<<endl;
/////////////////////////////
TH1F*hsx204=new TH1F("hsx204", "", 100,0,300);
TH1F*hsy204=new TH1F("hsy204", "", 100,0,10000000);
TH1F*hsyvis204=new TH1F("hsyvis204", "", 100,0,10000000);
for(int i=0;i<entriess204;i++) //50 veces
{
  trees204->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss204->size();j++){
    //X = Xs20->at(j);
    hsx204->Fill(Xss204->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl204->size();j++){
    //X = Xs20->at(j);
    hsx204->Fill(Xsl204->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;


  //fotones detectados en los coated
  for(int j=0;j<VUVss204->size();j++){
     VUV+= VUVss204->at(j);
  }
  for(int j=0;j<VUVsl204->size();j++){
     VUV1+= VUVsl204->at(j);
  }
  hsy204->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss204->size();j++){
     VIS+= VISss204->at(j);
  }
  for(int j=0;j<VISsl204->size();j++){
     VIS1+= VISsl204->at(j);
  }
  hsyvis204->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[11] = hsx204->GetMean();
 exs[11]= hsx204->GetRMS();
//punto y del graph final con su error
ys[11]= hsy204->GetMean();
eys[11]= hsy204->GetRMS();

ysvis[11]=hsyvis204->GetMean();
eyhvis[11]=hsyvis204->GetRMS();

cout<<xs[11]<<" "<<ys[11]<<endl;

/////////////////////////////
TH1F*hsx212=new TH1F("hsx212", "", 100,0,300);
TH1F*hsy212=new TH1F("hsy212", "", 100,0,10000000);
TH1F*hsyvis212=new TH1F("hsyvis212", "", 100,0,10000000);
for(int i=0;i<entriess212;i++) //50 veces
{
  trees212->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss212->size();j++){
    //X = Xs20->at(j);
    hsx212->Fill(Xss212->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl212->size();j++){
    //X = Xs20->at(j);
    hsx212->Fill(Xsl212->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;


  //fotones detectados en los coated
  for(int j=0;j<VUVss212->size();j++){
     VUV+= VUVss212->at(j);
  }
  for(int j=0;j<VUVsl212->size();j++){
     VUV1+= VUVsl212->at(j);
  }
  hsy212->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss212->size();j++){
     VIS+= VISss212->at(j);
  }
  for(int j=0;j<VISsl212->size();j++){
     VIS1+= VISsl212->at(j);
  }
  hsyvis212->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[12] = hsx212->GetMean();
 exs[12]= hsx212->GetRMS();
//punto y del graph final con su error
ys[12]= hsy212->GetMean();
eys[12]= hsy212->GetRMS();

ysvis[12]=hsyvis212->GetMean();
eyhvis[12]=hsyvis212->GetRMS();

cout<<xs[12]<<" "<<ys[12]<<endl;

/////////////////////////////
TH1F*hsx220=new TH1F("hsx220", "", 100,0,300);
TH1F*hsy220=new TH1F("hsy220", "", 100,0,10000000);
TH1F*hsyvis220=new TH1F("hsyvis220", "", 100,0,10000000);
for(int i=0;i<entriess220;i++) //50 veces
{
  trees220->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss220->size();j++){
    //X = Xs20->at(j);
    hsx220->Fill(Xss220->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl220->size();j++){
    //X = Xs20->at(j);
    hsx220->Fill(Xsl220->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVss220->size();j++){
     VUV+= VUVss220->at(j);
  }
  for(int j=0;j<VUVsl220->size();j++){
     VUV1+= VUVsl220->at(j);
  }
  hsy220->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss220->size();j++){
     VIS+= VISss220->at(j);
  }
  for(int j=0;j<VISsl220->size();j++){
     VIS1+= VISsl220->at(j);
  }
  hsyvis220->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[13] = hsx220->GetMean();
 exs[13]= hsx220->GetRMS();
//punto y del graph final con su error
ys[13]= hsy220->GetMean();
eys[13]= hsy220->GetRMS();

ysvis[13]=hsyvis220->GetMean();
eyhvis[13]=hsyvis220->GetRMS();

cout<<xs[13]<<" "<<ys[13]<<endl;

/////////////////////////////
TH1F*hsx228=new TH1F("hsx228", "", 100,0,300);
TH1F*hsy228=new TH1F("hsy228", "", 100,0,10000000);
TH1F*hsyvis228=new TH1F("hsyvis228", "", 100,0,10000000);
for(int i=0;i<entriess228;i++) //50 veces
{
  trees228->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss228->size();j++){
    //X = Xs20->at(j);
    hsx228->Fill(Xss228->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl228->size();j++){
    //X = Xs20->at(j);
    hsx228->Fill(Xsl228->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVss228->size();j++){
     VUV+= VUVss228->at(j);
  }
  for(int j=0;j<VUVsl228->size();j++){
     VUV1+= VUVsl228->at(j);
  }
  hsy228->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss228->size();j++){
     VIS+= VISss228->at(j);
  }
  for(int j=0;j<VISsl228->size();j++){
     VIS1+= VISsl228->at(j);
  }
  hsyvis228->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[14] = hsx228->GetMean();
 exs[14]= hsx228->GetRMS();
//punto y del graph final con su error
ys[14]= hsy228->GetMean();
eys[14]= hsy228->GetRMS();

ysvis[14]=hsyvis228->GetMean();
eyhvis[14]=hsyvis228->GetRMS();

cout<<xs[14]<<" "<<ys[14]<<endl;

/////////////////////////////
TH1F*hsx236=new TH1F("hsx236", "", 100,0,300);
TH1F*hsy236=new TH1F("hsy236", "", 100,0,10000000);
TH1F*hsyvis236=new TH1F("hsyvis236", "", 100,0,10000000);
for(int i=0;i<entriess236;i++) //50 veces
{
  trees236->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss236->size();j++){
    //X = Xs20->at(j);
    hsx236->Fill(Xss236->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl236->size();j++){
    //X = Xs20->at(j);
    hsx236->Fill(Xsl236->at(j)); //llena todas las x de los 50 muones
  }

  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVss236->size();j++){
     VUV+= VUVss236->at(j);
  }
  for(int j=0;j<VUVsl236->size();j++){
     VUV1+= VUVsl236->at(j);
  }
  hsy236->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss236->size();j++){
     VIS+= VISss236->at(j);
  }
  for(int j=0;j<VISsl236->size();j++){
     VIS1+= VISsl236->at(j);
  }
  hsyvis236->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[15] = hsx236->GetMean();
 exs[15]= hsx236->GetRMS();
//punto y del graph final con su error
ys[15]= hsy236->GetMean();
eys[15]= hsy236->GetRMS();

ysvis[15]=hsyvis236->GetMean();
eyhvis[15]=hsyvis236->GetRMS();

cout<<xs[15]<<" "<<ys[15]<<endl;
/////////////////////////////

TH1F*hsx244=new TH1F("hsx244", "", 100,0,300);
TH1F*hsy244=new TH1F("hsy244", "", 100,0,10000000);
TH1F*hsyvis244=new TH1F("hsyvis244", "", 100,0,10000000);
for(int i=0;i<entriess244;i++) //50 veces
{
  trees244->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss244->size();j++){
    //X = Xs20->at(j);
    hsx244->Fill(Xss244->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl244->size();j++){
    //X = Xs20->at(j);
    hsx244->Fill(Xsl244->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVss244->size();j++){
     VUV+= VUVss244->at(j);
  }
  for(int j=0;j<VUVsl244->size();j++){
     VUV1+= VUVsl244->at(j);
  }
  hsy244->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss244->size();j++){
     VIS+= VISss244->at(j);
  }
  for(int j=0;j<VISsl244->size();j++){
     VIS1+= VISsl244->at(j);
  }
  hsyvis244->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[16] = hsx244->GetMean();
 exs[16]= hsx244->GetRMS();
//punto y del graph final con su error
ys[16]= hsy244->GetMean();
eys[16]= hsy244->GetRMS();

ysvis[16]=hsyvis244->GetMean();
eyhvis[16]=hsyvis244->GetRMS();

cout<<xs[16]<<" "<<ys[16]<<endl;

/////////////////////////////

TH1F*hsx252=new TH1F("hsx252", "", 100,0,300);
TH1F*hsy252=new TH1F("hsy252", "", 100,0,10000000);
TH1F*hsyvis252=new TH1F("hsyvis252", "", 100,0,10000000);
for(int i=0;i<entriess252;i++) //50 veces
{
  trees252->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xss252->size();j++){
    //X = Xs20->at(j);
    hsx252->Fill(Xss252->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xsl252->size();j++){
    //X = Xs20->at(j);
    hsx252->Fill(Xsl252->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVss252->size();j++){
     VUV+= VUVss252->at(j);
  }
  for(int j=0;j<VUVsl252->size();j++){
     VUV1+= VUVsl252->at(j);
  }
  hsy252->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VISss252->size();j++){
     VIS+= VISss252->at(j);
  }
  for(int j=0;j<VISsl252->size();j++){
     VIS1+= VISsl252->at(j);
  }
  hsyvis252->Fill((VIS+VIS1)*0.03);
}

// punto x del graph final con su error
 xs[17] = hsx252->GetMean();
 exs[17]= hsx252->GetRMS();
//punto y del graph final con su error
ys[17]= hsy252->GetMean();
eys[17]= hsy252->GetRMS();

ysvis[17]=hsyvis252->GetMean();
eyhvis[17]=hsyvis252->GetRMS();

cout<<xs[17]<<" "<<ys[17]<<endl;




///////////////////////////////////////

//Hibrido usando UseModLarqlRecomb=false//////////////////////////////////////////////////////////////////////////////////////////
cout<<"-----Hibrido usando UseModLarqlRecomb=false-----"<<endl;
TH1F*hhx20=new TH1F("hhx20", "", 100,0,300);
TH1F*hhy20=new TH1F("hhy20", "", 100,0,10000000);
TH1F*hhyvis20=new TH1F("hhyvis20", "", 100,0,10000000);
for(int i=0;i<entriesh20;i++) //50 veces
{
  treeh20->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs20->size();j++){
    //X = Xs20->at(j);
    hhx20->Fill(Xhs20->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl20->size();j++){
    //X = Xs20->at(j);
    hhx20->Fill(Xhl20->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVhs20->size();j++){
     VUV+= VUVhs20->at(j);
  }
  for(int j=0;j<VUVhl20->size();j++){
     VUV1+= VUVhl20->at(j);
  }
  hhy20->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs20->size();j++){
     VIS+= VIShs20->at(j);
  }
  for(int j=0;j<VIShl20->size();j++){
     VIS1+= VIShl20->at(j);
  }
  hhyvis20->Fill((VIS+VIS1)*0.03);
}

// punto x del hist final
xh[0] = hhx20->GetMean();
exh[0]= hhx20->GetRMS();
//punto y del hist final
yh[0]= hhy20->GetMean();
eyh[0]= hhy20->GetRMS();

yhvis[0]=hhyvis20->GetMean();
eyhvis[0]=hhyvis20->GetRMS();

cout<<xh[0]<<" "<<yh[0]<<endl;
//hhy20->Draw("");

//////////////////////////////////////////////////

TH1F*hhx40=new TH1F("hhx40", "", 100,0,300);
TH1F*hhy40=new TH1F("hhy40", "", 100,0,10000000);
TH1F*hhyvis40=new TH1F("hhyvis40", "", 100,0,10000000);
for(int i=0;i<entriesh40;i++) //50 veces
{
  treeh40->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs40->size();j++){
    //X = Xs20->at(j);
    hhx40->Fill(Xhs40->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl40->size();j++){
    //X = Xs20->at(j);
    hhx40->Fill(Xhl40->at(j)); //llena todas las x de los 50 muones
  }



  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVhs40->size();j++){
     VUV+= VUVhs40->at(j);
  }
  for(int j=0;j<VUVhl40->size();j++){
     VUV1+= VUVhl40->at(j);
  }
  hhy40->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs40->size();j++){
     VIS+= VIShs40->at(j);
  }
  for(int j=0;j<VIShl40->size();j++){
     VIS1+= VIShl40->at(j);
  }
  hhyvis40->Fill((VIS+VIS1)*0.03);
}

// punto x del hist final
xh[1] = hhx40->GetMean();
exh[1]= hhx40->GetRMS();
//punto y del hist final
yh[1]= hhy40->GetMean();
eyh[1]= hhy40->GetRMS();

yhvis[1]=hhyvis40->GetMean();
eyhvis[1]=hhyvis40->GetRMS();

cout<<xh[1]<<" "<<yh[1]<<endl;

///////////////////////////////////////////////

TH1F*hhx60=new TH1F("hhx60", "", 100,0,300);
TH1F*hhy60=new TH1F("hhy60", "", 100,0,10000000);
TH1F*hhyvis60=new TH1F("hhyvis60", "", 100,0,10000000);
for(int i=0;i<entriesh60;i++) //50 veces
{
  treeh60->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs60->size();j++){
    //X = Xs20->at(j);
    hhx60->Fill(Xhs60->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl60->size();j++){
    //X = Xs20->at(j);
    hhx60->Fill(Xhl60->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVhs60->size();j++){
     VUV+= VUVhs60->at(j);
  }
  for(int j=0;j<VUVhl60->size();j++){
     VUV1+= VUVhl60->at(j);
  }
  hhy60->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs60->size();j++){
     VIS+= VIShs60->at(j);
  }
  for(int j=0;j<VIShl60->size();j++){
     VIS1+= VIShl60->at(j);
  }
  hhyvis60->Fill((VIS+VIS1)*0.03);
}

// punto x del hist final
xh[2] = hhx60->GetMean();
exh[2]= hhx60->GetRMS();
//punto y del hist final
yh[2]= hhy60->GetMean();
eyh[2]= hhy60->GetRMS();

yhvis[2]=hhyvis60->GetMean();
eyhvis[2]=hhyvis60->GetRMS();

cout<<xh[2]<<" "<<yh[2]<<endl;

/////////////////////////////////////////////////////////////

TH1F*hhx80=new TH1F("hhx80", "", 100,0,300);
TH1F*hhy80=new TH1F("hhy80", "", 100,0,10000000);
TH1F*hhyvis80=new TH1F("hhyvis80", "", 100,0,10000000);
for(int i=0;i<entriesh80;i++) //50 veces
{
  treeh80->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs80->size();j++){
    //X = Xs20->at(j);
    hhx80->Fill(Xhs80->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl80->size();j++){
    //X = Xs20->at(j);
    hhx80->Fill(Xhl80->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVhs80->size();j++){
     VUV+= VUVhs80->at(j);
  }
  for(int j=0;j<VUVhl80->size();j++){
     VUV1+= VUVhl80->at(j);
  }
  hhy80->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs80->size();j++){
     VIS+= VIShs80->at(j);
  }
  for(int j=0;j<VIShl80->size();j++){
     VIS1+= VIShl80->at(j);
  }
  hhyvis80->Fill((VIS+VIS1)*0.03);
}

// punto x del hist final
xh[3] = hhx80->GetMean();
exh[3]= hhx80->GetRMS();
//punto y del hist final
yh[3]= hhy80->GetMean();
eyh[3]= hhy80->GetRMS();

yhvis[3]=hhyvis80->GetMean();
eyhvis[3]=hhyvis80->GetRMS();

cout<<xh[3]<<" "<<yh[3]<<endl;

///////////////////////////////////////////////////

TH1F*hhx100=new TH1F("hhx100", "", 100,0,300);
TH1F*hhy100=new TH1F("hhy100", "", 100,0,10000000);
TH1F*hhyvis100=new TH1F("hhyvis100", "", 100,0,10000000);
for(int i=0;i<entriesh100;i++) //50 veces
{
  treeh100->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs100->size();j++){
    //X = Xs20->at(j);
    hhx100->Fill(Xhs100->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl100->size();j++){
    //X = Xs20->at(j);
    hhx100->Fill(Xhl100->at(j)); //llena todas las x de los 50 muones
  }

  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVhs100->size();j++){
     VUV+= VUVhs100->at(j);
  }
  for(int j=0;j<VUVhl100->size();j++){
     VUV1+= VUVhl100->at(j);
  }
  hhy100->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs100->size();j++){
     VIS+= VIShs100->at(j);
  }
  for(int j=0;j<VIShl100->size();j++){
     VIS1+= VIShl100->at(j);
  }
    hhyvis100->Fill((VIS+VIS1)*0.03);
}

// punto x del hist final
xh[4] = hhx100->GetMean();
exh[4]= hhx100->GetRMS();
//punto y del hist final
yh[4]= hhy100->GetMean();
eyh[4]= hhy100->GetRMS();

yhvis[4]=hhyvis100->GetMean();
eyhvis[4]=hhyvis100->GetRMS();

cout<<xh[4]<<" "<<yh[4]<<endl;


/////////////////////////////////////////////////////

TH1F*hhx120=new TH1F("hhx120", "", 100,0,300);
TH1F*hhy120=new TH1F("hhy120", "", 100,0,10000000);
TH1F*hhyvis120=new TH1F("hhyvis120", "", 100,0,10000000);
for(int i=0;i<entriesh120;i++) //50 veces
{
  treeh120->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs120->size();j++){
    //X = Xs20->at(j);
    hhx120->Fill(Xhs120->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl120->size();j++){
    //X = Xs20->at(j);
    hhx120->Fill(Xhl120->at(j)); //llena todas las x de los 50 muones
  }

  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVhs120->size();j++){
     VUV+= VUVhs120->at(j);
  }
  for(int j=0;j<VUVhl120->size();j++){
     VUV1+= VUVhl120->at(j);
  }
  hhy120->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs120->size();j++){
     VIS+= VIShs120->at(j);
  }
  for(int j=0;j<VIShl120->size();j++){
     VIS1+= VIShl120->at(j);
  }
  hhyvis120->Fill((VIS+VIS1)*0.03);
}

// punto x del hist final
xh[5] = hhx120->GetMean();
exh[5]= hhx120->GetRMS();
//punto y del hist final
yh[5]= hhy120->GetMean();
eyh[5]= hhy120->GetRMS();

yhvis[5]=hhyvis120->GetMean();
eyhvis[5]=hhyvis120->GetRMS();

cout<<xh[5]<<" "<<yh[5]<<endl;


///////////////////////////////////////////////////////

TH1F*hhx140=new TH1F("hhx140", "", 100,0,300);
TH1F*hhy140=new TH1F("hhy140", "", 100,0,10000000);
TH1F*hhyvis140=new TH1F("hhyvis140", "", 100,0,10000000);
for(int i=0;i<entriesh140;i++) //50 veces
{
  treeh140->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs140->size();j++){
    //X = Xs20->at(j);
    hhx140->Fill(Xhs140->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl140->size();j++){
    //X = Xs20->at(j);
    hhx140->Fill(Xhl140->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;


  //fotones detectados en los coated
  for(int j=0;j<VUVhs140->size();j++){
     VUV+= VUVhs140->at(j);
  }
  for(int j=0;j<VUVhl140->size();j++){
     VUV1+= VUVhl140->at(j);
  }
  hhy140->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs140->size();j++){
     VIS+= VIShs140->at(j);
  }
  for(int j=0;j<VIShl140->size();j++){
     VIS1+= VIShl140->at(j);
  }
  hhyvis140->Fill((VIS+VIS1)*0.03);
}

// punto x del hist final
xh[6] = hhx140->GetMean();
exh[6]= hhx140->GetRMS();
//punto y del hist final
yh[6]= hhy140->GetMean();
eyh[6]= hhy140->GetRMS();

yhvis[6]=hhyvis140->GetMean();
eyhvis[6]=hhyvis140->GetRMS();

cout<<xh[6]<<" "<<yh[6]<<endl;

////////////////////////////////////////////////////////////


TH1F*hhx160=new TH1F("hhx160", "", 100,0,300);
TH1F*hhy160=new TH1F("hhy160", "", 100,0,10000000);
TH1F*hhyvis160=new TH1F("hhyvis160", "", 100,0,10000000);
for(int i=0;i<entriesh160;i++) //50 veces
{
  treeh160->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs160->size();j++){
    //X = Xs20->at(j);
    hhx160->Fill(Xhs160->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl160->size();j++){
    //X = Xs20->at(j);
    hhx160->Fill(Xhl160->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;


  //fotones detectados en los coated
  for(int j=0;j<VUVhs160->size();j++){
     VUV+= VUVhs160->at(j);
  }
  for(int j=0;j<VUVhl160->size();j++){
     VUV1+= VUVhl160->at(j);
  }
  hhy160->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs160->size();j++){
     VIS+= VIShs160->at(j);
  }
  for(int j=0;j<VIShl160->size();j++){
     VIS1+= VIShl160->at(j);
  }
  hhyvis160->Fill((VIS+VIS1)*0.03);

}

// punto x del hist final
xh[7] = hhx160->GetMean();
exh[7]= hhx160->GetRMS();
//punto y del hist final
yh[7]= hhy160->GetMean();
eyh[7]= hhy160->GetRMS();

yhvis[7]=hhyvis160->GetMean();
eyhvis[7]=hhyvis160->GetRMS();

cout<<xh[7]<<" "<<yh[7]<<endl;


/////////////////////////////////////////////////////////


TH1F*hhx175=new TH1F("hhx175", "", 100,0,300);
TH1F*hhy175=new TH1F("hhy175", "", 100,0,10000000);
TH1F*hhyvis175=new TH1F("hhyvis175", "", 100,0,10000000);
for(int i=0;i<entriesh175;i++) //50 veces
{
  treeh175->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs175->size();j++){
    //X = Xs20->at(j);
    hhx175->Fill(Xhs175->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl175->size();j++){
    //X = Xs20->at(j);
    hhx175->Fill(Xhl175->at(j)); //llena todas las x de los 50 muones
  }

  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVhs175->size();j++){
     VUV+= VUVhs175->at(j);
  }
  for(int j=0;j<VUVhl175->size();j++){
     VUV1+= VUVhl175->at(j);
  }
  hhy175->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs175->size();j++){
     VIS+= VIShs175->at(j);
  }
  for(int j=0;j<VIShl175->size();j++){
     VIS1+= VIShl175->at(j);
  }
  hhyvis175->Fill((VIS+VIS1)*0.03);

}

// punto x del hist final
xh[8] = hhx175->GetMean();
exh[8]= hhx175->GetRMS();
//punto y del hist final
yh[8]= hhy175->GetMean();
eyh[8]= hhy175->GetRMS();

yhvis[8]=hhyvis175->GetMean();
eyhvis[8]=hhyvis175->GetRMS();

cout<<xh[8]<<" "<<yh[8]<<endl;
/////////////////////////////////////////////////////////


TH1F*hhx185=new TH1F("hhx185", "", 100,0,300);
TH1F*hhy185=new TH1F("hhy185", "", 100,0,10000000);
TH1F*hhyvis185=new TH1F("hhyvis185", "", 100,0,10000000);
for(int i=0;i<entriesh185;i++) //50 veces
{
  treeh185->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs185->size();j++){
    //X = Xs20->at(j);
    hhx185->Fill(Xhs185->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl185->size();j++){
    //X = Xs20->at(j);
    hhx185->Fill(Xhl185->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVhs185->size();j++){
     VUV+= VUVhs185->at(j);
  }
  for(int j=0;j<VUVhl185->size();j++){
     VUV1+= VUVhl185->at(j);
  }
  hhy185->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs185->size();j++){
     VIS+= VIShs185->at(j);
  }
  for(int j=0;j<VIShl185->size();j++){
     VIS+= VIShl185->at(j);
  }
  hhyvis185->Fill((VIS+VIS1)*0.03);

}

// punto x del hist final
xh[9] = hhx185->GetMean();
exh[9]= hhx185->GetRMS();
//punto y del hist final
yh[9]= hhy185->GetMean();
eyh[9]= hhy185->GetRMS();

yhvis[9]=hhyvis185->GetMean();
eyhvis[9]=hhyvis185->GetRMS();

cout<<xh[9]<<" "<<yh[9]<<endl;
/////////////////////////////////////////////////////////


TH1F*hhx195=new TH1F("hhx195", "", 100,0,300);
TH1F*hhy195=new TH1F("hhy195", "", 100,0,10000000);
TH1F*hhyvis195=new TH1F("hhyvis195", "", 100,0,10000000);
for(int i=0;i<entriesh195;i++) //50 veces
{
  treeh195->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs195->size();j++){
    //X = Xs20->at(j);
    hhx195->Fill(Xhs195->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl195->size();j++){
    //X = Xs20->at(j);
    hhx195->Fill(Xhl195->at(j)); //llena todas las x de los 50 muones
  }

  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVhs195->size();j++){
     VUV+= VUVhs195->at(j);
  }
  for(int j=0;j<VUVhl195->size();j++){
     VUV1+= VUVhl195->at(j);
  }
  hhy195->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs195->size();j++){
     VIS+= VIShs195->at(j);
  }
  for(int j=0;j<VIShl195->size();j++){
     VIS1+= VIShl195->at(j);
  }
  hhyvis195->Fill((VIS+VIS1)*0.03);

}

// punto x del hist final
xh[10] = hhx195->GetMean();
exh[10]= hhx195->GetRMS();
//punto y del hist final
yh[10]= hhy195->GetMean();
eyh[10]= hhy195->GetRMS();

yhvis[10]=hhyvis195->GetMean();
eyhvis[10]=hhyvis195->GetRMS();

cout<<xh[10]<<" "<<yh[10]<<endl;
/////////////////////////////////////////////////////////


TH1F*hhx204=new TH1F("hhx204", "", 100,0,300);
TH1F*hhy204=new TH1F("hhy204", "", 100,0,10000000);
TH1F*hhyvis204=new TH1F("hhyvis204", "", 100,0,10000000);
for(int i=0;i<entriesh204;i++) //50 veces
{
  treeh204->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs204->size();j++){
    //X = Xs20->at(j);
    hhx204->Fill(Xhs204->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl204->size();j++){
    //X = Xs20->at(j);
    hhx204->Fill(Xhl204->at(j)); //llena todas las x de los 50 muones
  }

  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;


  //fotones detectados en los coated
  for(int j=0;j<VUVhs204->size();j++){
     VUV+= VUVhs204->at(j);
  }
  for(int j=0;j<VUVhl204->size();j++){
     VUV1+= VUVhl204->at(j);
  }
  hhy204->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs204->size();j++){
     VIS+= VIShs204->at(j);
  }
  for(int j=0;j<VIShl204->size();j++){
     VIS1+= VIShl204->at(j);
  }
  hhyvis204->Fill((VIS+VIS1)*0.03);

}

// punto x del hist final
xh[11] = hhx204->GetMean();
exh[11]= hhx204->GetRMS();
//punto y del hist final
yh[11]= hhy204->GetMean();
eyh[11]= hhy204->GetRMS();

yhvis[11]=hhyvis204->GetMean();
eyhvis[11]=hhyvis204->GetRMS();

cout<<xh[11]<<" "<<yh[11]<<endl;


///////////////////////////////////////////////////////


TH1F*hhx212=new TH1F("hhx212", "", 100,0,300);
TH1F*hhy212=new TH1F("hhy212", "", 100,0,10000000);
TH1F*hhyvis212=new TH1F("hhyvis212", "", 100,0,10000000);
for(int i=0;i<entriesh212;i++) //50 veces
{
  treeh212->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs212->size();j++){
    //X = Xs20->at(j);
    hhx212->Fill(Xhs212->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl212->size();j++){
    //X = Xs20->at(j);
    hhx212->Fill(Xhl212->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVhs212->size();j++){
     VUV+= VUVhs212->at(j);
  }
  for(int j=0;j<VUVhl212->size();j++){
     VUV1+= VUVhl212->at(j);
  }
  hhy212->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs212->size();j++){
     VIS+= VIShs212->at(j);
  }
  for(int j=0;j<VIShl212->size();j++){
     VIS1+= VIShl212->at(j);
  }
  hhyvis212->Fill((VIS+VIS1)*0.03);

}

// punto x del hist final
xh[12]= hhx212->GetMean();
exh[12]= hhx212->GetRMS();
//punto y del hist final
yh[12]= hhy212->GetMean();
eyh[12]= hhy212->GetRMS();

yhvis[12]=hhyvis212->GetMean();
eyhvis[12]=hhyvis212->GetRMS();

cout<<xh[12]<<" VUV= "<<yh[12]<<" errory: "<<eyh[12]<<endl;
//hhy220->Draw("");
cout<<xh[12]<<" VIS= "<<yhvis[12]<<endl;




/////////////////////////////////////////////////////////

TH1F*hhx220=new TH1F("hhx220", "", 100,0,300);
TH1F*hhy220=new TH1F("hhy220", "", 100,0,10000000);
TH1F*hhyvis220=new TH1F("hhyvis220", "", 100,0,10000000);
for(int i=0;i<entriesh220;i++) //50 veces
{
  treeh220->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs220->size();j++){
    //X = Xs20->at(j);
    hhx220->Fill(Xhs220->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl220->size();j++){
    //X = Xs20->at(j);
    hhx220->Fill(Xhl220->at(j)); //llena todas las x de los 50 muones
  }

  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVhs220->size();j++){
     VUV+= VUVhs220->at(j);
  }
  for(int j=0;j<VUVhl220->size();j++){
     VUV1+= VUVhl220->at(j);
  }
  hhy220->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs220->size();j++){
     VIS+= VIShs220->at(j);
  }
  for(int j=0;j<VIShl220->size();j++){
     VIS1+= VIShl220->at(j);
  }
  hhyvis220->Fill((VIS+VIS1)*0.03);
}

// punto x del hist final
xh[13] = hhx220->GetMean();
exh[13]= hhx220->GetRMS();
//punto y del hist final
yh[13]= hhy220->GetMean();
eyh[13]= hhy220->GetRMS();

yhvis[13]=hhyvis220->GetMean();
eyhvis[13]=hhyvis220->GetRMS();

cout<<xh[13]<<" VUV= "<<yh[13]<<endl;
cout<<xh[13]<<" VIS= "<<yhvis[13]<<endl;

/////////////////////////////////////////////////////


TH1F*hhx228=new TH1F("hhx228", "", 100,0,300);
TH1F*hhy228=new TH1F("hhy228", "", 100,0,10000000);
TH1F*hhyvis228=new TH1F("hhyvis228", "", 100,0,10000000);
for(int i=0;i<entriesh228;i++) //50 veces
{
  treeh228->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs228->size();j++){
    //X = Xs20->at(j);
    hhx228->Fill(Xhs228->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl228->size();j++){
    //X = Xs20->at(j);
    hhx228->Fill(Xhl228->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVhs228->size();j++){
     VUV+= VUVhs228->at(j);
  }
  for(int j=0;j<VUVhl228->size();j++){
     VUV1+= VUVhl228->at(j);
  }
  hhy228->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs228->size();j++){
     VIS+= VIShs228->at(j);
  }
  for(int j=0;j<VIShl228->size();j++){
     VIS1+= VIShl228->at(j);
  }
  hhyvis228->Fill((VIS+VIS1)*0.03);

}

// punto x del hist final
xh[14]  = hhx228->GetMean();
exh[14] = hhx228->GetRMS();
//punto y del hist final
yh[14] = hhy228->GetMean();
eyh[14] = hhy228->GetRMS();

yhvis[14]=hhyvis228->GetMean();
eyhvis[14]=hhyvis228->GetRMS();

cout<<xh[14]<<" VUV= "<<yh[14]<<endl;
cout<<xh[14]<<" VIS= "<<yhvis[14]<<endl;

//////////////////////////////////////////////////

TH1F*hhx236=new TH1F("hhx236", "", 100,0,300);
TH1F*hhy236=new TH1F("hhy236", "", 100,0,10000000);
TH1F*hhyvis236=new TH1F("hhyvis236", "", 100,0,10000000);
for(int i=0;i<entriesh236;i++) //50 veces
{
  treeh236->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs236->size();j++){
    //X = Xs20->at(j);
    hhx236->Fill(Xhs236->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl236->size();j++){
    //X = Xs20->at(j);
    hhx236->Fill(Xhl236->at(j)); //llena todas las x de los 50 muones
  }

  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVhs236->size();j++){
     VUV+= VUVhs236->at(j);
  }
  for(int j=0;j<VUVhl236->size();j++){
     VUV1+= VUVhl236->at(j);
  }
  hhy236->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs236->size();j++){
     VIS+= VIShs236->at(j);
  }
  for(int j=0;j<VIShl236->size();j++){
     VIS1+= VIShl236->at(j);
  }
  hhyvis236->Fill((VIS+VIS1)*0.03);

}

// punto x del hist final
xh[15] = hhx236->GetMean();
exh[15]= hhx236->GetRMS();
//punto y del hist final
yh[15]= hhy236->GetMean();
eyh[15]= hhy236->GetRMS();

yhvis[15]=hhyvis236->GetMean();
eyhvis[15]=hhyvis236->GetRMS();

cout<<xh[15]<<" VUV= "<<yh[15]<<endl;
cout<<xh[15]<<" VIS= "<<yhvis[15]<<endl;

//////////////////////////////////////////////////

TH1F*hhx244=new TH1F("hhx244", "", 100,0,300);
TH1F*hhy244=new TH1F("hhy244", "", 100,0,10000000);
TH1F*hhyvis244=new TH1F("hhyvis244", "", 100,0,10000000);
for(int i=0;i<entriesh244;i++) //50 veces
{
  treeh244->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs244->size();j++){
    //X = Xs20->at(j);
    hhx244->Fill(Xhs244->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl244->size();j++){
    //X = Xs20->at(j);
    hhx244->Fill(Xhl244->at(j)); //llena todas las x de los 50 muones
  }


  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVhs244->size();j++){
     VUV+= VUVhs244->at(j);
  }
  for(int j=0;j<VUVhl244->size();j++){
     VUV1+= VUVhl244->at(j);
  }
  hhy244->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs244->size();j++){
     VIS+= VIShs244->at(j);
  }
  for(int j=0;j<VIShl244->size();j++){
     VIS1+= VIShl244->at(j);
  }
  hhyvis244->Fill((VIS+VIS1)*0.03);

}

// punto x del hist final
xh[16] = hhx244->GetMean();
exh[16]= hhx244->GetRMS();
//punto y del hist final
yh[16]= hhy244->GetMean();
eyh[16]= hhy244->GetRMS();

yhvis[16]=hhyvis244->GetMean();
eyhvis[16]=hhyvis244->GetRMS();

cout<<xh[16]<<" VUV= "<<yh[16]<<endl;
cout<<xh[16]<<" VIS= "<<yhvis[16]<<endl;

//////////////////////////////////////////////////

TH1F*hhx252=new TH1F("hhx252", "", 100,0,300);
TH1F*hhy252=new TH1F("hhy252", "", 100,0,10000000);
TH1F*hhyvis252=new TH1F("hhyvis252", "", 100,0,10000000);
for(int i=0;i<entriesh252;i++) //50 veces
{
  treeh252->GetEntry(i);
  //Hace esto para cada muon
  //posx
  for(int j=0;j<Xhs252->size();j++){
    //X = Xs20->at(j);
    hhx252->Fill(Xhs252->at(j)); //llena todas las x de los 50 muones
  }
  for(int j=0;j<Xhl252->size();j++){
    //X = Xs20->at(j);
    hhx252->Fill(Xhl252->at(j)); //llena todas las x de los 50 muones
  }

  double VUV=0;
  double VUV1=0;
  double VIS=0;
  double VIS1=0;

  //fotones detectados en los coated
  for(int j=0;j<VUVhs252->size();j++){
     VUV+= VUVhs252->at(j);
  }
  for(int j=0;j<VUVhl252->size();j++){
     VUV1+= VUVhl252->at(j);
  }
  hhy252->Fill((VUV+VUV1)*0.03); //llena con los vuv/E de los 50 muones (50 puntos)

  for(int j=0;j<VIShs252->size();j++){
     VIS+= VIShs252->at(j);
  }
  for(int j=0;j<VIShl252->size();j++){
     VIS1+= VIShl252->at(j);
  }
  hhyvis252->Fill((VIS+VIS1)*0.03);

}

// punto x del hist final
xh[17] = hhx252->GetMean();
exh[17]= hhx252->GetRMS();
//punto y del hist final
yh[17]= hhy252->GetMean();
eyh[17]= hhy252->GetRMS();

yhvis[17]=hhyvis252->GetMean();
eyhvis[17]=hhyvis252->GetRMS();

cout<<xh[17]<<" VUV= "<<yh[17]<<endl;
cout<<xh[17]<<" VIS= "<<yhvis[17]<<endl;






///
//Para plotearlo en un graph
//---------------------------VUV component-------------------//
//hib LArQL
 auto gs = new TGraphErrors(ns,xs,ys,exs,eys);

//hib sin LArQL
 auto gh = new TGraphErrors(nh,xh,yh,exh,eyh);
 //-------------------------VIS component-----------------------//
 //hib LArQL
  auto gsvis = new TGraphErrors(ns,xs,ysvis,exs,eysvis);
  //hib sin LArQL
  auto ghvis = new TGraphErrors(nh,xh,yhvis,exh,eyhvis);

  auto mg = new TMultiGraph();

//Pinto los graphs

  gs->SetMarkerStyle(21);
  gs->SetMarkerColor(4);
  //gs->Draw("AP,SAME");


  gh->SetMarkerStyle(21);
  gh->SetMarkerColor(6);
  //gh->Draw("APSame");
  gsvis->SetMarkerStyle(22);
  gsvis->SetMarkerColor(kBlack);

  ghvis->SetMarkerStyle(22);
  ghvis->SetMarkerColor(kGray+1);

  mg->Add( gs );
  mg->Add( gh );

  mg->Add( gsvis );
  mg->Add( ghvis );

pad1->cd();

  mg->Draw("AP");
  mg->SetTitle("Downward muon 0.5 GeV: y=190 cm, z=250 cm");
  mg->GetXaxis()->SetTitle("Drift coordinate <X> (cm)");
  mg->GetYaxis()->SetTitle("#PE");

  auto lvuv = new TLegend(0.1,0.7,0.48,0.9);
    //ls= new TLegend(0.5,0.9,0.9,0.9);
    lvuv->AddEntry(gs,"Hybrid VUV (with LArQL Model)","lep");
    lvuv->AddEntry(gh,"Hybrid VUV","lep");
    lvuv->Draw();

    auto lvis = new TLegend(0.1,0.7,0.48,0.9);
      //ls= new TLegend(0.5,0.9,0.9,0.9);
      lvis->AddEntry(gsvis,"Hybrid VIS (with LArQL Model)","lep");
      lvis->AddEntry(ghvis,"Hybrid VIS","lep");
      lvis->Draw();


pad2->cd();
const Int_t n = 18;
 Double_t x[n], y[n];

for (Int_t i=0;i<n;i++) {
     x[i] = xs[i];
     y[i] = (yh[i]-ys[i])/((yh[i]+ys[i])/2);
     cout<<x[i]<<" "<<y[i]<<endl;
   }
   TGraph* gresid = new TGraph(n,x,y);
   gresid->Draw("AP");
   gresid->SetTitle("");
   gresid->SetMarkerStyle(5);
   gresid->GetYaxis()->SetRangeUser(-0.4,0.4);
   gresid->GetYaxis()->SetTitle("#varepsilon_{VUV}");





  }
