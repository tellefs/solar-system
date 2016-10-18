import numpy as np
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import os

with open("../build-SolarSystem-Desktop_Qt_5_7_0_clang_64bit-Debug/positions.dat", "r") as infile:

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


	def extract_plot_planet(integer_number):
		r_planet = np.zeros((n,4))
		for i in range(n-1):
			r_planet[i] = np.asarray(planets[integer_number][i].split()).astype(float)
		ax.plot(r_planet[0:-1,1],r_planet[0:-1,2],r_planet[0:-1,3], label="balle")

	
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

	r_vec_planet = {}
	for i in range(1, numberOfPlanets+1):
		r_vec_planet[i] = np.zeros((n,4))
		for j in range(n-1):
			r_vec_planet[i][j] = np.asarray(planets[2][i].split()).astype(float)


	# r_earth = np.zeros((n,4))
	# for i in range(n-1):
	# 	r_earth[i] = np.asarray(planets[2][i].split()).astype(float)


	mpl.rcParams['legend.fontsize'] = 10
	fig = plt.figure()
	ax = fig.gca(projection='3d')
	for k in range(1, numberOfPlanets+1):
		extract_plot_planet(k)
	ax.legend()
	ax.set_xlim3d(-2,2)
	ax.set_ylim3d(-2,2)
	ax.set_zlim3d(-2,2)

	plt.show()
