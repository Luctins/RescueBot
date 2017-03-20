
module Wheel (wheelrad = 75, $fn = 100) {
   width = 10;  //largura da roda
    tichn = 3.5; //espesura da roda
    nrad = 8;  //numero de raios na roda
   /* difference() {
        cylinder(width, r = wheelrad, center = true);
        cylinder(width, r = wheelrad - tichn, center = true); 
    }
    */
    rotate_extrude(angle = 360, convexity = 10, $fn=100) {
        translate([-wheelrad,0,0]) union() {
            difference(){
                circle(r=3.5,center=true);
                translate([tichn/2,0,0]) square([tichn,tichn*2], center =true);
            }
            translate([-tichn/2,-width/2,0]) square([tichn,width], center = true);
        }
    }
   for ( i = [ 0 : nrad ]) {
       rotate([0,0,360*i/nrad]) translate([0,-tichn/2,-7]) cube([wheelrad,tichn,width], center = false);
       }
}
Wheel(75);


        
    
    