#ifndef MODIFYREFMESSBOX_H
#define MODIFYREFMESSBOX_H

#include "EditRefMessBox.h"

class ModifyRefMessBox:public EditRefMessBox
{
    Q_OBJECT
public:
    ModifyRefMessBox(vector<string>* arrayptr);
public slots:
        //将新文献的信息写入到文件中
        virtual void saveRefMess();
public:
        //发出 closeBox 信号
        virtual void emitCloseBox();
private:
    QString ModifyDOI;

};

#endif // MODIFYREFMESSBOX_H
