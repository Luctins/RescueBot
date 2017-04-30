//engine Module

module engine() {
    //Engine parameters
    $fn = 30;
    eng_rad = 15;
    eng_h = 43;
    eng_axle_rad = 1.5;
    eng_axle_h = 8;
    
    module eng_connector() {
        color([76/255, 74/255, 74/255]) difference() {
            cube([2.5,1,6],true);
            translate([0,0,-2]) rotate([90,0,0]) cylinder(d=1.5, h=10, center=true);    
        }    
    }
    
    
    union() {
        translate([0,-(eng_rad-2),-(eng_h/2+2)]) eng_connector();
        translate([0,(eng_rad-2),-(eng_h/2+2)]) eng_connector();
        
        cylinder(r=eng_rad, h=eng_h, center=true);
        translate([0,0,eng_h/2+eng_axle_h/2]) cylinder(r=eng_axle_rad, h=eng_axle_h, center=true);
     }
}

engine();