//main car file

//Car parts
include <body.scad>
include <wheel2.scad>
include <gear.scad>

larg=110;
espes=20;
compr=75;


//body(80);
translate([0,larg/2,0]) rotate([-90,(360*$t),0]) wheel(75/2);
translate([0,-larg/2,0]) rotate([90,(360*$t),,0]) wheel(75/2);