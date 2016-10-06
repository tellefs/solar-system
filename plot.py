import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt


with open("positions.dat", "r") as infile:

	data = np.char.strip(np.array(infile.readlines()))
	numberOfPlanets = int(data[0])
	n = len(data)/(numberOfPlanets+2)

	planets = {}
	for i in range(1, numberOfPlanets+1):
		planets[i] = data[i+1::numberOfPlanets+2]

	# a = np.asarray(planets[1][0].split()).astype(float)
	# print a

	r_earth = np.zeros((n,4))
	for i in range(n-1):
		r_earth[i] = np.asarray(planets[2][i].split()).astype(float)

	# x_earth = []
	# for i in range(n):
	# 	x_earth.append(float(planets[2][i][0]))

	# print x_earth[0]
	# print type(x_earth[0])


	# for i in range(1, numberOfPlanets+1):
	# 	for j in range(n):
	# 		print planets[i][j][2]

	# sun = data[2::numberOfPlanets+2]
	# earth = data[3::numberOfPlanets+2]
	
	# # t = np.linspace()
	# x = r[:,0]
	# y = r[:,1]
	# z = r[:,2]

	# x_earth = x[1::2]
	# # print x_earth
	# y_earth = y[1::2]
	# z_earth = z[1::2]

	mpl.rcParams['legend.fontsize'] = 10
	fig = plt.figure()
	ax = fig.gca(projection='3d')
	ax.plot(r_earth[:,1],r_earth[:,2],r_earth[:,3], label="balle")
	ax.legend()

	plt.show()