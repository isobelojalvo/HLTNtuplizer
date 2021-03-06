#!/bin/sh                                                                                                                                                                                                                                                                                                                     
#voms-proxy-init --voms cms --valid 100:00                                                                                                                                                                                                                                                                                   
cat Stage1RCTCalib.py > SUBStage1.py
cat submit.py >> SUBStage1.py

farmoutAnalysisJobs    --vsize-limit=8000  --skip-existing-output --input-dir=/store/mc/Fall13dr/Neutrino_Pt-2to20_gun/GEN-SIM-RAW/tsg_PU40bx25_POSTLS162_V2-v1/    tauRates-rctCal-e3-h3       $CMSSW_BASE   $CMSSW_BASE/src/L1Trigger/L1TNtuplizer/test/SUBStage1.py eActivityCut=3 hActivityCut=3 tauThresh=2 tauNThresh=0 maxPtTauVeto=64 tauMinPtIso=192 tauMaxJetIso=100 tauIsoValue=0.1
farmoutAnalysisJobs    --vsize-limit=8000  --skip-existing-output --input-dir=/store/mc/Fall13dr/Neutrino_Pt-2to20_gun/GEN-SIM-RAW/tsg_PU40bx25_POSTLS162_V2-v1/    tauRates-rctCal-e4-h4       $CMSSW_BASE   $CMSSW_BASE/src/L1Trigger/L1TNtuplizer/test/SUBStage1.py eActivityCut=4 hActivityCut=4 tauThresh=2 tauNThresh=0 maxPtTauVeto=64 tauMinPtIso=192 tauMaxJetIso=100 tauIsoValue=0.1
farmoutAnalysisJobs    --vsize-limit=8000  --skip-existing-output --input-dir=/store/mc/Fall13dr/Neutrino_Pt-2to20_gun/GEN-SIM-RAW/tsg_PU40bx25_POSTLS162_V2-v1/    tauRates-rctCal-e5-h5       $CMSSW_BASE   $CMSSW_BASE/src/L1Trigger/L1TNtuplizer/test/SUBStage1.py eActivityCut=5 hActivityCut=5 tauThresh=2 tauNThresh=0 maxPtTauVeto=64 tauMinPtIso=192 tauMaxJetIso=100 tauIsoValue=0.1
farmoutAnalysisJobs    --vsize-limit=8000  --skip-existing-output --input-dir=/store/mc/Fall13dr/Neutrino_Pt-2to20_gun/GEN-SIM-RAW/tsg_PU40bx25_POSTLS162_V2-v1/    tauRates-rctCal-e6-h6       $CMSSW_BASE   $CMSSW_BASE/src/L1Trigger/L1TNtuplizer/test/SUBStage1.py eActivityCut=6 hActivityCut=6 tauThresh=2 tauNThresh=0 maxPtTauVeto=64 tauMinPtIso=192 tauMaxJetIso=100 tauIsoValue=0.1

farmoutAnalysisJobs    --vsize-limit=8000  --skip-existing-output --input-dir=/store/mc/Fall13dr/Neutrino_Pt-2to20_gun/GEN-SIM-RAW/tsg_PU40bx25_POSTLS162_V2-v1/    tauRates-rctCal-e3-h5       $CMSSW_BASE   $CMSSW_BASE/src/L1Trigger/L1TNtuplizer/test/SUBStage1.py eActivityCut=3 hActivityCut=5 tauThresh=2 tauNThresh=0 maxPtTauVeto=64 tauMinPtIso=192 tauMaxJetIso=100 tauIsoValue=0.1

farmoutAnalysisJobs    --vsize-limit=8000  --skip-existing-output --input-dir=/store/mc/Fall13dr/Neutrino_Pt-2to20_gun/GEN-SIM-RAW/tsg_PU40bx25_POSTLS162_V2-v1/    tauRates-rctCal-e3-h6       $CMSSW_BASE   $CMSSW_BASE/src/L1Trigger/L1TNtuplizer/test/SUBStage1.py eActivityCut=3 hActivityCut=6 tauThresh=2 tauNThresh=0 maxPtTauVeto=64 tauMinPtIso=192 tauMaxJetIso=100 tauIsoValue=0.1

farmoutAnalysisJobs    --vsize-limit=8000  --skip-existing-output --input-dir=/store/mc/Fall13dr/Neutrino_Pt-2to20_gun/GEN-SIM-RAW/tsg_PU40bx25_POSTLS162_V2-v1/    tauRates-rctCal-e4-h5       $CMSSW_BASE   $CMSSW_BASE/src/L1Trigger/L1TNtuplizer/test/SUBStage1.py eActivityCut=4 hActivityCut=5 tauThresh=2 tauNThresh=0 maxPtTauVeto=64 tauMinPtIso=192 tauMaxJetIso=100 tauIsoValue=0.1

farmoutAnalysisJobs    --vsize-limit=8000  --skip-existing-output --input-dir=/store/mc/Fall13dr/Neutrino_Pt-2to20_gun/GEN-SIM-RAW/tsg_PU40bx25_POSTLS162_V2-v1/    tauRates-rctCal-e4-h6       $CMSSW_BASE   $CMSSW_BASE/src/L1Trigger/L1TNtuplizer/test/SUBStage1.py eActivityCut=4 hActivityCut=6 tauThresh=2 tauNThresh=0 maxPtTauVeto=64 tauMinPtIso=192 tauMaxJetIso=100 tauIsoValue=0.1

#farmoutAnalysisJobs    --vsize-limit=8000  --skip-existing-output --input-dir=/store/user/alevine/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6/     tauSeed-9-hTT       $CMSSW_BASE   $CMSSW_BASE/src/L1Trigger/L1TNtuplizer/test/SUBStage1.py eActivityCut=4 hActivityCut=4 tauThresh=2 tauNThresh=0 maxPtTauVeto=64 tauMinPtIso=192 tauMaxJetIso=100 tauIsoValue=0.1
#farmoutAnalysisJobs    --vsize-limit=8000  --skip-existing-output --input-dir=/store/mc/Fall13dr/Neutrino_Pt-2to20_gun/GEN-SIM-RAW/tsg_PU40bx25_POSTLS162_V2-v1/   tauSeed-9-neutrinoGunPU40bx25    $CMSSW_BASE   $CMSSW_BASE/src/L1Trigger/L1TNtuplizer/test/SUBStage1.py eActivityCut=5 hActivityCut=5 tauThresh=2 tauNThresh=0 maxPtTauVeto=64 tauMinPtIso=192 tauMaxJetIso=100 tauIsoValue=0.1

rm SUBStage1.py

#tauSeed-7-hTT was 5 actually