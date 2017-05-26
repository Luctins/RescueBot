module header(type="male",xPinCount=1,yPinCount=1,height=11.5){
    pinSpace = 2.5;
    for(i=[0:yPinCount-1]){
        translate([0,i*pinSpace,0]){
            for(j=[0:xPinCount-1]){
                //Pin
                translate([(j*pinSpace)-0.32,-0.32,0])
                    color("gold")cube([0.64,0.64,3]);
                if(type == "male" || type == 1){
                    translate([(j*pinSpace)-0.32,-0.32,3])
                        color("gold")cube([0.64,0.64,height - 3]);
                }//End of male
                if(type == "female" || type == 0){
                    difference(){
                        color([0.2,0.2,0.2])
                        translate([(j*pinSpace)-1.25,-1.25,5.5])
                            cube([pinSpace,2.5,height-5.5]);
                        
                        color([0.2,0.2,0.2])
                        translate([(j*pinSpace)-0.32,-0.32,3])
                            cube([0.64,0.64,height]);   
                    }//End of difference       
                }//End of female
                //Block
                color([0.2,0.2,0.2])
                translate([(j*pinSpace)-1.25,-1.25,3])
                    cube(pinSpace,2.5,2.5);
                
            }//End of xPin loop
        }//End of yPin loop
    }//End of yPin loop

}//End of module header

module USBJack(type="B"){
    if(type == "B" || type == "b")
    difference(){
        cube([12,16.3,10.5]);
        difference(){
            rotate([90,0,0])
            translate([1.3,1,-9])
            linear_extrude(height=10){
                polygon(points=[
                    [0,0],
                    [0,6.7],
                    [2.5,8],
                    [7,8],
                    [9.5,6.7],
                    [9.5,0]
                ]);//End of polygon
            }//End of linear_extrude
            translate([3.2,-1.1,4])
            cube([5.6,11,3.18]);
        }//End of second diff 
    }//End of first diff
    else{ echo("USB type no implimented yet");}
}


//board
difference(){
translate([0,0,-1.25]){
translate([0,0,1.25]){
    color("navy")
    difference(){
        cube([53.4,68.5,1.75]);
        translate([2.5,15,-0.01])
        cylinder(r=1.6,h=3,$fn=24);
        translate([51,13.5,-0.01])
        cylinder(r=1.6,h=3,$fn=24);
        translate([18,65.8,-0.01])
        cylinder(r=1.6,h=3,$fn=24);
        translate([45.5,65.8,-0.01])
        cylinder(r=1.6,h=3,$fn=24);
        translate([-0.01,65.7,-1])
        linear_extrude(height=5)
        polygon(points=[
            [0,0],
            [0,3],
            [15.5,3],
            [13,0]
        ]);
        
        translate([47.91,65.51,-1])
        linear_extrude(height=5)
        polygon(points=[
            [0,3],
            [5.5,3],
            [5.5,0],
            [2.25,0]
        ]);
    }
    //USB jack
    translate([9,-6.5,1.75])
    USBJack();
}

//Round Caps
translate([44.5,18,3])
cylinder(r=3,h=5,$fn=24);
translate([44.5,25,3])
cylinder(r=3,h=5,$fn=24);

//Oval Cap
translate([28,15.5,3])
hull(){
    cylinder(r=1.75,h=3,$fn=24);
    translate([0,6.4,0])
    cylinder(r=1.75,h=3,$fn=24);
}
//Power Jack
translate([40.3,-1,3])
color([0.2,0.2,0.2])
difference(){
    union(){
        cube([9,3.37,11]);
        hull(){
            cube([9,14.25,1]);
            rotate([-90,0,0])
            translate([4.5,-5.5,3.37])
            cylinder(r=4.25,h=10.88,$fn=24);
        }
    }
    rotate([90,0,0])
    translate([4.5,6,-10])
    cylinder(r=3.1,h=11,$fn=24);
}

//Chip
color([0.2,0.2,0.2])
translate([32,28.5,3])
cube([9.8,35.5,7.25]);

//TopHeaders
translate([2.7,19,0])
header(0,1,10);
translate([2.7,45.5,0])
header(0,1,8);

//BottomHeaders
translate([51,28,0])
header(0,1,8);
translate([51,50.5,0])
header(0,1,6);

//SDA SCL header
translate([5.75,15.6,0])
header(1,2,3);

//ICSP header
translate([23,64,0])
header(1,3,2);
}
translate([0,0,-3])
cube([100,100,3]);
}

