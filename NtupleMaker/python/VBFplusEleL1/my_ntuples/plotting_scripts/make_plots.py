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


def double_canvas():
  """ make two drawing pads on one canvas"""

  can = ROOT.TCanvas("can", "", 1100, 600)
  can.SetMargin(0.0, 0.0, 0.0, 0.0)
  can.Divide(2)
  split = 0.5
  can.cd(1)
  ROOT.gPad.SetPad('pad1', 'pad1', 0.05, 0.0, split, 1.0)
  ROOT.gPad.SetLeftMargin(0.12) # prevents yaxis label from being overlapped
  ROOT.gPad.SetFillColor(0)
  can.cd(2)
  ROOT.gPad.SetPad('pad2', 'pad2', split, 0.0, 1.0, 1.0)
  ROOT.gPad.SetLeftMargin(0.12)
  ROOT.gPad.SetFillColor(0)
  return can


def make_plot(in_file: 'str', var: 'str', L1: 'bool') -> 'None':
    """
    Create and save pT/mjj plots and efficiency plots side-by-side.

    :param: in_file - input file to be used with ready histograms
    :param: var     - variable to be plotted [ElePt, Jet1Pt, Jet2Pt, Mjj] 
    :param: L1      - flag to toggle using L1 or Offline variables

    :return: Nothing, but produce and save a nice plot on the way there :)
    """

    can = double_canvas()

    ROOT.gStyle.SetOptStat(0)
    ROOT.TH1.SetDefaultSumw2()

    new_file = ROOT.TFile.Open(in_file, "READ") 

    # get left plot
    can.cd(1)

    # make labels for later use
    den_legend_label = "Offline"
    num_legend_label = "(L1 + Offline + matching)"
    # set title, axis label, and rebinning (from config file)
    title = "Num. and Denom. Plots "
    title += var_configs[var][TITLE_INDEX]

    xaxis_label = var_configs[var][XAXIS_LABEL_INDEX]
    xbins_L1  = var_configs[var][L1_RE_BINS_INDEX]
    xbins_Off = var_configs[var][OFF_RE_BINS_INDEX]

    # construct hist name from input var
    hist_var = var
    xbins = xbins_Off
    if (L1 == True):
      hist_var = "L1" + var
      xbins = xbins_L1

    m_hist_var = "m" + hist_var #originally the m meant matching, but now it just corresponds to the numerator

    # get histograms from file
    h_den = new_file.Get(hist_var)
    h_den.SetDirectory(0) # keeps open after file close
    h_num = new_file.Get(m_hist_var)
    h_num.SetDirectory(0)
    new_file.Close()

    # set styles and labels
    set_style(h_den, 4, 4)
    set_labels(h_den, title, "Events", xaxis_label)
    h_den.Draw("HIST, PE")

    set_style(h_num, 3, 26)
    set_labels(h_num, title, "Events", xaxis_label)
    h_num.Draw("SAME, PE")

    # add legend to left plot
    leg_left = ROOT.TLegend(0.55, 0.82, 0.9, 0.9)
    leg_left.SetTextSize(0.025)
    leg_left.AddEntry(h_den, den_legend_label)
    leg_left.AddEntry(h_num, num_legend_label)
    leg_left.Draw()

    can.cd(2) # switch to right plot

    # make and draw ratio plot
    h_ratio = h_num.Clone()
    h_ratio.Divide(h_den)
    set_style(h_ratio, 1, 25)
    ratio_title = num_legend_label + " / " + den_legend_label
    set_labels(h_ratio, ratio_title, "Efficiency", xaxis_label)
    h_ratio.GetYaxis().SetRangeUser(0.0, 1.5)
    h_ratio.Draw("HIST, PE")
    h_ratio.SetDirectory(0)

    # make and draw rebinned ratio
    h_rebin_num = h_num.Rebin(len(xbins)-1, "h_rebin_num", xbins) 
    h_rebin_den = h_den.Rebin(len(xbins)-1, "h_rebin_den", xbins)

    h_rebin_ratio = h_rebin_num.Clone()
    h_rebin_ratio.Divide(h_rebin_den)
    set_style(h_rebin_ratio, 2, 25)
    set_labels(h_rebin_ratio, ratio_title, "Efficiency", xaxis_label)
    h_rebin_ratio.Draw("SAME, PE")
    h_rebin_ratio.SetDirectory(0)

    # add legend to right plot
    leg_right = ROOT.TLegend(0.12, 0.82, 0.4, 0.9)
    leg_right.SetTextSize(0.025)
    leg_right.AddEntry(h_ratio, "Efficiency")
    leg_right.AddEntry(h_rebin_ratio, "Rebinned")
    leg_right.Draw()

    # save plots
    out_png_name = in_file.replace(".root","") + "_" + hist_var + ".png"
    can.SaveAs(out_png_name)
    if DEBUG == True: input()

    # write ratio hist and rebinned ratio hist to new file
    strip_in_file = in_file.replace("../","").replace("data/","")
    out_file_name = "ratios_" + strip_in_file
    out_file = ROOT.TFile.Open(out_file_name, "UPDATE")
    h_ratio.Write("ratio_"+hist_var)
    h_rebin_ratio.Write("ratio_rebinned_"+hist_var)
    print(f"ratio hists written to {out_file_name}")


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--in_file', '-i', required=True, action='store', help='input file')
    parser.add_argument('--L1', '-L', required=True, action='store', help='L1 True / False')

    args = parser.parse_args()

    # be careful with boolean values in argparse, they are a headache.
    # Manually setting with more obvious python syntax :)

    L1 = False
    str_L1 = args.L1
    if (str_L1 == "True"): L1 = True

    variables = ["TauPt", "ElePt", "Jet1Pt", "Jet2Pt", "Mjj"]
    if (L1 == True):
      variables = variables[1::] # remove TauPt

    if DEBUG == True: variables = ["ElePt"]

    for var in variables:
      make_plot(args.in_file, var, L1)

