from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'Run2016G_ReReco_v1_SingleElectron'
config.General.workArea = 'crab_DATA_2016'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'rootMaker_DATA_cfg.py'

config.Data.inputDataset = '/SingleElectron/Run2016G-23Sep2016-v1/MINIAOD' #ReReco
#config.Data.inputDataset = '/SingleElectron/Run2016H-PromptReco-v3/MINIAOD' #PromptReco
config.JobType.sendExternalFolder = True

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
config.Data.lumiMask = '/afs/cern.ch/work/a/amodak/public/HiggsWHRun2/CMSSW_8_0_20/src/AnalysisSpace/TreeMaker/test/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'

#config.Data.runRange = '' 

config.Data.outLFNDirBase = '/store/user/amodak/PerugiaData/2016/' # (getUsernameFromSiteDB())
config.Data.publication = False

#config.Data.publishDataName = 'CRAB3_May2015_Data_analysis'

config.Site.storageSite = 'T2_IT_Bari'
