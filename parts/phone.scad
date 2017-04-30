//Phone model, for reference to the other modules
//in the model size will be added 3 mm in every direction for a beter fit

module phone() {
//Module variables
    tichn = 10; //tichness3
    width = 78 - 2*tichn; // 
    heigth = 151 - 2*tichn; //
    
//internal modules
    module edge (length = 10, edge_rad = tichn) {
        adj = 1; //adjust value
        
        rotate([0,0,0]) difference() {
            cylinder(r=edge_rad, h=length, center = true);
            translate([0,-(edge_rad+adj/2),-(length/2+adj/2)]) cube([edge_rad+adj, 2*edge_rad+adj, length+adj]);
            translate([-(edge_rad+adj/2),0,-(length/2+adj/2)]) cube([edge_rad+adj, edge_rad+adj, length+adj]);
        }
    }
    
    module edge_connect() {
        adj = 1;
        difference() {
            sphere(tichn);
            translate([tichn/2,0,0]) cube([tichn,2*tichn,2*tichn],true);
        }
    }
    
    module camera (diam = 10) { 
        heig = 8;
        //Camera Eye
        rotate([0,0,180]) union() {
            color("grey") minkowski () {
                $fn = 20;
                rotate([0,90,0]) cylinder(h=heig,d=diam,center= true);
                sphere(1); 
            }
            color("black") translate([heig/2+1,0,0]) rotate([0,90]) cylinder(h=2, d=3, center=true, $fn = 10);
        }              
    } 
    
    
    translate([-1,0,heigth/2+tichn-17]) camera();
    hull() {
        translate([tichn/2, width/2, heigth/2]) edge_connect();
        translate([tichn/2, -width/2, heigth/2]) edge_connect();
        translate([tichn/2, width/2, -heigth/2]) edge_connect();
        translate([tichn/2, -width/2, -heigth/2]) edge_connect();
        
        translate([tichn/2,width/2]) rotate([0,0,-90]) edge(heigth);
        translate([tichn/2,-width/2]) edge(heigth);
        translate([tichn/2,0,heigth/2]) rotate([-90,0,0]) edge(width);
        translate([tichn/2,0,-heigth/2]) rotate([90,0,0]) edge(width);
        rotate([0,0,0]) cube([tichn,width,heigth],true);
    }
}

phone();
