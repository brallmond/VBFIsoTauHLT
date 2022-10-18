import ROOT
import os
import sys

from make_plots import set_style
#ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)

def make_comparison_plot(in_file_one: 'str', in_file_two: 'str', in_file_three: 'str', in_file_four: 'str',
    var: 'str', label_one: 'str', label_two: 'str', label_three: 'str', label_four: 'str') -> 'None':
    """Create and save comparison of loose/tight efficiency plot"""

    # make two drawing pads on one canvas
    can = ROOT.TCanvas("can", "", 800, 600)

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

    # set styles and labels
    set_style(h_one, 4, 4)
    h_one.GetYaxis().SetRangeUser(0, 1.5)
    h_one.Draw("HIST, PE")

    set_style(h_two, 2, 25)
    h_two.Draw("SAME, PE")

    set_style(h_three, 3, 26)
    h_three.Draw("SAME, PE")

    set_style(h_four, 1, 1)
    h_four.Draw("SAME, PE")

    # add legend to left plot
    leg = ROOT.TLegend(0.55, 0.67, 0.9, 0.9)
    leg.SetTextSize(0.025)
    leg.AddEntry(h_one, label_one)
    leg.AddEntry(h_two, label_two)
    leg.AddEntry(h_three, label_three)
    leg.AddEntry(h_four, label_four)
    leg.Draw()

    can.SaveAs("compare_"+var+".png")
    input() # preserve graph display until user input


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--in_file_one', '-i1', required=True, action='store', help='input file one')
    parser.add_argument('--label_one', '-l1', required=True, action='store', help='label for input file one on legend')
    parser.add_argument('--in_file_two', '-i2', required=True, action='store', help='input file two')
    parser.add_argument('--label_two', '-l2', required=True, action='store', help='label for input file two on legend')
    parser.add_argument('--in_file_three', '-i3', required=True, action='store', help='input file three')
    parser.add_argument('--label_three', '-l3', required=True, action='store', help='label for input file three on legend')
    parser.add_argument('--in_file_four', '-i4', required=True, action='store', help='input file four')
    parser.add_argument('--label_four', '-l4', required=True, action='store', help='label for input file four on legend')


    args = parser.parse_args()

    variables = ["TauPt", "ElePt", "Jet1Pt", "Jet2Pt", "Mjj"]

    DEBUG = False
    if DEBUG == True: variables = ["ElePt"]
    for var in variables:
      make_comparison_plot(args.in_file_one, args.in_file_two, args.in_file_three, args.in_file_four, var, \
                           args.label_one, args.label_two, args.label_three, args.label_four)

