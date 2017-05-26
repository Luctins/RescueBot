echo("included Body file");
echo("toplevel vars: None");
echo("Arguments: width, length, heigth, eng_rad");



module body(width= 100, length= 100, heigth= 20, eng_rad = 15 ) {
    tichn= 4; //wall tichness
    
    
    
    difference() {
        cube([length,width,heigth],true);
        translate([0,0,-tichn]) cube([length-2*tichn, width-2*tichn, heigth-tichn], true);
        
        //Engine holes
        translate([-(length/2-eng_rad-5),-(width/2-2),-3]) rotate([90,0,0]) cylinder(r=eng_rad,h=tichn+2,center=true);
         translate([-(length/2-eng_rad-5),(width/2-2),-3]) rotate([90,0,0]) cylinder(r=eng_rad,h=tichn+2,center=true);
        
       //corte traseiro
       //TODO: make this escallable
        translate([60,0,-20])  rotate([0,-20,0]) cube([200,105,50], true);
    }
}

//body(100,150,50);