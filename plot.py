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
	figure.plot(r_planet[0:-1,1],r_planet[0:-1,2],r_planet[0:-1,3], label='balle')

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
"""
#with open("../build-SolarSystem-Desktop_Qt_5_7_0_clang_64bit-Debug/positions.dat", "r") as infile:
with open("../build-SolarSystem-Desktop-Debug/positions.dat", "r") as infile: #for tellef

	plot_solarsystem(infile)
	plt.show()
"""

with open("../build-SolarSystem-Desktop_Qt_5_7_0_clang_64bit-Debug/positions_earth_sun.dat", "r") as infile: #for tellef

	plot_solarsystem(infile)
	plt.show()


"""
def perhelionPrecision(file):
	infile = open(file, 'r')
	theta = []
	for line in infile:
		values = float(line.split()[0])
		theta.append(values)

	n = len(theta)
	time = np.linspace(0, 100, n)

	return time, theta

time_rel, theta_rel = perhelionPrecision('../build-SolarSystem-Desktop-Debug/theta_rel_fewer.dat')
time_class, theta_class = perhelionPrecision('../build-SolarSystem-Desktop-Debug/theta_class_fewer.dat')

plt.plot(time_class, theta_class, 'b', label='Classical mechanics')
plt.plot(time_rel, theta_rel, 'r', label='Relativistic correction')
plt.xlabel('time [years on earth]')
plt.ylabel('$\Theta_P$ [arcsec]')
plt.title('Perihelion precision of Mercury')
plt.legend(loc='upper left')
plt.savefig('perihelion_precision_fewer.png')
plt.show()


print "observed perhelion precision, theta_p[diff between rel and class] = ", abs(theta_rel[-1] - theta_class[-1]), "arcsec."
"""



