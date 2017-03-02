import FWCore.ParameterSet.Config as cms

triggerBlock = cms.EDAnalyzer("TriggerBlock",
  verbosity = cms.untracked.int32(1),
  l1InputTag = cms.untracked.InputTag('gtDigis'),
  hltInputTag = cms.untracked.InputTag('TriggerResults','','HLT2'), #Due to reHLT in MC, process name changed
#  hltInputTag = cms.untracked.InputTag('TriggerResults','','HLT'),
  l1PreScaleInputTag = cms.untracked.InputTag('patTrigger', ''),
  l1minPreScaleInputTag = cms.untracked.InputTag('patTrigger', 'l1min'),
  l1maxPreScaleInputTag = cms.untracked.InputTag('patTrigger', 'l1max'),
  hltPathsOfInterest = cms.vstring ()
#  if no path of interest are provided all will be saved
#  hltPathsOfInterest = cms.vstring ("HLT_DoubleMu",
#                                    "HLT_Mu",
#                                    "HLT_IsoMu",
#                                    "HLT_TripleMu",
#                                    "IsoPFTau",
#                                    "TrkIsoT",
#                                    "HLT_Ele")
)
