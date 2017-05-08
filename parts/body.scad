//corpo do carrinho
include<phone.scad>

module body(width= 100, length= 100, heigth= 20 ) {
    tichn= 4; //wall tichness
    phone_h = 151;
    phone_angle = 30;
    suport_h = (phone_h/2)*sin(abs(90-phone_angle));
    
    
    difference() {
        cube([width,length,heigth],true);
        translate([0,0,tichn]) cube([width-2*tichn, length-2*tichn, heigth-tichn], true);  
    }
    translate([(phone_h)*cos(abs(90-phone_angle))-(phone_h/2)*cos(phone_angle), 0, suport_h/2]) cube([tichn+1, 75, suport_h], true);
    //translate(,0,0]) cube([tichn, 75, 55], true);
    
    %translate([0,0,(phone_h/2)*cos(phone_angle)]) rotate([0,phone_angle,0]) phone();
}

body();
