#include <Python.h>

//#include "scrypt.h"

static PyObject *scrypt_getpowhash(PyObject *self, PyObject *args)
{
    PyStringObject *input;
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    uint8_t *output = PyMem_Malloc(32);
    scrypt_1024_1_1_256((uint8_t *)PyString_AsString((PyObject*) input), output);
    Py_DECREF(input);
    PyObject *value = Py_BuildValue("s#", output, 32);
    PyMem_Free(output);
    return value;
}

static PyMethodDef ScryptMethods[] = {
    { "getPoWHash", scrypt_getpowhash, METH_VARARGS, "Returns the proof of work hash using scrypt" },
    { NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC initltc_scrypt(void) {
    (void) Py_InitModule("ltc_scrypt", ScryptMethods);
}