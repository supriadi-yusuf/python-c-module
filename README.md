Python can call function developed with c programming language.

Steps :
1. install python3-devel
   we need python3-devel library in our computer to make c function can be called from python3.
   you can search for the library that matched your python3 version with
   command : sudo yum search python3 | grep devel
   since python3 in this machine is version 3.6, we use python36-devel.x86_64.
   check if the module has been installed or not with command :
   sudo yum info python36-devel.x86_64
   if the library is not installed yet then install the library with command :
   sudo yum install python36-devel.x86_64
2. create module in c
   For example : just read file myModule.c in this directory.
3. create setup.py in python3
   For example : just read file setup.py in this directory.
4. run : python3 setup.py build or python3 setup.py install
   if execution is successfull the directory named 'build' is created at
   your current directory.
   Look at [your current directory]/build/lib.linux-x86_64-3.6 directory.
   Copy file in that directory into your current directory.
5. create file in python3 to call C function
   For example : please read test.py.
   Then execute the file, example : python3 test.py
