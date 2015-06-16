#!/bin/sh 
mkdir /scratch/ojalvo/tauSeedStudy
cd /scratch/ojalvo/tauSeedStudy

#farmoutAnalysisJobs \
#   --merge \
#   --input-files-per-job=100 \
#   --input-dir=root://cmsxrootd.hep.wisc.edu//store/user/ojalvo/tauSeed-7-hTT-really-SUBStage1 \
#   htt-tauSeed-7 \
#   /cms/ojalvo/stage1Emulator/test1/CMSSW_7_5_0_pre1


for dir in tau-e3-h3 tau-e3-h6 tau-e4-h5 tau-e5-h5 tau-rctCal-e3-h3 tau-rctCal-e3-h6 tau-rctCal-e4-h5 tau-rctCal-e5-h5 tau-e3-h5 tau-e4-h4 tau-e4-h6 tau-e6-h6 tau-rctCal-e3-h5 tau-rctCal-e4-h4 tau-rctCal-e4-h6 tau-rctCal-e6-h6;
do
    hadd $dir /hdfs/store/user/ojalvo/$dir-SUBStage1-merge-mergeFilesJob/*
done

#hadd $dir /hdfs/store/user/ojalvo/tau-e3-h3-SUBStage1-merge-mergeFilesJob/*
