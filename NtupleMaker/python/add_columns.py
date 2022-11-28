file_name = 'l1_event_counts.txt'
with open(file_name, encoding='utf-8') as data_file:
  processed_values = []
  for line in data_file:
    values = line.split(":") # put each entry into an array
    values = values[:2]      # keep the first two columnes
    for i in range(len(values)):
      values[i] = int(values[i].strip()) # strip whitespace and turn into ints
    processed_values.append(values)

# after file is closed, loop over processed values to get two sums and percentage
total_nEvents = 0
total_nViable = 0
total_percent = 0
for i in range(len(processed_values)):
  total_nEvents += processed_values[i][0]
  total_nViable += processed_values[i][1]
total_percent = float(total_nViable)/float(total_nEvents)

print("nEvents : nViable : Percent")
print(total_nEvents, total_nViable, total_percent)

