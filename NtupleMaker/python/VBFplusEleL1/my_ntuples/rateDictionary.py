# run >= 360486, L1DoubleTau32 is disabled, emulate L1DoubleTau34 for all eras after E
rateDictionary = {
      "NOTRATE" : {"nBunches" : -999, "runNumber" : -999, "minLS" : -999, "maxLS" : -999},

      "2018O"   : {"nBunches" : 2544, "runNumber" : 323755, "minLS" : 52, "maxLS" : 152, "approxLumi" : 1.79},

      "2022E"   : {"nBunches" : 2448, "runNumber" : 359871, "minLS" : 35,  "maxLS" : 59, "approxLumi" : 1.84},
      #"2022E"   : {"nBunches" : 2448, "runNumber" : 359661, "minLS" : 56,  "maxLS" : 196, "approxLumi" : 0.565},

      "2022F"   : {"nBunches" : 2450, "runNumber" : 361468, "minLS" : 148,  "maxLS" : 292, "approxLumi" : 1.84},
      # LS 39-294 available 
      # bad LS 109 132 140 147

      #"2022G_PU60"   : {"nBunches" : 2450, "runNumber" : 362616, "minLS" : 1,  "maxLS" : 101, "approxLumi" : 2.00},
      "2022G_PU60"   : {"nBunches" : 2450, "runNumber" : 362616, "minLS" : 75,  "maxLS" : 350, "approxLumi" : 2.00},

      #"2022G_PU70"   : {"nBunches" : 2450, "runNumber" : 362439, "minLS" : 1,  "maxLS" : 101, "approxLumi" : 2.4},
      "2022G_PU70"   : {"nBunches" : 2450, "runNumber" : 362439, "minLS" : 35,  "maxLS" : 221, "approxLumi" : 2.4},
      # bad LS 156 188 189 218
}
