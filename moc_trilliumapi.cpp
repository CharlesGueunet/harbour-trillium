/****************************************************************************
** Meta object code from reading C++ file 'trilliumapi.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/trilliumapi.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trilliumapi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TrilliumApi_t {
    QByteArrayData data[19];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TrilliumApi_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TrilliumApi_t qt_meta_stringdata_TrilliumApi = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TrilliumApi"
QT_MOC_LITERAL(1, 12, 11), // "busyChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 16), // "connectionTested"
QT_MOC_LITERAL(4, 42, 7), // "success"
QT_MOC_LITERAL(5, 50, 12), // "errorMessage"
QT_MOC_LITERAL(6, 63, 13), // "notesReceived"
QT_MOC_LITERAL(7, 77, 12), // "parentNoteId"
QT_MOC_LITERAL(8, 90, 5), // "notes"
QT_MOC_LITERAL(9, 96, 19), // "noteContentReceived"
QT_MOC_LITERAL(10, 116, 6), // "noteId"
QT_MOC_LITERAL(11, 123, 7), // "content"
QT_MOC_LITERAL(12, 131, 14), // "testConnection"
QT_MOC_LITERAL(13, 146, 3), // "url"
QT_MOC_LITERAL(14, 150, 8), // "password"
QT_MOC_LITERAL(15, 159, 5), // "token"
QT_MOC_LITERAL(16, 165, 10), // "fetchNotes"
QT_MOC_LITERAL(17, 176, 16), // "fetchNoteContent"
QT_MOC_LITERAL(18, 193, 4) // "busy"

    },
    "TrilliumApi\0busyChanged\0\0connectionTested\0"
    "success\0errorMessage\0notesReceived\0"
    "parentNoteId\0notes\0noteContentReceived\0"
    "noteId\0content\0testConnection\0url\0"
    "password\0token\0fetchNotes\0fetchNoteContent\0"
    "busy"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TrilliumApi[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       1,   84, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    2,   55,    2, 0x06 /* Public */,
       6,    2,   60,    2, 0x06 /* Public */,
       9,    2,   65,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      12,    3,   70,    2, 0x02 /* Public */,
      16,    1,   77,    2, 0x02 /* Public */,
      16,    0,   80,    2, 0x22 /* Public | MethodCloned */,
      17,    1,   81,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonArray,    7,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   13,   14,   15,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,

 // properties: name, type, flags
      18, QMetaType::Bool, 0x00495001,

 // properties: notify_signal_id
       0,

       0        // eod
};

void TrilliumApi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TrilliumApi *_t = static_cast<TrilliumApi *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->busyChanged(); break;
        case 1: _t->connectionTested((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->notesReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QJsonArray(*)>(_a[2]))); break;
        case 3: _t->noteContentReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->testConnection((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 5: _t->fetchNotes((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->fetchNotes(); break;
        case 7: _t->fetchNoteContent((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TrilliumApi::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TrilliumApi::busyChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TrilliumApi::*_t)(bool , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TrilliumApi::connectionTested)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TrilliumApi::*_t)(const QString & , const QJsonArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TrilliumApi::notesReceived)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TrilliumApi::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TrilliumApi::noteContentReceived)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        TrilliumApi *_t = static_cast<TrilliumApi *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->busy(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject TrilliumApi::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TrilliumApi.data,
      qt_meta_data_TrilliumApi,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TrilliumApi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrilliumApi::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TrilliumApi.stringdata0))
        return static_cast<void*>(const_cast< TrilliumApi*>(this));
    return QObject::qt_metacast(_clname);
}

int TrilliumApi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
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
void TrilliumApi::busyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void TrilliumApi::connectionTested(bool _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TrilliumApi::notesReceived(const QString & _t1, const QJsonArray & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TrilliumApi::noteContentReceived(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
