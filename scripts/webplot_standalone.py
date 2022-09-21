#!/usr/bin/env python

import argparse
import os
import string

webplottingdict = {
  "plot": '		<div><a href="${json}"><h4>${title}</a> ${links}</h4><a href="${image}" title="${title}"><img src="${image}" height="400"></a></div>'
}
webplotdict = {
  "description": '<p><a href="..">Parent Directory</a>${subdirs}</p>\n<p>Download all plots:<br><code>wget -nd -r -e robots=off --no-parent -P plots <script type="text/javascript">document.write(document.URL);</script></code></p>',
  "link": '<a href="${plot}" title="${title}">${extension}</a>',
  "overview": '<!DOCTYPE html>\n<html>\n	<head>\n	<style type="text/css">\n		div { float:left; padding: 3px 7px; }\n		pre { display: inline; padding: 3px 7px; font-size: 16px; background-color: #F5F5F5; border: 1px solid rgba(0, 0, 0, 0.15); border-radius: 4px; }\n		h3 { color: #888; font-size: 16px; }\n	</style>\n	</head>\n	<body>\n		<h1>${title}</h1>\n		${description}\n		${plots}\n	</body>\n</html>',
  "plot": '		<div><h4>${title} ${links}</h4><a href="${image}" title="${title}"><img src="${image}" height="400"></a></div>',
  "subdir": '<br><a href="${subdir}/">${subdir}</a>'
}


def get_inputs(input_dir, **kwargs):
	file_types = kwargs.get("file_types", ["png", "jpg", "pdf", "svg", "eps"])
	
	input_dir_content =	os.listdir(input_dir)
	
	plot_files = {}
	subdirs = []
	for input_object in input_dir_content:
		full_input_object = os.path.join(input_dir, input_object)
		
		if os.path.isfile(full_input_object):
			split_input_object = os.path.splitext(input_object)
			extension = split_input_object[-1].replace(".", "").lower()
			
			if extension in file_types:
				plot_files.setdefault(split_input_object[0], []).append(extension)
		
		else:
			subdirs.append(full_input_object)
	
	for filename, extensions in plot_files.iteritems():
		extensions.sort(key=lambda extension: file_types.index(extension))
	subdirs.sort()
	
	return plot_files, subdirs


def webplot(input_dir, **kwargs):

	plot_files, subdirs = get_inputs(input_dir, **kwargs)
	html_texts = {}
	for var in ["overview", "description", "subdir", "plot", "link"]:
		html_texts[var] = string.Template(webplotdict[var])
	html_texts["plotjson"] = string.Template(webplottingdict["plot"])

	# treat subdirs recursively
	html_desciption = ""
	if kwargs.get("recursive"):
		html_subdirs = ""
		for subdir in subdirs:
			webplot(subdir, **kwargs)
			html_subdirs += html_texts["subdir"].substitute(subdir=os.path.relpath(subdir, input_dir))
		html_desciption = html_texts["description"].substitute(subdirs=html_subdirs)
	else:
		html_desciption = html_texts["description"].substitute(subdirs="")
	
	html_plots = ""
	for filename, extensions in sorted(plot_files.iteritems()):
		if os.path.isfile(os.path.join(input_dir, filename+".json")):
			html_plots += html_texts["plotjson"].substitute(
					image=filename+"."+extensions[0],
					json=filename+".json",
					title=filename,
					links=" ".join([html_texts["link"].substitute(
							plot=filename+"."+extension,
							title=filename,
							extension=extension
					) for extension in extensions])
			)
		else:
			html_plots += html_texts["plot"].substitute(
					image=filename+"."+extensions[0],
					title=filename,
					links=" ".join([html_texts["link"].substitute(
							plot=filename+"."+extension,
							title=filename,
							extension=extension
					) for extension in extensions])
			)
	
	if not plot_files == {}:
		html_index_filename = os.path.join(input_dir, "index.html")
		with open(html_index_filename, "w") as html_index_file:
			html_index_file.write(html_texts["overview"].substitute(
					title=kwargs.get("title", input_dir),
					description=html_desciption,
					plots=html_plots
			))
			print "Created", html_index_filename


def main():
	parser = argparse.ArgumentParser(description="Create web gallery for a set of plots.")

	parser.add_argument("input_dir", help="Input directory containing the plots")
	parser.add_argument("-r", "--recursive", default=False, action="store_true",
	                    help="Recursively search for plots in the input directory.")
	parser.add_argument("--file-types", default=["png", "jpg", "pdf", "svg", "eps"],
	                    help="File types to be considered as plots. [Default: %(default)s]")

	args = parser.parse_args()

	if "/" in args.input_dir[0:-1]:
		print "Please do not use '/' for the input directory."
		print "Instead, go into the directory where your directory containing the plots is located, then run webplot.py."
		print "(This is to avoid getting lots of subdirectories in your webspace)"
		exit()

	webplot(
			input_dir=args.input_dir,
			recursive=args.recursive,
			file_types=args.file_types
	)
	

if __name__ == "__main__":
	main()
