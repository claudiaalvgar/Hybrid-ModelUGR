//Crear PMTs.root
{
//Leemos el PMT y la posicion de cada uno de ellos
fstream file;
file.open("PMTs.txt",ios::in);
double numpmt1, Xpmt1, Ypmt1, Zpmt1;
std::vector<double> numpmt, Xpmt, Ypmt, Zpmt;
//Hacemos un tree
TFile*pmts=new TFile("PMTs.root","recreate");
TTree*tree=new TTree("treepmt","treepmt");

numpmt.clear();
Xpmt.clear();
Ypmt.clear();
Zpmt.clear();

//Definimos branches
tree->Branch("numpmt", &numpmt);
tree->Branch("Xpmt", &Xpmt);
tree->Branch("Ypmt", &Ypmt);
tree->Branch("Zpmt", &Zpmt);
  int i=0;

  while(i<320)
  {
    file>> numpmt1 >> Xpmt1 >> Ypmt1 >> Zpmt1;

    numpmt.push_back(numpmt1);
    Xpmt.push_back(Xpmt1);
    Ypmt.push_back(Ypmt1);
    Zpmt.push_back(Zpmt1);

    if(file.eof())break;
    //cout<<numpmt1<<" "<<Xpmt1<<" "<<Ypmt1<<" "<<" "<<Zpmt1<<endl;
    cout<<numpmt[i]<<" "<<Xpmt[i]<<" "<<Ypmt[i]<<" "<<" "<<Zpmt[i]<<endl;

    tree->Fill();
    i++;
  }
  pmts->Write();
  pmts->Close();
file.close();

  }
