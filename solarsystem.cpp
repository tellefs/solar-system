#include "solarsystem.h"
#include <iostream>
#include <cmath>
using namespace std;

SolarSystem::SolarSystem() :
    m_kineticEnergy(0),
    m_potentialEnergy(0),
    m_potentialEnergy_mercury(0)
{}


CelestialBody& SolarSystem::createCelestialBody(vec3 position, vec3 velocity, double mass) {
    m_bodies.push_back( CelestialBody(position, velocity, mass) );
    return m_bodies.back(); // Return reference to the newest added celstial body
}

void SolarSystem::calculateForcesAndEnergy()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_angularMomentum.zeros();
    m_potentialEnergy_mercury = 0;

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
            vec3 force = G*body1.mass*body2.mass/(dr*dr*dr)*deltaRVector;
            body1.force += force;
            body2.force -= force;

            m_potentialEnergy += G*body1.mass*body2.mass/dr;
        }

        m_kineticEnergy += 0.5*body1.mass*body1.velocity.lengthSquared();

    }
    //caclulating m_potentialEnergy_mercury
    CelestialBody mercury = m_bodies[0];
    double c_squared = 173*173/365.242199;
    double r_squared = mercury.position.lengthSquared()*mercury.position.lengthSquared();
    double l_squared = mercury.position.cross(mercury.velocity).lengthSquared();
    m_potentialEnergy = (G*mercury.mass*2e30/r_squared)*(1 +  3*l_squared/(c_squared*r_squared));

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

/*double SolarSystem::potentialEnergy_mercury () const
{
    double r_squared = ;
    double c_squared = ;
    double l_squared =

    return m_potentialEnergy_mercury;
}*/

double SolarSystem::kineticEnergy() const
{
    return m_kineticEnergy;
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
    m_file << "Planet1 = sun, planet2 = earth,... " << endl;
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
