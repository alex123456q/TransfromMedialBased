/****************************************************************************
** Meta object code from reading C++ file 'skeletondemogui.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SkeletonDemoGUI/skeletondemogui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'skeletondemogui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SkeletonDemoGUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      51,   16,   16,   16, 0x08,
      76,   16,   16,   16, 0x08,
      99,   16,   16,   16, 0x08,
     116,   16,   16,   16, 0x08,
     128,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SkeletonDemoGUI[] = {
    "SkeletonDemoGUI\0\0filepath_\0"
    "newImageLoaded(QString)\0"
    "openImageButtonClicked()\0"
    "checkBoxesChanged(int)\0updateSkeleton()\0"
    "saveImage()\0savePolygons()\0"
};

void SkeletonDemoGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SkeletonDemoGUI *_t = static_cast<SkeletonDemoGUI *>(_o);
        switch (_id) {
        case 0: _t->newImageLoaded((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->openImageButtonClicked(); break;
        case 2: _t->checkBoxesChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateSkeleton(); break;
        case 4: _t->saveImage(); break;
        case 5: _t->savePolygons(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SkeletonDemoGUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SkeletonDemoGUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SkeletonDemoGUI,
      qt_meta_data_SkeletonDemoGUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SkeletonDemoGUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SkeletonDemoGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SkeletonDemoGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SkeletonDemoGUI))
        return static_cast<void*>(const_cast< SkeletonDemoGUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SkeletonDemoGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SkeletonDemoGUI::newImageLoaded(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
