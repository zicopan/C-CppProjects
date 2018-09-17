#include <stdio.h>
#include <math.h>
#include "cpgplot.h"

int main()
{
    const int nintervals = 2000000;
    float x[nintervals+1], y[nintervals+1], ax, ay, vx, vy, G, ms, me, r;
    float re, ra, years, ans, ans2;
    float d, dx, dy;
    float x1[nintervals+1], y1[nintervals+1], ax1, ay1, vx1, vy1;
    float dt;
    int i;
    
    G=1;    //grav const
    ms=1;   //Sun mass in solar masses
    me=3.0e-6; //Earth in solar masses
    
    x[0]=1; //original x-position of Earth
    y[0]=0; //original y-position of Earth
    vx=0;   //initial vx
    vy=1;   //intial vy

    x1[0]=4; //original x-position of asteroid
    y1[0]=0; //original y-position of asteroid
    vx1=0;   //initial vx 
    vy1=0.15; //initial vy
    
    
    // Open a plot window
    if (!cpgopen("/XWINDOW")) return 1;
    
    // Set-up plot axes
    cpgenv(-5,5,-5.,5,1,1);

    // Label axes
    cpglab("x", "y", "Orbital Trajectories");
    
// Time step
    dt = 100./nintervals;
  
    // Compute the function at the points
    for (i=0;i<=nintervals;i++) {
        
//acceleration components
        ax = -((G*ms*x[i])/sqrt((x[i]*x[i]+y[i]*y[i])*(x[i]*x[i]+y[i]*y[i])*(x[i]*x[i]+y[i]*y[i])));
        ay = -((G*ms*y[i])/sqrt((x[i]*x[i]+y[i]*y[i])*(x[i]*x[i]+y[i]*y[i])*(x[i]*x[i]+y[i]*y[i])));

//asteroid with contributions from sun & earth
ax1 = -((G*ms*x1[i])/sqrt((x1[i]*x1[i]+y1[i]*y1[i])*(x1[i]*x1[i]+y1[i]*y1[i])*(x1[i]*x1[i]+y1[i]*y1[i])))
-((G*me*x[i])/sqrt((x[i]*x[i]+y[i]*y[i])*(x[i]*x[i]+y[i]*y[i])*(x[i]*x[i]+y[i]*y[i])));
 
ay1 = -((G*ms*y1[i])/sqrt((x1[i]*x1[i]+y1[i]*y1[i])*(x1[i]*x1[i]+y1[i]*y1[i])*(x1[i]*x1[i]+y1[i]*y1[i])))
-((G*me*y[i])/sqrt((x[i]*x[i]+y[i]*y[i])*(x[i]*x[i]+y[i]*y[i])*(x[i]*x[i]+y[i]*y[i])));

//velocity components with time step
        vx = vx + (dt/2)*ax;
        vy = vy + (dt/2)*ay;

        vx1 = vx1 + (dt/2)*ax1;
        vy1 = vy1 + (dt/2)*ay1;

//new postions
        x[i+1] = x[i] + dt*vx;
        y[i+1] = y[i] + dt*vy;

        x1[i+1] = x1[i] + dt*vx1;
        y1[i+1] = y1[i] + dt*vy1;
        

ax = -((G*ms*x[i+1])/sqrt((x[i+1]*x[i+1]+y[i+1]*y[i+1])*(x[i+1]*x[i+1]+y[i+1]*y[i+1])*(x[i+1]*x[i+1]+y[i+1]*y[i+1])));
ay = -((G*ms*y[i+1])/sqrt((x[i+1]*x[i+1]+y[i+1]*y[i+1])*(x[i+1]*x[i+1]+y[i+1]*y[i+1])*(x[i+1]*x[i+1]+y[i+1]*y[i+1])));

ax1 = -((G*ms*x1[i+1])/sqrt((x1[i+1]*x1[i+1]+y1[i+1]*y1[i+1])*(x1[i+1]*x1[i+1]+y1[i+1]*y1[i+1])*(x1[i+1]*x1[i+1]+y1[i+1]*y1[i+1])))
-((G*me*x[i])/sqrt((x[i+1]*x[i+1]+y[i+1]*y[i+1])*(x[i+1]*x[i+1]+y[i+1]*y[i+1])*(x[i+1]*x[i+1]+y[i+1]*y[i+1])));
 
ay1 = -((G*ms*y1[i+1])/sqrt((x1[i+1]*x1[i+1]+y1[i+1]*y1[i+1])*(x1[i+1]*x1[i+1]+y1[i+1]*y1[i+1])*(x1[i+1]*x1[i+1]+y1[i+1]*y1[i+1])))
-((G*me*y[i+1])/sqrt((x[i+1]*x[i+1]+y[i+1]*y[i+1])*(x[i+1]*x[i+1]+y[i+1]*y[i+1])*(x[i+1]*x[i+1]+y[i+1]*y[i+1])));



       //repeat
        vx = vx + (dt/2)*ax;
        vy = vy + (dt/2)*ay;

        vx1 = vx1 + (dt/2)*ax1;
        vy1 = vy1 + (dt/2)*ay1; 

//near Earth asteroid computation
dx = x1[i+1] - x[i+1];
dy = y1[i+1] - y[i+1];
r = sqrt(dx*dx + dy*dy);


//distance from Earth to Moon in AU = about 0.002
if (r <= 0.002)
printf("After %d years, the asteroid is as close to the Earth as the Earth is to the Moon \n",i/251292);

    }


//iterations for one orbit
ans = 439239 - 187947;
printf("Iterations for 1 orbit: %f  \n",ans);

//years
ans2 = (nintervals/251292);
printf("Total # of orbits = %f\n\n",ans2);
printf("This plot, therefore, displays the orbital trajectories of\nan Earth-Asteroid system over %f years.\n",ans2);

//Sun
cpgsci(7); 
cpgcirc(0,0,0.1);

 // Plot the curve
    cpgsci(6);
    cpgline(nintervals+1,x,y);
   
    cpgsci(3);
    cpgline(nintervals+1,x1,y1);
    
    // Pause and then close plot window
    cpgclos();
    
}
