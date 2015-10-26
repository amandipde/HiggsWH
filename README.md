# HiggsWH
create area using:
cmsrel CMSSW_7_4_14
git cms-merge-topic ikrav:egm_id_7.4.12_v1 (for electron MVA ID)

Configs in TreeMaker test area:
crab config for DATA and MC: crabConfig_Run2_Data_analysis.py, crabConfig_Run2_MC_analysis.py
rootMaker config: rootMaker_DATA_cfg.py, rootMaker_MC_cfg.py 
rootMaker_cfg.py_full contains many other stuff like running mvamet, adding external JEC etc...not needed now
Two JSON for 25ns and 50ns
