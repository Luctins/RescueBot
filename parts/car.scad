//File for assembling the car itself

//Car parts
include <body.scad>
include <wheel.scad>
//include <gear.scad>
include <engine.scad>
include <engine_connector.scad>

translate([35,-35,20]) rotate([0,0,90]) color("lightBlue") import ("Arduino_Model/files/Arduino.stl");

//Body vars
body_length = 100;
body_width = 75;
body_h = eng_rad*2+10;
eng_fit = 0.5;

body(body_width,body_length,body_h,eng_rad+eng_fit);

//Engine
translate([-(body_length/2-eng_rad-5-eng_fit),-body_width/2,-3])rotate([90])engine();
translate([-(body_length/2-eng_rad-5-eng_fit),body_width/2,-3]) rotate([-90]) engine();

//engine Connector
conn_len = 25;
#translate([-(body_length/2-eng_rad-5-eng_fit),-(body_width/2+eng_h/2+eng_axle_h+9),-3])rotate([90]) eng_connector(1,1.5);
#translate([-(body_length/2-eng_rad-5-eng_fit),(body_width/2+eng_h/2+eng_axle_h+9),-3]) rotate([90]) eng_connector(1,1.5);

//Wheel
translate([-(body_length/2-eng_rad-5-eng_fit),-(body_width/2+eng_h+eng_axle_h+conn_len/2),-3])rotate([90]) wheel(25,3);
%translate([-(body_length/2-eng_rad-5-eng_fit),(body_width/2+eng_h+eng_axle_h+conn_len/2),-3]) rotate([-90]) wheel(25,3);




