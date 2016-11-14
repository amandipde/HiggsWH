#!/bin/bash
set -o nounset
particle_name=DYJets_Skim_40PU_PF2PAT 

let "nfile = 3"
let "i = 0"
filelist=""
let "j = 0"

for file in `cat /cmshome/amodak/prod/CMSSW_7_0_6_patch1/src/RecoTauTag/RecoTau/test/DYJets/70X_40PU.list | grep '^/store'`
do

  let "++i"
  filelist=$filelist"  '"$file"',"
  if [ $i -eq $nfile ]; then
    let "j++"
  cname="$particle_name""_CSA14_""$j""_cfg.py"
  oname="$particle_name""_CSA14_""$j"".root"
  lname="$particle_name""_CSA14_""$j"".log"
  echo $filelist
  echo $cname
  sed -e "s@INPUT_FILES@$filelist@g" \
      -e "s@OUTPUT_FILE@$oname@g" \
       ConfFile_cfg.py.tmpl > $cname

  jname='subDYJets_PU40_job_'$j
  echo $jname
  sed -e "s@INDX@$j@g" \
      -e "s@JOB_NAME@$cname@g" \
      -e "s@LOG_NAME@$lname@g"\
      -e "s@OUTPUT_FILE@$oname@g"\
      submitjob.tmpl > $jname      
#  chmod 755 $jname
   let "i = 0"
    filelist=""
  echo "submitting job : "$jname
#qsub -q local < $jname
  fi
done
