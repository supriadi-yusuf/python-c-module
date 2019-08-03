#include <Python.h> //mandatory

#include <stdio.h> //depends on need

/*==============================================================================
============= C function to be called from C programming languange =============
==============================================================================*/
int Cfib(int n){
  if( n < 2)
    return n;
  else
    return Cfib(n-1) + Cfib(n-2);
}

int volumeBalok(int panjang, int lebar, int tinggi){
  return panjang * lebar * tinggi;
}

int luasBalok(int panjang, int lebar){
  return panjang * lebar;
}

/*==============================================================================
======================= C function to called from python =======================
==============================================================================*/

/*******************************************************************************
 C function with an input argument and an output.
*******************************************************************************/
static PyObject* fib(PyObject* self, PyObject* args){
  int n;

  /***************************************************************/
  /* PyArg_ParseTuple function is to take arguments from python. */
  /***************************************************************/

  /* get 1 input argument from python */
  if(!PyArg_ParseTuple(
          args, //input arguments
          "i", //format. since there is only one letter so there is only 1 input.
               // i means integer.
          &n)) //variable where we want to store value of input argument. must be the same type.
    return NULL;

  printf("test fungsi fibonaci \n");
  printf("parameter input n = %d \n", n);

  /*************************************************************/
  /* Py_BuildValue function is to set output value into python. */
  /*************************************************************/

  /* set output value to python */
  return Py_BuildValue(
        "i", //type of data which we want to store. i means integer.
        Cfib(n)); //value that we want to store into python.
}

/*******************************************************************************
 C function without input arguments but with an output.
*******************************************************************************/
static PyObject* version(PyObject* self){

  //set 1 output value to python
  return Py_BuildValue(
      "s", // 1 output value to python. s means string.
      "version 1.0"); //value that we want to store into python.
}

/*******************************************************************************
 C function without any input arguments nor output
*******************************************************************************/
static PyObject* hello_func(PyObject* self){
  printf("Hello world!\n");
  Py_RETURN_NONE; //macro indicating that there is no output value for python.
}

/*******************************************************************************
 C function with three input arguments and two outputs
*******************************************************************************/
static PyObject* balok_func(PyObject* self, PyObject* args){
  int pjg, lbr, tinggi;

  /*****************************************************************************
  if we need arguments which are type of integer, double, and string so we type
  PyArg_ParseTuple(args, "ids", &integer_var, &double_var, &string_var).
  Since we need three arguments which are all integer so we put triple i (iii)
  like below.
  *****************************************************************************/
  if(!PyArg_ParseTuple(
                        args, //arguments
                        "iii", // i means integer. since there are three i
                               // it means there are three inputs
                               // type of each input is integer
                        &pjg, // input 1 is stored in variable pjg
                        &lbr, // input 2 is stored in variable lbr
                        &tinggi)) // input 3 is stored in variable tinggi
    return NULL;

  return Py_BuildValue(
                        "ii", // since since there are two i
                              // it means there are two inputs
                              // type of each input is integer
                        luasBalok( pjg, lbr), //output 1
                        volumeBalok( pjg, lbr, tinggi) // output 2
                      );
}

/*******************************************************************************
 C function with input keywords but without output.
*******************************************************************************/
static PyObject* printParam_func(PyObject* self, PyObject* args, PyObject* kws){
  char* nama;
  int umur = 20;
  float tinggi = 1.85;
  char* keywords[] = {
    "nama", //first keyword
    "umur", //second keyword
    "tinggi", //third keyword
    NULL //terminated with NULL
  };

  if(!PyArg_ParseTupleAndKeywords(
                          args, //positional input arguments
                          kws, //keyword input argument
                          "s|if", //format. there are there inputs. s (string), i (integer) and f (float).
                                  //character/characters coming before pipe (|) means mandatory.
                                  //but character/characters coming after pipe (|) means optional.
                                  //in this case, s (string) is mandatory but i (integer) and f (float) are optional.
                          keywords, //list of allowed keyword for python
                          &nama,//variable for storing input value. order of variable must be match with order of keyword
                          &umur,//variable for storing input value. order of variable must be match with order of keyword
                          &tinggi //variable for storing input value. order of variable must be match with the order of keyword
                        ))
    return NULL;

  printf("nama : %s \n", nama);
  printf("umur :%d \n", umur);
  printf("tinggi badan : %.2f meter \n", tinggi); //print only 2 digits after comma

  Py_RETURN_NONE;// macro indicating that there is no output
}

/*==============================================================================
=============================== method mapping table ===========================
==============================================================================*/
static PyMethodDef myMethods[]={
  {
    "fib_c", // name that is used to call c function from python
    (PyCFunction)fib, // c function's name
    METH_VARARGS, //flag. this flag means that function takes input argument.
    "Calculates the fibonaci numbers." //description of c function.
  },
  {"version_c", (PyCFunction)version, METH_NOARGS, "return the version."},
  {"hello_c", (PyCFunction)hello_func, METH_NOARGS, "print \'hello world!\'"},
  {"balok_c", (PyCFunction)balok_func, METH_VARARGS, "find area and volume"},
  {"param_c", (PyCFunction)printParam_func, METH_VARARGS | METH_KEYWORDS, "print paramenter from python in c"},
  {NULL} //terminate indication
};

static struct PyModuleDef myModule = {
  PyModuleDef_HEAD_INIT,
  "myModule",
  "Fibonaci module",
  -1,
  myMethods
};

/*==============================================================================
================================= init function ================================
it must be name PyInit_modulename.
example : if module name is myModule so the init function name must be
          PyInit_myModule.
==============================================================================*/
PyMODINIT_FUNC PyInit_myModule(void){
  return PyModule_Create(&myModule);
}
