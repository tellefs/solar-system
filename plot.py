import numpy as np
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from scipy.signal import argrelextrema

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
with open("../build-SolarSystem-Desktop-Debug/positions.dat", "r") as infile: #for tellef

	plot_solarsystem(infile)
	plt.show()
"""

"""
with open("../build-SolarSystem-Desktop_Qt_5_7_0_clang_64bit--Debug/positions.dat", "r") as infile: #for andreas

	plot_solarsystem(infile)
	plt.show()
"""

"""
with open("../build-SolarSystem-Desktop-Debug/mercury_system.dat", "r") as infile: #for tellef
	plot_mercury(infile)
	plt.show()
"""

"""
with open("../build-SolarSystem-Desktop_Qt_5_7_0_clang_64bit-Debug/mercury_system.dat", "r") as infile: #for andreas

	plot_mercury(infile)
	plt.show()
"""

def perhelionPrecision(file):
	numberOfPlanets, n, planets = read_planets(file)
	r_planet = np.zeros((n,4))
	for k in range(1, numberOfPlanets+1):
		for i in range(n-1):
			r_planet[i] = np.asarray(planets[k][i].split()).astype(float)

	x_pos = r_planet[0:-1,1]
	y_pos = r_planet[0:-1,2]
	N = len(x_pos)

	distToSun = np.zeros(N)
	
	for i in range(N):
		distToSun[i] = np.linalg.norm([x_pos[i], y_pos[i]])
	
	time = np.linspace(0, N, N)
	plt.plot(time, distToSun)
	
	localMinIndex = argrelextrema(distToSun, np.less)[0]
	N_new = len(localMinIndex)

	localMinPlot = np.zeros(N_new)
	for i in range(N_new):
		k = localMinIndex[i]
		localMinPlot[i] = distToSun[k]
	plt.plot(localMinIndex, localMinPlot, 'ro')

	plt.show()

	theta = np.zeros(N_new)
	
	for i in range(N_new):
		k = localMinIndex[i]
		theta[i] = np.arctan2(x_pos[k],y_pos[k])*(360*3600)/(2*np.pi)
	
	time = np.linspace(0, 100, N_new)
	

	return time, theta
	


with open("../build-SolarSystem-Desktop-Debug/mercury_system_class.dat", "r") as infile:

	time, theta_class = perhelionPrecision(infile)


with open("../build-SolarSystem-Desktop-Debug/mercury_system_rel.dat", "r") as infile:

	time, theta_rel = perhelionPrecision(infile)


plt.plot(time, theta_rel, label='rel', color='r')
plt.plot(time, theta_class, label='class', color='b')
plt.legend()
plt.xlabel('time')
plt.ylabel('arcsec')
plt.show()




