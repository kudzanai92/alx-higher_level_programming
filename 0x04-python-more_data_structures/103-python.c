#include <Python.h>
#include <stdio.h>

void print_python_list(PyObject *p) {
    if (!PyList_Check(p)) {
        fprintf(stderr, "Invalid Python list object\n");
        return;
    }

    Py_ssize_t size = PyObject_Length(p);

    printf("[*] Python list info\n");
    printf("[*] Size of the Python List = %ld\n", size);

    PyObject *allocated = PyObject_GetAttrString(p, "allocated");
    printf("[*] Allocated = %ld\n", PyLong_AsLong(allocated));
    Py_DECREF(allocated);

    for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject *item = PyList_GetItem(p, i);
        printf("Element %ld: %s\n", i, Py_TYPE(item)->tp_name);
    }
}

void print_python_bytes(PyObject *p) {
    if (!PyBytes_Check(p)) {
        fprintf(stderr, "Invalid Python bytes object\n");
        return;
    }

    Py_ssize_t size = PyObject_Length(p);

    printf("[.] bytes object info\n");
    printf("  Size: %ld\n", size);
    
    printf("  Trying string: %s\n", PyUnicode_AsUTF8AndSize(p, NULL));

    printf("  first %ld bytes:", size < 10 ? size : 10);
    const char *bytes = PyBytes_AsString(p);
    for (Py_ssize_t i = 0; i < (size < 10 ? size : 10); ++i) {
        printf(" %02hhx", bytes[i]);
    }
    printf("\n");
}

int main(void) {
    // For demonstration purposes
    Py_Initialize();

    // Example Python list
    PyObject *pyList = PyList_New(3);
    PyList_SET_ITEM(pyList, 0, PyLong_FromLong(42));
    PyList_SET_ITEM(pyList, 1, PyUnicode_DecodeUTF8("Hello", 5, "strict"));
    PyList_SET_ITEM(pyList, 2, PyFloat_FromDouble(3.14));

    // Example Python bytes
    PyObject *pyBytes = PyBytes_FromStringAndSize("example bytes", 13);

    // Call the functions
    print_python_list(pyList);
    print_python_bytes(pyBytes);

    // Cleanup
    Py_DECREF(pyList);
    Py_DECREF(pyBytes);

    Py_Finalize();
    return 0;
}
