import numpy as np
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

def read_planets(file):
	data = np.char.strip(np.array(infile.readlines()))
	
	numberOfPlanets = int(data[0])
	n = len(data)/(numberOfPlanets+2)
	planets = {}
	for i in range(1, numberOfPlanets+1):
		planets[i] = data[i+1::numberOfPlanets+2]
	return numberOfPlanets, n, planets

def extract_plot_planet(planet_number, numberOfPlanets, n, planets, figure):
	r_planet = np.zeros((n,4))
	for i in range(n-1):
		r_planet[i] = np.asarray(planets[planet_number][i].split()).astype(float)
	figure.plot(r_planet[0:-1,1],r_planet[0:-1,2],r_planet[0:-1,3], label="balle")

def plot_solarsystem(file):
	mpl.rcParams['legend.fontsize'] = 10
	fig = plt.figure()
	ax = fig.gca(projection='3d')

	numberOfPlanets, n, planets = read_planets(file)
	for k in range(1, numberOfPlanets+1):
		extract_plot_planet(k, numberOfPlanets, n, planets, ax)
	ax.legend()
	ax.set_xlim3d(-2,2)
	ax.set_ylim3d(-2,2)
	ax.set_zlim3d(-2,2)

#functions to plot mercury in 2D 

def extract_plot_planet_xy(planet_number, numberOfPlanets, n, planets):
	r_planet = np.zeros((n,4))
	for i in range(n-1):
		r_planet[i] = np.asarray(planets[planet_number][i].split()).astype(float)
	plt.plot(r_planet[0:-1,1],r_planet[0:-1,2])
	plt.axis([-.5, .5, -.5, .5])

def plot_mercury(file):

	numberOfPlanets, n, planets = read_planets(file)
	for k in range(1, numberOfPlanets+1):
		extract_plot_planet_xy(k, numberOfPlanets, n, planets)
	
"""
with open("../build-SolarSystem-Desktop-Debug/positions.dat", "r") as infile:

	plot_solarsystem(infile)
	plt.show()

with open("../build-SolarSystem-Desktop-Debug/mercury_system.dat", "r") as infile:

	plot_mercury(infile)
	plt.show()
"""

def perhelion_after_99yr(file):
	numberOfPlanets, n, planets = read_planets(file)
	index_after_99yr = int(99*1e3)
	r_planet = np.zeros((n,4))
	for k in range(1, numberOfPlanets+1):
		for i in range(n-1):
			r_planet[i] = np.asarray(planets[k][i].split()).astype(float)

	x_pos = r_planet[0:-1,1]
	y_pos = r_planet[0:-1,2]
	N = len(x_pos)

	
	x_pos_after99 = x_pos[index_after_99yr:N]
	y_pos_after99 = y_pos[index_after_99yr:N]

	norm = np.zeros(len(x_pos_after99))
	
	norm_min = 1e10
	index_min = 0
	for i in range(len(norm)):
		norm[i] = np.linalg.norm([x_pos_after99[i], y_pos_after99[i]])
		if norm[i]<norm_min:
			norm_min = norm[i]
			index_min = i

	theta = np.arctan(x_pos_after99[index_min]/y_pos_after99[index_min])*648000/np.pi 
	print theta

	time = np.linspace(index_after_99yr, n, len(norm))
	plt.plot(time, norm)
	plt.plot(time[index_min], norm[index_min], 'o')
	plt.show()


with open("../build-SolarSystem-Desktop-Debug/mercury_system.dat", "r") as infile:

	perhelion_after_99yr(infile)


