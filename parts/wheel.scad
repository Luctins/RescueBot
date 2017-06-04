//Wheel

echo("included wheel");
echo("toplevel variables: wheel_tich, wheel_frame, axle_len, axle_rad");
echo("parameters: radius, rumber_of_rad, axle_rad");

wheel_thick = 22; //wheel tichness
wheel_frame = 5; //wheel frame tichness
axle_len = 30;

module wheel (wheel_radius = 75, wheel_nrad = 6, axle_rad = 1.5) {
     $fn = 30;
    

                    //wheel exterior
                    rotate_extrude(angle=360) translate([wheel_radius,0,0]) hull() {
                        translate([0,wheel_thick/2,0]) circle(wheel_frame/2);
                        translate([0,-(wheel_thick/2),0]) square(wheel_frame,true);
                    }
                
                    //wheel axles
                    for (i = [0 : wheel_nrad]) {
                       translate([sin(i*360/wheel_nrad)*axle_rad,-cos(i*360/wheel_nrad)*axle_rad,0]) rotate([90,0,i*360/wheel_nrad]) linear_extrude(height = wheel_radius-axle_rad) hull() {
                            translate([0,wheel_thick/2,0]) circle(wheel_frame/2);
                            translate([0,-(wheel_thick/2),0]) square(wheel_frame,true);
                        }
                    }
                    difference() {
             cylinder(h=wheel_thick+wheel_frame, r=axle_rad+5, center=true);
         //wheel main axle
        /*translate([0,0,-10])*/ cylinder(h=axle_len, r=axle_rad, center=true);
                    }
    
}

//wheel(25,3,1.5);
