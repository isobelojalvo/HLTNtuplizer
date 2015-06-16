import FWCore.ParameterSet.Config as cms


l1NtupleProducer = cms.EDAnalyzer("HLTNtuplizer",
                                  rctSource            = cms.InputTag("simRctDigis"),
                                  gctTauJetsSource     = cms.InputTag("simCaloStage1LegacyFormatDigis","tauJets"),
                                  gctIsoTauJetsSource  = cms.InputTag("simCaloStage1LegacyFormatDigis","isoTauJets"),
                                  l1ExtraTauSource     = cms.InputTag("hltL1extraParticles","Tau"),
                                  l1ExtraIsoTauSource  = cms.InputTag("hltL1extraParticles","IsoTau"),
                                  recoTau              = cms.InputTag("hpsPFTauProducer"),
                                  recoTauDiscriminator = cms.InputTag("hpsPFTauDiscriminationByLooseIsolation"),
                                  folderName           = cms.untracked.string("firstFolder"),
                                  filters              = cms.vstring(
                                                         'hltL1sMu16erTauJet20er',
                                                         'hltOverlapFilterIsoMu17LooseIsoPFTau20',
                                                         'hltL1sL1IsoEG20erTauJet20er',
                                                         'hltOverlapFilterIsoEle22WP85GsfLooseIsoPFTau20'
                                            ),
#reco::PFTauDiscriminator              "hpsPFTauDiscriminationByLooseIsolation"
)
