//File for assembling the car itself

//Car parts
include <body.scad>
include <wheel.scad>
//include <gear.scad>
include <engine.scad>
include <engine_connector.scad>



//Body vars
body_length = 100;
body_width = 75;
body_h = eng_rad*2+15;
eng_fit = 0.5;
body_wall_tichn = 5;

body(body_width,body_length,body_h,eng_rad+eng_fit,eng_axle_rad, body_wall_tichn);

//Arduino
%translate([35,-35,body_h/2]) rotate([0,0,90]) /*color("lightBlue")*/ import ("Arduino_Model/files/Arduino.stl");

//Engine
%translate([-(0),-body_width/2,-3]) rotate([90])engine();
%translate([-(0),body_width/2,-3]) rotate([-90]) engine();

//Wheel
wheel_axle_rad = 1.5;
%translate([-(4*body_length/10),(body_width/2-body_wall_tichn/2+axle_len*2),-(3*body_h/8)]) rotate([-90]) wheel(25,3);
%translate([-(4*body_length/10),-(body_width/2-body_wall_tichn/2+axle_len*2),-(3*body_h/8)]) rotate([90]) wheel(25,3);




