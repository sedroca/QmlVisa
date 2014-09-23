#ifndef USBRAW_H
#define USBRAW_H




#ifndef NIVISA_H
#define NIVISA_USB 1
#define NIVISA_H
#include "C:\Program Files\IVI Foundation\VISA\Win64\Include\visa.h"

#endif



#include <QQuickItem>

class UsbRaw : public QQuickItem
{
    Q_OBJECT

    Q_ENUMS(Pipe)

    Q_PROPERTY(qint16   bulkInPipe      READ bulkInPipe     WRITE setBulkInPipe     NOTIFY bulkInPipeChanged)
    Q_PROPERTY(Pipe     bulkInStatus    READ bulkInStatus   WRITE setBulkInStatus   NOTIFY bulkInStatusChanged)
    Q_PROPERTY(qint16   bulkOutPipe     READ bulkOutPipe    WRITE setBulkOutPipe    NOTIFY bulkOutPipeChanged)
    Q_PROPERTY(Pipe     bulkOutStatus   READ bulkOutStatus  WRITE setBulkOutStatus  NOTIFY bulkOutStatusChanged)
    Q_PROPERTY(qint16   classUsed       READ classUsed                              NOTIFY classUsedChanged)
    Q_PROPERTY(qint16   intfcNum        READ intfcNum                               NOTIFY intfcNumChanged)
    Q_PROPERTY(qint16   intrInPipe      READ intrInPipe     WRITE setIntrInPipe     NOTIFY intrInPipeChanged)
    Q_PROPERTY(Pipe     intrInStatus    READ intrInStatus   WRITE setIntrInStatus   NOTIFY intrInStatusChanged)
    Q_PROPERTY(quint16  maxIntrSize     READ maxIntrSize    WRITE setMaxIntrSize    NOTIFY maxIntrSizeChanged)
    Q_PROPERTY(qint16   numIntfcs       READ numIntfcs                              NOTIFY numIntfcsChanged)
    Q_PROPERTY(qint16   numPipes        READ numPipes                               NOTIFY numPipesChanged)
    Q_PROPERTY(qint16   protocol        READ protocol                               NOTIFY protocolChanged)
    Q_PROPERTY(quint8*  recvIntrData    READ recvIntrData                           NOTIFY recvIntrDataChanged)
    Q_PROPERTY(quint16  recvIntrSize    READ recvIntrSize                           NOTIFY recvIntrSizeChanged)
    Q_PROPERTY(QString  serialNum       READ serialNum                              NOTIFY serialNumChanged)
    Q_PROPERTY(qint16   subclass        READ subclass                               NOTIFY subclassChanged)

public:
    explicit UsbRaw(QQuickItem *parent = 0);

    //  Pipe
    //    VI_USB_PIPE_STATE_UNKNOWN (–1);
    //    VI_USB_PIPE_READY (0);
    //    VI_USB_PIPE_STALLED (1)
    enum Pipe {PipeStateUnknown = VI_USB_PIPE_STATE_UNKNOWN, PipeReady = VI_USB_PIPE_READY, PipeStalled = VI_USB_PIPE_STALLED};

    qint16      bulkInPipe();       void setBulkInPipe(const qint16 &rn);
    Pipe        bulkInStatus();     void setBulkInStatus(const Pipe &rn);
    qint16      bulkOutPipe();      void setBulkOutPipe(const qint16 &rn);
    Pipe        bulkOutStatus();    void setBulkOutStatus(const Pipe &rn);
    qint16      classUsed();        void setClassUsed(const qint16 &rn);  //read only
    qint16      intfcNum();         void setIntfcNum(const qint16 &rn);
    qint16      intrInPipe();       void setIntrInPipe(const qint16 &rn);
    Pipe        intrInStatus();     void setIntrInStatus(const Pipe &rn);
    quint16     maxIntrSize();      void setMaxIntrSize(const quint16 &rn);
    qint16      numIntfcs();        void setNumIntfcs(const qint16 &rn);
    qint16      numPipes();         void setNumPipes(const qint16 &rn);
    qint16      protocol();         void setProtocol(const qint16 &rn);
    quint8*     recvIntrData();     void setRecvIntrData(quint8 *&rn);
    quint16     recvIntrSize();     void setRecvIntrSize(const quint16 &rn);
    QString     serialNum();        void setSerialNum(const QString &rn);
    qint16      subclass();         void setSubclass(const qint16 &rn);

    void toVisa_BulkInPipe();         void fromVisa_BulkInPipe();
    void toVisa_BulkInStatus();       void fromVisa_BulkInStatus();
    void toVisa_BulkOutPipe();        void fromVisa_BulkOutPipe();
    void toVisa_BulkOutStatus();      void fromVisa_BulkOutStatus();
    void fromVisa_ClassUsed();
    void fromVisa_IntfcNum();
    void toVisa_IntrInPipe();         void fromVisa_IntrInPipe();
    void toVisa_IntrInStatus();       void fromVisa_IntrInStatus();
    void toVisa_MaxIntrSize();        void fromVisa_MaxIntrSize();
    void fromVisa_NumIntfcs();
    void fromVisa_NumPipes();
    void fromVisa_Protocol();
    void fromVisa_RecvIntrData();
    void fromVisa_RecvIntrSize();
    void fromVisa_SerialNum();
    void fromVisa_Subclass();
    void toVisa_UserData();           void fromVisa_UserData();

    bool        bulkInPipeWasSet();     void setBulkInPipeWasSet(const bool &rn);
    bool        bulkInStatusWasSet();   void setBulkInStatusWasSet(const bool &rn);
    bool        bulkOutPipeWasSet();    void setBulkOutPipeWasSet(const bool &rn);
    bool        bulkOutStatusWasSet();  void setBulkOutStatusWasSet(const bool &rn);
    bool        intrInPipeWasSet();     void setIntrInPipeWasSet(const bool &rn);
    bool        intrInStatusWasSet();   void setIntrInStatusWasSet(const bool &rn);
    bool        maxIntrSizeWasSet();    void setMaxIntrSizeWasSet(const bool &rn);

    void    setInstr(const ViSession rn);
    void    setConnected(const bool &rn);
    bool    connected();

signals:
    void bulkInPipeChanged();
    void bulkInStatusChanged();
    void bulkOutPipeChanged();
    void bulkOutStatusChanged();
    void classUsedChanged();
    void intfcNumChanged();
    void intrInPipeChanged();
    void intrInStatusChanged();
    void maxIntrSizeChanged();
    void numIntfcsChanged();
    void numPipesChanged();
    void protocolChanged();
    void recvIntrDataChanged();
    void recvIntrSizeChanged();
    void serialNumChanged();
    void subclassChanged();

    void updateVisaAttributes();
    void statusUpdate(const QString &rn);

public slots:

protected:
    qint16      _bulkInPipe;
    Pipe        _bulkInStatus;
    qint16      _bulkOutPipe;
    Pipe        _bulkOutStatus;
    qint16      _classUsed;
    qint16      _intfcNum;
    qint16      _intrInPipe;
    Pipe        _intrInStatus;
    quint16     _maxIntrSize;
    qint16      _numIntfcs;
    qint16      _numPipes;
    qint16      _protocol;
    quint8*     _recvIntrData;
    quint16     _recvIntrSize;
    QString     _serialNum;
    qint16      _subclass;

    bool        _bulkInPipeWasSet;
    bool        _bulkInStatusWasSet;
    bool        _bulkOutPipeWasSet;
    bool        _bulkOutStatusWasSet;
    bool        _intrInPipeWasSet;
    bool        _intrInStatusWasSet;
    bool        _maxIntrSizeWasSet;

    ViSession   _instr;
    bool        _connected;


};

#endif // USBRAW_H
