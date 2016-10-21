#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include "solarsystem.h"
#include "euler.h"
#include "verlet.h"
#include <fstream>
#include <iomanip>

using namespace std;

int main(int numArguments, char **arguments)
{
    int numTimesteps = 1e5; // numTimesteps*dt = years
    if(numArguments >= 2) numTimesteps = atoi(arguments[1]);
    double years = 100;
    double dt = years/numTimesteps;
    double t_elapsed;
    double sun_mass = 2e30;  
    double pi = M_PI;
    double G = 4*pi*pi;
    double AUday_to_AUyear = 365.242199;


    // Circular orbit
    cout << "Earth-Sun system: " << endl;
    SolarSystem earthSun;
    earthSun.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0 );
    earthSun.createCelestialBody( vec3(1,0,0),
                                     vec3(0,2*pi,0),
                                     (6e24)/sun_mass)
                                    ; //earth,  init. conditions for pos and vel retrieved from NASA october 5. 2016
    earthSun.calculateForcesAndEnergy();
    earthSun.printEnergy();
    cout << "Total angular momentum: " << earthSun.angularMomentum() << endl;
    earthSun.writeToFile("positions_earth_sun.dat");   // initial position

    clock_t start = clock();
    // Euler integrator(dt);
    Verlet integrator(dt);
    for(int timestep=0; timestep<numTimesteps; timestep++) {
        integrator.integrateOneStep(earthSun, false);
        earthSun.writeToFile("positions_earth_sun.dat");
    }
    clock_t finish = clock();
    t_elapsed = double(finish - start) / CLOCKS_PER_SEC;
    earthSun.printEnergy();
    cout << "Total angular momentum: " << earthSun.angularMomentum() << endl;
    cout << "time elapsed: " << t_elapsed << endl;


    // Escape velocity
    cout << "Earth-Sun (escape) system: " << endl;
    SolarSystem earthSun2;
    earthSun2.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0 );
    earthSun2.createCelestialBody( vec3(1,0,0),
                                     vec3(0,sqrt(8)*pi,0),
                                     (6e24)/sun_mass)
                                    ; //earth,  init. conditions for pos and vel retrieved from NASA october 5. 2016
    earthSun2.calculateForcesAndEnergy();
    earthSun2.printEnergy();
    cout << "Total angular momentum: " << earthSun2.angularMomentum() << endl;
    earthSun2.writeToFile("positions_earth_sun_esc.dat");   // initial position

    clock_t start1 = clock();
    //Verlet integrator(dt);
    for(int timestep=0; timestep<numTimesteps; timestep++) {
        integrator.integrateOneStep(earthSun2, false);
        earthSun2.writeToFile("positions_earth_sun_esc.dat");
    }
    clock_t finish1 = clock();
    t_elapsed = double(finish1 - start1) / CLOCKS_PER_SEC;
    earthSun2.printEnergy();
    cout << "Total angular momentum: " << earthSun2.angularMomentum() << endl;
    cout << "time elapsed: " << t_elapsed << endl;


    // Three body problem
    cout << "Earth-Jupiter-Sun system: " << endl;
    SolarSystem threebody;
    double jupiter_factor = 1e2;
    threebody.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0 );
    threebody.createCelestialBody( vec3(9.819128739328793E-01, 2.104822076393571E-01, -1.756137106591000E-04),
                                     vec3(-3.851159854117840E-03, 1.677807321756382E-02, -7.444403689401816E-07)*AUday_to_AUyear,
                                     (6e24)/sun_mass)
                                    ; //earth,  init. conditions for pos and vel retrieved from NASA october 5. 2016

    threebody.createCelestialBody(vec3(-5.433468170028908E+00, -3.819061221110369E-01, 1.231004384238452E-01),
                                     vec3(4.425651679847022E-04, -7.171108917491057E-03, 1.992744446163222E-05)*AUday_to_AUyear,
                                     jupiter_factor*(1e27)/sun_mass); //jupiter
    threebody.calculateForcesAndEnergy();
    threebody.writeToFile("positions_earth_sun_jup.dat");   // initial position

    clock_t start2 = clock();
    //Verlet integrator(dt);
    for(int timestep=0; timestep<numTimesteps; timestep++) {
        integrator.integrateOneStep(threebody, false);
        threebody.writeToFile("positions_earth_sun_jup.dat");
    }
    clock_t finish2 = clock();
    t_elapsed = double(finish2 - start2) / CLOCKS_PER_SEC;
    cout << "time elapsed: " << t_elapsed << endl;


    cout << "Full solar system:" << endl;
    SolarSystem solarSystem;
    // We create new bodies like this. Note that the createCelestialBody function returns a reference to the newly created body
    // This can then be used to modify properties or print properties of the body if desired
    // Use with: solarSystem.createCelestialBody( position, velocity, mass );

    // CelestialBody &sun = solarSystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0 );

    // We don't need to store the reference, but just call the function without a left hand side
    // now i need my planets

    solarSystem.createCelestialBody( vec3(9.819128739328793E-01, 2.104822076393571E-01, -1.756137106591000E-04),
                                     vec3(-3.851159854117840E-03, 1.677807321756382E-02, -7.444403689401816E-07)*AUday_to_AUyear,
                                     (5.972e24)/sun_mass)
                                    ; //earth,  init. conditions for pos and vel retrieved from NASA october 5. 2016

    solarSystem.createCelestialBody(vec3(-5.433468170028908E+00, -3.819061221110369E-01, 1.231004384238452E-01),
                                     vec3(4.425651679847022E-04, -7.171108917491057E-03, 1.992744446163222E-05)*AUday_to_AUyear,
                                     (1.898e27)/sun_mass); //jupiter

    solarSystem.createCelestialBody(vec3(-1.388351215994794E-01, 2.874076124640064E-01, 3.611730762400382E-02),
                                     vec3(-3.081033504804020E-02, -1.153752302730325E-02, 1.883146626624065E-03)*AUday_to_AUyear,
                                     (3.285e23)/sun_mass); //mercury

    solarSystem.createCelestialBody(vec3(2.531171709934956E-03, -7.235439738148072E-01, -1.006620932838833E-02),
                                    vec3(2.008934322426700E-02, -9.726053625259401E-05, -1.160780990531775E-03)*AUday_to_AUyear,
                                    (4.867e24)/sun_mass); //venus

    solarSystem.createCelestialBody(vec3(1.074137801923908E+00, -8.751565791508180E-01, -4.484330241084649E-02),
                                     vec3(9.406114898320066E-03, 1.202410268499505E-02, 2.097435381751857E-05)*AUday_to_AUyear,
                                     (6.39e23)/sun_mass); //mars

    solarSystem.createCelestialBody(vec3(-2.318303159285024E+00, -9.761896118742531E+00, 2.619996914174937E-01),
                                     vec3(5.122777078109817E-03, -1.306326757884738E-03, -1.812965626845902E-04)*AUday_to_AUyear,
                                     (5.683e26)/sun_mass); //saturn

    solarSystem.createCelestialBody(vec3(1.847838443295973E+01, 7.526847462019028E+00, -2.114361038013451E-01),
                                     vec3(-1.512383759608680E-03, 3.459146288519939E-03, 3.242416050249801E-05)*AUday_to_AUyear,
                                     (8.681e25)/sun_mass); //uranus

    solarSystem.createCelestialBody(vec3(2.825072704568992E+01, -9.952093577677799E+00, -4.461218547546795E-01),
                                     vec3(1.022588623946866E-03, 2.979574756810357E-03, -8.514325155122657E-05)*AUday_to_AUyear,
                                     (1.024e26)/sun_mass); //neptune

    solarSystem.createCelestialBody(vec3(9.393096450667111E+00, -3.182064102580347E+01, 6.879522592437006E-01),
                                     vec3(3.065499934972441E-03, 2.293283900283695E-04, -9.119583887771224E-04)*AUday_to_AUyear,
                                     (1.31e22)/sun_mass); //pluto

    vec3 sunVelocity;
    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
    vector<CelestialBody> &bodies = solarSystem.bodies();
    // Give the position and velocity of objects
    for(int i = 0; i<bodies.size(); i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        sunVelocity += body.mass*body.velocity;
    }
    sunVelocity /= sun_mass;
    solarSystem.createCelestialBody( vec3(0,0,0), sunVelocity, 1.0 );

//  // Create some random celestial objects
//    for (int i=0; i<300; i++){
//        double r1 = ((double) rand() / (RAND_MAX));
//        double r2 = ((double) rand() / (RAND_MAX));
//        double r3 = ((double) rand() / (RAND_MAX));
//        double r4 = ((double) rand() / (RAND_MAX));
//        double r5 = ((double) rand() / (RAND_MAX));
//        double r6 = ((double) rand() / (RAND_MAX));
//        double r7 = ((double) rand() / (RAND_MAX));

//        solarSystem.createCelestialBody(vec3(r1, r2, r3)*5, vec3(r4, r5, r6)*AUday_to_AUyear*(1e-2), r7);
//    }


//  // example for creating multiple objects randomly placed between -10:10
//    for(int i=0; i<100; i++) {
//        double x = (2*rand() / double(RAND_MAX) - 1) * 10;
//        double y = (2*rand() / double(RAND_MAX) - 1) * 10;
//        double z = (2*rand() / double(RAND_MAX) - 1) * 10;

//        vec3 pos(x,y,z);

//        solarSystem.createCelestialBody(pos, vec3(0,0,0), 0.000000001);

//    }

//    // To get a list (a reference, not copy) of all the bodies in the solar system, we use the .bodies() function
//    vector<CelestialBody> &bodies = solarSystem.bodies();

//    // Give the position and velocity of objects
//    for(int i = 0; i<bodies.size(); i++) {
//        CelestialBody &body = bodies[i]; // Reference to this body
//        cout << "The position of this object is " << body.position << " with velocity " << body.velocity << endl;
//    }


    solarSystem.calculateForcesAndEnergy();
    solarSystem.writeToFile("positions.dat");   // initial position
    // Euler integrator(dt);
    // Verlet integrator(dt);
    // Verlet integrator(dt);
    bool relCorr = false;
    for(int timestep=0; timestep<numTimesteps; timestep++) {
        integrator.integrateOneStep(solarSystem, relCorr);
        solarSystem.writeToFile("positions.dat");
        /* if (timestep % 1000 == 0 ) {
            cout << solarSystem.totalEnergy() << endl;
        } */
    }
//    cout << "I just created a solar system that has " << solarSystem.bodies().size() << " objects." << endl;


    // Mercury perihelion precession
    cout << "Classical Mercury system: " << endl;
    SolarSystem mercurySystem;  // classical

    mercurySystem.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0 );     // sun
    mercurySystem.createCelestialBody(vec3(0.3075, 0, 0),
                                     vec3(0, 12.44, 0),
                                     (3.285e23)/sun_mass);    //mercury

    mercurySystem.writeToFile("mercury_system_class.dat");    // initial position
    for(int timestep=0; timestep<numTimesteps; timestep++) {
        integrator.integrateOneStep(mercurySystem, false);
        mercurySystem.writeToFile("mercury_system_class.dat");
    }


    cout << "Gen rel Mercury system: " << endl;
    SolarSystem mercurySystem_rel;

    mercurySystem_rel.createCelestialBody( vec3(0,0,0), vec3(0,0,0), 1.0 );     // sun
    mercurySystem_rel.createCelestialBody(vec3(0.3075, 0, 0),
                                     vec3(0, 12.44, 0),
                                     (3.285e23)/sun_mass);    //mercury

    vec3 threePositions(0, 0, 0);
    vec3 threeTheta(0,0,0);

    mercurySystem_rel.writeToFile("mercury_system_rel.dat");    // initial position

    for(int timestep=0; timestep<numTimesteps; timestep++) {
        integrator.integrateOneStep(mercurySystem_rel, true);

        double r = (mercurySystem_rel.bodies().at(0).position - mercurySystem_rel.bodies().at(1).position).length();

        threePositions[0] = threePositions[1];
        threePositions[1] = threePositions[2];
        threePositions[2] = r;

        double theta = atan2(mercurySystem_rel.bodies().at(1).position.y(), mercurySystem_rel.bodies().at(1).position.x())*(360*3600)/(2* M_PI );

        threeTheta[0] = threeTheta[1];
        threeTheta[1] = threeTheta[2];
        threeTheta[2] = theta;

        ofstream outFile;
        outFile.open("theta_rel.dat", ofstream::app);
        outFile << setprecision(15) << 0 << endl;
        if(threePositions[0] > threePositions[1] && threePositions[2] > threePositions[1]){
            //writing to file
            outFile <<7.6 << endl;
            //cout<<threeTheta[1]<<endl;

        }
        outFile.close();


        mercurySystem_rel.writeToFile("mercury_system_rel.dat");
    }
    return 0;
}
