echo("included Body file");
echo("toplevel vars: None");
echo("Arguments: width, length, heigth, eng_rad, wheel_axle_rad,wall_tichn");


module body(width= 100, length= 100, heigth= 20, eng_rad = 15, wheel_axle_rad = 1.5, tichn= 5) {
     //wall tichness
    
    
    
    difference() {
        cube([length,width,heigth],true);
        translate([0,0,-tichn]) cube([length-2*tichn, width-2*tichn, heigth-tichn], true);
        
        //Engine holes
        //translate([-(length/2-eng_rad-5),-(width/2-2),-3]) rotate([90,0,0]) cylinder(r=eng_rad,h=tichn+2,center=true);
        //translate([-(length/2-eng_rad-5),(width/2-2),-3]) rotate([90,0,0]) cylinder(r=eng_rad,h=tichn+2,center=true);
        translate([-(0),-(width/2-2),-3]) rotate([90,0,0]) cylinder(r=eng_rad,h=tichn+2,center=true);
        translate([-(0),(width/2-2),-3]) rotate([90,0,0]) cylinder(r=eng_rad,h=tichn+2,center=true);
        
        //Wheel Axle Hole
        translate([-(4*length/10),(width/2-tichn/2),-(3*heigth/8)]) rotate([90]) cylinder(r=wheel_axle_rad,h=tichn+2,center=true,$fn=15); 
        translate([-(4*length/10),-(width/2-tichn/2),-(3*heigth/8)]) rotate([90]) cylinder(r=wheel_axle_rad,h=tichn+2,center=true,$fn=15); 
       
        //corte traseiro
       
        translate([length/2,0,-(1.5*tichn)]) cube([length/2+tichn,width+1,heigth], true);
    }
}

//body(100,150,50);