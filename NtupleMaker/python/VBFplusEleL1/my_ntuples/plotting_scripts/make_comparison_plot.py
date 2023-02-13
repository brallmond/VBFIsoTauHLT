import ROOT
import os
import sys
import re
import array

from make_plots import set_style, double_canvas
#ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)

def rebin_hist_to_int_range(hist):
  """make histogram with same contents and errors as input, but integer bins for labeling purposes"""
  nBins_hist = hist.GetNbinsX()
  int_rebin_hist = ROOT.TH1F("", "", nBins_hist+1, 0, nBins_hist+1)
  #for i in range(1, nBins_hist+1+1):
  for i in range(1, nBins_hist-1):
    int_rebin_hist.Fill(i, hist.GetBinContent(i))
    int_rebin_hist.SetBinError(i, hist.GetBinError(i))
  return int_rebin_hist


def make_comparison_plot(in_file_one: 'str', in_file_two: 'str', in_file_three: 'str', in_file_four: 'str',\
                         in_file_five: 'str',\
    var: 'str', label_one: 'str', label_two: 'str', label_three: 'str', label_four: 'str',\
                         label_five: 'str') -> 'None':
    """Create and save comparison of loose/tight efficiency plot"""

    # make two drawing pads on one canvas
    can = ROOT.TCanvas("can", "", 800, 600)
    #can = double_canvas()
    #can.cd(1)

    ROOT.gStyle.SetOptStat(0)
    ROOT.TH1.SetDefaultSumw2()

    # valid vars are ElePt, TauPt, Jet1Pt, Jet2Pt, Mjj
    hist_var = "ratio_rebinned_"+var

    root_file_one = ROOT.TFile.Open(in_file_one, "READ") 
    h_one = root_file_one.Get(hist_var)
    h_one.SetDirectory(0) # keeps open after file close
    root_file_one.Close()

    root_file_two = ROOT.TFile.Open(in_file_two, "READ")
    h_two = root_file_two.Get(hist_var)
    h_two.SetDirectory(0)
    root_file_two.Close()

    root_file_three = ROOT.TFile.Open(in_file_three, "READ")
    h_three = root_file_three.Get(hist_var)
    h_three.SetDirectory(0)
    root_file_three.Close()

    root_file_four = ROOT.TFile.Open(in_file_four, "READ")
    h_four = root_file_four.Get(hist_var)
    h_four.SetDirectory(0)
    root_file_four.Close()

    root_file_five = ROOT.TFile.Open(in_file_five, "READ")
    h_five = root_file_five.Get(hist_var)
    h_five.SetDirectory(0)
    root_file_five.Close()

    # set styles and labels
    set_style(h_one, 4, 4)
    h_one.GetYaxis().SetRangeUser(0, 1.5)
    #ROOT.gPad.SetLogx()
    h_one.Draw("HIST, PE")

    set_style(h_two, 2, 25)
    h_two.Draw("SAME, PE")

    set_style(h_three, 3, 26)
    h_three.Draw("SAME, PE")

    set_style(h_four, 1, 1)
    h_four.Draw("SAME, PE")

    set_style(h_five, 1, 3)
    h_five.Draw("SAME, PE")

    # add legend to left plot
    leg_left = ROOT.TLegend(0.55, 0.67, 0.9, 0.9)
    leg_left.SetTextSize(0.025)
    leg_left.AddEntry(h_one, label_one)
    leg_left.AddEntry(h_two, label_two)
    leg_left.AddEntry(h_three, label_three)
    leg_left.AddEntry(h_four, label_four)
    leg_left.AddEntry(h_five, label_five)
    leg_left.Draw()

    #can.cd(2)
    # draw the rebinned hists
    #h_int_one_rebin = rebin_hist_to_int_range(h_one)
    #set_style(h_int_one_rebin, 4, 4)
    #h_int_one_rebin.GetYaxis().SetRangeUser(0, 1.5)
    #h_int_one_rebin.Draw("HIST, PE")
    
    #h_int_two_rebin = rebin_hist_to_int_range(h_two)
    #set_style(h_int_two_rebin, 2, 25)
    #h_int_two_rebin.Draw("SAME, PE")

    #h_int_three_rebin = rebin_hist_to_int_range(h_three)
    #set_style(h_int_three_rebin, 3, 26)
    #h_int_three_rebin.Draw("SAME, PE")

    #h_int_four_rebin = rebin_hist_to_int_range(h_four)
    #set_style(h_int_four_rebin, 1, 1)
    #h_int_four_rebin.Draw("SAME, PE")

    #print(i, int_rebin_hist.GetXaxis().GetBinLabel(i), hist.GetXaxis().GetBinLabel(i))
    #print(i, hist.GetXaxis().GetBinLabel(i))
    #for i in range(1, h_int_one_rebin.GetNbinsX()+1):
    #  print(i-1, h_int_one_rebin.GetBinLowEdge(i-1), h_one.GetBinLowEdge(i-1))
    #  h_int_one_rebin.GetXaxis().SetBinLabel(i-1, str(h_one.GetBinLowEdge(i-1)))


    #leg_right = ROOT.TLegend(0.12, 0.67, 0.4, 0.9)
    #leg_right.SetTextSize(0.025)
    #leg_right.AddEntry(h_int_one_rebin, label_one)
    #leg_right.AddEntry(h_int_two_rebin, label_two)
    #leg_right.AddEntry(h_int_three_rebin, label_three)
    #leg_right.AddEntry(h_int_four_rebin, label_four)
    #leg_right.Draw()

    can.SaveAs("compare_"+var+".png")
    #input() # preserve graph display until user input


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--in_file_one', '-i1', required=True, action='store', help='input file one')
    parser.add_argument('--in_file_two', '-i2', required=True, action='store', help='input file two')
    parser.add_argument('--in_file_three', '-i3', required=True, action='store', help='input file three')
    parser.add_argument('--in_file_four', '-i4', required=True, action='store', help='input file four')
    parser.add_argument('--in_file_five', '-i5', required=True, action='store', help='input file five')

    args = parser.parse_args()

    # Mantras and Cleansing Vows before proceeding
    # making loops on root files in python is a fool's errand
    # i will use this code once for this express purpose and never try to adapt it
    # i will write better code that avoids the use of this type of construction
    # i will also strive to avoid tasks where this type of coding is required

    # old format
    #label_regex = re.compile(r'(Loose|Tight)_\d\d_\d\d\d_\d\d')
    # VBF_DoubleJets30_Mass_Min500_LooseIsoEG10
    label_regex = re.compile(r'\d\d_Mass_Min\d\d\d_(Loose|Tight|'')IsoEG\d\d')
    # above, compile is just the keyword the re module uses to indicate a regex expression in raw text format
    # r'' is the python raw text format
    # \d is regex for 'digit', val1|val2 is regex for 'match either of these' 
    # below, you 'search' the desired string as a method of the regex you 'compile'd above
    # 'group' concatenates the groups of your regex (we have two groups above, one in () and one not)
    #
    label_one   = label_regex.search(args.in_file_one).group()
    label_two   = label_regex.search(args.in_file_two).group()
    label_three = label_regex.search(args.in_file_three).group()
    label_four  = label_regex.search(args.in_file_four).group()
    label_five  = label_regex.search(args.in_file_five).group()

    variables = ["TauPt", "ElePt", "Jet1Pt", "Jet2Pt", "Mjj"]

    DEBUG = False
    if DEBUG == True: variables = ["ElePt"]
    for var in variables:
      make_comparison_plot(args.in_file_one, args.in_file_two, args.in_file_three, args.in_file_four, args.in_file_five, var, \
                           label_one, label_two, label_three, label_four, label_five)

