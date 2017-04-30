//corpo do carrinho

module body(larg=80, compr=100, ) {
    espes = 10; //10 mm de espesura no carrinho
    
    minkowski() {
        %cube([larg, compr, espes], center = true);
        #cylinder(h=15,r=5);
    }
}

body();

