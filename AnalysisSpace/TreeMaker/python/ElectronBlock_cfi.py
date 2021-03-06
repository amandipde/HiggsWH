import FWCore.ParameterSet.Config as cms

electronBlock = cms.EDAnalyzer("ElectronBlock",
  verbosity = cms.untracked.int32(1),
  beamSpotCorr = cms.untracked.bool(True),
  offlineBeamSpot = cms.untracked.InputTag('offlineBeamSpot'),
  vertexSrc = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
  #vertexSrc = cms.untracked.InputTag('offlineSlimmedPrimaryVertices'),
  #electronSrc = cms.untracked.InputTag('slimmedElectrons'),
  electronSrc = cms.untracked.InputTag('UserElectron')
)
