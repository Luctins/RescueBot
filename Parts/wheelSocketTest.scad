//Wheel -->engine socket test

walltich = 1; //Espessura parede
axle = 5; // raio eixo motor
ajuste = 0.5; //valor para ajuste do encaixe do motor
$fn = 100;

rotate([0,0,0]) difference() {
    cylinder(h=30,r=axle+walltich,center=true);
    translate([0,0,6]) cylinder(h=20,r=axle-ajuste,center=true);
    translate([0,0,11]) #cube([30,1,10], center = true);
    
}