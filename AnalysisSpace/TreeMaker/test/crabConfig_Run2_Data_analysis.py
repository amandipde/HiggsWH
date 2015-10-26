from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'CRAB3_Run2015D_v4_topup_25ns_SingleElectron'
config.General.workArea = 'crab_Run2'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'rootMaker_DATA_cfg.py'

#config.Data.inputDataset = '/DoubleMuon/Run2015C_50ns-05Oct2015-v1/MINIAOD' #ReMiniAOD of C 50ns
#config.Data.inputDataset = '/DoubleMuon/Run2015B-05Oct2015-v1/MINIAOD' #ReMiniAOD of B 50ns
config.Data.inputDataset = '/SingleElectron/Run2015D-PromptReco-v4/MINIAOD' #MiniAOD of D 2nd part, 25ns 3nd&last part
#config.Data.inputDataset = '/DoubleMuon/Run2015D-05Oct2015-v1/MINIAOD' #ReMiniAOD of D 1st part, 25ns 2nd part
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
#config.Data.lumiMask = '/cmshome/amodak/CMSSW_7_4_14/src/AnalysisSpace/TreeMaker/test/Cert_246908-255031_13TeV_PromptReco_Collisions15_50ns_JSON_v2.txt'
#config.Data.lumiMask = '/cmshome/amodak/CMSSW_7_4_14/src/AnalysisSpace/TreeMaker/test/Cert_246908-258159_13TeV_PromptReco_Collisions15_25ns_JSON_v2.txt'
config.Data.lumiMask = '/cmshome/amodak/CMSSW_7_4_14/src/AnalysisSpace/TreeMaker/test/Cert_246908-258750_13TeV_PromptReco_Collisions15_25ns_JSON.txt'

#config.Data.runRange = '258160-258750' # for 25 ns top up

config.Data.outLFNDirBase = '/store/user/amodak/RUN2/MiniAOD/DATA_v2/CRAB/' # (getUsernameFromSiteDB())
config.Data.publication = False

#config.Data.publishDataName = 'CRAB3_May2015_Data_analysis'

config.Site.storageSite = 'T2_IT_Bari'
