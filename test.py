#!/usr/local/bin/python3

import myModule # importing module

print(myModule.fib_c(10))
print(myModule.version_c())
myModule.hello_c()
luas, volume = myModule.balok_c( 5, 10, 20)
print("luas = {}, volume = {}".format(luas,volume))

myModule.param_c( "supriadi")
myModule.param_c( "supriadi", 30)
myModule.param_c( "supriadi", 30, 1.65)
myModule.param_c( "supriadi", tinggi=1.65, umur=30)
myModule.param_c( tinggi=1.65, nama="supriadi", umur=30)
