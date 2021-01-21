#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"

using namespace std;

const int hadron_nmax = 20000;

int dat2root(void)
{
	ifstream ampt_final("/mnt/c/Users/pjska/github/ampt_dchen/Ampt-v1.26t9b-v2.26t9b/ana/ampt.dat");
	if(!ampt_final.is_open()) return 1;

	//event-level info
	float b;
	int   projectile_ela_n;
	int   projectile_inela_n;
	int   target_ela_n;
	int   target_inela_n;
	//track-level info
	int   hadron_n;
	float mc_px[hadron_nmax];
	float mc_py[hadron_nmax];
	float mc_pz[hadron_nmax];
	float mc_m[hadron_nmax];
	float mc_vx_x[hadron_nmax];
	float mc_vx_y[hadron_nmax];
	float mc_vx_z[hadron_nmax];
	float mc_t[hadron_nmax];
	int   mc_pdgId[hadron_nmax];

	int   n_mc_eventid;
	float n_mc_px;
	float n_mc_py;
	float n_mc_pz;
	float n_mc_m;
	float n_mc_vx_x;
	float n_mc_vx_y;
	float n_mc_vx_z;
	float n_mc_t;
	int   n_mc_pdgId;
	float temp;
	int   event;

	TFile *myfile = new TFile("ampt_hadron.root", "RECREATE");

	TTree *mytree_hadron= new TTree("ampt_hadron","hadron level from AMPT");
	//event-level info
	mytree_hadron->Branch("b",&b);
	mytree_hadron->Branch("projectile_ela_n",&projectile_ela_n);
	mytree_hadron->Branch("projectile_inela_n",&projectile_inela_n);
	mytree_hadron->Branch("target_ela_n",&target_ela_n);
	mytree_hadron->Branch("target_inela_n",&target_inela_n);
	//track-level info
	mytree_hadron->Branch("hadron_n",&hadron_n);
	mytree_hadron->Branch("mc_px",mc_px,"mc_px[hadron_n]/F");
	mytree_hadron->Branch("mc_py",mc_py,"mc_py[hadron_n]/F");
	mytree_hadron->Branch("mc_pz",mc_pz,"mc_pz[hadron_n]/F");
	mytree_hadron->Branch("mc_m" ,mc_m,"mc_m[hadron_n]/F");
	mytree_hadron->Branch("mc_vx_x",mc_vx_x,"mc_vx_x[hadron_n]/F");
	mytree_hadron->Branch("mc_vx_y",mc_vx_y,"mc_vx_y[hadron_n]/F");
	mytree_hadron->Branch("mc_vx_z",mc_vx_z,"mc_vx_z[hadron_n]/F");
	mytree_hadron->Branch("mc_t",mc_t,"mc_t[hadron_n]/F");
	mytree_hadron->Branch("mc_pdgId",mc_pdgId,"mc_pdgId[hadron_n]/I");

	//read the info form ampt.dat
	while(!ampt_final.eof()){
		//event-level info
		ampt_final>>n_mc_eventid>>temp>>hadron_n>>b>>temp>>temp>>projectile_ela_n>>projectile_inela_n>>target_ela_n>>target_inela_n>>temp;
		if(ampt_final.eof()) break;

		//track-level info
		for(int i=0; i<hadron_n; i++){
			ampt_final>>n_mc_pdgId;
			ampt_final>>n_mc_px>>n_mc_py>>n_mc_pz>>n_mc_m;
			ampt_final>>n_mc_vx_x>>n_mc_vx_y>>n_mc_vx_z>>n_mc_t;

			mc_px[i]    = n_mc_px;
			mc_py[i]    = n_mc_py;
			mc_pz[i]    = n_mc_pz;
			mc_m[i]     = n_mc_m;
			mc_vx_x[i]  = n_mc_vx_x;
			mc_vx_y[i]  = n_mc_vx_y;
			mc_vx_z[i]  = n_mc_vx_z;
			mc_t[i]     = n_mc_t;
			mc_pdgId[i] = n_mc_pdgId;
		}

		mytree_hadron->Fill();
		event ++;
		if(event%100==0) cout << event << " events completed -----"  << endl;
	}

	mytree_hadron->Write();
	myfile->Write();

	return 0;
}
