#ifndef __AnalysisSpace_TreeMaker_TriggerBlock_h
#define __AnalysisSpace_TreeMaker_TriggerBlock_h

#include <string>
#include <vector>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/Common/interface/Ref.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Provenance/interface/EventID.h"
#include "FWCore/ParameterSet/interface/ProcessDesc.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

class TriggerBlock : public edm::EDAnalyzer
{
private:
  virtual void beginJob();
  virtual void beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup);
  virtual void analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup);
  virtual void endJob() {}

public:
  explicit TriggerBlock(const edm::ParameterSet& iConfig);
  virtual ~TriggerBlock();

private:

  const int verbosity_;

  const edm::InputTag l1Tag_;
  const edm::InputTag preScaleTag_;
  const edm::InputTag l1minpreScaleTag_;
  const edm::InputTag l1maxpreScaleTag_;
  const edm::InputTag hltTag_;
  const std::vector<std::string> hltPathsOfInterest_;
  HLTConfigProvider hltConfig_;

  std::vector<int>* l1physbits_;
  std::vector<int>* l1techbits_;
  std::vector<std::string>* hltpaths_;
  std::vector<int>* hltresults_;
  std::vector<int>* hltprescales_;
  std::vector<int>* l1minprescales_;
  std::vector<int>* l1maxprescales_;

  const edm::EDGetTokenT<L1GlobalTriggerReadoutRecord> l1Token_;
  const edm::EDGetTokenT<pat::PackedTriggerPrescales> preScaleToken_;
  const edm::EDGetTokenT<pat::PackedTriggerPrescales> l1minpreScaleToken_;
  const edm::EDGetTokenT<pat::PackedTriggerPrescales> l1maxpreScaleToken_;
  const edm::EDGetTokenT<edm::TriggerResults> hltToken_;
  HLTPrescaleProvider hltPrescaleProvider_;
};
#endif
