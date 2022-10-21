import array 
import numpy as np

ElePt_L1_bins  = array.array('d', np.concatenate((np.arange(0., 20., step=2), np.arange(20., 80., step=10), [80., 260.])))
ElePt_Off_bins = ElePt_L1_bins

TauPt_L1_bins = array.array('d', np.concatenate((np.arange(0, 40, step=4), np.arange(40, 100, step=10),\
                                                  [100, 150, 200, 320])))
TauPt_Off_bins = TauPt_L1_bins 

Jet1Pt_L1_bins = array.array('d', np.concatenate((np.arange(0, 40, step=4), np.arange(40, 200, step=10),\
                                                 [200, 250, 300, 600])))
Jet1Pt_Off_bins = Jet1Pt_L1_bins

Jet2Pt_L1_bins = array.array('d', np.concatenate((np.arange(0, 40, step=4), np.arange(40, 100, step=10),\
                                                 [120, 200])))
Jet2Pt_Off_bins = Jet2Pt_L1_bins

Mjj_L1_bins = array.array('d', np.concatenate((np.arange(0, 400, step=40), np.arange(500, 2000, step=100),\
                                               np.arange(2000, 4000, step=500), [4000, 7000])))
Mjj_Off_bins = Mjj_L1_bins

var_configs = { #"Key" :   ["plot title string",
                           #"Latex axis label,
                           # L1 bins,
                           # Offline bins,]

                "TauPt" :  ["Tau pT",
                           "p_{T}^{#tau}",
                           TauPt_L1_bins,
                           TauPt_Off_bins,
                           ],
                "ElePt" :  ["Electron pT",
                            "p_{T}^{e}",
                            ElePt_L1_bins,
                            ElePt_Off_bins,
                           ],

                "Jet1Pt" : ["Jet1 pT",
                            "p_{T}^{j1}",
                            Jet1Pt_L1_bins,
                            Jet1Pt_Off_bins,
                           ],

                "Jet2Pt" : ["Jet2 pT",
                            "p_{T}^{j2}",
                            Jet2Pt_L1_bins,
                            Jet2Pt_Off_bins,
                           ],
           
                "Mjj"    : ["Mjj",
                            "Mjj",
                            Mjj_L1_bins,
                            Mjj_Off_bins,
                           ],
              }
