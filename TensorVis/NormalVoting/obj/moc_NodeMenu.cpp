/****************************************************************************
** Meta object code from reading C++ file 'NodeMenu.h'
**
** Created: Tue Apr 12 13:14:46 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/treeVisualizer/NodeMenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NodeMenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PopupNodeMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      40,   14,   14,   14, 0x08,
      66,   14,   14,   14, 0x08,
      83,   14,   14,   14, 0x08,
     100,   14,   14,   14, 0x08,
     122,   14,   14,   14, 0x08,
     138,   14,   14,   14, 0x08,
     156,   14,   14,   14, 0x08,
     182,  176,   14,   14, 0x08,
     204,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PopupNodeMenu[] = {
    "PopupNodeMenu\0\0openFeatureSelectorBox()\0"
    "closeFeatureSelectorBox()\0accpetNodeMenu()\0"
    "cancelNodeMenu()\0SetSelectedFeatures()\0"
    "setSaveStatus()\0setDeleteStatus()\0"
    "openColorSelector()\0color\0"
    "setColorIndex(QColor)\0setVisualizeStatus()\0"
};

void PopupNodeMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PopupNodeMenu *_t = static_cast<PopupNodeMenu *>(_o);
        switch (_id) {
        case 0: _t->openFeatureSelectorBox(); break;
        case 1: _t->closeFeatureSelectorBox(); break;
        case 2: _t->accpetNodeMenu(); break;
        case 3: _t->cancelNodeMenu(); break;
        case 4: _t->SetSelectedFeatures(); break;
        case 5: _t->setSaveStatus(); break;
        case 6: _t->setDeleteStatus(); break;
        case 7: _t->openColorSelector(); break;
        case 8: _t->setColorIndex((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 9: _t->setVisualizeStatus(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PopupNodeMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PopupNodeMenu::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PopupNodeMenu,
      qt_meta_data_PopupNodeMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PopupNodeMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PopupNodeMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PopupNodeMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PopupNodeMenu))
        return static_cast<void*>(const_cast< PopupNodeMenu*>(this));
    return QDialog::qt_metacast(_clname);
}

int PopupNodeMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
