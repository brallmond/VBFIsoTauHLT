import ROOT
import os
import sys

from var_configs_dictionary import var_configs

# would be nice if this could be hidden in var_configs since that's what it is associated with
TITLE_INDEX = 0
XAXIS_LABEL_INDEX = 1
L1_RE_BINS_INDEX = 2
OFF_RE_BINS_INDEX = 3

DEBUG = False
if DEBUG == False : ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)

def set_style(in_hist: ROOT.TH1F, line_color: int, marker_style: int, marker_color: int=1) -> None:
    """Set the style of a histogram (as a function since this is done often)"""
    """
    For colors,    1,   2,     3,    4 is
               black, red, green, blue
    For markers,   4,     25,       26 is
              circle, square, triangle
    """
    color_dict = {"black" : 1, "red" : 2, "green" : 3, "blue" : 4}
    marker_dict = {"circle" : 4, "square" : 25, "triangle" : 26}

    # set marker_color and line_color the same
    marker_color = line_color
    in_hist.SetLineColor(line_color)
    in_hist.SetMarkerStyle(marker_style)
    in_hist.SetMarkerColor(marker_color)


def set_labels(hist: ROOT.TH1F, hist_title: str, hist_yaxis: str, hist_xaxis: str) -> None:
    """Set the title and axis lables of a histogram"""
    hist.SetTitle(hist_title)
    hist.GetYaxis().SetTitle(hist_yaxis)
    hist.GetXaxis().SetTitle(hist_xaxis)


def make_plot(in_file_one: 'str', label_one: 'str', in_file_two: 'str', label_two: 'str', var: 'str') -> 'None':

  can = ROOT.TCanvas("can", "", 800, 600)

  ROOT.gStyle.SetOptStat(0)
  ROOT.TH1.SetDefaultSumw2()

  title = "2018 and 2022 L1 Kinem Distributions "
  title += var_configs[var][TITLE_INDEX]

  xaxis_label = var_configs[var][XAXIS_LABEL_INDEX]
  xbins_L1  = var_configs[var][L1_RE_BINS_INDEX]

  # construct hist name from input var
  hist_var = "L1" + var
  xbins = xbins_L1

  # get histograms from file
  file_one = ROOT.TFile.Open(in_file_one, "READ") 
  h_one = file_one.Get(hist_var)
  h_one.SetDirectory(0) # keeps open after file close
  file_one.Close()

  file_two = ROOT.TFile.Open(in_file_two, "READ")
  h_two = file_two.Get(hist_var)
  h_two.SetDirectory(0)
  file_two.Close()

  # set styles and labels
  set_style(h_one, 4, 4)
  set_labels(h_one, title, "Events", xaxis_label)
  h_one.Draw("HIST, PE")

  set_style(h_two, 1, 26)
  set_labels(h_two, title, "Events", xaxis_label)
  h_two.Draw("SAME, PE")

  # add legend to left plot
  leg = ROOT.TLegend(0.55, 0.82, 0.9, 0.9)
  leg.SetTextSize(0.025)
  leg.AddEntry(h_one, label_one)
  leg.AddEntry(h_two, label_two)
  leg.Draw()

  # save plots
  out_png_name =  "compare_years_" + hist_var + ".png"
  can.SaveAs(out_png_name)
  if DEBUG == True: input()


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--in_file_one', '-i1', required=True, action='store', help='input file one')
    parser.add_argument('--label_one', '-l1', required=True, action='store', help='lable one')
    parser.add_argument('--in_file_two', '-i2', required=True, action='store', help='input file two')
    parser.add_argument('--label_two', '-l2', required=True, action='store', help='lable two')

    args = parser.parse_args()

    variables = ["EleEt", "Jet1Et", "Jet2Et", "Mjj"]

    if DEBUG == True: variables = ["EleEt"]

    for var in variables:
      make_plot(args.in_file_one, args.label_one, args.in_file_two, args.label_two, var)

