//Gear Module
// Arguments: Gear Radius, number of teeth, gear depht and gear tichness

module gear (gear_rad = 10, teethcount = 30, gear_dep = 1, gear_wid = 10) {
    resol = 0.5; //point resolution

    gear_pts= [for (i = [0:resol:360]) let ( 
        x = gear_rad*cos(i)+cos(i)*sin(teethcount*i)*gear_dep, 
        y= gear_rad*sin(i)+sin(i)*sin(i*teethcount)*gear_dep 
        ) [x,y] ];
    
    linear_extrude(height = gear_wid, convexity= 10, slices = 50, center = true)polygon(points = gear_pts);
}

gear(10,30,1);
translate([30.5,0,0])gear(20,60,1);

