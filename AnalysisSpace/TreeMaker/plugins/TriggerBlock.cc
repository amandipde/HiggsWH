#include <iostream>
#include <algorithm>

#include "TTree.h"
#include "TPRegexp.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"
#include "AnalysisSpace/TreeMaker/plugins/TriggerBlock.h"
#include "AnalysisSpace/TreeMaker/interface/Utility.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "FWCore/Common/interface/TriggerNames.h"

static const unsigned int NmaxL1AlgoBit = 128;
static const unsigned int NmaxL1TechBit = 64;

// Constructor
TriggerBlock::TriggerBlock(const edm::ParameterSet& iConfig) :
  verbosity_(iConfig.getUntrackedParameter<int>("verbosity", 1)),
//  l1Tag_(iConfig.getUntrackedParameter<edm::InputTag>("l1InputTag", edm::InputTag("gtDigis"))),
  preScaleTag_(iConfig.getUntrackedParameter<edm::InputTag>("l1PreScaleInputTag", edm::InputTag("patTrigger", ""))),
  l1minpreScaleTag_(iConfig.getUntrackedParameter<edm::InputTag>("l1minPreScaleInputTag", edm::InputTag("patTrigger", "l1min"))),
  l1maxpreScaleTag_(iConfig.getUntrackedParameter<edm::InputTag>("l1maxPreScaleInputTag", edm::InputTag("patTrigger", "l1max"))),
  hltTag_(iConfig.getUntrackedParameter<edm::InputTag>("hltInputTag", edm::InputTag("TriggerResults","","HLT"))),
  hltPathsOfInterest_(iConfig.getParameter<std::vector<std::string> >("hltPathsOfInterest")),
//  l1Token_(consumes<L1GlobalTriggerReadoutRecord>(l1Tag_)),
  preScaleToken_(consumes<pat::PackedTriggerPrescales>(preScaleTag_)),
  l1minpreScaleToken_(consumes<pat::PackedTriggerPrescales>(l1minpreScaleTag_)),
  l1maxpreScaleToken_(consumes<pat::PackedTriggerPrescales>(l1maxpreScaleTag_)),
  hltToken_(consumes<edm::TriggerResults>(hltTag_)),
  hltPrescaleProvider_(iConfig, consumesCollector(), *this)
{
}
TriggerBlock::~TriggerBlock() {
  delete l1physbits_;
  delete l1techbits_;
  delete hltpaths_;
  delete hltresults_;
  delete hltprescales_;
  delete l1minprescales_;
  delete l1maxprescales_;
}
void TriggerBlock::beginJob()
{
  std::string tree_name = "vhtree";
  TTree* tree = vhtm::Utility::getTree(tree_name);

  l1physbits_ = new std::vector<int>();
  tree->Branch("l1physbits", "vector<int>", &l1physbits_);

  l1techbits_ = new std::vector<int>();
  tree->Branch("l1techbits", "vector<int>", &l1techbits_);

  hltpaths_ = new std::vector<std::string>();
  tree->Branch("hltpaths", "vector<string>", &hltpaths_);

  hltresults_ = new std::vector<int>();
  tree->Branch("hltresults", "vector<int>", &hltresults_);

  hltprescales_ = new std::vector<int>();
  tree->Branch("hltprescales", "vector<int>", &hltprescales_);

  l1minprescales_ = new std::vector<int>();
  tree->Branch("l1minprescales", "vector<int>", &l1minprescales_);
  l1maxprescales_ = new std::vector<int>();
  tree->Branch("l1maxprescales", "vector<int>", &l1maxprescales_);
}
void TriggerBlock::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup) {
  std::cout << "begin run" << std::endl;
  bool changed = true;
  if (hltConfig_.init(iRun, iSetup, hltTag_.process(), changed)) {
    // if init returns TRUE, initialisation has succeeded!
    edm::LogInfo("TriggerBlock") << "HLT config with process name "
                                 << hltTag_.process() << " successfully extracted";
  }
  else {
    // if init returns FALSE, initialisation has NOT succeeded, which indicates a problem
    // with the file and/or code and needs to be investigated!
    edm::LogError("TriggerBlock") << "Error! HLT config extraction with process name "
                                  << hltTag_.process() << " failed";
    // In this case, all access methods will return empty values!
  }
  //bool isChanged = true;
  //hltPrescaleProvider_.init(iRun, iSetup, "HLT", isChanged);
}
void TriggerBlock::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  std::cout << "1" << std::endl;
  // Reset the vectors
  l1physbits_->clear();
  l1techbits_->clear();
  hltpaths_->clear();
  hltresults_->clear();
  hltprescales_->clear();
  l1minprescales_->clear();
  l1maxprescales_->clear();

  //New way of having prescale
  edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;
  iEvent.getByToken(preScaleToken_, triggerPrescales);
  std::cout << "2" << std::endl;

  edm::Handle<pat::PackedTriggerPrescales> triggerPrescalesl1min;
  iEvent.getByToken(l1minpreScaleToken_, triggerPrescalesl1min);
  std::cout << "3" << std::endl;

  edm::Handle<pat::PackedTriggerPrescales> triggerPrescalesl1max;
  iEvent.getByToken(l1maxpreScaleToken_, triggerPrescalesl1max);
  std::cout << "4" << std::endl;

  edm::Handle<edm::TriggerResults> triggerResults;
  bool found = iEvent.getByToken(hltToken_, triggerResults);
  if (found && triggerResults.isValid()) {
    std::cout << "inside trigger result 1" << std::endl;
    edm::LogInfo("TriggerBlock") << "Successfully obtained " << hltTag_;
    const std::vector<std::string>& pathList = hltConfig_.triggerNames();
    for (auto path: pathList) {
      if (hltPathsOfInterest_.size()) {
        int nmatch = 0;
        for (auto kt: hltPathsOfInterest_) {
          nmatch += TPRegexp(kt).Match(path);
        }
        if (!nmatch) continue;
      }
      hltpaths_->push_back(path);

      int fired = -1;
      int prescale = -1;
      int prescale_l1min = -1;
      int prescale_l1max = -1;
      unsigned int index = hltConfig_.triggerIndex(path);
      if (index < triggerResults->size()) {
        fired    = (triggerResults->accept(index)) ? 1 : 0;
        prescale = triggerPrescales->getPrescaleForIndex(index);
        prescale_l1min = triggerPrescalesl1min->getPrescaleForIndex(index);
        prescale_l1max = triggerPrescalesl1max->getPrescaleForIndex(index);
      }
      else {
        edm::LogInfo("TriggerBlock") << "Requested HLT path \"" << path << "\" does not exist";
      }
      hltresults_->push_back(fired);
      hltprescales_->push_back(prescale);
      l1minprescales_->push_back(prescale_l1min);
      l1maxprescales_->push_back(prescale_l1max);

      if (verbosity_) {
      }    
    }      
  } 
  else {
    edm::LogError("TriggerBlock") << "Failed to get TriggerResults for label: "
                                  << hltTag_;
  }
}
#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(TriggerBlock);
