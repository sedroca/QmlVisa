#include "asrl.h"

Asrl::Asrl(QQuickItem *parent) :
    QQuickItem(parent)
{
}


//-----------------------------------------------------------------------------------

// ASRL Available Number
//
// (read only)
//
//QString Asrl::availNum()
//{
//    ViStatus status;
//    ViUInt32 aViUInt32;


//   qDebug() << QString("asrlAvailNum");

//    // ASRL available num
//    //
//    // Read only
//    //
//    status = viGetAttribute (_instr, VI_ATTR_ASRL_AVAIL_NUM, &aViUInt32);
//    if (status < VI_SUCCESS)
//    {
//        _availNum.setNum(0);
//        viStatusDesc(_instr, status, desc);
//        _statusMsg = QString("--Visa attribute read failed: %1").arg(desc);
//        emit statusMsgChanged();
//        qDebug() << _statusMsg;
//    }
//    else
//    {
//        _availNum.setNum(aViUInt32);
//        _statusMsg = QString("Serial data available %1").arg(aViUInt32);
//        emit statusMsgChanged();
//        qDebug() << _statusMsg;
//    }
//    emit statusMsgChanged();


//    return _asrlAvailNum;
//}



// ASRL Baud
//
QString Asrl::baud()
{
    return _baud;
}
void Asrl::setBaud(const QString &to)
{
    if (to != _baud) {
        _baud = to;
        emit baudChanged();
        setBaudWasSet(true);  // keep for open / close
        if (connected()) {
            toVisa_Baud();
        }
        //emit updateVisaAttributes();
    }
}

// ASRL Data Bits
//
QString Asrl::dataBits()
{
    return _dataBits;
}
void Asrl::setDataBits(const QString &to)
{
    if (to != _dataBits) {
        _dataBits = to;
        emit dataBitsChanged();
        setDataBitsWasSet(true);
        if (connected()) {
            toVisa_DataBits();
        }
//        emit updateVisaAttributes();
    }
}

// ASRL Flow Control
//
QString Asrl::flowControl()
{
    return _flowControl;
}
void Asrl::setFlowControl(const QString &to)
{
    if (to != _flowControl) {
        _flowControl = to;
        emit flowControlChanged();
        setFlowControlWasSet(true);
        if (connected()) {
            toVisa_FlowControl();
        }
//        emit updateVisaAttributes();
    }
}

// ASRL Parity
//
QString Asrl::parity()
{
    return _parity;
}

void Asrl::setParity(const QString &to)
{
    if (to != _parity) {
        _parity = to;
        emit parityChanged();
        setParityWasSet(true);
        if (connected()) {
            toVisa_Parity();
        }
//        emit updateVisaAttributes();
    }
}

// ASRL Stop Bits
//
QString Asrl::stopBits()
{
    return _stopBits;
}
void Asrl::setStopBits(const QString &to)
{
    if (to != _stopBits) {
        _stopBits = to;
        emit stopBitsChanged();
        setStopBitsWasSet(true);
        if (connected()) {
            toVisa_StopBits();
        }
//        emit updateVisaAttributes();
    }
}

void Asrl::setInstr(const ViSession instr) {
    _instr = instr;
}

bool Asrl::connected() {
    return _connected;
}

void Asrl::setConnected(const bool &rn) {
    _connected = rn;
}

bool Asrl::baudWasSet() {
    return _baudWasSet;
}

bool Asrl::dataBitsWasSet() {
    return _dataBitsWasSet;
}

bool Asrl::flowControlWasSet() {
    return _flowControlWasSet;
}

bool Asrl::parityWasSet() {
    return _parityWasSet;
}

bool Asrl::stopBitsWasSet() {
    return _stopBitsWasSet;
}

void Asrl::setBaudWasSet(const bool &rn) {
    _baudWasSet = rn;
}

void Asrl::setDataBitsWasSet(const bool &rn) {
    _dataBitsWasSet = rn;
}

void Asrl::setFlowControlWasSet(const bool &rn) {
    _flowControlWasSet = rn;
}

void Asrl::setParityWasSet(const bool &rn) {
    _parityWasSet = rn;
}

void Asrl::setStopBitsWasSet(const bool &rn) {
    _stopBitsWasSet = rn;
}

void Asrl::toVisa_Baud() {
    ViStatus status;
    char desc[256];

    //    _statusMsg = QString("Sent asrlBaud to Visa");
    //    emit statusMsgChanged();
    //    qDebug() << _statusMsg;

    status = viSetAttribute (_instr, VI_ATTR_ASRL_BAUD, (ViUInt32) baud().toUInt());
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
        //        _statusMsg = QString("  --%1").arg(desc);
        //        emit statusMsgChanged();
        //        qDebug() << _statusMsg;
    }

}

void Asrl::toVisa_DataBits() {

    ViStatus status;
    char desc[256];


    //    _statusMsg = QString("Send asrlDataBits to Visa");
    //    emit statusMsgChanged();
    //    qDebug() << _statusMsg;

    status = viSetAttribute (_instr, VI_ATTR_ASRL_DATA_BITS, (ViUInt16) dataBits().toUInt());
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
        //        _statusMsg = QString("  --%1").arg(desc);
        //        emit statusMsgChanged();
        //        qDebug() << _statusMsg;
    }

}

void Asrl::toVisa_FlowControl() {
    ViStatus status;
    char desc[256];

    //    _statusMsg = QString("Send asrlFlowControl to Visa");
    //    emit statusMsgChanged();
    //    qDebug() << _statusMsg;

    status = viSetAttribute (_instr, VI_ATTR_ASRL_FLOW_CNTRL, (ViUInt16) flowControl().toUInt());
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
        //        _statusMsg = QString("  --%1").arg(desc);
        //        emit statusMsgChanged();
        //        qDebug() << _statusMsg;
    }

}

void Asrl::toVisa_Parity() {
    ViStatus status;
    char desc[256];

    //    _statusMsg = QString("Send asrlSetParity to Visa");
    //    emit statusMsgChanged();
    //    qDebug() << _statusMsg;

    status = viSetAttribute (_instr, VI_ATTR_ASRL_PARITY, (ViUInt16) parity().toUInt());
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
        //        _statusMsg = QString("  --%1").arg(desc);
        //        emit statusMsgChanged();
        //        qDebug() << _statusMsg;
    }
}

void Asrl::toVisa_StopBits() {
    ViStatus status;
    char desc[256];

    //    _statusMsg = QString("Send asrlStopBits to Visa");
    //    emit statusMsgChanged();
    //    qDebug() << _statusMsg;

    status = viSetAttribute (_instr, VI_ATTR_ASRL_STOP_BITS,(ViUInt16) stopBits().toUInt());
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
        //        _statusMsg = QString("  --%1").arg(desc);
        //        emit statusMsgChanged();
        //        qDebug() << _statusMsg;
    }

}

void Asrl::fromVisa_Baud() {
    ViStatus status;
    ViUInt32 aViUInt32;
    char desc[256];

    //    _statusMsg = QString("Read asrlBaud from Visa");
    //    emit statusMsgChanged();
    //    qDebug() << _statusMsg;

    status = viGetAttribute (_instr, VI_ATTR_ASRL_BAUD, &aViUInt32);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
        //        _statusMsg = QString("  --%1").arg(desc);
    }
    else
    {
        setBaud(QString("%1").arg(aViUInt32));
        emit baudChanged();
        emit statusUpdate(QString("  Asrl baud: ") + baud());
        //        _statusMsg = QString("  Asrl baud: ") + asrl()->baud();
    }
    //    emit statusMsgChanged();
    //    qDebug() << _statusMsg;
}

void Asrl::fromVisa_DataBits() {
    ViStatus status;
    ViUInt16 aViUInt16;
    char desc[256];

    //    _statusMsg = QString("Read asrlDataBits from Visa");
    //    emit statusMsgChanged();
    //    qDebug() << _statusMsg;

    status = viGetAttribute (_instr, VI_ATTR_ASRL_DATA_BITS, &aViUInt16);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
        //        _statusMsg = QString("  --%1").arg(desc);
    }
    else
    {
        setDataBits(QString("%1").arg(aViUInt16));
        emit dataBitsChanged();
        emit statusUpdate(QString("  Asrl data bits: ") + dataBits());
        //        _statusMsg = QString("  Asrl data bits: ") + asrl()->dataBits();
    }
    //    emit statusMsgChanged();
    //    qDebug() << _statusMsg;
}

void Asrl::fromVisa_FlowControl() {
    ViStatus status;
    ViUInt16 aViUInt16;
    char desc[256];

    //    _statusMsg = QString("Read asrlFlowControl from Visa");
    //    emit statusMsgChanged();
    //    qDebug() << _statusMsg;

    status = viGetAttribute (_instr, VI_ATTR_ASRL_FLOW_CNTRL, &aViUInt16);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
        //        _statusMsg = QString("  --%1").arg(desc);
    }
    else
    {
        setFlowControl(QString("%1").arg(aViUInt16));
        emit flowControlChanged();
        emit statusUpdate(QString("  Asrl flow control: ") + flowControl());
        //        _statusMsg = QString("  Asrl flow control: ") + asrl()->flowControl();
    }
    //    emit statusMsgChanged();
    //    qDebug() << _statusMsg;
}

void Asrl::fromVisa_Parity() {
    ViStatus status;
    ViUInt16 aViUInt16;
    char desc[256];

    //    _statusMsg = QString("Read asrlParity from Visa");
    //    emit statusMsgChanged();
    //    qDebug() << _statusMsg;

    status = viGetAttribute (_instr, VI_ATTR_ASRL_PARITY, &aViUInt16);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
        //        _statusMsg = QString("  --%1").arg(desc);
    }
    else
    {
        setParity(QString("%1").arg(aViUInt16));
        emit parityChanged();
        emit statusUpdate(QString("Asrl parity: ") + parity());
        //        _statusMsg = QString("Asrl parity: ") + asrl()->parity();
    }
    //    emit statusMsgChanged();
    //    qDebug() << _statusMsg;
}

void Asrl::fromVisa_StopBits() {
    ViStatus status;
    ViUInt16 aViUInt16;
    char desc[256];

    //    _statusMsg = QString("Read asrlStopBits from Visa");
    //    emit statusMsgChanged();
    //    qDebug() << _statusMsg;

    status = viGetAttribute (_instr, VI_ATTR_ASRL_STOP_BITS, &aViUInt16);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else
    {


        setStopBits(QString("%1").arg(aViUInt16));
        emit stopBitsChanged();
        emit statusUpdate(QString("  Asrl stopBits: ") + stopBits());
        //        _statusMsg = QString("  Asrl stopBits: ") + asrl()->stopBits();
    }
    //    emit statusMsgChanged();
    //    qDebug() << _statusMsg;
}



