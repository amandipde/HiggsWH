import FWCore.ParameterSet.Config as cms
process = cms.Process("TreeMaker")
#------------------------
# Message Logger Settings
#------------------------
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1
process.MessageLogger.infos.threshold = cms.untracked.string("ERROR")

process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')

#--------------------------------------
# Event Source & # of Events to process
#---------------------------------------
Source_Files = cms.untracked.vstring()     
process.source = cms.Source("PoolSource",
  fileNames = Source_Files
)
process.maxEvents = cms.untracked.PSet(
  input = cms.untracked.int32(-1)
)
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

#-----------------------------
# Geometry
#-----------------------------
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
#-----------------------------
# Magnetic Field
#-----------------------------
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')

#=============================================================
#-------------
# Global Tag
#-------------
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
#process.GlobalTag.globaltag = '80X_mcRun2_asymptotic_2016_miniAODv2_v1'
process.GlobalTag.globaltag = '80X_mcRun2_asymptotic_2016_TrancheIV_v8'

#--------------------------------------------------
# Analysis Tree Specific
#--------------------------------------------------
process.load('AnalysisSpace.TreeMaker.TreeCreator_cfi')
process.load('AnalysisSpace.TreeMaker.TreeWriter_cfi')
process.load('AnalysisSpace.TreeMaker.TreeContentConfig_cff')

#################################################################
#
# Set up electron ID (VID framework)
#
from RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff import *
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
# turn on VID producer, indicate data format  to be
# DataFormat.AOD or DataFormat.MiniAOD, as appropriate

switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
# define which IDs we want to produce
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff']

#add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

#################################################################
#User Defined Collections
#################################################################

process.UserElectron = cms.EDProducer('ElectronsUserEmbedder',
  beamSpotCorr = cms.untracked.bool(True),
  offlineBeamSpot = cms.untracked.InputTag('offlineBeamSpot'),
  vertexSrc = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
  #vertexSrc = cms.untracked.InputTag('offlineSlimmedPrimaryVertices'),
  electronSrc = cms.untracked.InputTag('slimmedElectrons'),
  eleMediumIdMap = cms.InputTag("egmGsfElectronIDs:mvaEleID-Spring16-GeneralPurpose-V1-wp90"),
  eleTightIdMap = cms.InputTag("egmGsfElectronIDs:mvaEleID-Spring16-GeneralPurpose-V1-wp80"),
  mvaValuesMap = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring16GeneralPurposeV1Values"),
  mvaCategoriesMap = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring16GeneralPurposeV1Categories"),
)

process.UserMuon = cms.EDProducer('MuonsUserEmbedder',
  beamSpotCorr = cms.untracked.bool(True),
  offlineBeamSpot = cms.untracked.InputTag('offlineBeamSpot'),
  vertexSrc = cms.untracked.InputTag('goodOfflinePrimaryVertices'),
  #vertexSrc = cms.untracked.InputTag('offlineSlimmedPrimaryVertices'),
  muonSrc = cms.untracked.InputTag('slimmedMuons'),
)

process.goodOfflinePrimaryVertices = cms.EDFilter("VertexSelector",
  src = cms.InputTag('offlineSlimmedPrimaryVertices'),
  cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && abs(position.Rho) <= 2"),
  filter = cms.bool(True)                                          
)
#############################################################################
#Prepare lepton collections for MVA MET 
#############################################################################
process.ElectronsForMVAMet = cms.EDFilter("PATElectronSelector",
        src = cms.InputTag("UserElectron"),
        cut = cms.string("pt >= 20.0 && abs(eta) < 2.1 && userFloat('mvaId') > 0.0 && userFloat('pfRelIso') < 0.1"),
        filter = cms.bool(False)
)
process.MuonsForMVAMet = cms.EDFilter("PATMuonSelector",
        src = cms.InputTag("UserMuon"),
        cut = cms.string("pt >= 20.0 && abs(eta) < 2.1 && isGlobalMuon && userFloat('chargedHadronIso') < 0.1"),
        filter = cms.bool(False)
)
process.TausForMVAMet = cms.EDFilter('PATTauSelector',
        src = cms.InputTag('slimmedTaus'),
        cut = cms.string("pt > 20 && abs(eta) < 2.3 && tauID('decayModeFinding') > 0.5 && tauID('againstMuonTight3') > 0.5 && tauID('againstElectronLooseMVA5') > 0.5 && tauID('chargedIsoPtSum') < 2.0"),
        filter = cms.bool(False)
)

process.p = cms.Path(
  process.goodOfflinePrimaryVertices*
  process.egmGsfElectronIDSequence*
  process.UserElectron*
  process.UserMuon*
#  process.ElectronsForMVAMet*
#  process.MuonsForMVAMet*
#  process.TausForMVAMet*
  process.treeCreator*
  process.treeContentSequence*
  process.treeWriter
)
#################################
#-------------
# Output ROOT file
#-------------
process.TFileService = cms.Service("TFileService",
   fileName = cms.string('Summer16_MiniAODv2.root')
)

