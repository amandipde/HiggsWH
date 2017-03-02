// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/Common/interface/ValueMap.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

#include "DataFormats/PatCandidates/interface/Isolation.h"


using namespace std;
using namespace reco;
class EGammaMvaEleEstimatorCSA14;
//
// class declaration
//

class ElectronsUserEmbedder : public edm::EDProducer {
   public:
      explicit ElectronsUserEmbedder(const edm::ParameterSet&);
      ~ElectronsUserEmbedder();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   enum {
     kMaxElectron_ = 100
   };

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------

      bool bsCorr_;
      bool trigMode_;
      const edm::InputTag bsTag_;
      const edm::InputTag vertexTag_;
      const edm::InputTag electronTag_;

      const edm::EDGetTokenT<reco::BeamSpot> bsToken_;
      const edm::EDGetTokenT<reco::VertexCollection> vertexToken_;
      const edm::EDGetTokenT<pat::ElectronCollection> electronToken_;
      const edm::EDGetToken electronTokenMVAId_;

      // ID decisions objects
      edm::EDGetTokenT<edm::ValueMap<bool> > eleMediumIdMapToken_;
      edm::EDGetTokenT<edm::ValueMap<bool> > eleTightIdMapToken_;

      // MVA values and categories (optional)
      edm::EDGetTokenT<edm::ValueMap<float> > mvaValuesMapToken_;
      edm::EDGetTokenT<edm::ValueMap<int> > mvaCategoriesMapToken_;

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
ElectronsUserEmbedder::ElectronsUserEmbedder(const edm::ParameterSet& iConfig) :

  bsCorr_(iConfig.getUntrackedParameter<bool>("beamSpotCorr", false)),
  trigMode_(iConfig.getUntrackedParameter<bool>("useTrigMode", false)),
  bsTag_(iConfig.getUntrackedParameter<edm::InputTag>("offlineBeamSpot", edm::InputTag("offlineBeamSpot"))),
  vertexTag_(iConfig.getUntrackedParameter<edm::InputTag>("vertexSrc", edm::InputTag("goodOfflinePrimaryVertices"))),
  electronTag_(iConfig.getUntrackedParameter<edm::InputTag>("electronSrc", edm::InputTag("selectedPatElectrons"))),
  bsToken_(consumes<reco::BeamSpot>(bsTag_)),
  vertexToken_(consumes<reco::VertexCollection>(vertexTag_)),
  electronToken_(consumes<pat::ElectronCollection>(electronTag_)),
  electronTokenMVAId_(consumes<edm::View<reco::GsfElectron> >(electronTag_)),
  eleMediumIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleMediumIdMap"))),
  eleTightIdMapToken_(consumes<edm::ValueMap<bool> >(iConfig.getParameter<edm::InputTag>("eleTightIdMap"))),
  mvaValuesMapToken_(consumes<edm::ValueMap<float> >(iConfig.getParameter<edm::InputTag>("mvaValuesMap"))),
  mvaCategoriesMapToken_(consumes<edm::ValueMap<int> >(iConfig.getParameter<edm::InputTag>("mvaCategoriesMap")))
{
  produces<pat::ElectronCollection>("");
}

ElectronsUserEmbedder::~ElectronsUserEmbedder()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
ElectronsUserEmbedder::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace reco;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  std::auto_ptr< pat::ElectronCollection > electronsUserEmbeddedColl( new pat::ElectronCollection() ) ;

  edm::Handle<pat::ElectronCollection> electrons;
  bool found = iEvent.getByToken(electronToken_, electrons);

  edm::Handle<edm::View<reco::GsfElectron>> MVAIDelectrons;
  iEvent.getByToken(electronTokenMVAId_, MVAIDelectrons);


  //Get MVA ID WP
  edm::Handle<edm::ValueMap<bool> > medium_id_decisions;
  edm::Handle<edm::ValueMap<bool> > tight_id_decisions; 
  iEvent.getByToken(eleMediumIdMapToken_,medium_id_decisions);
  iEvent.getByToken(eleTightIdMapToken_,tight_id_decisions);

  // Get MVA values and categories (optional)
  edm::Handle<edm::ValueMap<float> > mvaValues;
  edm::Handle<edm::ValueMap<int> > mvaCategories;
  iEvent.getByToken(mvaValuesMapToken_,mvaValues);
  iEvent.getByToken(mvaCategoriesMapToken_,mvaCategories);


  if (found && electrons.isValid()) {
    edm::Handle<reco::BeamSpot> beamSpot;
    if (bsCorr_) iEvent.getByToken(bsToken_, beamSpot);

    edm::Handle<reco::VertexCollection> primaryVertices;
    iEvent.getByToken(vertexToken_, primaryVertices);

    size_t i = 0;
    for (const pat::Electron& v: *electrons) {

      const auto elMVA = MVAIDelectrons->ptrAt(i);
      pat::Electron userElectron (v);
      
      // PF Isolation
      reco::GsfElectron::PflowIsolationVariables pfIso = v.pfIsolationVariables();
      float absiso = pfIso.sumChargedHadronPt + std::max(0.0, pfIso.sumNeutralHadronEt + pfIso.sumPhotonEt - 0.5 * pfIso.sumPUPt);
      float iso = absiso/(v.p4().pt());
      userElectron.addUserFloat("pfRelIso", iso);

      bool isPassMedium = (*medium_id_decisions)[elMVA];
      bool isPassTight  = (*tight_id_decisions)[elMVA];
      userElectron.addUserInt("isPassMedium_MVAIDWP90", (int) isPassMedium);
      userElectron.addUserInt("isPassTight_MVAIDWP80", (int) isPassTight);
      userElectron.addUserFloat("mvaId", (*mvaValues)[elMVA]);
      //userElectron.addUserFloat("mvaId_def", v.userFloat("ElectronMVAEstimatorRun2Spring16GeneralPurpose"));

      electronsUserEmbeddedColl->push_back(userElectron);
      ++i;
    }
  }

  iEvent.put( electronsUserEmbeddedColl );
  return;
}

// ------------ method called once each job just before starting event loop  ------------
void 
ElectronsUserEmbedder::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ElectronsUserEmbedder::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
ElectronsUserEmbedder::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
ElectronsUserEmbedder::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
ElectronsUserEmbedder::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
ElectronsUserEmbedder::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ElectronsUserEmbedder::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ElectronsUserEmbedder);
