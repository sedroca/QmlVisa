#ifndef QMLVISA_H
#define QMLVISA_H

#include <QQuickItem>
#include <QStringList>
#include <QString>

#include "asrl.h"
#include "tcpip.h"
#include "usbraw.h"




#ifndef NIVISA_H
#define NIVISA_USB
#define NIVISA_H
#include "C:\Program Files\IVI Foundation\VISA\Win64\Include\visa.h"

#endif

//#include "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\include\visa.h"

ViStatus _VI_FUNCH visaEventHandler(ViSession vi, ViEventType eventType, ViEvent event, ViAddr userHandle);




class Visa : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(Visa)


    friend ViStatus _VI_FUNCH visaEventHandler(ViSession vi, ViEventType eventType, ViEvent event, ViAddr userHandle);

    Q_PROPERTY(Asrl*   asrl          READ asrl )
    Q_PROPERTY(QString intfInstName  READ intfInstName                          NOTIFY intfInstNameChanged)
    Q_PROPERTY(QString intfNum       READ intfNum                               NOTIFY intfNumChanged)
    Q_PROPERTY(QString intfType      READ intfType                              NOTIFY intfTypeChanged)
    Q_PROPERTY(QString ioProt        READ ioProt        WRITE setIoProt         NOTIFY ioProtChanged)

    Q_PROPERTY(quint16 manfId        READ manfId                                NOTIFY manfIdChanged)
    Q_PROPERTY(QString manfName      READ manfName                              NOTIFY manfNameChanged)
    Q_PROPERTY(quint16 modelCode     READ modelCode                             NOTIFY modelCodeChanged)
    Q_PROPERTY(QString modelName     READ modelName                             NOTIFY modelNameChanged)

    Q_PROPERTY(QString rsrcClass     READ rsrcClass                             NOTIFY rsrcClassChanged)
    Q_PROPERTY(QString rsrcLockState READ rsrcLockState WRITE setRsrcLockState  NOTIFY rsrcLockStateChanged)
    Q_PROPERTY(QString rsrcName      READ rsrcName      WRITE setRsrcName       NOTIFY rsrcNameChanged)
    Q_PROPERTY(QString statusMsg     READ statusMsg                             NOTIFY statusMsgChanged) // read only
    Q_PROPERTY(Tcpip*  tcpip         READ tcpip )

    Q_PROPERTY(QString termChar      READ termChar      WRITE setTermChar       NOTIFY termCharChanged)
    Q_PROPERTY(QString termCharEn    READ termCharEn    WRITE setTermCharEn     NOTIFY termCharEnChanged)
    Q_PROPERTY(QString tmoValue      READ tmoValue      WRITE setTmoValue       NOTIFY tmoValueChanged)
    Q_PROPERTY(UsbRaw* usbRaw        READ usbRaw )
    Q_PROPERTY(QString retString     READ retString                             NOTIFY retStringChanged) // read only
    Q_PROPERTY(int     retCount      READ retCount                              NOTIFY retCountChanged) // read only
    Q_PROPERTY(int     stb           READ stb                                   NOTIFY stbChanged) // read only
    Q_PROPERTY(bool    connected     READ connected                             NOTIFY connectedChanged)

public:
    Visa(QQuickItem *parent = 0);
    ~Visa();

    Q_INVOKABLE void open(const QString &qRsrcName);
    Q_INVOKABLE void write(const QString &qCommand);
    Q_INVOKABLE QString read (const int &countToRead);
    Q_INVOKABLE void readAsync (const int &countToRead);
//    Q_INVOKABLE void sscanf(const QString &readFmt, );
//    Q_INVOKABLE vscanf(const QString &readFmt, );
    Q_INVOKABLE QList<qreal> getRetList(const QString &readFmt, const quint32 &count);
    Q_INVOKABLE quint32 getAsrlAvailNum();
    Q_INVOKABLE void close();

    // property read/writes
    Asrl*   asrl();
    QString intfInstName();     // Read only
    QString intfNum();          // Read only
    QString intfType();         // Read only
    QString ioProt();           void setIoProt(const QString &rn);
    quint16 manfId();
    QString manfName();
    quint16 modelCode();
    QString modelName();
    QString rsrcClass();        // Read only
    QString rsrcLockState();    void setRsrcLockState(const QString &rn);
    QString rsrcName();         void setRsrcName(const QString &rn);
    QString statusMsg();        // Read only
    Tcpip*  tcpip();
    QString termChar();         void setTermChar(const QString &tc);
    QString termCharEn();       void setTermCharEn(const QString &tce);
    QString tmoValue();         void setTmoValue(const QString &to);
    UsbRaw* usbRaw();
    QString retString();        // Read only
    int     retCount();         // Read only
    int     stb();              // Read only

    bool connected();       void setConnected(const bool &rn);

    // was sets - set once when class variable instance is set
    // to know which attributes to send to Visa.
    bool ioProtWasSet();        void setIoProtWasSet(const bool &rn);
    bool rsrcLockStateWasSet(); void setRsrcLockStateWasSet(const bool &rn);
    bool rsrcNameWasSet();      void setRsrcNameWasSet(const bool &rn);
    bool termCharWasSet();      void setTermCharWasSet(const bool &rn);
    bool termCharEnWasSet();    void setTermCharEnWasSet(const bool &rn);
    bool tmoValueWasSet();      void setTmoValueWasSet(const bool &rn);

    ViSession    instr();

    //    void fromVisa_AsrlAvailNum();
    void toVisa_AsrlBaud();                 void fromVisa_AsrlBaud();
    void toVisa_AsrlDataBits();             void fromVisa_AsrlDataBits();
    void toVisa_AsrlFlowControl();          void fromVisa_AsrlFlowControl();
    void toVisa_AsrlParity();               void fromVisa_AsrlParity();
    void toVisa_AsrlStopBits();             void fromVisa_AsrlStopBits();
                                            void fromVisa_IntfInstName();
                                            void fromVisa_IntfNum();
                                            void fromVisa_IntfType();
    void toVisa_IoProt();                   void fromVisa_IoProt();
                                            void fromVisa_ManfId();
                                            void fromVisa_ManfName();
                                            void fromVisa_ModelCode();
                                            void fromVisa_ModelName();
                                            void fromVisa_RsrcClass() ;
    void toVisa_RsrcLockState();            void fromVisa_RsrcLockState();
                                            void fromVisa_RsrcName();
    void toVisa_TermChar();                 void fromVisa_TermChar();
    void toVisa_TermCharEn();               void fromVisa_TermCharEn();
    void toVisa_TmoValue();                 void fromVisa_TmoValue();
                                            void fromVisa_TcpipAddr();
                                            void fromVisa_TcpipHostname();
                                            void fromVisa_TcpipPort();



signals:

    void intfInstNameChanged();
    void intfNumChanged();
    void intfTypeChanged();
    void ioProtChanged();
    void manfIdChanged();
    void manfNameChanged();
    void modelCodeChanged();
    void modelNameChanged();
    void rsrcClassChanged();
    void rsrcLockStateChanged();
    void rsrcNameChanged();
    void statusMsgChanged();
    void termCharChanged();
    void termCharEnChanged();
    void tmoValueChanged();

    void connectedChanged();

    // events
    //
    void serviceReq();
    void ioCompletion();
    void retStringChanged();
    void retCountChanged();
    void stbChanged();

public slots:
    void updateVisaAttributes();
    void statusUpdate(const QString &rn);
    //    void getAsrlAvailNum();

protected:
    Asrl*   _asrl;
    Tcpip*  _tcpip;
    UsbRaw* _usbRaw;
    QString _intfInstName;
    QString _intfNum;
    QString _intfType;
    QString _ioProt;            bool    _ioProtWasSet;
    quint16 _manfId;
    QString _manfName;
    quint16 _modelCode;
    QString _modelName;
    QString _rsrcClass;
    QString _rsrcLockState;     bool    _rsrcLockStateWasSet;
    QString _rsrcName;          bool    _rsrcNameWasSet;
    QString _statusMsg;
    QString _termChar;          bool    _termCharWasSet;
    QString _termCharEn;        bool    _termCharEnWasSet;
    QString _tmoValue;          bool    _tmoValueWasSet;

    ViSession _defaultRM;
    ViSession _instr;

    // misc
    char    _buffer[50000];
    QString _retString;
    int     _retCount;
    int     _stb;
    bool    _connected;

};


#endif // QMLVISA_H

