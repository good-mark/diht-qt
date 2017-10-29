extern "C" {
#include <Python.h>
}
#include <string>
#include "widgets.h"

extern "C" PyObject* Application_New_python(PyObject* module)
{
    return PyLong_FromLong(long(Application_New()));
}

extern "C" PyObject* Object_GetClassName_python(PyObject* module, PyObject* args)
{
    Object* object = (Object*) PyLong_AsLong(PyTuple_GetItem(args, 0));
    return PyUnicode_FromString(Object_GetClassName(object));
}

extern "C" PyObject* Widget_New_python(PyObject* module, PyObject* args)
{
    //Widget* object = (Widget*) PyLong_AsLong(PyTuple_GetItem(args, 0));
    return PyLong_FromLong(long(Widget_New(nullptr)));
}

extern "C" PyObject* VBoxLayout_New_python(PyObject* module, PyObject* args)
{
    Widget* object = (Widget*) PyLong_AsLong(PyTuple_GetItem(args, 0));
    return PyLong_FromLong(long(VBoxLayout_New(object)));
}

extern "C" PyObject* Widget_SetLayout_python(PyObject* module, PyObject* args)
{
    Widget* arg1 = (Widget*) PyLong_AsLong(PyTuple_GetItem(args, 0));
    Layout* arg2 = (Layout*) PyLong_AsLong(PyTuple_GetItem(args, 1));
    Widget_SetLayout(arg1, arg2);
    return PyLong_FromLong(0);
}

extern "C" PyObject* Label_New_python(PyObject* module, PyObject* args)
{
    Widget* object = (Widget*) PyLong_AsLong(PyTuple_GetItem(args, 0));
    return PyLong_FromLong(long(Label_New(object)));
}

extern "C" PyObject* Label_SetText_python(PyObject* module, PyObject* args)
{
    long arg1 = PyLong_AsLong(PyTuple_GetItem(args, 0));
    PyObject * arg2 = PyTuple_GetItem(args, 1);
    const char * cs2 = PyUnicode_AsUTF8(arg2);
    Label_SetText((Label*)arg1, cs2);
    return PyLong_FromLong(0);
}

extern "C" PyObject* Layout_AddWidget_python(PyObject* module, PyObject* args)
{
    Layout* arg1 = (Layout*) PyLong_AsLong(PyTuple_GetItem(args, 0));
    Widget* arg2 = (Widget*) PyLong_AsLong(PyTuple_GetItem(args, 1));
    Layout_AddWidget(arg1, arg2);
    return PyLong_FromLong(0);
}

extern "C" PyObject* PushButton_New_python(PyObject* module, PyObject* args)
{
    Widget* object = (Widget*) PyLong_AsLong(PyTuple_GetItem(args, 0));
    return PyLong_FromLong(long(PushButton_New(object)));
}

extern "C" PyObject* PushButton_SetText_python(PyObject* module, PyObject* args)
{
    PushButton* arg1 = (PushButton*) PyLong_AsLong(PyTuple_GetItem(args, 0));
    const char* arg2 = PyUnicode_AsUTF8(PyTuple_GetItem(args, 1));
    PushButton_SetText(arg1, arg2);
    return PyLong_FromLong(0);
}

extern "C" PyObject* Widget_SetWindowTitle_python(PyObject* module, PyObject* args)
{
    Widget* arg1 = (Widget*) PyLong_AsLong(PyTuple_GetItem(args, 0));
    const char* arg2 = PyUnicode_AsUTF8(PyTuple_GetItem(args, 1));
    Widget_SetWindowTitle(arg1, arg2);
    return PyLong_FromLong(0);
}

extern "C" PyObject* Widget_SetSize_python(PyObject* module, PyObject* args)
{
    Widget* arg1 = (Widget*) PyLong_AsLong(PyTuple_GetItem(args, 0));
    int arg2 = PyLong_AsLong(PyTuple_GetItem(args, 1));
    int arg3 = PyLong_AsLong(PyTuple_GetItem(args, 2));
    Widget_SetSize(arg1, arg2, arg3);
    return PyLong_FromLong(0);
}

extern "C" PyObject* Widget_SetVisible_python(PyObject* module, PyObject* args)
{
    Widget* arg1 = (Widget*) PyLong_AsLong(PyTuple_GetItem(args, 0));
    bool arg2 = PyObject_IsTrue(PyTuple_GetItem(args, 1));
    Widget_SetVisible(arg1, arg2);
    return PyLong_FromLong(0);
}

extern "C" PyObject* Application_Exec_python(PyObject* module, PyObject* args)
{
    Application* arg1 = (Application*) PyTuple_GetItem(args, 0);
    return PyLong_FromLong(arg1->app->exec());
}

PyMODINIT_FUNC PyInit__pywidgets() {

    static PyMethodDef methods[] = {
      {"Application_New", Application_New_python, METH_VARARGS, ""},
      {"Object_GetClassName", Object_GetClassName_python, METH_VARARGS, ""},
      {"Widget_New", Widget_New_python, METH_VARARGS, ""},
      {"VBoxLayout_New", VBoxLayout_New_python, METH_VARARGS, ""},
      {"Widget_SetLayout", Widget_SetLayout_python, METH_VARARGS, ""},
      {"Label_New", Label_New_python, METH_VARARGS, ""},
      {"Label_SetText", Label_SetText_python, METH_VARARGS, ""},
      {"Layout_AddWidget", Layout_AddWidget_python, METH_VARARGS, ""},
      {"PushButton_New", PushButton_New_python, METH_VARARGS, ""},
      {"PushButton_SetText", PushButton_SetText_python, METH_VARARGS, ""},
      {"Widget_SetWindowTitle", Widget_SetWindowTitle_python, METH_VARARGS, ""},
      {"Widget_SetSize", Widget_SetSize_python, METH_VARARGS, ""},
      {"Widget_SetVisible", Widget_SetVisible_python, METH_VARARGS, ""},
      {"Application_Exec", Application_Exec_python, METH_VARARGS, ""},
      {NULL, NULL, 0, NULL}
    };

    static PyModuleDef modDef = {
        PyModuleDef_HEAD_INIT,
        "_pywidgets",
        "My cool module!!!",
        -1, methods
    };

    PyObject* mod = PyModule_Create(&modDef);
    return mod;

