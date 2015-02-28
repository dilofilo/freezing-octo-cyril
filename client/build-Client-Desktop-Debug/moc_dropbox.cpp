/****************************************************************************
** Meta object code from reading C++ file 'dropbox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/dropbox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dropbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DropBox_t {
    QByteArrayData data[18];
    char stringdata[357];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_DropBox_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_DropBox_t qt_meta_stringdata_DropBox = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 18),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 20),
QT_MOC_LITERAL(4, 49, 21),
QT_MOC_LITERAL(5, 71, 27),
QT_MOC_LITERAL(6, 99, 20),
QT_MOC_LITERAL(7, 120, 20),
QT_MOC_LITERAL(8, 141, 18),
QT_MOC_LITERAL(9, 160, 20),
QT_MOC_LITERAL(10, 181, 18),
QT_MOC_LITERAL(11, 200, 22),
QT_MOC_LITERAL(12, 223, 20),
QT_MOC_LITERAL(13, 244, 19),
QT_MOC_LITERAL(14, 264, 26),
QT_MOC_LITERAL(15, 291, 5),
QT_MOC_LITERAL(16, 297, 27),
QT_MOC_LITERAL(17, 325, 30)
    },
    "DropBox\0on_btnMake_clicked\0\0"
    "on_btnDelete_clicked\0on_btnUnshare_clicked\0"
    "on_btnConfirmRevert_clicked\0"
    "on_btnSearch_clicked\0on_btnUpload_clicked\0"
    "on_btnSync_clicked\0on_btnLogout_clicked\0"
    "on_btnExit_clicked\0on_btnDownload_clicked\0"
    "on_btnRemove_clicked\0on_btnShare_clicked\0"
    "on_shareTreeWidget_clicked\0index\0"
    "on_serverTreeWidget_clicked\0"
    "on_textSearch_selectionChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DropBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08,
       3,    0,   90,    2, 0x08,
       4,    0,   91,    2, 0x08,
       5,    0,   92,    2, 0x08,
       6,    0,   93,    2, 0x08,
       7,    0,   94,    2, 0x08,
       8,    0,   95,    2, 0x08,
       9,    0,   96,    2, 0x08,
      10,    0,   97,    2, 0x08,
      11,    0,   98,    2, 0x08,
      12,    0,   99,    2, 0x08,
      13,    0,  100,    2, 0x08,
      14,    1,  101,    2, 0x08,
      16,    1,  104,    2, 0x08,
      17,    0,  107,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   15,
    QMetaType::Void, QMetaType::QModelIndex,   15,
    QMetaType::Void,

       0        // eod
};

void DropBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DropBox *_t = static_cast<DropBox *>(_o);
        switch (_id) {
        case 0: _t->on_btnMake_clicked(); break;
        case 1: _t->on_btnDelete_clicked(); break;
        case 2: _t->on_btnUnshare_clicked(); break;
        case 3: _t->on_btnConfirmRevert_clicked(); break;
        case 4: _t->on_btnSearch_clicked(); break;
        case 5: _t->on_btnUpload_clicked(); break;
        case 6: _t->on_btnSync_clicked(); break;
        case 7: _t->on_btnLogout_clicked(); break;
        case 8: _t->on_btnExit_clicked(); break;
        case 9: _t->on_btnDownload_clicked(); break;
        case 10: _t->on_btnRemove_clicked(); break;
        case 11: _t->on_btnShare_clicked(); break;
        case 12: _t->on_shareTreeWidget_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 13: _t->on_serverTreeWidget_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 14: _t->on_textSearch_selectionChanged(); break;
        default: ;
        }
    }
}

const QMetaObject DropBox::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_DropBox.data,
      qt_meta_data_DropBox,  qt_static_metacall, 0, 0}
};


const QMetaObject *DropBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DropBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DropBox.stringdata))
        return static_cast<void*>(const_cast< DropBox*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int DropBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
