/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue May 10 22:25:06 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/main/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   12,   11,   11, 0x05,
      57,   47,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      84,   79,   11,   11, 0x0a,
     105,  100,   11,   11, 0x0a,
     125,  121,   11,   11, 0x0a,
     147,  140,   11,   11, 0x0a,
     174,  167,   11,   11, 0x0a,
     206,  194,   11,   11, 0x0a,
     236,  226,   11,   11, 0x0a,
     254,   11,   11,   11, 0x08,
     268,   11,   11,   11, 0x08,
     287,   11,   11,   11, 0x08,
     295,   11,   11,   11, 0x08,
     316,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0displymode\0displaymodeChanged(int)\0"
    "pointmode\0pointmodeChanged(int)\0rmin\0"
    "setRmin(double)\0rmax\0setRmax(double)\0"
    "eps\0setEps(double)\0sigmin\0setSigmaMin(double)\0"
    "sigmax\0setSigmaMax(double)\0displayMode\0"
    "setDisplayMode(int)\0pointMode\0"
    "setPointMode(int)\0setFilePath()\0"
    "performReduction()\0about()\0"
    "setFeatDispMode(int)\0setMeatFeatDispMode(int)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->displaymodeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->pointmodeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setRmin((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->setRmax((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->setEps((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->setSigmaMin((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->setSigmaMax((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->setDisplayMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setPointMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setFilePath(); break;
        case 10: _t->performReduction(); break;
        case 11: _t->about(); break;
        case 12: _t->setFeatDispMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->setMeatFeatDispMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::displaymodeChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::pointmodeChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
