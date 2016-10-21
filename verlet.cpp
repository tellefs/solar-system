#include "verlet.h"
#include "celestialbody.h"
#include "solarsystem.h"
#include <cmath>
Verlet::Verlet(double dt):
    m_dt(dt)
{
}

void Verlet::integrateOneStep(SolarSystem &system, bool relCorr){

    if(relCorr == true){
        system.calculateForcesAndEnergy_relCorr(); //calculating the force with relativistis correction
    }
    else if(relCorr == false){
        system.calculateForcesAndEnergy(); //caclulating the force without relativistic correction
    }

    for(CelestialBody &body : system.bodies()){
        //need to save the last step for the position, previousPosition
        body.velocity += body.force / body.mass * m_dt*0.5; //half-step for the velocity, not final
        body.position += body.velocity * m_dt; //updating the position, final
    }

    if(relCorr == true){
        system.calculateForcesAndEnergy_relCorr(); //re-caclulating forces with relativistic correction
    }
    else if(relCorr == false){
        system.calculateForcesAndEnergy(); //re-calculating the forces without relativistic correction
    }

    for(CelestialBody &body : system.bodies()){
        body.velocity += body.force/body.mass*m_dt*0.5; //updating the velocity, final
    }

}

