module wheel (radius = 75, nrad = 6, $fn = 100) {
    thichn = 5; // wheel tichness
    width = 15; //wheel width
    
    //translate([radius,0,0]) rotate([90,0,0])
    rotate_extrude(angle = 360, convexity = 100) {
      translate([radius,0,0]) {
        #hull() {  
          translate([0,width/2-thichn/2,0]) circle(thichn/2);
          translate([0,-(width/2-thichn/2),0]) circle(thichn/2);
          square([thichn,width-2*thichn/2],true);
        } } }
        
    //Now for the axles
    for (i = [0 : nrad]) {
        rotate([90,0,i*360/nrad]) linear_extrude(height = radius) { 
            translate([0,width/2-thichn/2,0]) circle(thichn/2);
            translate([0,-(width/2-thichn/2),0]) circle(thichn/2);
            square([thichn,width-2*thichn/2],true);
        }
    }
    //cylinder()
}

//wheel(50,8);
