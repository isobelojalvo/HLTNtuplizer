import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')

options.register ('eActivityCut',   4, VarParsing.multiplicity.singleton, VarParsing.varType.int,
                  "Tau Veto ECAL Activity Threshold")

options.parseArguments()
print '========Tau Parameter Configuration======='
print 'eActivityCut =   ',options.eActivityCut,' GeV'

process = cms.Process('L1TEMULATION')

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.Geometry.GeometryIdeal_cff')

# Select the Message Logger output you would like to see:
process.load('FWCore.MessageService.MessageLogger_cfi')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10000)
    )

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring(
        "file:/hdfs/store/mc/Fall13dr/Neutrino_Pt-2to20_gun/GEN-SIM-RAW/tsg_PU40bx25_POSTLS162_V2-v1/00004/FE73ECAD-0C7F-E311-BC2C-0025905A60CA.root", ##ZeroBias
"/store/user/alevine/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6_Sept12AtUW_Fall13dr-tsg_PU40bx25_POSTLS162_V2-v1/05a81b8d696d27a5c3c2ca036967addd/skim_100_1_35f.root",
"/store/user/alevine/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6_Sept12AtUW_Fall13dr-tsg_PU40bx25_POSTLS162_V2-v1/05a81b8d696d27a5c3c2ca036967addd/skim_101_1_Am4.root",
"/store/user/alevine/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6_Sept12AtUW_Fall13dr-tsg_PU40bx25_POSTLS162_V2-v1/05a81b8d696d27a5c3c2ca036967addd/skim_102_1_3Us.root",
"/store/user/alevine/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6_Sept12AtUW_Fall13dr-tsg_PU40bx25_POSTLS162_V2-v1/05a81b8d696d27a5c3c2ca036967addd/skim_103_1_eYo.root",
"/store/user/alevine/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6_Sept12AtUW_Fall13dr-tsg_PU40bx25_POSTLS162_V2-v1/05a81b8d696d27a5c3c2ca036967addd/skim_104_1_tlE.root",
"/store/user/alevine/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6_Sept12AtUW_Fall13dr-tsg_PU40bx25_POSTLS162_V2-v1/05a81b8d696d27a5c3c2ca036967addd/skim_105_1_pL0.root",
"/store/user/alevine/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6_Sept12AtUW_Fall13dr-tsg_PU40bx25_POSTLS162_V2-v1/05a81b8d696d27a5c3c2ca036967addd/skim_106_1_sRJ.root",
"/store/user/alevine/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6_Sept12AtUW_Fall13dr-tsg_PU40bx25_POSTLS162_V2-v1/05a81b8d696d27a5c3c2ca036967addd/skim_107_1_mEU.root",
"/store/user/alevine/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6_Sept12AtUW_Fall13dr-tsg_PU40bx25_POSTLS162_V2-v1/05a81b8d696d27a5c3c2ca036967addd/skim_108_1_0M9.root",
"/store/user/alevine/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6_Sept12AtUW_Fall13dr-tsg_PU40bx25_POSTLS162_V2-v1/05a81b8d696d27a5c3c2ca036967addd/skim_109_1_sig.root",
"/store/user/alevine/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6_Sept12AtUW_Fall13dr-tsg_PU40bx25_POSTLS162_V2-v1/05a81b8d696d27a5c3c2ca036967addd/skim_10_1_Pel.root"
                                      )
    )

process.options = cms.untracked.PSet()


process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('L1Tree.root')
)


process.load("L1Trigger.L1TNtuplizer.l1NtupleProducer_cfi")

process.p1 = cms.Path(
    process.HLTNtupleProducer
    )

process.schedule = cms.Schedule(
    process.p1
    )

# Spit out filter efficiency at the end.
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
