#!/bin/bash
# init

crab resubmit -d crab_Run2/crab_CRAB3_Run2015B_50ns_SingleElectron
sleep 5s
crab resubmit -d crab_Run2/crab_CRAB3_Run2015C_50ns_SingleElectron
sleep 5s
crab resubmit -d crab_Run2/crab_CRAB3_Run2015C_25ns_SingleElectron
sleep 5s
crab resubmit -d crab_Run2/crab_CRAB3_Run2015D_25ns_SingleElectron
sleep 5s
crab resubmit -d crab_Run2/crab_CRAB3_Run2015B_50ns_SingleMuon
sleep 5s
crab resubmit -d crab_Run2/crab_CRAB3_Run2015C_50ns_SingleMuon
sleep 5s
crab resubmit -d crab_Run2/crab_CRAB3_Run2015C_25ns_SingleMuon
sleep 5s
crab resubmit -d crab_Run2/crab_CRAB3_Run2015D_25ns_SingleMuon
sleep 5s
