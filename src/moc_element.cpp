/****************************************************************************
** Meta object code from reading C++ file 'element.h'
**
** Created: Mon Jan 10 19:52:04 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "element.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'element.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_element[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,    9,    8,    8, 0x05,
      77,   68,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_element[] = {
    "element\0\0sender,dir\0"
    "sign_touchedLimit(element*,element::directions)\0"
    "sender,e\0sign_touchedByElement(element*,element*)\0"
};

const QMetaObject element::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_element,
      qt_meta_data_element, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &element::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *element::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *element::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_element))
        return static_cast<void*>(const_cast< element*>(this));
    return QObject::qt_metacast(_clname);
}

int element::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sign_touchedLimit((*reinterpret_cast< element*(*)>(_a[1])),(*reinterpret_cast< element::directions(*)>(_a[2]))); break;
        case 1: sign_touchedByElement((*reinterpret_cast< element*(*)>(_a[1])),(*reinterpret_cast< element*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void element::sign_touchedLimit(element * _t1, element::directions _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void element::sign_touchedByElement(element * _t1, element * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
