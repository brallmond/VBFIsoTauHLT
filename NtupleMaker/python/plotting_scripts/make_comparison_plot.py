import ROOT
import os
import sys
import re

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
    #input() # preserve graph display until user input


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--in_file_one', '-i1', required=True, action='store', help='input file one')
    parser.add_argument('--in_file_two', '-i2', required=True, action='store', help='input file two')
    parser.add_argument('--in_file_three', '-i3', required=True, action='store', help='input file three')
    parser.add_argument('--in_file_four', '-i4', required=True, action='store', help='input file four')

    args = parser.parse_args()

    # Mantras and Cleansing Vows before proceeding
    # making loops on root files in python is a fool's errand
    # i will use this code once for this express purpose and never try to adapt it
    # i will write better code that avoids the use of this type of construction
    # i will also strive to avoid tasks where this type of coding is required

    label_regex = re.compile(r'(Loose|Tight)_\d\d_\d\d\d_\d\d')
    # above, compile is just the keyword the re module uses to indicate a regex expression in raw text format
    # r'' is the python raw text format
    # \d is regex for 'digit', val1|val2 is regex for 'match either of these' 
    # below, you 'search' the desired string as a method of the regex you 'compile'd above
    # 'group' concatenates the groups of your regex (we have two groups above, one in () and one not)
    label_one   = label_regex.search(args.in_file_one).group()
    label_two   = label_regex.search(args.in_file_two).group()
    label_three = label_regex.search(args.in_file_three).group()
    label_four  = label_regex.search(args.in_file_four).group()

    variables = ["TauPt", "ElePt", "Jet1Pt", "Jet2Pt", "Mjj"]

    DEBUG = False
    if DEBUG == True: variables = ["ElePt"]
    for var in variables:
      make_comparison_plot(args.in_file_one, args.in_file_two, args.in_file_three, args.in_file_four, var, \
                           label_one, label_two, label_three, label_four)

