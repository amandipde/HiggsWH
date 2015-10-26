// -*- C++ -*-
//
// Package:    MyFilter/mttORettFilter
// Class:      mttORettFilter
// 
/**\class mttORettFilter mttORettFilter.cc MyFilter/mttORettFilter/plugins/mttORettFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  
//         Created:  Wed, 20 Aug 2014 14:27:14 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

//
// class declaration
//

class mttORettFilter : public edm::EDFilter {
   public:
      explicit mttORettFilter(const edm::ParameterSet&);
      ~mttORettFilter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      
      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
      edm::InputTag srcMuons_;
      edm::InputTag srcElectrons_;
      edm::InputTag srcTaus_;
      double minMuonPt_;
      double minElectronPt_;
      double minTauPt_;
      double maxMuonEta_;
      double maxElectronEta_;
      double maxTauEta_;

      edm::EDGetTokenT<pat::MuonCollection> muonToken_;
      edm::EDGetTokenT<pat::ElectronCollection> elecToken_;
      edm::EDGetTokenT<pat::TauCollection> tauToken_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
mttORettFilter::mttORettFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
  srcMuons_ = iConfig.getParameter<edm::InputTag>("srcMuons");
  srcElectrons_ = iConfig.getParameter<edm::InputTag>("srcElectrons");
  srcTaus_ = iConfig.getParameter<edm::InputTag>("srcTaus");
  muonToken_ = consumes<pat::MuonCollection>(srcMuons_);
  elecToken_ = consumes<pat::ElectronCollection>(srcElectrons_);
  tauToken_ = consumes<pat::TauCollection>(srcTaus_);

  minMuonPt_ = iConfig.getParameter<double>("MinMuonPt");
  minElectronPt_ = iConfig.getParameter<double>("MinElectronPt");
  minTauPt_ = iConfig.getParameter<double>("MinTauPt");
  maxMuonEta_ = iConfig.getParameter<double>("MaxMuonEta");
  maxElectronEta_ = iConfig.getParameter<double>("MaxElectronEta");
  maxTauEta_ = iConfig.getParameter<double>("MaxTauEta");
}


mttORettFilter::~mttORettFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
mttORettFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   // Input pat::Muon
   edm::Handle<pat::MuonCollection> muonsHandle;
   iEvent.getByToken(muonToken_, muonsHandle);
   const pat::MuonCollection* muons = muonsHandle.product();

   // electrons
   edm::Handle<pat::ElectronCollection> electronsHandle;
   iEvent.getByToken(elecToken_, electronsHandle);
   const pat::ElectronCollection* electrons = electronsHandle.product();

   // taus
   edm::Handle<pat::TauCollection> tausHandle;
   iEvent.getByToken(tauToken_, tausHandle);
   const pat::TauCollection* taus = tausHandle.product();

   int tauCount = 0;
   for (auto it = taus->begin(); it != taus->end(); ++it) {
     pat::Tau pTau((*it));
     if (pTau.pt() > minTauPt_ && std::abs(pTau.eta()) < maxTauEta_) tauCount += 1;
     if (tauCount >= 2) break;
   }

   int eleCount = 0;
   for (auto it = electrons->begin(); it != electrons->end(); ++it) {
     pat::Electron pElectron((*it));
     if (pElectron.pt() > minElectronPt_ && std::abs(pElectron.eta()) < maxElectronEta_) eleCount += 1;
     if (eleCount >= 1) break;
   }

   int muoCount = 0;
   for (auto it = muons->begin(); it != muons->end(); ++it) {
     pat::Muon pMuon((*it));
     if (pMuon.pt() > minMuonPt_ && std::abs(pMuon.eta()) < maxMuonEta_) muoCount += 1;
     if (muoCount >= 1) break;
   }

   std::cout << "MTT or ETT Filterting ......" << std::endl;
   if ((muoCount >= 1 || eleCount >=1) && tauCount >= 2) return true;
   else return false;
}

// ------------ method called once each job just before starting event loop  ------------
void 
mttORettFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
mttORettFilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
mttORettFilter::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
mttORettFilter::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
mttORettFilter::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
mttORettFilter::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
mttORettFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(mttORettFilter);
