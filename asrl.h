#ifndef ASRL_H
#define ASRL_H

#ifndef NIVISA_H
#define NIVISA_H
#define NIVISA_USB
#include "C:\Program Files\IVI Foundation\VISA\Win64\Include\visa.h"
#endif

//#include "qmlvisa.h"
#include <QQuickItem>

class Asrl : public QQuickItem
{
    Q_OBJECT

    Q_ENUMS(FlowControl)
    Q_ENUMS(Parity)
    Q_ENUMS(StopBits)


//    Q_PROPERTY(QString availNum READ availNum NOTIFY availNumChanged) // read only
    Q_PROPERTY(QString baud         READ baud           WRITE setBaud           NOTIFY baudChanged)
    Q_PROPERTY(QString dataBits     READ dataBits       WRITE setDataBits       NOTIFY dataBitsChanged)
    Q_PROPERTY(QString flowControl  READ flowControl    WRITE setFlowControl    NOTIFY flowControlChanged)
    Q_PROPERTY(QString parity       READ parity         WRITE setParity         NOTIFY parityChanged)
    Q_PROPERTY(QString stopBits     READ stopBits       WRITE setStopBits       NOTIFY stopBitsChanged)

public:
    explicit Asrl(QQuickItem *parent = 0);

    // ASRL data bits
    //
    //  8 default
    //  5 to 8 allowed
    //

    // ASRL flow control
    //
    // VI_ASRL_FLOW_NONE default
    // Allowed:
    //    VI_ASRL_FLOW_NONE (0)
    //    VI_ASRL_FLOW_XON_XOFF (1)
    //    VI_ASRL_FLOW_RTS_CTS (2)
    //    VI_ASRL_FLOW_DTR_DSR (4)
    //
    enum FlowControl {NoFlowControl = VI_ASRL_FLOW_NONE, XonXOff = VI_ASRL_FLOW_XON_XOFF, RtsCts = VI_ASRL_FLOW_RTS_CTS, DtrDsr = VI_ASRL_FLOW_DTR_DSR};


    // ASRL parity
    //
    // VI_ASRL_PAR_NONE default
    // Allowed:
    //    VI_ASRL_PAR_NONE (0)
    //    VI_ASRL_PAR_ODD (1)
    //    VI_ASRL_PAR_EVEN (2)
    //    VI_ASRL_PAR_MARK (3)
    //    VI_ASRL_PAR_SPACE (4)
    //
    enum Parity {NoParity = VI_ASRL_PAR_NONE, Odd = VI_ASRL_PAR_ODD, Even = VI_ASRL_PAR_EVEN, Mark = VI_ASRL_PAR_MARK, Space = VI_ASRL_PAR_SPACE};


    // ASRL stop bits
    //
    // VI_ASRL_STOP_ONE default
    // Allowed:
    //    VI_ASRL_STOP_ONE (10)
    //    VI_ASRL_STOP_ONE5 (15)
    //    VI_ASRL_STOP_TWO (20)
    //
    enum StopBits {One = VI_ASRL_STOP_ONE, One5 = VI_ASRL_STOP_ONE5, Two = VI_ASRL_STOP_TWO};

    //QString availNum();    // Read only
    QString baud();         void setBaud(const QString &rn);
    QString dataBits();     void setDataBits(const QString &rn);
    QString flowControl();  void setFlowControl(const QString &rn);
    QString parity();       void setParity(const QString &rn);
    QString stopBits();     void setStopBits(const QString &rn);

    void toVisa_Baud();                 void fromVisa_Baud();
    void toVisa_DataBits();             void fromVisa_DataBits();
    void toVisa_FlowControl();          void fromVisa_FlowControl();
    void toVisa_Parity();               void fromVisa_Parity();
    void toVisa_StopBits();             void fromVisa_StopBits();

    bool    baudWasSet();       void setBaudWasSet(const bool &rn);
    bool    dataBitsWasSet();   void setDataBitsWasSet(const bool &rn);
    bool    flowControlWasSet();void setFlowControlWasSet(const bool &rn);
    bool    parityWasSet();     void setParityWasSet(const bool &rn);
    bool    stopBitsWasSet();   void setStopBitsWasSet(const bool &rn);

    void    setInstr(const ViSession rn);
    void    setConnected(const bool &rn);
    bool    connected();



signals:

//    void availNumChanged();
    void baudChanged();
    void dataBitsChanged();
    void flowControlChanged();
    void parityChanged();
    void stopBitsChanged();

    void updateVisaAttributes();
    void getAvailNum();
    void statusUpdate(const QString &rn);

public slots:

protected:
//    QString _availNum;
    ViSession _instr;
    bool      _connected;

    QString _baud;
    QString _dataBits;
    QString _flowControl;
    QString _parity;
    QString _stopBits;
    bool    _baudWasSet;
    bool    _dataBitsWasSet;
    bool    _flowControlWasSet;
    bool    _parityWasSet;
    bool    _stopBitsWasSet;
};

#endif // ASRL_H
