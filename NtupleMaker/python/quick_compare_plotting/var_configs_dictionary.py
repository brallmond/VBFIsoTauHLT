import array 
import numpy as np

ElePt_L1_bins  = array.array('d', np.concatenate((np.arange(0., 20., step=2), np.arange(20., 80., step=10), [80., 100.])))
ElePt_Off_bins = ElePt_L1_bins
#260

TauPt_L1_bins = array.array('d', np.concatenate((np.arange(0, 40, step=4), np.arange(40, 100, step=10),\
                                                  [100, 150, 200])))
TauPt_Off_bins = TauPt_L1_bins 
#300

Jet1Pt_L1_bins = array.array('d', np.concatenate((np.arange(0, 40, step=4), np.arange(40, 200, step=10),\
                                                 [200, 250, 300])))
Jet1Pt_Off_bins = Jet1Pt_L1_bins
#600

Jet2Pt_L1_bins = array.array('d', np.concatenate((np.arange(0, 40, step=4), np.arange(40, 100, step=10),\
                                                 [120, 200])))
Jet2Pt_Off_bins = Jet2Pt_L1_bins

Mjj_L1_bins = array.array('d', np.concatenate((np.arange(0, 400, step=40), np.arange(500, 2000, step=100),\
                                               np.arange(2000, 3000, step=500))))
Mjj_Off_bins = Mjj_L1_bins
#3000, 4000, 7000

var_configs = { #"Key" :   ["plot title string",
                           #"Latex axis label,
                           # L1 bins,
                           # Offline bins,]

                "EleEt" :  ["Electron pT",
                            "p_{T}^{e}",
                            ElePt_L1_bins,
                            ElePt_Off_bins,
                           ],

                "Jet1Et" : ["Jet1 pT",
                            "p_{T}^{j1}",
                            Jet1Pt_L1_bins,
                            Jet1Pt_Off_bins,
                           ],

                "Jet2Et" : ["Jet2 pT",
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
