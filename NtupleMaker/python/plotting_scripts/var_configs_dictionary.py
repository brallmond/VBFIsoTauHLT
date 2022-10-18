import array 

var_configs = { "TauPt" :  ["Tau pT",
                           "p_{T}^{#tau}",
                            array.array('d', [0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 300]),
                            array.array('d', [0, 20, 40, 60, 80, 100, 120, 300]),
                           ],
                "ElePt" :  ["Electron pT",
                            "p_{T}^{e}",
                            array.array('d', [0, 20, 40, 60, 80, 100, 260]), # L1 bins
                            array.array('d', [0, 20, 40, 60, 80, 100, 260]), # Offline bins
                           ],

                "Jet1Pt" : ["Jet1 pT",
                            "p_{T}^{j1}",
                            array.array('d', [0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 400]),
                            array.array('d', [0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 400]),
                           ],

                "Jet2Pt" : ["Jet2 pT",
                            "p_{T}^{j2}",
                            array.array('d', [0, 20, 40, 60, 80, 100, 120, 140, 260]),
                            array.array('d', [0, 20, 40, 60, 80, 100, 120, 140, 160, 400]),
                           ],
           
                "Mjj"    : ["Mjj",
                            "Mjj",
                            array.array('d', [0, 150, 300, 450, 600, 750, 900, 1050, 1200, 1350, 1500, 3000]),
                            array.array('d', [0, 150, 300, 450, 600, 750, 900, 1050, 1200, 1350, 1500, 3000]),
                           ],
              }
