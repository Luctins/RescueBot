//engine Module

//Top level variables and parameters
eng_rad= 32/2;
eng_h= 25;
eng_axle_rad= 1;
eng_axle_h= 7;
eng_bump_h= 2;
eng_bump_rad= 7/2;

echo("Included Engine File");
echo("Toplevel variables:  eng_rad, eng_h, eng_axle_rad, eng_bump_h, eng_bump_rad");
echo("Function Parameters: none");

module engine() {
    //Engine parameters
    $fn = 20;
    
    module eng_connector() {
        color([76/255, 74/255, 74/255]) difference() {
            cube([6,11,1],true);
            translate([0,0,-2]) rotate([90,0,0]) cylinder(d=1.5, h=10, center=true);    
        }    
    }
    
    
    union() {
        translate([(eng_rad+2.7),0,-(eng_h/2-1)]) eng_connector();
       //translate([0,(eng_rad-2),-(eng_h/2+2)]) eng_connector();
        
        translate([0,0,eng_h/2+eng_axle_h/2+2]) union() { 
            cylinder(h=2,r1=5, r2= 2.5, center=true);
            translate([0,0,2]) rotate([180]) cylinder(h=2,r1=5, r2= 2.5, center=true);
            }
        
         cylinder(r=eng_rad, h=eng_h, center=true);
        translate([0,0,eng_h/2])cylinder(r=eng_bump_rad,h=eng_bump_h);
         translate([0,0,eng_h/2+eng_axle_h/2+eng_bump_h]) cylinder(r=eng_axle_rad, h=eng_axle_h, center=true);
     }
}

//engine();