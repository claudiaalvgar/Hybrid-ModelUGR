////////////////////////////////////////////////////////////////////////
// Class:       AnalyzeEvents
// Plugin Type: analyzer (art v3_05_01)
// File:        AnalyzeEvents_module.cc
//
// Generated at Thu Jan 14 11:40:27 2021 by Claudia Alvarez Garcia using cetskelgen
// from cetlib version v3_10_00.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
// #include "nusimdata/SimulationBase/MCTruth.h"
// #include "nusimdata/SimulationBase/MCNeutrino.h"
// #include "nusimdata/SimulationBase/MCParticle.h"

#include "lardataobj/Simulation/SimPhotons.h"
#include "lardataobj/Simulation/SimEnergyDeposit.h"
//Aditional framework includes
#include "art_root_io/TFileService.h"

//Root include
#include <TTree.h>
// C/C++ standard libraries
#include <map>
#include <vector>
#include <string>
#include <limits> // std::numeric_limits<>
#include <cmath>
//#include "TH1F.h"


namespace test {
  class AnalyzeEvents;
}


class test::AnalyzeEvents : public art::EDAnalyzer {
public:
  explicit AnalyzeEvents(fhicl::ParameterSet const& p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  AnalyzeEvents(AnalyzeEvents const&) = delete;
  AnalyzeEvents(AnalyzeEvents&&) = delete;
  AnalyzeEvents& operator=(AnalyzeEvents const&) = delete;
  AnalyzeEvents& operator=(AnalyzeEvents&&) = delete;

  // Required functions.
  void analyze(art::Event const& e) override;

  // Selected optional functions.
  void beginJob() override;
  void endJob() override;

private:
  //Declare member data here
  // TH1F* fHist; //Output histogram

  //Output tree declaration
  TTree *fTree;
  //Variables to go in output tree
  //unsigned int fEventID;
  //float energy_deposit;
  // float step_length;
  //float numphot;
  // float energystep;

  //Variables para los fotones generados: el 1 para la libreria y nada para las variables del semianalitico
  //Energia depositada
  std:: vector< double>  E;
  std:: vector< double>  E1;
  //dE/dx: guardamos la energia depositada entre el step length
  // std:: vector< double>  dEdx;
  // std:: vector< double>  dEdx1;
  //numphot/steplenght: guardamos el numero de fotones generados en la deposicion de energia entre el step length
  // std:: vector< double>   NumPhotons;
  // std:: vector< double>   NumPhotons1;
  //posicion x e y del detector donde ocurre la deposicion de energia
  std:: vector< double> Y;
  std:: vector< double> Y1;
  std:: vector< double> X;
  std:: vector< double> X1;
  std:: vector< double> Z;
  std:: vector< double> Z1;
  //phot/MeV: fotones generados entre la deposicion de energia
  // std:: vector< double> photMeV;
  // std:: vector< double> photMeV1;
  //Step length
  // std:: vector< double> step;
  // std:: vector< double> step1;


  //Variables para los fotones detectados: el 1 para la libreria y nada para el semianalitico
  //ref para los fotones VIS y nada para los fotones VUV

  //Canal optico en el que se detectan los fotones
  std:: vector< int> chanopt;
  std:: vector< int> chanoptref;
  std:: vector< int> chanopt1;
  std:: vector< int> chanoptref1;

  //Numero de fotones detectados por MeV para semianalitico (directos y reflejados) y para la libreria
  std:: vector <double> phot_detected;
  std:: vector <double> phot_detectedref;
  std:: vector <double> phot_detected1;
  std:: vector <double> phot_detectedref1;


};


test::AnalyzeEvents::AnalyzeEvents(fhicl::ParameterSet const& p)
  : EDAnalyzer{p}  // ,
  // More initializers here.
{
  // Call appropriate consumes<>() for any products to be retrieved by this module.
  // float maxEnergy = p.get<float>("MaxNuEnergy", 3.0);
  //art::ServiceHandle<art::TFileService> tfs;
   // fHist = tfs->make<TH1F>("enu", ";E_{#nu} (GeV);Events", 100, 0, maxEnergy);
}



void test::AnalyzeEvents::analyze(art::Event const& e)
{ //Esto es una comprobacion y sale cada vez que cambiamos de evento (cuando haya más de un evento)
  std::cout<<"Hemos cambiado de entrada"<<std::endl;


  // art::Handle<std::vector<simb::MCTruth> > mctruths;
  // e.getByLabel("generator", mctruths);
  // for (auto const& truth : *mctruths) {
  // const simb::MCNeutrino& mcnu = truth.GetNeutrino();
  //const simb::MCParticle& nu = mcnu.Nu();
  //enu = nu.E();
 //fHist->Fill(enu);
  // }



  //------------------------VARIABLES PARA LA LIBRERIA OPTICA------------------------------------

  //Esta parte se comenta cuando se use solo el modelo semianalitico
 art::Handle<std::vector<sim::SimEnergyDeposit> > edepHandle1;
 e.getByLabel("IonAndScintOUT", edepHandle1);

 art::Handle<std::vector<sim::SimPhotonsLite> > simphotons1;
 e.getByLabel("LIB", simphotons1);

 art::Handle<std::vector<sim::SimPhotonsLite> > simphotonsref1;
 e.getByLabel("LIB:Reflected", simphotonsref1);

 E1.clear();
 //dEdx1.clear();
 //NumPhotons1.clear();
 Y1.clear();
 // photMeV1.clear();
 X1.clear();
 Z1.clear();
 //step1.clear();

 phot_detected1.clear();
 phot_detectedref1.clear();
 chanopt1.clear();
 chanoptref1.clear();


 //Fotones generados
 for (auto const& edepi : *edepHandle1) {

    double  energy_deposit  = edepi.Energy();
    // double  step_length  = edepi.StepLength();
    //double  energystep = energy_deposit/step_length;
    //double  numphot  = edepi.NumPhotons()/step_length;
    //double  photenergy = edepi.NumPhotons()/energy_deposit;

    double  posY = edepi.MidPointY();
    double  posZ = edepi.MidPointZ();
    double  posX = edepi.MidPointX();

   E1.push_back(energy_deposit);
   //dEdx1.push_back(energystep);
   // NumPhotons1.push_back(numphot);
   Y1.push_back(posY);
   X1.push_back(posX);
   Z1.push_back(posZ);
   //photMeV1.push_back(photenergy);
   //step1.push_back(step_length);

   // std::cout<<"posX= "<<posX<<std::endl;
   // std::cout<<"energy_deposit= "<<energy_deposit<<std::endl;

 }
 //Fotones detectados VUV libreria
 for (auto const& phots : *simphotons1) {

   int opt = phots.OpChannel;
   //Solo usamos los PMT coated
   if(opt==7||opt==9||opt==11||opt==13||opt==15||opt==17||opt==61||opt==63||opt==65||opt==67||opt==69||opt==71||opt==85||opt==87||opt==89||opt==91||opt==93||opt==95||opt==139||opt==141||opt==143||opt==145||opt==147||opt==149||opt==163||opt==165||opt==167||opt==169||opt==171||opt==173||opt==217||opt==219||opt==221||opt==223||opt==225||opt==227||opt==241||opt==243||opt==245||opt==247||opt==249||opt==251||opt==295||opt==297||opt==299||opt==301||opt==303||opt==305){
     int  dp=0;
     std::map<int, int> photmap = phots.DetectedPhotons;
     //suma sobre todos los fotones que llegan a un PMT

     for(auto fphoton = photmap.begin();fphoton != photmap.end();fphoton++){

       dp+=fphoton->second;
     }//for

    phot_detected1.push_back(dp);
    chanopt1.push_back(opt);

     std::cout<<"phot_detected vuvlib= "<<dp<<std::endl;
     std::cout<<"chanopt= "<<opt<<std::endl;
   }
 }

//Fotones detectados VIS libreria
 for (auto const& photsref1 : *simphotonsref1) {

   int opt = photsref1.OpChannel;
   //Solo usamos los PMT coated
   if(opt==7||opt==9||opt==11||opt==13||opt==15||opt==17||opt==61||opt==63||opt==65||opt==67||opt==69||opt==71||opt==85||opt==87||opt==89||opt==91||opt==93||opt==95||opt==139||opt==141||opt==143||opt==145||opt==147||opt==149||opt==163||opt==165||opt==167||opt==169||opt==171||opt==173||opt==217||opt==219||opt==221||opt==223||opt==225||opt==227||opt==241||opt==243||opt==245||opt==247||opt==249||opt==251||opt==295||opt==297||opt==299||opt==301||opt==303||opt==305){
     int  dp=0;
     std::map<int, int> photmap = photsref1.DetectedPhotons;
     //suma sobre todos los fotones que llegan a un PMT

     for(auto fphoton = photmap.begin();fphoton != photmap.end();fphoton++){

       dp+=fphoton->second;
     }//for

     phot_detectedref1.push_back(dp);
     chanoptref1.push_back(opt);

     std::cout<<"phot_detected vislib= "<<dp<<std::endl;
     std::cout<<"chanopt_ref= "<<opt<<std::endl;
   }
 }




 std::cout<<"--------------------------------------------------------------------"<<std::endl;

 //------------------------VARIABLES PARA MODELO SEMIANALITICO------------------------------------
  art::Handle<std::vector<sim::SimEnergyDeposit> > edepHandle;
  e.getByLabel("IonAndScintIN", edepHandle);
  art::Handle<std::vector<sim::SimPhotonsLite> > simphotons;
  e.getByLabel("PAR", simphotons);
  art::Handle<std::vector<sim::SimPhotonsLite> > simphotonsref;
  e.getByLabel("PAR:Reflected", simphotonsref);

   E.clear();
   //dEdx.clear();
   //NumPhotons.clear();
   Y.clear();
   //photMeV.clear();
   X.clear();
   Z.clear();
   //step.clear();

   phot_detected.clear();
   chanopt.clear();

   phot_detectedref.clear();
   chanoptref.clear();

 //Fotones generados
 for (auto const& edepi : *edepHandle) {

    double energy_deposit  = edepi.Energy();
    //double step_length  = edepi.StepLength();
    //double  energystep = energy_deposit/step_length;
    // double  numphot  = edepi.NumPhotons()/step_length;
    //double  photenergy = edepi.NumPhotons()/energy_deposit;
    double  posY = edepi.MidPointY();
    double  posZ = edepi.MidPointZ();
    double  posX = edepi.MidPointX();

   E.push_back(energy_deposit);
   // dEdx.push_back(energystep);
   // NumPhotons.push_back(numphot);
   Y.push_back(posY);
   X.push_back(posX);
   Z.push_back(posZ);
   //photMeV.push_back(photenergy);
   //step.push_back(step_length);


   // std::cout<<"posX= "<<posX<<std::endl;
   // std::cout<<"energy_deposit= "<<energy_deposit<<std::endl;
}

 //Fotones directos detectados VUV semianalitico
 for (auto const& phots : *simphotons){

   int opt = phots.OpChannel;
   //Usando PMTs coated
   if(opt==7||opt==9||opt==11||opt==13||opt==15||opt==17||opt==61||opt==63||opt==65||opt==67||opt==69||opt==71||opt==85||opt==87||opt==89||opt==91||opt==93||opt==95||opt==139||opt==141||opt==143||opt==145||opt==147||opt==149||opt==163||opt==165||opt==167||opt==169||opt==171||opt==173||opt==217||opt==219||opt==221||opt==223||opt==225||opt==227||opt==241||opt==243||opt==245||opt==247||opt==249||opt==251||opt==295||opt==297||opt==299||opt==301||opt==303||opt==305){

     int  dp=0;
     std::map<int, int> photmap = phots.DetectedPhotons;
     //suma sobre todos los fotones que llegan a un PMT

     for(auto fphoton = photmap.begin();fphoton != photmap.end();fphoton++){

       dp+=fphoton->second;
     }//for

    phot_detected.push_back(dp);
   chanopt.push_back(opt);

   std::cout<<"phot_detected vuvsemi= "<<dp<<std::endl;
   std::cout<<"chanopt= "<<opt<<std::endl;
   }
 }

//Fotones directos detectados VIS semianalitico
 for (auto const& photsref : *simphotonsref) {

   int opt = photsref.OpChannel;
   //Usando PMTs coated
   if(opt==7||opt==9||opt==11||opt==13||opt==15||opt==17||opt==61||opt==63||opt==65||opt==67||opt==69||opt==71||opt==85||opt==87||opt==89||opt==91||opt==93||opt==95||opt==139||opt==141||opt==143||opt==145||opt==147||opt==149||opt==163||opt==165||opt==167||opt==169||opt==171||opt==173||opt==217||opt==219||opt==221||opt==223||opt==225||opt==227||opt==241||opt==243||opt==245||opt==247||opt==249||opt==251||opt==295||opt==297||opt==299||opt==301||opt==303||opt==305){
     int  dp=0;
     std::map<int, int> photmap = photsref.DetectedPhotons;
     //suma sobre todos los fotones que llegan a un PMT

     for(auto fphoton = photmap.begin();fphoton != photmap.end();fphoton++){

       dp+=fphoton->second;
     }//for

     phot_detectedref.push_back(dp);
     chanoptref.push_back(opt);

     std::cout<<"phot_detected vissemi= "<<dp<<std::endl;
     std::cout<<"chanopt_ref= "<<opt<<std::endl;
   }
 }


  // Implementation of required member function here.
  //Define our event ID variable
  // fEventID = e.id().event();
  //Fill the output tree with all relevant variables
  fTree->Fill();
}





void test::AnalyzeEvents::beginJob()
{
  // Implementation of optional member function here.
  //The TFileService is used to define the TTree and writing is to the output file
  art::ServiceHandle<art::TFileService> tfs; //Define service
  fTree = tfs->make<TTree>("tree","Analyzer Output Tree"); //Define tree
  // fTree->Branch("eventID",&fEventID,"eventID/i");
  // fTree->Branch("Enu",&enu,"Enu/f");
  //fTree->Branch("chanopt","std::vector<int>", &chanopt);

  //Branches para la libreria
  fTree->Branch("E1", &E1);
  //fTree->Branch("dEdx1", &dEdx1);
  //fTree->Branch("NumPhotons1", &NumPhotons1);
  fTree->Branch("Y1", &Y1);
  fTree->Branch("X1", &X1);
  fTree->Branch("Z1", &Z1);
  //fTree->Branch("photMeV1", &photMeV1);
  //fTree->Branch("step1", &step1);

  fTree->Branch("chanopt1", &chanopt1);
  fTree->Branch("phot_detected1", &phot_detected1);
  fTree->Branch("chanoptref1", &chanoptref1);
  fTree->Branch("phot_detectedref1", &phot_detectedref1);

  //Branches para el modelo semianalitico
  fTree->Branch("E", &E);
  //fTree->Branch("dEdx", &dEdx);
  //fTree->Branch("NumPhotons", &NumPhotons);
  fTree->Branch("Y", &Y);
  fTree->Branch("X", &X);
  fTree->Branch("Z", &Z);
  //fTree->Branch("photMeV", &photMeV);
  //fTree->Branch("step", &step);

  fTree->Branch("chanopt", &chanopt);
  fTree->Branch("phot_detected", &phot_detected);
      //Componente reflejada
  fTree->Branch("chanoptref", &chanoptref);
  fTree->Branch("phot_detectedref", &phot_detectedref);

}



void test::AnalyzeEvents::endJob()
{
  // Implementation of optional member function here.
}

DEFINE_ART_MODULE(test::AnalyzeEvents)
