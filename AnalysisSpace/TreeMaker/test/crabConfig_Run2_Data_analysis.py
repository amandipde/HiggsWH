from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'Run2016B_v2_SingleElectron'
config.General.workArea = 'crab_DATA_2016'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'rootMaker_DATA_cfg.py'

#config.Data.inputDataset = '/SingleElectron/Run2015C_25ns-05Oct2015-v1/MINIAOD' #ReMiniAOD of C 25ns
#config.Data.inputDataset = '/SingleMuon/Run2015C_50ns-05Oct2015-v1/MINIAOD' #ReMiniAOD of C 50ns
#config.Data.inputDataset = '/DoubleMuon/Run2015B-05Oct2015-v1/MINIAOD' #ReMiniAOD of B 50ns
#config.Data.inputDataset = '/SingleElectron/Run2015D-PromptReco-v4/MINIAOD' #MiniAOD of D 2nd part, 25ns 3nd&last part
#config.Data.inputDataset = '/SingleElectron/Run2015D-05Oct2015-v1/MINIAOD' #ReMiniAOD of D 1st part, 25ns 2nd part

config.Data.inputDataset = '/SingleElectron/Run2016B-PromptReco-v2/MINIAOD'

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
config.Data.lumiMask = '/afs/cern.ch/work/a/amodak/public/HiggsWHRun2/CMSSW_8_0_8_patch1/src/AnalysisSpace/TreeMaker/test/Cert_271036-277148_13TeV_PromptReco_Collisions16_JSON.txt'

#config.Data.runRange = '' 

config.Data.outLFNDirBase = '/store/user/amodak/PerugiaData/2016/' # (getUsernameFromSiteDB())
config.Data.publication = False

#config.Data.publishDataName = 'CRAB3_May2015_Data_analysis'

config.Site.storageSite = 'T2_IT_Bari'
