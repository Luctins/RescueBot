module wheel (wheel_radius = 75, wheel_nrad = 6, $fn = 50) {
    wheel_thick = 10; //wheel tichness
    wheel_frame = 5; //wheel frame tichness
    axle_len = 20;
    axle_rad = 5;
    
    //wheel exterior
    rotate_extrude(angle=360) translate([wheel_radius,0,0]) hull() {
        translate([0,wheel_thick/2,0]) circle(wheel_frame/2);
        translate([0,-(wheel_thick/2),0]) square(wheel_frame,true);
    }

    //wheel axles
    for (i = [0 : wheel_nrad]) {
        rotate([90,0,i*360/wheel_nrad]) linear_extrude(height = wheel_radius) hull() {
            translate([0,wheel_thick/2,0]) circle(wheel_frame/2);
            translate([0,-(wheel_thick/2),0]) square(wheel_frame,true);
        }
    }

    //wheel main axle
    cylinder(h=wheel_thick+wheel_frame, r=axle_rad+5, center=true);
    translate([0,0,-10]) cylinder(h=axle_len, r=axle_rad, center=true);
}
