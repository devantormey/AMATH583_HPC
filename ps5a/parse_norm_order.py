import os
import sys
import matplotlib.pyplot as plt

runs = [1000000, 500000, 100000, 50000, 10000, 5000, 1000, 500, 100, 50]

reversed_flag = 0
sorted_flag = 0

reversed_absolute = []
reversed_relative = []

sorted_absolute = []
sorted_relative = []
sorted_runs = []
runs_count = 0

# Wrote something to parse the log 
with open("norm_order.log","r+") as f:
	for line in f:
		for word in line.split(' '):
			if word == "reversed":
				runs_count = runs_count + 1
				sorted_flag = 0
				reversed_flag = 1
			if reversed_flag == 1:
				if word == "Absolute":
					reversed_absolute.append(float(line.split(' ')[-1]))
				if word == "Relative":
					reversed_relative.append(float(line.split(' ')[-1]))
					reversed_flag = 0
			if word == "sorted":
				sorted_flag = 1
			if sorted_flag == 1:
				if word == "Absolute":
					print("Found the absolute")
					print(line)
					# print(line.split(' ')[-1])
					sorted_absolute.append(float(line.split(' ')[-1]))
				if word == "Relative":
					sorted_relative.append(float(line.split(' ')[-1]))
					print(runs_count)
					sorted_runs.append(runs[runs_count])
					sorted_flag = 0
		




print(runs)
print(reversed_absolute)
print(reversed_relative)
fig, ax = plt.subplots(2)
ax[0].plot(runs, reversed_absolute, 'b-',label='Absolute Diff')
ax[0].plot(runs, reversed_relative, 'r-',label='Relative Diff')
ax[0].legend()
ax[1].plot(sorted_runs, sorted_absolute, 'b-',label='Absolute Diff')
ax[1].plot(sorted_runs, sorted_relative, 'r-',label='Relative Diff')
ax[1].legend()

plt.show()
plt.savefig('norm_order_LengthTest.png')
# Cant save as bitmap :(
# plt.savefig('norm_order_LengthTest.bmp')
