// Arquivo Principal do carrinho

include <body.scad>
include <wheel.scad>

larg=110;
espes=20;
compr=75;


//body(80);
translate([0,larg/2,0]) rotate([-90,(90*$t),0]) wheel(75/2);
translate([0,-larg/2,0]) rotate([90,(90*$t),,0]) wheel(75/2);