/****************************************************************************
** Meta object code from reading C++ file 'notemodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/notemodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'notemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NoteModel_t {
    QByteArrayData data[9];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NoteModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NoteModel_t qt_meta_stringdata_NoteModel = {
    {
QT_MOC_LITERAL(0, 0, 9), // "NoteModel"
QT_MOC_LITERAL(1, 10, 12), // "countChanged"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9), // "loadNotes"
QT_MOC_LITERAL(4, 34, 9), // "jsonArray"
QT_MOC_LITERAL(5, 44, 5), // "clear"
QT_MOC_LITERAL(6, 50, 7), // "getNote"
QT_MOC_LITERAL(7, 58, 5), // "index"
QT_MOC_LITERAL(8, 64, 5) // "count"

    },
    "NoteModel\0countChanged\0\0loadNotes\0"
    "jsonArray\0clear\0getNote\0index\0count"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NoteModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       1,   42, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       3,    1,   35,    2, 0x02 /* Public */,
       5,    0,   38,    2, 0x02 /* Public */,
       6,    1,   39,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QJsonArray,    4,
    QMetaType::Void,
    QMetaType::QVariantMap, QMetaType::Int,    7,

 // properties: name, type, flags
       8, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       0,

       0        // eod
};

void NoteModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NoteModel *_t = static_cast<NoteModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->countChanged(); break;
        case 1: _t->loadNotes((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 2: _t->clear(); break;
        case 3: { QVariantMap _r = _t->getNote((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NoteModel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoteModel::countChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        NoteModel *_t = static_cast<NoteModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->count(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject NoteModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_NoteModel.data,
      qt_meta_data_NoteModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NoteModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NoteModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NoteModel.stringdata0))
        return static_cast<void*>(const_cast< NoteModel*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int NoteModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void NoteModel::countChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
