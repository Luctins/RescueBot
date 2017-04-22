
module wheel (wheelrad = 75, $fn = 100) {
   width = 10;  //largura da roda
    tichn = 3.5; //espesura da roda
    nrad = 8;  //numero de raios na roda
   /* difference() {
        cylinder(width, r = wheelrad, center = true);
        cylinder(width, r = wheelrad - tichn, center = true); 
    }
    */
    union() {
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
      walltich = 1; //Espessura parede
      axle = 5; // raio eixo motor
      ajuste = 0.5; //valor para ajuste do encaixe do motor
      $fn = 100;

      rotate([180,0,0]) translate([0,0,10]) difference() {
        cylinder(h=30,r=axle+walltich,center=true);
        translate([0,0,6]) cylinder(h=20,r=axle-ajuste,center=true);
        translate([0,0,11]) #cube([30,1,10], center = true);
      }
  }
       
}


//wheel();
        
    
    