/****************************************************************************
** Meta object code from reading C++ file 'scene.h'
**
** Created: Mon Jan 10 19:52:04 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "scene.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_scene[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x0a,
      31,   22,    6,    6, 0x0a,
      81,   70,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_scene[] = {
    "scene\0\0updatePoints()\0sender,e\0"
    "slot_touchedElement(element*,element*)\0"
    "sender,dir\0slot_touchedLimit(element*,element::directions)\0"
};

const QMetaObject scene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_scene,
      qt_meta_data_scene, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &scene::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *scene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *scene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_scene))
        return static_cast<void*>(const_cast< scene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int scene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updatePoints(); break;
        case 1: slot_touchedElement((*reinterpret_cast< element*(*)>(_a[1])),(*reinterpret_cast< element*(*)>(_a[2]))); break;
        case 2: slot_touchedLimit((*reinterpret_cast< element*(*)>(_a[1])),(*reinterpret_cast< element::directions(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
