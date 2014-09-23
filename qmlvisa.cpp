#include "qmlvisa.h"

Visa::Visa(QQuickItem *parent):
    QQuickItem(parent)
{
    ViChar desc[256];
    ViStatus status;

    //    this->m_axis = new GraphAxis(this);
    //    this->m_plot = new GraphPlot(this, this->m_axis);
    //    this->connect(this->m_axis,SIGNAL(update()),this,SLOT(repaint()));

    //    this->_asrl = new Asrl(this);
    //    this->_tcpip = new Tcpip(this);
    //    this->connect(this->_asrl,SIGNAL(updateVisaAttributes()),this,SLOT(updateVisaAttributes()));
    //    this->connect(this->_tcpip,SIGNAL(updateVisaAttributes()),this,SLOT(updateVisaAttributes()));

    _asrl = new Asrl(this);
    _tcpip = new Tcpip(this);
    _usbRaw = new UsbRaw(this);
    connect(_asrl,SIGNAL(updateVisaAttributes()),this,SLOT(updateVisaAttributes()));
    connect(_asrl,SIGNAL(statusUpdate(QString)),this,SLOT(statusUpdate(QString)));
    connect(_tcpip,SIGNAL(updateVisaAttributes()),this,SLOT(updateVisaAttributes()));
    connect(_usbRaw,SIGNAL(updateVisaAttributes()),this,SLOT(updateVisaAttributes()));
    connect(_usbRaw,SIGNAL(statusUpdate(QString)),this,SLOT(statusUpdate(QString)));
    //    connect(_asrl,SIGNAL(getAvailNum()),this,SLOT(getAsrlAvailNum()));

    /*
     * First we must call viOpenDefaultRM to get the resource manager
     * handle.  We will store this handle in defaultRM.
     */
    status=viOpenDefaultRM (&_defaultRM);
    if (status < VI_SUCCESS)
    {
        //      printf("Could not open a session to the VISA Resource Manager!\n");
        //      exit (EXIT_FAILURE);
        viStatusDesc(_instr, status, desc);
        _statusMsg = QString("Could not open a session to the VISA Resource Manager: %1").arg(desc);
    }
    else
    {
        _statusMsg = "Session opened to VISA Resource Manager";
    }
    emit statusMsgChanged();
    qDebug() << _statusMsg;
    _instr = 0;  //
    setConnected(false);
    //    emit connectedChanged();

    asrl()->setBaudWasSet(false);
    asrl()->setDataBitsWasSet(false);
    asrl()->setFlowControlWasSet(false);
    asrl()->setParityWasSet(false);
    asrl()->setStopBitsWasSet(false);
    setIoProtWasSet(false);
    setRsrcLockStateWasSet(false);
    setRsrcNameWasSet(false);
    setTermCharWasSet(false);
    setTermCharEnWasSet(false);
    setTmoValueWasSet(false);
    usbRaw()->setBulkInPipeWasSet(false);
    usbRaw()->setBulkInStatusWasSet(false);
    usbRaw()->setBulkOutPipeWasSet(false);
    usbRaw()->setBulkOutStatusWasSet(false);
    usbRaw()->setIntrInPipeWasSet(false);
    usbRaw()->setIntrInStatusWasSet(false);
    usbRaw()->setMaxIntrSizeWasSet(false);

}

Visa::~Visa()
{
    ViStatus status;
    status = viClose(_instr);
    _instr = -1;
    status = viClose(_defaultRM);
    _defaultRM = -1;
}

void Visa::statusUpdate(const QString &rn) {
    _statusMsg = rn;
    emit statusMsgChanged();
    qDebug() << _statusMsg;
}

void Visa::open(const QString &qResourceName)
{
    ViStatus status;
    //static ViRsrc viRsrc;

    char viResource[100];
    QByteArray qBaResourceName;

    //    char outputBuffer[256];
    //    ViUInt32 aViUInt32;
    //    ViUInt16 aViUInt16;
    //    ViUInt8  aViUInt8;
    //    ViBoolean aViBoolean;
    //    ViAccessMode aViAccessMode;
    //ViAddr aViAddr;
    //    char aViRsrc[256];
    ViChar desc[256];


    qBaResourceName = qResourceName.toLatin1();
    strcpy_s(viResource,qBaResourceName.constData());
    status = viOpen (_defaultRM, viResource, VI_NULL, VI_NULL, &_instr);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        _statusMsg = QString("Cannot open a session to %1: %2").arg(viResource).arg(desc);
        emit statusMsgChanged();
        qDebug() << _statusMsg;
    }
    else
    {
        _statusMsg = QString("Session opened to %1").arg(viResource);
        emit statusMsgChanged();
        qDebug() << _statusMsg;
        setConnected(true);
        emit connectedChanged();
        asrl()->setInstr(_instr);
        asrl()->setConnected(true);
        usbRaw()->setInstr(_instr);
        usbRaw()->setConnected(true);




        // Event handling -------------------------------------------------------------------------------


        // Install ioCompletion handler
        //
        _statusMsg = QString("Set ioCompletion Handler");
        emit statusMsgChanged();
        qDebug() << _statusMsg;

        status = viInstallHandler (_instr, VI_EVENT_IO_COMPLETION, &visaEventHandler, this);
        if (status < VI_SUCCESS)
        {
            viStatusDesc(_instr, status, desc);
            _statusMsg = QString("  --%1").arg(desc);
        }
        else
        {
            _statusMsg = QString("  IoCompletion event handler is connected");
        }
        emit statusMsgChanged();
        qDebug() << _statusMsg;


        // Enable ioCompletion event
        //

        _statusMsg = QString("Enable ioCompletion event");
        emit statusMsgChanged();
        qDebug() << _statusMsg;

        status = viEnableEvent (_instr, VI_EVENT_IO_COMPLETION, VI_HNDLR, VI_NULL);
        if (status < VI_SUCCESS)
        {
            viStatusDesc(_instr, status, desc);
            _statusMsg = QString("  --%1").arg(desc);
        }
        else
        {
            _statusMsg = QString("  IoCompletion event is enabled");
        }
        emit statusMsgChanged();
        qDebug() << _statusMsg;


        // Install serviceReq handler
        //

        _statusMsg = QString("Set serviceReq event handler");
        emit statusMsgChanged();
        qDebug() << _statusMsg;

        status = viInstallHandler (_instr, VI_EVENT_SERVICE_REQ, &visaEventHandler, this);
        if (status < VI_SUCCESS)
        {
            viStatusDesc(_instr, status, desc);
            _statusMsg = QString("  --%1").arg(desc);
        }
        else
        {
            _statusMsg = QString("  ServiceReq event handler is connected");
        }
        emit statusMsgChanged();
        qDebug() << _statusMsg;


        // Enable serviceReq event
        //

        _statusMsg = QString("Enable serviceReq event");
        emit statusMsgChanged();
        qDebug() << _statusMsg;

        status = viEnableEvent (_instr, VI_EVENT_SERVICE_REQ, VI_HNDLR, VI_NULL);
        if (status < VI_SUCCESS)
        {
            viStatusDesc(_instr, status, desc);
            _statusMsg = QString("  --%1").arg(desc);
        }
        else
        {
            _statusMsg = QString("  ServiceReq event is enabled");
        }
        emit statusMsgChanged();
        qDebug() << _statusMsg;



        // Initialize attributes ----------------------------------------------------------------------

        updateVisaAttributes();  // those which have been set in QML will have a flag set
        // and will be sent to Visa.
        // those others will just be initialized from Visa.
        // more synchronization than initialization in a way.

    }
}

//void Visa::write(const QString &qCommand, int &writeCount)
void Visa::write(const QString &qCommand)
{
    ViStatus status;
    //static int writeCount;
    QString command;
    QByteArray qBaCommand;
    char viCommand[256];
    unsigned char* viCommandUC;
    int writeCount;
    ViChar desc[256];

    command = qCommand + "\n";
    qBaCommand = command.toLatin1();

    strcpy_s(viCommand,qBaCommand.constData());
    viCommandUC = (unsigned char *) viCommand;

    //status = viWrite (_instr, (ViBuf)viCommand, (ViUInt32)strlen(viCommand), &writeCount);
    status = viWrite (_instr, viCommandUC, (ViUInt32)strlen(viCommand), (ViPUInt32) &writeCount);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        _statusMsg = QString("Error writing to the device: %1").arg(desc);
    }
    else
    {
        _statusMsg = QString("Write completed with %1 characters sent").arg(writeCount);
    }
    emit statusMsgChanged();
    qDebug() << _statusMsg;
}

QString Visa::read(const int &countToRead)
{
    static ViStatus status;
    ViChar buffer[1025];
    QString bufferRead;
    ViUInt32 retCount;
    //int returnCount;
    ViChar desc[256];


    //    status = viRead (_instr, (ViPBuf) buffer, countToRead, &retCount);
    status = viRead (_instr, (ViPBuf) _buffer, countToRead, &retCount);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        _statusMsg = QString("Error reading a response from the device: %1").arg(desc);
    }
    else
    {
        _statusMsg = QString("Data read: %1 chars: %2").arg(retCount).arg(buffer);
    }
    emit statusMsgChanged();
    qDebug() << _statusMsg;

    bufferRead = QString::fromLocal8Bit(_buffer,retCount);
    _retString = bufferRead;
    emit retStringChanged();
    _retCount = retCount;
    emit retCountChanged();
    return bufferRead;
}

void Visa::readAsync(const int &countToRead)
{
    static ViStatus status;
    ViJobId aViJobId;

    _statusMsg = QString("ReadAsync about to start. Asking for %1 bytes").arg(countToRead);
    emit statusMsgChanged();
    qDebug() << _statusMsg;

    status = viReadAsync (_instr, (ViPBuf) _buffer, countToRead, &aViJobId);
    if (status < VI_SUCCESS)
    {
        _statusMsg = QString("--viReadAsync failed");
        emit statusMsgChanged();
        qDebug() << _statusMsg;
    }
}


void Visa::close()
{
    static ViStatus status;
    status = viClose(_instr);
    setConnected(false);
    emit connectedChanged();
    _instr = -1;
    _statusMsg = QString("Visa session closed");
    emit statusMsgChanged();
}

bool Visa::connected()
{
    return _connected;
}

void Visa::setConnected(const bool &rn)
{
    if (rn != _connected)
    {
        _connected = rn;
        emit connectedChanged();
    }
}

//**********************

bool Visa::ioProtWasSet() {
    return _ioProtWasSet;
}

void Visa::setIoProtWasSet(const bool &rn) {
    _ioProtWasSet = rn;
}

bool Visa::rsrcLockStateWasSet() {
    return _rsrcLockStateWasSet;
}

void Visa::setRsrcLockStateWasSet(const bool &rn) {
    _rsrcLockStateWasSet = rn;
}

bool Visa::rsrcNameWasSet() {
    return _rsrcNameWasSet;
}

void Visa::setRsrcNameWasSet(const bool &rn) {
    _rsrcNameWasSet = rn;
}

bool Visa::termCharWasSet() {
    return _termCharWasSet;
}

void Visa::setTermCharWasSet(const bool &rn) {
    _termCharWasSet = rn;
}

bool Visa::termCharEnWasSet() {
    return _termCharEnWasSet;
}

void Visa::setTermCharEnWasSet(const bool &rn) {
    _termCharEnWasSet = rn;
}

bool Visa::tmoValueWasSet() {
    return _tmoValueWasSet;
}

void Visa::setTmoValueWasSet(const bool &rn) {
    _tmoValueWasSet = rn;
}




// Visa class property reads and writes
// --------------------------------------------------------------------
//
// --------------------------------------------------------------------

Asrl* Visa::asrl() {return _asrl;}
Tcpip* Visa::tcpip() {return _tcpip;}
UsbRaw* Visa::usbRaw() {return _usbRaw;}

// ASRL Available Number
//
// (read only)///
//QString Visa::asrlAvailNum()
//{
//    return _asrlAvailNum;
//}


// Interface Name
// (read only)
//
QString Visa::intfInstName()
{
    return _intfInstName;
}

// Interface Number
// (read only)
//
QString Visa::intfNum()
{
    return _intfNum;
}

// Interface Type
// (read only)
//
QString Visa::intfType()
{
    return _intfType;
}

// IO Protocol
//
//
QString Visa::ioProt()
{
    return _ioProt;
}
void Visa::setIoProt(const QString &to)
{
    if (to != _ioProt) {
        _ioProt = to;
        setIoProtWasSet(true);
        if (connected()) {
            toVisa_IoProt();
        }
        emit ioProtChanged();
    }
}

quint16 Visa::manfId() {
    return _manfId;
}

QString Visa::manfName() {
    return _manfName;
}

quint16 Visa::modelCode() {
    return _modelCode;
}

QString Visa::modelName() {
    return _modelName;
}

//

// Resource Class
// (read only)
//
QString Visa::rsrcClass()
{
    return _rsrcClass;
}

// Resource lock
//
QString Visa::rsrcLockState()
{
    return _rsrcLockState;
}
void Visa::setRsrcLockState(const QString &to)
{
    if (to != _rsrcLockState) {
        _rsrcLockState = to;
        setRsrcLockStateWasSet(true);
        if (connected()) {
            toVisa_RsrcLockState();
        }
        emit rsrcLockStateChanged();
    }
}

// Resource name
//
QString Visa::rsrcName()
{
    return _rsrcName;
}
void Visa::setRsrcName(const QString &rn)
{
    //if (rn != _rsrcName) {
    _rsrcName = rn;
    emit rsrcNameChanged();
    setRsrcNameWasSet(true);
    Visa::open(_rsrcName);
    //}
}


// Status message
// (read only)
//
QString Visa::statusMsg()
{
    return _statusMsg;
}


// Termination Character
//
QString Visa::termChar()
{
    return _termChar;
}
void Visa::setTermChar(const QString &to)
{
    if (to != _termChar) {
        _termChar = to;
        setTermCharWasSet(true);
        if (connected()) {
            toVisa_TermChar();
        }
        emit termCharChanged();
    }
}

// Termination character enable
//
// Specify that the read operation should terminate when a termination
// character is received.
//      VI_FALSE (0) default
// Allowed:
//      VI_TRUE (1)
//      VI_FALSE (0)
//
QString Visa::termCharEn()
{
    return _termCharEn;
}
void Visa::setTermCharEn(const QString &to)
{
    if (to != _termCharEn) {
        _termCharEn = to;
        setTermCharEnWasSet(true);
        if (connected()) {
            toVisa_TermCharEn();
        }
        emit termCharEnChanged();
    }
}

// Timeout value in mS
// Default of 2000 is 2000mS.
//
//    VI_TMO_IMMEDIATE (0)
//    1 to FFFFFFFEh;
//    VI_TMO_INFINITE  (FFFFFFFFh)
//
QString Visa::tmoValue()
{
    return _tmoValue;
}
void Visa::setTmoValue(const QString &to)
{
    if (to != _tmoValue) {
        _tmoValue = to;
        setTmoValueWasSet(true);
        if (connected()) {
            toVisa_TmoValue();
        }
        emit tmoValueChanged();
    }
}

// Return string from Async Read
//
//
QString Visa::retString()
{
    return _retString;
}

// Resturn string length from Async Read
//
//
int Visa::retCount()
{
    return _retCount;
}

// Status byte returned by viReadStb
//
//
int Visa::stb()
{
    return _stb;
}


void Visa::updateVisaAttributes() {
    if (connected()) {
        if (asrl()->baudWasSet()) {asrl()->toVisa_Baud();}
        else                    {asrl()->fromVisa_Baud(); }

        if (asrl()->dataBitsWasSet()) {asrl()->toVisa_DataBits();}
        else                        {asrl()->fromVisa_DataBits(); }

        if (asrl()->flowControlWasSet()) {asrl()->toVisa_FlowControl(); }
        else                           {asrl()->fromVisa_FlowControl();}

        if (asrl()->parityWasSet()) {asrl()->toVisa_Parity();}
        else                      {asrl()->fromVisa_Parity();}

        if (asrl()->stopBitsWasSet()) {asrl()->toVisa_StopBits();}
        else                        {asrl()->fromVisa_StopBits();}

        if (ioProtWasSet()) {toVisa_IoProt();}
        else              {fromVisa_IoProt();}

        if (rsrcLockStateWasSet()) {toVisa_RsrcLockState();}
        else                     {fromVisa_RsrcLockState();}

        fromVisa_TcpipAddr();
        fromVisa_TcpipHostname();
        fromVisa_TcpipPort();

        if (termCharWasSet()) {toVisa_TermChar();}
        else                {fromVisa_TermChar();}

        if (termCharEnWasSet()) {toVisa_TermCharEn();}
        else                  {fromVisa_TermCharEn();}

        if (tmoValueWasSet()) {toVisa_TmoValue();}
        else                {fromVisa_TmoValue();}


        if (usbRaw()->bulkInPipeWasSet()) {usbRaw()->toVisa_BulkInPipe();}
        else                            {usbRaw()->fromVisa_BulkInPipe();}

        if (usbRaw()->bulkInStatusWasSet()) {usbRaw()->toVisa_BulkInStatus();}
        else                              {usbRaw()->fromVisa_BulkInStatus();}

        if (usbRaw()->bulkOutPipeWasSet()) {usbRaw()->toVisa_BulkOutPipe();}
        else                             {usbRaw()->fromVisa_BulkOutPipe();}

        if (usbRaw()->bulkOutStatusWasSet()) {usbRaw()->toVisa_BulkOutStatus();}
        else                               {usbRaw()->fromVisa_BulkOutStatus();}

        usbRaw()->fromVisa_ClassUsed();
        usbRaw()->fromVisa_IntfcNum();

        if (usbRaw()->intrInPipeWasSet()) {usbRaw()->toVisa_IntrInPipe();}
        else                            {usbRaw()->fromVisa_IntrInPipe();}

        if (usbRaw()->intrInStatusWasSet()) {usbRaw()->toVisa_IntrInStatus();}
        else                              {usbRaw()->fromVisa_IntrInStatus();}

        if (usbRaw()->maxIntrSizeWasSet()) {usbRaw()->toVisa_MaxIntrSize();}
        else                             {usbRaw()->fromVisa_MaxIntrSize();}

        usbRaw()->fromVisa_NumIntfcs();
        usbRaw()->fromVisa_NumPipes();
        usbRaw()->fromVisa_Protocol();
        usbRaw()->fromVisa_RecvIntrData();
        usbRaw()->fromVisa_RecvIntrSize();
        usbRaw()->fromVisa_SerialNum();
        usbRaw()->fromVisa_Subclass();

    }
}




ViSession    Visa::instr() {return _instr;}

ViStatus _VI_FUNC visaEventHandler(ViSession vi, ViEventType eventType, ViEvent event, ViAddr userHandle)
{
    ViUInt16 aViUInt16;
    ViUInt32 aViUInt32;
    ViStatus aViStatus;
    ViStatus status;
    ViBuf aViBuf;
    ViChar desc[256];

    Visa* ob = static_cast<Visa*>(userHandle);

    // send out proper response
    //

    ob->_statusMsg = QString(" event received for session %1: type %2 event %3").arg(vi).arg(eventType).arg(event);
    emit ob->statusMsgChanged();
    qDebug() << ob->_statusMsg;

    if(eventType == VI_EVENT_SERVICE_REQ)
    {
        status = viReadSTB (vi, &aViUInt16);
        if (status < VI_SUCCESS)
        {
            ob->_statusMsg = QString("--viReadSTB failed");
            emit ob->statusMsgChanged();
            qDebug() << ob->_statusMsg;
        }
        ob->_stb = (int) aViUInt16;
        emit ob->stbChanged();
        emit ob->serviceReq();
    }
    else if (eventType == VI_EVENT_IO_COMPLETION)
    {
        status  = viGetAttribute (event, VI_ATTR_STATUS, &aViStatus);
        status += viGetAttribute (event, VI_ATTR_RET_COUNT, &aViUInt32);
        status += viGetAttribute (event, VI_ATTR_BUFFER, &aViBuf);
        if (status < VI_SUCCESS)
        {
            ob->_statusMsg = QString("--viGetAttributes of event failed");
            emit ob->statusMsgChanged();
            qDebug() << ob->_statusMsg;
        }
        else
        {
            ob->_statusMsg = QString(" viGetAttributes of event succeeded.  ioStatus: %1, retCount %2").arg(aViStatus).arg(aViUInt32);
            emit ob->statusMsgChanged();
            qDebug() << ob->_statusMsg;
            if (aViStatus < VI_SUCCESS)
            {
                viStatusDesc(event, aViStatus, desc);
                ob->_statusMsg = QString("--ioCompleted with error status: %1").arg(desc);
                emit ob->statusMsgChanged();
                qDebug() << ob->_statusMsg;
            }
            ob->_retCount = aViUInt32;
            if (aViUInt32 > 0)
            {
                ob->_retString = QString::fromLocal8Bit(ob->_buffer);
            }
            else
            {
                ob->_retString = QString("--Async read completed with no data");
            }
            emit ob->retCountChanged();
            emit ob->retStringChanged();
            emit ob->ioCompletion();
        }
    }
    else
    {
        ob->_statusMsg = QString("--this visa event not recognized: %1").arg(eventType);
        emit ob->statusMsgChanged();
        qDebug() << ob->_statusMsg;
    }

    return VI_SUCCESS;
}



void Visa::toVisa_IoProt() {
    ViStatus status;
    char desc[256];

    status = viSetAttribute (_instr, VI_ATTR_IO_PROT, (ViUInt16) _ioProt.toUInt());
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
}

void Visa::toVisa_RsrcLockState() {
    static ViStatus status;
    char desc[256];

    status = viSetAttribute (_instr, VI_ATTR_RSRC_LOCK_STATE, (ViAccessMode) _rsrcLockState.toUInt());
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
}

void Visa::toVisa_TermChar() {
    static ViStatus status;
    char desc[256];

    status = viSetAttribute (_instr, VI_ATTR_TERMCHAR, (ViUInt8) _termChar.toUInt());
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
}

void Visa::toVisa_TermCharEn() {
    ViStatus status;
    char desc[256];

    status = viSetAttribute (_instr, VI_ATTR_TERMCHAR_EN, (ViBoolean) _termCharEn.toInt());
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
}

void Visa::toVisa_TmoValue() {
    ViStatus status;
    char desc[256];

    status = viSetAttribute (_instr, VI_ATTR_TMO_VALUE, (ViUInt32) _tmoValue.toInt());
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
}

QList<qreal> Visa::getRetList(const QString &readFmt, const quint32 &count) {

    ViStatus status;
    char desc[256];
    QList<qreal> retList;
    quint8 *retArray;
    quint32 i;

        retArray = new (std::nothrow) quint8[count];

        if (retArray == nullptr) {
            qDebug() << "Error: memory could not be allocated." << count << "not allocated" << endl;
            delete[] retArray;
            return retList;
        }


    status = viSScanf(_instr, (ViBuf) _buffer, (ViString) readFmt.toLocal8Bit().constData(), retArray);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
    else
    {
        statusUpdate(QString("  getRetList: %1").arg(count));
        statusUpdate(QString("  readFmt: %1").arg((ViString) readFmt.toLocal8Bit().constData()));
        statusUpdate(QString("  buffer: %1 %2 %3 %4 %5 %6 %7").arg(_buffer[0]).arg(_buffer[1]).arg(_buffer[2]).arg(_buffer[3]).arg(_buffer[4]).arg(_buffer[5]).arg(_buffer[6]));
        statusUpdate(QString("  buffer: %1 %2 %3 %4 %5 %6 %7").arg(retArray[0]).arg(retArray[1]).arg(retArray[2]).arg(retArray[3]).arg(retArray[4]).arg(retArray[5]).arg(retArray[6]));
    }
    for (i=0; i<count; i++) {
        retList.append((qreal)retArray[i]);
    }

    return retList;
}

quint32 Visa::getAsrlAvailNum() {
    ViStatus status;
    ViUInt32 aViUInt32;
    char desc[256];

    status = viGetAttribute (_instr, VI_ATTR_ASRL_AVAIL_NUM, &aViUInt32);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
    else
    {
        statusUpdate(QString("  Asrl availNum: %1").arg(aViUInt32));
    }

    return aViUInt32;
}

//void Visa::fromVisa_AsrlAvailNum() {
//    ViStatus status;
//    ViUInt32 aViUInt32;
//    char desc[256];

//    status = viGetAttribute (_instr, VI_ATTR_ASRL_AVAIL_NUM, &aViUInt32);
//    if (status < VI_SUCCESS)
//    {
//        viStatusDesc(_instr, status, desc);
//        _statusMsg = QString("--viGetAttribute for availNum failed: %1").arg(desc);
//    }
//    else
//    {
//        Asrl::_availNum.setNum(aViUInt32);
//        emit Asrl::availNumChanged();
//        _statusMsg = QString("Asrl availNum: ") + Asrl::_availNum;
//    }
//    emit statusMsgChanged();
//    qDebug() << _statusMsg;
//}


//*******************************************************************************************
void Visa::fromVisa_IntfInstName() {
    ViStatus status;
    char outputBuffer[256];
    char desc[256];

    status = viGetAttribute (_instr, VI_ATTR_INTF_INST_NAME, outputBuffer);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
    else
    {
        _intfInstName = QString::fromLocal8Bit(outputBuffer);
        statusUpdate(QString("  Interface instrument name: %1").arg(_intfInstName));
    }
}

// Interface Number
//
// Read only
//
void Visa::fromVisa_IntfNum() {
    ViStatus status;
    ViUInt16 aViUInt16;
    char desc[256];

    status = viGetAttribute (_instr, VI_ATTR_INTF_NUM, &aViUInt16);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
    else
    {
        _intfNum.setNum(aViUInt16);
        statusUpdate(QString("  Interface number: %1").arg(_intfNum));
    }

}

// Interface type
//
// Read only.
//
// The type of interface - GPIB, Serial, USB, TCPIP, etc.
//
// Allowed:
//    VI_INTF_GPIB (1)
//    VI_INTF_VXI (2)
//    VI_INTF_GPIB_VXI (3)
//    VI_INTF_ASRL (4)
//    VI_INTF_PXI (5)
//    VI_INTF_TCPIP (6)
//    VI_INTF_USB (7)
//
void Visa::fromVisa_IntfType() {
    ViStatus status;
    ViUInt16 aViUInt16;
    char desc[256];

    status = viGetAttribute (_instr, VI_ATTR_INTF_TYPE, &aViUInt16);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
    else
    {
        _intfType.setNum(aViUInt16);
        statusUpdate(QString("  Interface type: %1").arg(_intfType));
    }

}

// IO Protocol
//
//    GPIB:  VI_PROT_NORMAL (default)
//    VI_PROT_NORMAL (1)
//    VI_PROT_HS488 (3)
//
//    VXI:  VI_PROT_NORMAL (default)
//    VI_PROT_NORMAL (1)
//    VI_PROT_FDC (2)
//
//    GPIB-VXI:  VI_PROT_NORMAL (default)
//    VI_PROT_NORMAL (1)
//
//    Serial,TCPIP,USB RAW:  VI_PROT_NORMAL (default)
//    VI_PROT_NORMAL (1)
//    VI_PROT_4882_STRS (4)
//
//    USB INSTR:  VI_PROT_NORMAL (default)
//    VI_PROT_NORMAL (1)
//    VI_PROT_USBTMC_VENDOR (5)
//
void Visa::fromVisa_IoProt() {
    ViStatus status;
    ViUInt16 aViUInt16;
    char desc[256];

    status = viGetAttribute (_instr, VI_ATTR_IO_PROT, &aViUInt16);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
    else
    {
        _ioProt.setNum(aViUInt16);
        statusUpdate(QString("  IO Protocol: %1").arg(_ioProt));
    }

}

void Visa::fromVisa_ManfId() {
    ViStatus status;
    char desc[256];
    ViUInt16 aViUInt16;

    status = viGetAttribute (_instr, VI_ATTR_MANF_ID, &aViUInt16);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
    else
    {
        _manfId = (quint16) aViUInt16;
        emit manfIdChanged();
        statusUpdate(QString("  ManfID: %1").arg(_manfId));
    }
}
void Visa::fromVisa_ManfName() {
    ViStatus status;
    char desc[256];
    ViString aViString;

    status = viGetAttribute (_instr, VI_ATTR_MANF_NAME, &aViString);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
    else
    {
        _manfName = QString(QByteArray(aViString));
        emit manfNameChanged();
        statusUpdate(QString("  ManfName: %1").arg(_manfName));
    }
}

void Visa::fromVisa_ModelCode() {
    ViStatus status;
    char desc[256];
    ViUInt16 aViUInt16;

    status = viGetAttribute(_instr, VI_ATTR_MODEL_CODE, &aViUInt16);
    if(status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
    else
    {
        _modelCode = (quint16) aViUInt16;
        emit modelCodeChanged();
        statusUpdate(QString("  ModelCode: %1").arg(_modelCode));
    }
}
void Visa::fromVisa_ModelName() {
    ViStatus status;
    char desc[256];
    ViString aViString;

    status = viGetAttribute (_instr, VI_ATTR_MODEL_NAME, &aViString);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
    else
    {
        _modelName = QString(QByteArray(aViString));
        emit modelNameChanged();
        statusUpdate(QString("  ModelName: %1").arg(_modelName));
    }
}


// Resource class
//
// Read only
//
void Visa::fromVisa_RsrcClass() {
    ViStatus status;
    char outputBuffer[256];
    char desc[256];

    status = viGetAttribute (_instr, VI_ATTR_RSRC_CLASS, outputBuffer);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));

    }
    else
    {
        _rsrcClass = QString::fromLocal8Bit(outputBuffer);
        statusUpdate(QString("  Resource class: %1").arg(_rsrcClass));
    }
}

// Resource Lock State
//
// Status of whether the instrument is available or locked to one user only or sharable.
// VI_NO_LOCK default
// Allowed:
//    VI_NO_LOCK (0)
//    VI_EXCLUSIVE_LOCK (1)
//    VI_SHARED_LOCK (2)
//
void Visa::fromVisa_RsrcLockState(){
    ViStatus status;
    ViAccessMode aViAccessMode;
    char desc[256];

    status = viGetAttribute (_instr, VI_ATTR_RSRC_LOCK_STATE, &aViAccessMode);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
    else
    {
        _rsrcLockState.setNum(aViAccessMode);
        statusUpdate(QString("  Resource lock state: %1").arg(_rsrcLockState));
    }
}

// Resource name
//
// Read only
// Probably  not used; only as a set and verify.
//
void Visa::fromVisa_RsrcName(){
    ViStatus status;
    ViRsrc aViRsrc;
    char desc[256];

    status = viGetAttribute (_instr, VI_ATTR_RSRC_NAME, &aViRsrc);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
    else
    {
        _rsrcName = QString::fromLocal8Bit(aViRsrc);
        statusUpdate(QString("  Resource class: %1").arg(_rsrcName));
    }
}

// TCPIP address
//
void Visa::fromVisa_TcpipAddr(){
    ViStatus status;
    char outputBuffer[256];
    char desc[256];

    status = viGetAttribute (_instr, VI_ATTR_TCPIP_ADDR, outputBuffer);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));

    }
    else
    {
        tcpip()->setAddr(QString::fromLocal8Bit(outputBuffer));
        statusUpdate(QString("  Tcpip address: %1").arg(tcpip()->addr()));
    }
}

// TCPIP Hostname
//
void Visa::fromVisa_TcpipHostname() {
    ViStatus status;
    char outputBuffer[256];
    char desc[256];

    status = viGetAttribute (Visa::_instr, VI_ATTR_TCPIP_HOSTNAME, outputBuffer);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));

    }
    else
    {
        tcpip()->setHostname(QString::fromLocal8Bit(outputBuffer));
        statusUpdate(QString("  Tcpip host name: %1").arg(tcpip()->hostname()));
    }
}

// TCPIP port
//
// Read only
//
void Visa::fromVisa_TcpipPort() {
    ViStatus status;
    ViUInt16 aViUInt16;
    char desc[256];

    status = viGetAttribute (Visa::instr(), VI_ATTR_TCPIP_PORT, &aViUInt16);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(Visa::instr(), status, desc);
        statusUpdate(QString("  --%1").arg(desc));

    }
    else
    {
        tcpip()->setPort(QString("%1").arg(aViUInt16));
        statusUpdate(QString("  Tcpip port: %1").arg(tcpip()->port()));
    }
}

// Termination character
//
// 0xA default
// Anything allowed
//
void Visa::fromVisa_TermChar() {
    ViStatus status;
    ViUInt8 aViUInt8;
    char desc[256];

    status = viGetAttribute (_instr, VI_ATTR_TERMCHAR, &aViUInt8);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));

    }
    else
    {
        _termChar.setNum(aViUInt8);
        statusUpdate(QString("  Termination character: %1").arg(_termChar));
    }
}

// Termination character enable
//
// Specify that the read operation should terminate when a termination
// character is received.
//      VI_FALSE (0) default
// Allowed:
//      VI_TRUE (1)
//      VI_FALSE (0)
//
void Visa::fromVisa_TermCharEn() {
    ViStatus status;
    ViBoolean aViBoolean;
    char desc[256];

    status = viGetAttribute (_instr, VI_ATTR_TERMCHAR_EN, &aViBoolean);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
    else
    {
        _termCharEn.setNum(aViBoolean);
        statusUpdate(QString("  Termination character enable: %1").arg(_termCharEn));
    }
}

// Timeout
//
// 2000 default
// Allowed:
//    VI_TMO_IMMEDIATE (0)
//    1 to FFFFFFFEh;
//    VI_TMO_INFINITE  (FFFFFFFFh)
//
void Visa::fromVisa_TmoValue() {
    ViStatus status;
    ViUInt32 aViUInt32;
    char desc[256];

    status = viGetAttribute (_instr, VI_ATTR_TMO_VALUE, &aViUInt32);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        statusUpdate(QString("  --%1").arg(desc));
    }
    else
    {
        _tmoValue.setNum(aViUInt32);
        statusUpdate(QString("  Timeout: %1").arg(_tmoValue));
    }
}



