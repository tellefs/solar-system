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

def extract_plot_planet_xy(planet_number, numberOfPlanets, n, planets, figure):
	r_planet = np.zeros((n,4))
	for i in range(n-1):
		r_planet[i] = np.asarray(planets[planet_number][i].split()).astype(float)
	figure.plot(r_planet[0:-1,1],r_planet[0:-1,2])

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
	


with open("../build-SolarSystem-Desktop-Debug/positions.dat", "r") as infile:

	plot_solarsystem(infile)
	plt.show()


with open("../build-SolarSystem-Desktop-Debug/mercury_system.dat", "r") as infile:

	plot_mercury(infile)
	plt.show()
