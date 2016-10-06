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

	r_earth = np.zeros((n,4))
	for i in range(n-1):
		r_earth[i] = np.asarray(planets[2][i].split()).astype(float)

	mpl.rcParams['legend.fontsize'] = 10
	fig = plt.figure()
	ax = fig.gca(projection='3d')
	ax.plot(r_earth[:,1],r_earth[:,2],r_earth[:,3], label="balle")
	ax.legend()

	plt.show()