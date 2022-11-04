#import os, sys
import ROOT
ROOT.ROOT.EnableImplicitMT()
ROOT.gROOT.SetBatch(True)

import argparse
from plotter_from_ntuplizer import obtain_histograms
from channel_to_HLT_map import channel_to_HLT_map, channels
import numpy as np
from array import array


parser = argparse.ArgumentParser(description='Skim full tuple.')
parser.add_argument('--input_dataset', required=True, type=str, nargs='+', help="first input file")
parser.add_argument('--channel_A', required=True, type=str, 
        help=f"options are {channels}")
parser.add_argument('--channel_B', required=True, type=str, 
        help=f"options are {channels}")
parser.add_argument('--run', required=True, type=str, help="runs or fill used (look at your input files)")
parser.add_argument('--plot', required=True, type=str, help="plot name")
parser.add_argument('--iseta', action='store_true', help="sets flag for eta plotting")
parser.add_argument('--var', required=True, type=str, help="tau_pt, tau_eta, jet_pt, jet_eta")

if __name__ == "__main__":

    args = parser.parse_args()
    channel_A = args.channel_A
    channel_B = args.channel_B
    plottingVariable = args.var
    iseta = "eta" in "plottingVariable"
    print(f"input dataset: {args.input_dataset}")
    df = ROOT.RDataFrame("Events", tuple(args.input_dataset))

    h_num_os_A, h_den_os_A = obtain_histograms(df, channel_A, iseta, plottingVariable)
    h_ratio_A = h_num_os_A.GetPtr().Clone()
    h_ratio_A.Divide(h_den_os_A.GetPtr())

    h_num_os_B, h_den_os_B = obtain_histograms(df, channel_B, iseta, plottingVariable)
    h_ratio_B = h_num_os_B.GetPtr().Clone()
    h_ratio_B.Divide(h_den_os_B.GetPtr())

    nbins = h_ratio_A.GetNbinsX()
    xbins = h_ratio_A.GetXaxis()

    bins = np.arange(20, 40, step=10)
    bins = np.append(bins, np.arange(40, 120, step=4))
    high_pt_bins = [ 120, 150, 200]
    np.append(bins,high_pt_bins)

    xbins = bins

    c = ROOT.TCanvas("c", "", 800, 700)
    #print(xbins)
    toodeeplot = ROOT.TH2F("", "test", nbins, array('d', xbins), nbins, array('d', xbins))
    print(dir(toodeeplot))
    c.SetGrid()

    for i in range(nbins):
      print(i, h_ratio_A.GetBinCenter(i), h_ratio_A.GetBinContent(i))
      print(i, h_ratio_B.GetBinCenter(i), h_ratio_B.GetBinContent(i))
      for j in range(nbins):
        toodeeplot.Fill(xbins[i], xbins[j], h_ratio_A.GetBinContent(i)*h_ratio_B.GetBinContent(j))

    toodeeplot.SetStats(0)
    toodeeplot.Draw("COLZ, TEXT")
    c.SaveAs("test.png")

