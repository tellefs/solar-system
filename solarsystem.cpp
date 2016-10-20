#include "solarsystem.h"
#include <iostream>
#include <cmath>
using namespace std;

SolarSystem::SolarSystem() :
    m_kineticEnergy(0),
    m_potentialEnergy(0),
    m_totalEnergy(0)
{}


CelestialBody& SolarSystem::createCelestialBody(vec3 position, vec3 velocity, double mass) {
    m_bodies.push_back( CelestialBody(position, velocity, mass) );
    return m_bodies.back(); // Return reference to the newest added celestial body
}

void SolarSystem::calculateForcesAndEnergy()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_totalEnergy = 0;
    m_angularMomentum.zeros();

    for(CelestialBody &body : m_bodies) {
        // Reset forces on all bodies
        body.force.zeros();
    }
    double pi = M_PI;
    double G = -4*pi*pi;

    for(int i=0; i<numberOfBodies(); i++) {
        CelestialBody &body1 = m_bodies[i];
        for(int j=i+1; j<numberOfBodies(); j++) {
            CelestialBody &body2 = m_bodies[j];
            vec3 deltaRVector = body1.position - body2.position;
            double dr = deltaRVector.length();
            // Calculate the force and potential energy here (!!!!!)
            vec3 force = G*body1.mass*body2.mass/(dr*dr*dr) * deltaRVector;
            body1.force += force;
            body2.force -= force;

            m_potentialEnergy += G*body1.mass*body2.mass/dr; // Supposed to be negative?
            m_angularMomentum += body1.position.cross(body1.velocity);
        }

        m_kineticEnergy += 0.5*body1.mass*body1.velocity.lengthSquared();
        m_totalEnergy = m_kineticEnergy + m_potentialEnergy;
    }

}

void SolarSystem::calculateForcesAndEnergy_relCorr()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_angularMomentum.zeros();

    for(CelestialBody &body : m_bodies) {
        // Reset forces on all bodies
        body.force.zeros();
    }
    double pi = M_PI;
    double G = -4*pi*pi;
    //  Calculating potential and kinetic energy
    CelestialBody &sun = m_bodies[0];
    CelestialBody &mercury = m_bodies[1];
    double c_squared = 63239.7263*63239.7263; // AU^2/year^2
    double r_squared = mercury.position.lengthSquared();
    double l_squared = mercury.position.cross(mercury.velocity).lengthSquared();

    vec3 deltaRVector = mercury.position - sun.position;
    double dr = deltaRVector.length();
    // Calculate the force and potential energy here (!!!!!)
    vec3 force = (G*mercury.mass*sun.mass/(dr*dr*dr))*(1 +  3*l_squared/(c_squared*r_squared))*deltaRVector; //G*.mass*body2.mass/(dr*dr*dr) * deltaRVector;
    mercury.force += force;
    sun.force -= force;

    m_potentialEnergy += G*mercury.mass*sun.mass/dr;; // Supposed to be negative?
    m_kineticEnergy += 0.5*mercury.mass*mercury.velocity.lengthSquared();
}


int SolarSystem::numberOfBodies() const
{
    return m_bodies.size();
}

double SolarSystem::totalEnergy() const
{
    return m_kineticEnergy + m_potentialEnergy;
}

double SolarSystem::potentialEnergy() const
{
    return m_potentialEnergy;
}


double SolarSystem::kineticEnergy() const
{
    return m_kineticEnergy;
}

void SolarSystem::printEnergy() const
{
    cout << "Total energy, kinetic energy, potential energy: " << m_totalEnergy << " " << m_kineticEnergy << " " << m_potentialEnergy << endl;
}

void SolarSystem::writeToFile(string filename)
{
    if(!m_file.good()) {
        m_file.open(filename.c_str(), ofstream::out);
        if(!m_file.good()) {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }

    m_file <<  numberOfBodies() << endl;
    m_file << "Celestialbody1, Celestialbody2,...." << endl;
    for(CelestialBody &body : m_bodies) {
        m_file << "1 " << body.position.x() << " " << body.position.y() << " " << body.position.z() << "\n";
    }
}

vec3 SolarSystem::angularMomentum() const
{
    return m_angularMomentum;
}

std::vector<CelestialBody> &SolarSystem::bodies()
{
    return m_bodies;
}
