#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include "celestialbody.h"
#include <vector>
#include <string>
#include <fstream>

class SolarSystem
{
public:
    SolarSystem();
    CelestialBody &createCelestialBody(vec3 position, vec3 velocity, double mass);
    void calculateForcesAndEnergy();
    void calculateForcesAndEnergy_relCorr();
    int numberOfBodies() const;

    double totalEnergy() const;
    double potentialEnergy() const;
    double potentialEnergy_mercury() const;
    double kineticEnergy() const;
    void printEnergy() const;
    void writeToFile(std::string filename);
    void writeToFile_rel(std::string filename);
    vec3 angularMomentum() const;
    std::vector<CelestialBody> &bodies();

private:
    std::vector<CelestialBody> m_bodies;
    vec3 m_angularMomentum;
    std::ofstream m_file;
    double m_kineticEnergy;
    double m_potentialEnergy;
    double m_potentialEnergy_mercury;
    double m_totalEnergy;
};

#endif // SOLARSYSTEM_H
