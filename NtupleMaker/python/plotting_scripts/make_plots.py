import ROOT
import os
import sys

from var_configs_dictionary import var_configs

# would be nice if this could be hidden in var_configs since that's what it is associated with
TITLE_INDEX = 0
XAXIS_LABEL_INDEX = 1
L1_RE_BINS_INDEX = 2
OFF_RE_BINS_INDEX = 3

#ROOT.gROOT.SetBatch(True) # sets visual display off (i.e. no graphs/TCanvas)

def set_style(in_hist: ROOT.TH1F, line_color: int, marker_style: int, marker_color: int=1) -> None:
    """
    Set the style of a histogram (as a function since this is done often)

    :param: in_hist - input histogram to set the style for
    :param: line_color - an integer corresponding to a color in ROOT
    :param: marker_style - an integer corresponding to a shape in ROOT
    :param: marker_color - same corresponding ROOT colors as line_color

    :return: Nothing, but set style of histogram in the process
    """

    """
    For colors,    1,   2,     3,    4 is
               black, red, green, blue
    For markers,   4,     25,       26 is
              circle, square, triangle
    """

    # set marker_color and line_color the same by default
    marker_color = line_color
    in_hist.SetLineColor(line_color)
    in_hist.SetMarkerStyle(marker_style)
    in_hist.SetMarkerColor(marker_color)


def set_labels(hist: ROOT.TH1F, hist_title: str, hist_yaxis: str, hist_xaxis: str) -> None:
    """Set the title and axis lables of a histogram"""
    hist.SetTitle(hist_title)
    hist.GetYaxis().SetTitle(hist_yaxis)
    hist.GetXaxis().SetTitle(hist_xaxis)


def save_hists(out_file_name: str, hist_one: ROOT.TH1F, hist_two: ROOT.TH1F, add_label: str) -> None:
    """Make a new out file and write two histograms to it"""
    if ".root" not in out_file_name: out_file_name += ".root"
    #out_file = ROOT.TFile.Open(out_file_name, "RECREATE")
    out_file = ROOT.TFile.Open(out_file_name, "UPDATE")
    hist_one.Write("ratio_"+add_label)
    hist_two.Write("ratio_rebinned_"+add_label)
    print(f"ratio hists written to {out_file_name}")


def prepend_string(result: str, search_file: str) -> str:
    """ search 'search_file' for "Loose" or "Tight" and prepend it to 'in_str' if found"""
    if "Loose" in search_file: result += "Loose"
    elif "Tight" in search_file: result += "Tight"
    else: 
      print("Is this a 'Loose' or 'Tight' root file? Please let the name of your input datafile reflect this. Exiting...")
      sys.exit()
    return result


def make_plot(in_file: 'str', var: 'str', L1: 'bool') -> 'None':
    """
    Create and save pT/mjj plots and efficiency plots side-by-side.

    :param: in_file - input file to be used with ready histograms
    :param: var     - variable to be plotted [ElePt, Jet1Pt, Jet2Pt, Mjj] 
    :param: L1      - flag to toggle using L1 or Offline variables

    :return: Nothing, but produce and save a nice plot on the way there :)
    """

    # make two drawing pads on one canvas
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

    ROOT.gStyle.SetOptStat(0)
    ROOT.TH1.SetDefaultSumw2()

    new_file = ROOT.TFile.Open(in_file, "READ") 

    # get left plot
    can.cd(1)
    # make labels for later use
    leg_label = "Offline"
    leg_label_m = "Offline (matching L1)"
    # set title, axis label, and rebinning (from config file)
    title = "Num. and Denom. Plots "
    xaxis_label = ""
    title += var_configs[var][TITLE_INDEX]
    xaxis_label += var_configs[var][XAXIS_LABEL_INDEX]
    xbins_L1  = var_configs[var][L1_RE_BINS_INDEX]
    xbins_Off = var_configs[var][OFF_RE_BINS_INDEX]
    # construct hist name from input var
    hist_var = var
    xbins = xbins_Off
    if (L1 == True):
      hist_var = "L1" + var
      leg_label = "L1"
      leg_label_m = "L1 (matching Off.)"
      xbins = xbins_L1
    m_hist_var = "m" + hist_var

    # get histograms from file
    h_Den = new_file.Get(hist_var)
    h_Den.SetDirectory(0) # keeps open after file close
    h_Num = new_file.Get(m_hist_var)
    h_Num.SetDirectory(0)
    new_file.Close()

    # set styles and labels
    set_style(h_Den, 4, 4)
    set_labels(h_Den, title, "Events", xaxis_label)
    h_Den.Draw("HIST, PE")

    set_style(h_Num, 3, 26)
    set_labels(h_Num, title, "Events", xaxis_label)
    h_Num.Draw("SAME, PE")

    # add legend to left plot
    leg_left = ROOT.TLegend(0.55, 0.67, 0.9, 0.9)
    leg_left.SetTextSize(0.025)
    leg_left.AddEntry(h_Den, leg_label)
    leg_left.AddEntry(h_Num, leg_label_m)
    leg_left.Draw()

    can.cd(2) # switch to right plot

    # make and draw ratio plot
    h_ratio = h_Num.Clone()
    h_ratio.Divide(h_Den)
    set_style(h_ratio, 1, 25)
    ratio_title = leg_label_m + " / " + leg_label
    set_labels(h_ratio, ratio_title, "Efficiency", xaxis_label)
    h_ratio.GetYaxis().SetRangeUser(0.0, 1.5)
    h_ratio.Draw("HIST, PE")
    h_ratio.SetDirectory(0)

    # make and draw rebinned ratio
    h_rebin_Num = h_Num.Rebin(len(xbins)-1, "h_rebin_Num", xbins) 
    h_rebin_Den = h_Den.Rebin(len(xbins)-1, "h_rebin_Den", xbins)

    h_rebin_ratio = h_rebin_Num.Clone()
    h_rebin_ratio.Divide(h_rebin_Den)
    set_style(h_rebin_ratio, 2, 25)
    set_labels(h_rebin_ratio, ratio_title, "Efficiency", xaxis_label)
    h_rebin_ratio.Draw("SAME, PE")
    h_rebin_ratio.SetDirectory(0)

    # add legend to right plot
    leg_right = ROOT.TLegend(0.12, 0.67, 0.4, 0.9)
    leg_right.SetTextSize(0.025)
    leg_right.AddEntry(h_ratio, "Efficiency")
    leg_right.AddEntry(h_rebin_ratio, "Rebinned")
    leg_right.Draw()

    # save plot
    out_name = prepend_string("", in_file)
    out_name += "_" + hist_var + ".png"
   
    can.SaveAs(out_name)
    input() # preserve graph display until user input

    # write ratio hist and rebinned ratio hist to original file
    out_hist_name = prepend_string("", in_file)
    out_hist_name += "_ratio_hists.root"
    # FIXME: unable to open "ratio" plot from saved hists, but the rebin is fine
    # the below "setname" was suggested here, but does not appear to fix the issue.
    # https://root-forum.cern.ch/t/histogram-name-change-on-write/3622
    #h_ratio.SetName("ratio")
    #h_rebin_ratio.SetName("rebin_ratio")
    save_hists(out_hist_name, h_ratio, h_rebin_ratio, hist_var)


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

    DEBUG = False
    if DEBUG == True: variables = ["ElePt"]
    for var in variables:
      make_plot(args.in_file, var, L1)
