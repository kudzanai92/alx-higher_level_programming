#include <Python.h>
#include <stdio.h>

void print_python_list(PyObject *p) {
    if (!PyList_Check(p)) {
        fprintf(stderr, "Invalid Python list object\n");
        return;
    }

    Py_ssize_t size = PyList_Size(p);

    printf("[*] Python list info\n");
    printf("[*] Size of the Python List = %ld\n", size);

    printf("[*] Allocated = %ld\n", ((PyListObject *)p)->allocated);
    for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject *item = PyList_GET_ITEM(p, i);
        printf("Element %ld: %s\n", i, Py_TYPE(item)->tp_name);
    }
}

void print_python_bytes(PyObject *p) {
    if (!PyBytes_Check(p)) {
        fprintf(stderr, "Invalid Python bytes object\n");
        return;
    }

    printf("[.] bytes object info\n");
    printf("  Size: %ld\n", PyBytes_Size(p));
    printf("  Trying string: %s\n", PyBytes_AsString(p));

    printf("  first %ld bytes:", PyBytes_Size(p) + 1);
    if (PyBytes_Size(p) < 10) {
        for (Py_ssize_t i = 0; i < PyBytes_Size(p) + 1; ++i) {
            printf(" %02hhx", ((char *)PyBytes_AsString(p))[i]);
        }
    } else {
        for (Py_ssize_t i = 0; i < 10; ++i) {
            printf(" %02hhx", ((char *)PyBytes_AsString(p))[i]);
        }
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
