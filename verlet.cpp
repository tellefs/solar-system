#include "verlet.h"
#include "celestialbody.h"
#include "solarsystem.h"
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
    system.calculateForcesAndEnergy(); //re-calculating the forces, which we need for the full velocity step
    }

    for(CelestialBody &body : system.bodies()){
        body.velocity += body.force/body.mass*m_dt*0.5; //updating the velocity, final
    }

}

// Verlet-method made earlier
//   have to make this method work with this class system
//      The new way does not save all the elements, but i need the last position/velocity value
//force = force_factor*pos(k, i);
//vel_halfStep_negative = vel(k, i-1) + (vel(k, i) - vel(k,i-1))/2.;
//vel_halfStep_positive = vel_halfStep_negative + h*force;
//pos(k, i+1) = pos(k, i) + h + vel_halfStep_positive;
//force = force_factor*pos(k, i+1);
//vel(k, i+1) = vel_halfStep_positive + (h/2.)*force;


// Euler-method, already in this class system, just for comparison
//for(CelestialBody &body : system.bodies()) {
//    body.position += body.velocity*m_dt;
//    body.velocity += body.force / body.mass * m_dt;
