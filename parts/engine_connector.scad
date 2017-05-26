//Wheel to engine adapter
conn_len = 20;

module eng_connector(eng_axle_rad = 1.5, wheel_axle_rad = 1.5) {
    $fn = 30;
    conn_tichn = 2;
    
    
    //rotate([90])
    union() {
    difference() {
        cylinder(r= eng_axle_rad+conn_tichn, h=conn_len, center= true);
        
        cylinder(r= eng_axle_rad, h= conn_len/2+0.1, center=false);
        rotate([180]) cylinder(r= wheel_axle_rad, h=conn_len/2+0.1, center=false);
    }}
    
}

//eng_connector();
