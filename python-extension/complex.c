#define PY_SSIZE_T_CLEAN
#include <Python.h>

double add(double x, double y) {
    return x + y;
}


static PyObject *CalcError;

static PyObject *
calc_add(PyObject *self, PyObject *args)
{
    double arg1;
    double arg2;
    double res;

    if (!PyArg_ParseTuple(args, "dd", &arg1, &arg2))
        return NULL;

    res = add(arg1, arg2);

    if (res > 100.0) { /* artificial error */
        PyErr_SetString(CalcError, "Cannot add up numbers beyond 100");
        return NULL;
    }

    return PyFloat_FromDouble(res);
}

static PyMethodDef CalcMethods[] = {
    {
        "add",  calc_add, METH_VARARGS,
        "Add two doubles."
    },
    {NULL, NULL, 0, NULL}        /* Sentinel */
};


static PyModuleDef complexmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "complex",
    .m_doc = "Example module w/ multiple functions and extension types.",
    .m_size = -1,
    .m_methods = CalcMethods,
};


typedef struct {
    PyObject_HEAD
    /* Type-specific fields go here. */
} PersonObject;

typedef struct {
    PyObject_HEAD
    /* Type-specific fields go here. */
} VehicleObject;


static PyTypeObject PersonType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "complex.Person",
    .tp_doc = PyDoc_STR("Person objects"),
    .tp_basicsize = sizeof(PersonObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
};

static PyTypeObject VehicleType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "complex.Vehicle",
    .tp_doc = PyDoc_STR("Vehicle objects"),
    .tp_basicsize = sizeof(VehicleObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
};


PyMODINIT_FUNC
PyInit_complex(void)
{
    PyObject *m;

    if (PyType_Ready(&PersonType) < 0)
        return NULL;

    if (PyType_Ready(&VehicleType) < 0)
        return NULL;

    m = PyModule_Create(&complexmodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&PersonType);
    if (PyModule_AddObject(m, "Person", (PyObject *) &PersonType) < 0) {
        Py_DECREF(&PersonType);
        Py_DECREF(m);
        return NULL;
    }

    Py_INCREF(&VehicleType);
    if (PyModule_AddObject(m, "Vehicle", (PyObject *) &VehicleType) < 0) {
        Py_DECREF(&VehicleType);
        Py_DECREF(m);
        return NULL;
    }

    CalcError = PyErr_NewException("complex.error", NULL, NULL);
    Py_XINCREF(CalcError);
    if (PyModule_AddObject(m, "error", CalcError) < 0) {
        Py_XDECREF(CalcError);
        Py_CLEAR(CalcError);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}

