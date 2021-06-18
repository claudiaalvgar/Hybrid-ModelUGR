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
#include "nusimdata/SimulationBase/MCTruth.h"
// #include "nusimdata/SimulationBase/MCNeutrino.h"
#include "nusimdata/SimulationBase/MCParticle.h"
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

//Flashes: reconstructed light
#include "canvas/Persistency/Common/FindManyP.h"
#include "lardataobj/RecoBase/OpFlash.h"
#include "lardataobj/RecoBase/OpHit.h"
#include "sbndcode/OpDetSim/sbndPDMapAlg.hh"



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
  unsigned int fEventID;
  //Guarda la energía de los electrones michel
  std:: vector< double> EventEnergy;
  //Energia depositada
  std:: vector< double>  E;
  //Fotones generados en cada step
  std:: vector< double> phot_generated;
  //posicion x e y del detector donde ocurre la deposicion de energia
  std:: vector< double> X;
  std:: vector< double> Y;
  std:: vector< double> Z;
  //Step length
  std:: vector< double> step;

  //Variables para los fotones detectados (g4)
  //Canal optico en el que se detectan los fotones
  std:: vector< int> chanopt;
  //std:: vector< int> chanoptref;

  //Numero de fotones detectados
    //Directos
  std:: vector <double> phot_detected;
    //Reflejados
  // std:: vector <double> phot_detectedref;

  //Flashes: numero de fotones reconstruidos y su canal optico (posiciones del vector)
  std::vector<double> _flash_pe_vuv;
  std::vector<double> hitsperchan;


  int _run, _subrun, _event;
  double _flash_time;
  // std::vector<double> phot_detected_dig;
  // std::vector<int> chanopt_dig;
};


test::AnalyzeEvents::AnalyzeEvents(fhicl::ParameterSet const& p)
  : EDAnalyzer{p}  // ,
  // More initializers here.
{

  //Flashes
  //_flash_label_v   = p.get<std::vector<std::string>>("FlashProducer",   _flash_label_v);
  //_mcflash_label_v = p.get<std::vector<std::string>>("MCFlashProducer", _mcflash_label_v);
  // _ophit_label_v   = p.get<std::vector<std::string>>("OpHitProducer", _ophit_label_v);
  //_tpc_v           = p.get<std::vector<int>>("TPC", _tpc_v);
  // Call appropriate consumes<>() for any products to be retrieved by this module.
  // float maxEnergy = p.get<float>("MaxNuEnergy", 3.0);
  //art::ServiceHandle<art::TFileService> tfs;
   // fHist = tfs->make<TH1F>("enu", ";E_{#nu} (GeV);Events", 100, 0, maxEnergy);
}



void test::AnalyzeEvents::analyze(art::Event const& e)
{ //Esto es una comprobacion y sale cada vez que cambiamos de evento (cuando haya más de un evento)
  std::cout<<"Hemos cambiado de entrada"<<std::endl;
  //Define our event ID variable
  _event = e.id().event();
  _run    = e.id().run();
  _subrun = e.id().subRun();
  std::cout<<"Event: "<<_event<<std::endl;
  //double fEventEnergy=e.Energy();
  //------------------------MICHEL ELECTRONS------------------------------------
  art::Handle<std::vector<simb::MCParticle> > mcparticles;

  EventEnergy.clear();
  //Sacar la energia de los electrones de Michel que lanzo
  e.getByLabel("largeant", mcparticles);
  for (auto const& particle : *mcparticles) {
    int pdg = particle.PdgCode();
    int ID= particle.TrackId();


    //Guardo la energía del primer electron (electron Michel)
    if((pdg==11)&&(ID==1)){
      double MichelEnergy= particle.E();
      std::cout<<"Energía del electron Michel numero "<<fEventID<<": "<<MichelEnergy<<std::endl;
      EventEnergy.push_back(MichelEnergy);
      }
  }




  // art::Handle<std::vector<simb::MCTruth> > mctruths;
  // e.getByLabel("generator", mctruths);
  // for (auto const& truth : *mctruths) {
  // const simb::MCNeutrino& mcnu = truth.GetNeutrino();
  //const simb::MCParticle& nu = mcnu.Nu();
  //enu = nu.E();
 //fHist->Fill(enu);
  // }




 std::cout<<"--------------------------------------------------------------------"<<std::endl;
 //Sacamos los fotones generados, su energia, su x, y, z en cada step y el step
 //Sacamos los fotones detectados (directos y reflejados y su canal optico) true sin reconstruccion

 //SimEnergyDeposit: Generación
  art::Handle<std::vector<sim::SimEnergyDeposit> > edepHandle;
  e.getByLabel("IonAndScint", edepHandle);

  //SimPhotons: Detección
  // art::Handle<std::vector<sim::SimPhotons> > simphotons;
  // e.getByLabel("largeant", simphotons);
  // art::Handle<std::vector<sim::SimPhotons> > simphotonsref;
  //e.getByLabel("largeant:Reflected", simphotonsref);

  //SimPhotonsLite: Detección
  art::Handle<std::vector<sim::SimPhotonsLite> > simphotons;
  e.getByLabel("LIB", simphotons);
  //art::Handle<std::vector<sim::SimPhotonsLite> > simphotonsref;
  //e.getByLabel("LIB:Reflected", simphotonsref);



   E.clear();
   X.clear();
   Y.clear();
   Z.clear();
   step.clear();
   phot_generated.clear();

   phot_detected.clear();
   chanopt.clear();

   //phot_detectedref.clear();
   //chanoptref.clear();

   double Total_Energydeposit=0;
   double Total_photdetected =0;
   //double Total_photdetectedref=0;

 //Fotones generados igual para SimPhotons y SimPhotonsLite
   for (auto const& edepi : *edepHandle) {

     //cm
     double step_length  = edepi.StepLength();
     // if(step_length>0){

      //MeV
     double energy_deposit  = edepi.Energy();

    //dEdx
     // double dEdx= energy_deposit/step_length;
   //Numero de fotones generados
     double numphot=edepi.NumPhotons();
   //Numero de fotones generados formula
     // double recomb=log(0.93+(0.153142*dEdx/0.5))/(0.153142*dEdx/0.5);
     // double numphotformdec=energy_deposit*((1./0.0000195)-(recomb/0.0000236));
     //Devuelve la parte entera
     // int numphotform= (int) numphotformdec;


     //if steplength=0
     //else{
       //MeV
       //double energy_deposit  = edepi.Energy();
       //double numphotformdec=energy_deposit/0.0000195;
       // int numphotform= (int) numphotformdec;



    double  posX = edepi.MidPointX();
    double  posY  = edepi.MidPointY();
    double  posZ = edepi.MidPointZ();

   E.push_back(energy_deposit);
   step.push_back(step_length);
   phot_generated.push_back(numphot);
   Y.push_back(posY);
   X.push_back(posX);
   Z.push_back(posZ);
   Total_Energydeposit +=energy_deposit;
   //std::cout<<"posX= "<<posX<<" posY= "<<posY<<" posZ= "<<posZ<<std::endl;
   //std::cout<<"Energy deposit at step= "<<energy_deposit<<std::endl;
   //std::cout<<"Step= "<<step_length<<std::endl;
   //std::cout<<"Generated photons= "<<numphot<<std::endl;
   //std::cout<<"Generated photons formula= "<<numphotform<<std::endl;

   //}//if steplength
   }
 std::cout<<"----------------------------------------------------------"<<std::endl;
 std::cout<<"Energia total depositada= "<<Total_Energydeposit<<std::endl;
 //------------------------------------------SIMPHOTONS LITE-----------------------------------------//
 //Fotones directos detectados: SimPhotonsLite
 //Bucle sobre los 320 canales
 for (auto const& phots : *simphotons){

   int opt = phots.OpChannel;
   //Sumamos para todos los canales
     int  dp=0;
     std::map<int, int> photmap = phots.DetectedPhotons;
     //suma sobre todos los fotones que llegan a un PMT
      for(auto fphoton = photmap.begin();fphoton != photmap.end();fphoton++){
	dp+=fphoton->second;
	}//for

   phot_detected.push_back(dp);
   chanopt.push_back(opt);
   Total_photdetected +=dp;
    std::cout<<"chanopt= "<<opt<<std::endl;
    std::cout<<"phot_detected VUV= "<<dp<<std::endl;
    // }//if
 }//for phots
 std::cout<<"----------------------------------------------------------"<<std::endl;
 std::cout<<"Fotones directos(VUV) detectados totales= "<<Total_photdetected<<std::endl;

 std::cout<<"----------------------------------------------------------"<<std::endl;
 std::cout<<"phdetectadosVUV/MeV= "<<Total_photdetected/Total_Energydeposit<<std::endl;


 _flash_pe_vuv.clear();

 //Fotones detectados flash
 art::Handle<std::vector<recob::OpHit> > ophit_h;
 e.getByLabel("ophitpmt", ophit_h);

 std::vector<art::Ptr<recob::OpHit>> ophit_v;
 art::fill_ptr_vector(ophit_v, ophit_h);




 //El l=2 0 para una tpc y 1 para la otra
 // for (size_t l = 0;l < _flash_label_v.size(); l++) {

   art::Handle<std::vector<recob::OpFlash>> flash_h;
   e.getByLabel("opflashtpc1", flash_h);


   art::FindManyP<recob::OpHit> flashToOpHitAssns(flash_h, e, "opflashtpc1");
   //Para cada flash

   int flashsize=flash_h->size();
     if(flashsize!=0){
    std::cout<<"Entradas flash: "<<flash_h->size()<<std::endl;
    //Me quedo con el primer flash
   if(flashsize>1){flashsize=1;}
      for (int i = 0; i < flashsize; i++) {
      hitsperchan.clear();
      //Flash
    auto const& f = (*flash_h)[i];
     std::cout << "Flash " << i << ", time " << f.AbsTime() << std::endl;
     _flash_time = f.AbsTime();
     _flash_pe_vuv = f.PEs();

     //OpHit
     const Int_t n=_flash_pe_vuv.size();
     std::vector<double> vhitsperchan(n);

     for(int h=0;h<n;h++){
       vhitsperchan[h]=0;
     }//for int


     std::vector<art::Ptr<recob::OpHit>> ophit_v = flashToOpHitAssns.at(i);
     for (auto ophit : ophit_v) {
       double k=ophit->OpChannel();
       vhitsperchan[k]+=ophit->PE();
       //for(int k=0;k<n;k++){
       //if(ophit->OpChannel()==k){vhitsperchan[k]+=ophit->PE();}//if
       //}//for int

       //_flash_ophit_pe.push_back(ophit->PE());
       // _flash_ophit_ch.push_back(ophit->OpChannel());

     }//for auto


     for(size_t j=0; j < _flash_pe_vuv.size(); j++){
       hitsperchan.push_back(vhitsperchan[j]);
       std::cout<<"Canal: "<<j<<" Numero de fotones dig flash= "<<_flash_pe_vuv[j]<<std::endl;
       std::cout<<"Canal: "<<j<<" Hits= "<<hitsperchan[j]<<std::endl;
	   }
     //  fTree->Fill();
     //   _flash_pe_vuv.clear();
    }//for i

    //}//for l

  // Implementation of required member function here.

  //Fill the output tree with all relevant variables
  fTree->Fill();
   }//ifflashsize es distinto de 0 lleno el tree
}





void test::AnalyzeEvents::beginJob()
{
  // Implementation of optional member function here.
  //The TFileService is used to define the TTree and writing is to the output file
  art::ServiceHandle<art::TFileService> tfs; //Define service
  fTree = tfs->make<TTree>("tree","Analyzer Output Tree"); //Define tree

  fTree->Branch("run", &_run, "run/I");
  fTree->Branch("subrun", &_subrun, "subrun/I");
  fTree->Branch("event", &_event, "event/I");
  fTree->Branch("flash_time", &_flash_time, "flash_time/D");
  fTree->Branch("EventEnergy", &EventEnergy);
  //fTree->Branch("Enu",&enu,"Enu/f");
  //fTree->Branch("chanopt","std::vector<int>", &chanopt);

  fTree->Branch("E", &E);
  fTree->Branch("phot_generated", &phot_generated);

  fTree->Branch("X", &X);
  fTree->Branch("Y", &Y);
  fTree->Branch("Z", &Z);
  fTree->Branch("step", &step);

  fTree->Branch("chanopt", &chanopt);
  fTree->Branch("phot_detected", &phot_detected);
  //Componente reflejada
  //fTree->Branch("chanoptref", &chanoptref);
  //fTree->Branch("phot_detectedref", &phot_detectedref);
  //Fotones detectados y canal optico despues de la reconstruccion
  //fTree->Branch("flash_ophit_pe", &_flash_ophit_pe);
  // fTree->Branch("flash_ophit_ch", &_flash_ophit_ch);
  fTree->Branch("hitsperchan", &hitsperchan);
  fTree->Branch("flash_pe_vuv", &_flash_pe_vuv);

}



void test::AnalyzeEvents::endJob()
{
  // Implementation of optional member function here.
}

DEFINE_ART_MODULE(test::AnalyzeEvents)
