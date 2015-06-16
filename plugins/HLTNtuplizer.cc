/*
 * \file HLTNtuplizer.cc
 *
 * \author I. Ojalvo
 *
 */

#include "FWCore/Framework/interface/MakerMacros.h"
#include "HLTrigger/HLTNtuplizer/interface/HLTNtuplizer.h"
#include "DataFormats/Provenance/interface/EventAuxiliary.h"
#include "DataFormats/L1Trigger/interface/Tau.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/Common/interface/RefToPtr.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"

using namespace edm;
using std::cout;
using std::endl;

HLTNtuplizer::HLTNtuplizer( const ParameterSet & cfg ) :
  rctSource_(cfg.getParameter<edm::InputTag>("rctSource"))
  {

  hlTriggerResults_    = cfg.getUntrackedParameter<edm::InputTag>("TriggerResultsTag", edm::InputTag("TriggerResults", "", "HLT"));
  l1ExtraTauSource_    = cfg.getParameter<edm::InputTag>("l1ExtraTauSource");
  l1ExtraIsoTauSource_ = cfg.getParameter<edm::InputTag>("l1ExtraIsoTauSource");
  gctTauJetsSource_    = cfg.getParameter<edm::InputTag>("gctTauJetsSource");
  gctIsoTauJetsSource_ = cfg.getParameter<edm::InputTag>("gctIsoTauJetsSource");
  tauSrc_              = cfg.getParameter<edm::InputTag>("recoTau");
  discriminatorSrc_    = cfg.getParameter<edm::InputTag>("recoTauDiscriminator");
  filters_             = cfg.getParameter<std::vector<std::string> >("filters");
  folderName_          = cfg.getUntrackedParameter<std::string>("folderName");

  //cout<<"folderName "<<folderNameSrc_<<endl;
  //TFileDirectory subDir = tfs_->mkdir( folderName_ );
  //TFileDirectory subSubDir = subDir.mkdir( folderName_ );

  efficiencyTree = tfs_->make<TTree>("EfficiencyTree", "Efficiency Tree");
  efficiencyTree->Branch("recoPt",   &recoPt,   "recoPt/D");
  efficiencyTree->Branch("isoTauPt", &isoTauPt, "isoTauPt/D");
  efficiencyTree->Branch("rlxTauPt", &rlxTauPt, "rlxTauPt/D");

  efficiencyTree->Branch("recoEta",   &recoEta,   "recoEta/D");
  efficiencyTree->Branch("isoTauEta", &isoTauEta, "isoTauEta/D");
  efficiencyTree->Branch("rlxTauEta", &rlxTauEta, "rlxTauEta/D");

  efficiencyTree->Branch("recoPhi",   &recoPhi,   "recoPhi/D");
  efficiencyTree->Branch("isoTauPhi", &isoTauPhi, "isoTauPhi/D");
  efficiencyTree->Branch("rlxTauPhi", &rlxTauPhi, "rlxTauPhi/D");

  efficiencyTree->Branch("l1IsoMatched", &l1IsoMatched, "l1IsoMatched/I");
  efficiencyTree->Branch("l1RlxMatched", &l1RlxMatched, "l1RlxMatched/I");

  isoTau_pt   = tfs_->make<TH1F>( "isoTau_pt"  , "p_{T}", 100,  0., 100. );
  tau_pt      = tfs_->make<TH1F>( "tau_pt"  , "p_{t}", 100,  0., 100. );
  recoTau_pt  = tfs_->make<TH1F>( "recoTau_pt"  , "p_{t}", 100,  0., 100. );
  hltTau_pt   = tfs_->make<TH1F>( "hltTau_pt"  , "p_{t}", 100,  0., 100. );

}

void HLTNtuplizer::beginJob( const EventSetup & es) {
}

void HLTNtuplizer::analyze( const Event& evt, const EventSetup& es ) {

  Handle<L1CaloRegionCollection> regions;

  edm::Handle<reco::PFTauDiscriminator> discriminator;

  edm::Handle < L1GctJetCandCollection > l1IsoTauJets;
  edm::Handle < L1GctJetCandCollection > l1TauJets;

  edm::Handle < vector<l1extra::L1JetParticle> > l1ExtraTaus;
  edm::Handle < vector<l1extra::L1JetParticle> > l1ExtraIsoTaus;

  std::vector<reco::PFTauRef> goodTaus;
  //std::vector<std::string> filters_;

  if(triggerfound(evt,HLTR,triggerName_))
    std::cout<<"Found trigger"

  //for(unsigned int i=0;i<filters_.size();++i) {
  //std::cout<<"Found Filter"<<std::endl;
  //}
  //Make Rates
  // loop over taus
  Handle<reco::PFTauCollection> taus;
  if(evt.getByLabel(tauSrc_, taus)){//Begin Getting Reco Taus
    for ( unsigned iTau = 0; iTau < taus->size(); ++iTau ) {
      reco::PFTauRef tauCandidate(taus, iTau);
      if(evt.getByLabel(discriminatorSrc_, discriminator)){
	if( (*discriminator)[tauCandidate] > 0.5){
	  recoTau_pt->Fill( tauCandidate->pt() );
	  if(tauCandidate->pt() > 6 ) //get rid of the garbage
	    goodTaus.push_back(tauCandidate);
	}
      }
    }
  }//End Getting Reco Taus
  

  //HLT
  edm::InputTag trigEventTag("hltTriggerSummaryAOD","","HLT"); //make sure have correct process on MC
  //data process=HLT, MC depends, Spring11 is REDIGI311X
  edm::Handle<trigger::TriggerEvent> trigEvent; 
  evt.getByLabel(trigEventTag,trigEvent);

  std::string filterName("HLT_IsoMu17_eta2p1_LooseIsoPFTau20_SingleL1_v2");
  //std::string filterName("HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg_v2"); 

  //it is important to specify the right HLT process for the filter
  trigger::size_type filterIndex = trigEvent->filterIndex(edm::InputTag(filterName,"",trigEventTag.process())); 
  if(filterIndex<trigEvent->sizeFilters()){ 
    const trigger::Keys& trigKeys = trigEvent->filterKeys(filterIndex); 
    const trigger::TriggerObjectCollection & trigObjColl(trigEvent->getObjects());
    //now loop of the trigger objects passing filter
    for(trigger::Keys::const_iterator keyIt=trigKeys.begin();keyIt!=trigKeys.end();++keyIt){ 
      const trigger::TriggerObject& obj = trigObjColl[*keyIt];
      std::cout<<"obj pt "<<obj.pt()<<std::endl;
      //do what you want with the trigger objects, you have
      //eta,phi,pt,mass,p,px,py,pz,et,energy accessors
      double pt =  obj.pt();
      hltTau_pt->Fill( pt );
    }
    
  }//end filter size check
  //End HLT


  //Begin Making Rate Plots
  if(evt.getByLabel(gctTauJetsSource_, l1TauJets)){
    if (!l1TauJets.isValid() && gctTauJetsSource_.label() != "none")
      edm::LogWarning("DataNotFound") << " Could not find l1TauJets"", label was " << gctTauJetsSource_;
    else {
      for( L1GctJetCandCollection::const_iterator tau = l1TauJets->begin(); tau != l1TauJets->end(); tau++ ) {
	double pt =  tau->rank();
	tau_pt->Fill( pt );
      }
    }
  }

  if(evt.getByLabel(gctIsoTauJetsSource_, l1IsoTauJets)){
    if (!l1IsoTauJets.isValid() && gctIsoTauJetsSource_.label() != "none"){
      edm::LogWarning("DataNotFound") << " Could not find l1IsoTauJets"", label was " << gctIsoTauJetsSource_; 
    }
    else{
      for( L1GctJetCandCollection::const_iterator tau = l1IsoTauJets->begin(); 
	   tau != l1IsoTauJets->end(); 
	 ++tau ) {
	isoTau_pt->Fill( tau->rank() );
      }
    }
  }
  //End Making Rate Plots

  double deltaR_ = 0.5;
  
  //Make efficiencies
  //for(std::vector<reco::PFTauRef>::const_iterator recoTau = goodTaus.begin(); recoTau != goodTaus.end() ; ++recoTau ){
  for(unsigned int i = 0; i < goodTaus.size(); i++){
    reco::PFTauRef recoTau = goodTaus.at(i);
    l1IsoMatched = -1; l1RlxMatched = -1;
    recoPt  = recoTau->pt();
    recoEta = recoTau->eta();
    recoPhi = recoTau->phi();
    isoTauPt = 0; isoTauEta = -99; isoTauPhi = -99; 
    rlxTauPt = 0; rlxTauEta = -99; rlxTauPhi = -99;
    
    if(evt.getByLabel(l1ExtraIsoTauSource_ , l1ExtraIsoTaus))
      for( vector<l1extra::L1JetParticle>::const_iterator isoTau = l1ExtraIsoTaus->begin();  isoTau != l1ExtraIsoTaus->end();  ++isoTau ) {
	double dR = deltaR( recoTau->p4(), isoTau->p4());
	if( dR < deltaR_){
	  //std::cout<<"Pt "<< isoTau->pt() << " Eta "<< isoTau->eta()<< " Phi "<< isoTau->phi()<< " DR "<< dR << endl;
	  //isoTauPt  = isoTau->gctJetCandRef()->rank();//isoTau->pt();
	  isoTauPt  = isoTau->pt();
	  isoTauEta = isoTau->eta();
	  isoTauPhi = isoTau->phi();
	  l1IsoMatched = 1;
	  break;
	}
      }
    
    if(evt.getByLabel(l1ExtraTauSource_, l1ExtraTaus))
      for( vector<l1extra::L1JetParticle>::const_iterator rlxTau = l1ExtraTaus->begin(); rlxTau != l1ExtraTaus->end(); rlxTau++ ) {
	double dR = deltaR( recoTau->p4(), rlxTau->p4());
	if(dR < deltaR_){
	  //isoTauPt  = rlxTau->gctJetCandRef()->rank();//isoTau->pt();
	  rlxTauPt  = rlxTau->pt();
	  rlxTauEta = rlxTau->eta();
	  rlxTauPhi = rlxTau->phi();
	  l1RlxMatched = 1;
	  break;
	}
      }

    efficiencyTree->Fill();
  }
  
}

bool HLTNtuplizer::triggerfound(const edm::Event& ev, edm::Handle<edm::TriggerResults> triggerResultsHandle_, TString trigname){
  const edm::TriggerNames TrigNames_ = ev.triggerNames(*triggerResultsHandle_);
  const unsigned int ntrigs = triggerResultsHandle_->size();
  for (unsigned int itr=0; itr<ntrigs; itr++){
    TString trigName=TrigNames_.triggerName(itr);
    std::cout<<"Trigger Name "<< trigName<<std::endl;
    //if(trigName.Contains(trigname))      return true;
  }
  return true;
  //return false;
}


void HLTNtuplizer::endJob() {
}

HLTNtuplizer::~HLTNtuplizer(){
}

DEFINE_FWK_MODULE(HLTNtuplizer);
