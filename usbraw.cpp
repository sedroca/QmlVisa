#include "usbraw.h"

UsbRaw::UsbRaw(QQuickItem *parent) :
    QQuickItem(parent)
{
}

void UsbRaw::setInstr(const ViSession instr) {
    _instr = instr;
}

bool UsbRaw::connected() {
    return _connected;
}

void UsbRaw::setConnected(const bool &rn) {
    _connected = rn;
}

qint16     UsbRaw::bulkInPipe() {return _bulkInPipe;}
void UsbRaw::setBulkInPipe(const qint16 &rn) {
    if (rn != _bulkInPipe) {
        _bulkInPipe = rn;
        emit bulkInPipeChanged();
    }
}

UsbRaw::Pipe        UsbRaw::bulkInStatus() {return _bulkInStatus;}
void UsbRaw::setBulkInStatus(const Pipe &rn) {
    if (rn != _bulkInStatus) {
        _bulkInStatus = rn;
        emit bulkInStatusChanged();
    }
}

qint16     UsbRaw::bulkOutPipe() {return _bulkOutPipe;}
void UsbRaw::setBulkOutPipe(const qint16 &rn) {
    if (rn != _bulkOutPipe) {
        _bulkOutPipe = rn;
        emit bulkOutPipeChanged();
    }
}

UsbRaw::Pipe        UsbRaw::bulkOutStatus() {return _bulkOutStatus;}
void UsbRaw::setBulkOutStatus(const Pipe &rn) {
    if (rn != _bulkOutStatus) {
        _bulkOutStatus = rn;
        emit bulkOutStatusChanged();
    }
}

qint16     UsbRaw::classUsed() {return _classUsed;}
void UsbRaw::setClassUsed(const qint16 &rn) {
    if (rn != _classUsed) {
        _classUsed = rn;
        emit classUsedChanged();
    }
}

qint16     UsbRaw::intfcNum() {return _intfcNum;}
void UsbRaw::setIntfcNum(const qint16 &rn) {
    if (rn != _intfcNum) {
        _intfcNum = rn;
        emit intfcNumChanged();
    }
}

qint16 UsbRaw::intrInPipe() {return _intrInPipe;}
void UsbRaw::setIntrInPipe(const qint16 &rn) {
    if (rn != _intrInPipe) {
        _intrInPipe = rn;
        emit intrInPipeChanged();
    }
}

UsbRaw::Pipe        UsbRaw::intrInStatus() {return _intrInStatus;}
void UsbRaw::setIntrInStatus(const Pipe &rn) {
    if (rn != _intrInStatus) {
        _intrInStatus = rn;
        emit intrInStatus();
    }
}

quint16 UsbRaw::maxIntrSize() {return _maxIntrSize;}
void UsbRaw::setMaxIntrSize(const quint16 &rn) {
    if (rn != _maxIntrSize) {
        _maxIntrSize = rn;
        emit maxIntrSize();
    }
}

qint16 UsbRaw::numIntfcs() {return _numIntfcs;}
void UsbRaw::setNumIntfcs(const qint16 &rn) {
    if (rn != _numIntfcs) {
        _numIntfcs = rn;
        emit numIntfcsChanged();
    }
}

qint16 UsbRaw::numPipes() {return _numPipes;}
void UsbRaw::setNumPipes(const qint16 &rn) {
    if (rn != _numPipes) {
        _numPipes = rn;
        emit numPipesChanged();
    }
}

qint16 UsbRaw::protocol() {return _protocol;}
void UsbRaw::setProtocol(const qint16 &rn) {
    if (rn != _protocol) {
        _protocol = rn;
        emit protocolChanged();
    }
}

quint8 *UsbRaw::recvIntrData() {return _recvIntrData;}
void UsbRaw::setRecvIntrData(quint8* &rn) {
    if (rn != _recvIntrData) {
        _recvIntrData = rn;
        emit recvIntrDataChanged();
    }
}

quint16 UsbRaw::recvIntrSize() {return _recvIntrSize;}
void UsbRaw::setRecvIntrSize(const quint16 &rn) {
    if (rn != _recvIntrSize) {
        _recvIntrSize = rn;
        emit recvIntrSizeChanged();
    }
}

QString UsbRaw::serialNum() {return _serialNum;}
void UsbRaw::setSerialNum(const QString &rn) {
    if (rn != _serialNum) {
        _serialNum = rn;
        emit serialNumChanged();
    }
}

qint16 UsbRaw::subclass() {return _subclass;}
void UsbRaw::setSubclass(const qint16 &rn) {
    if (rn != _subclass) {
        _subclass = rn;
        emit subclassChanged();
    }
}


bool    UsbRaw::bulkInPipeWasSet() {return _bulkInPipeWasSet;}
void UsbRaw::setBulkInPipeWasSet(const bool &rn) {_bulkInPipeWasSet = rn;}

bool    UsbRaw::bulkInStatusWasSet() {return _bulkInStatusWasSet;}
void UsbRaw::setBulkInStatusWasSet(const bool &rn) {_bulkInStatusWasSet = rn;}

bool    UsbRaw::bulkOutPipeWasSet() {return _bulkOutPipeWasSet;}
void UsbRaw::setBulkOutPipeWasSet(const bool &rn) {_bulkOutPipeWasSet = rn;}

bool    UsbRaw::bulkOutStatusWasSet() {return _bulkOutStatusWasSet;}
void UsbRaw::setBulkOutStatusWasSet(const bool &rn) {_bulkOutStatusWasSet = rn;}

bool    UsbRaw::intrInPipeWasSet() {return _intrInPipeWasSet;}
void UsbRaw::setIntrInPipeWasSet(const bool &rn) {_intrInPipeWasSet = rn;}

bool    UsbRaw::intrInStatusWasSet() {return _intrInStatusWasSet;}
void UsbRaw::setIntrInStatusWasSet(const bool &rn) {_intrInStatusWasSet = rn;}

bool    UsbRaw::maxIntrSizeWasSet() {return _maxIntrSizeWasSet;}
void UsbRaw::setMaxIntrSizeWasSet(const bool &rn) {_maxIntrSizeWasSet = rn;}

void UsbRaw::toVisa_BulkInPipe() {
    ViStatus status;
    char desc[256];

    status = viSetAttribute(_instr, VI_ATTR_USB_BULK_IN_PIPE, (ViInt16) bulkInPipe());
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
}

void UsbRaw::fromVisa_BulkInPipe() {
    ViStatus status;
    ViInt16 aViInt16;
    char desc[256];

    status = viGetAttribute(_instr, VI_ATTR_USB_BULK_IN_PIPE, &aViInt16);
    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setBulkInPipe((qint16) aViInt16);  // emits signal if a new value
    }
}




void UsbRaw::toVisa_BulkInStatus() {
    ViStatus status;
    char desc[256];

    status = viSetAttribute(_instr, VI_ATTR_USB_BULK_IN_STATUS, (ViInt16) bulkInStatus());

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
}

void UsbRaw::fromVisa_BulkInStatus() {
    ViStatus status;
    ViInt16 aViInt16;
    char desc[256];

    status = viGetAttribute(_instr, VI_ATTR_USB_BULK_IN_STATUS, &aViInt16);

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setBulkInStatus((Pipe) aViInt16);
    }
}

void UsbRaw::toVisa_BulkOutPipe() {
    ViStatus status;
    char desc[256];

    status = viSetAttribute(_instr, VI_ATTR_USB_BULK_OUT_PIPE, (ViInt16) bulkOutPipe());

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
}

void UsbRaw::fromVisa_BulkOutPipe() {
    ViStatus status;
    ViInt16 aViInt16;
    char desc[256];

    status = viGetAttribute(_instr, VI_ATTR_USB_BULK_OUT_PIPE, &aViInt16);

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setBulkOutPipe((qint16) aViInt16);
    }

}

void UsbRaw::toVisa_BulkOutStatus() {
    ViStatus status;
    char desc[256];

    status = viSetAttribute(_instr, VI_ATTR_USB_BULK_OUT_STATUS, (ViInt16) bulkOutStatus());

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
}

void UsbRaw::fromVisa_BulkOutStatus() {
    ViStatus status;
    ViInt16 aViInt16;
    char desc[256];

    status = viGetAttribute(_instr, VI_ATTR_USB_BULK_OUT_STATUS, &aViInt16);

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setBulkOutStatus((Pipe) aViInt16);
    }
}


void UsbRaw::fromVisa_ClassUsed() {
    ViStatus status;
    ViInt16 aViInt16;
    char desc[256];

    status = viGetAttribute(_instr, VI_ATTR_USB_CLASS, &aViInt16);

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setClassUsed((qint16) aViInt16);
    }
}


void UsbRaw::fromVisa_IntfcNum() {
    ViStatus status;
    ViInt16 aViInt16;
    char desc[256];

    status = viGetAttribute(_instr, VI_ATTR_USB_INTFC_NUM, &aViInt16);

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setIntfcNum((qint16) aViInt16);
    }

}


void UsbRaw::toVisa_IntrInPipe() {
    ViStatus status;
    char desc[256];

    status = viSetAttribute(_instr, VI_ATTR_USB_INTR_IN_PIPE,(ViInt16) intrInPipe());

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }


}

void UsbRaw::fromVisa_IntrInPipe() {
    ViStatus status;
    char desc[256];
    ViInt16 aViInt16;

    status = viGetAttribute(_instr, VI_ATTR_USB_INTR_IN_PIPE, &aViInt16);

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setIntrInPipe((qint16) aViInt16);
    }
}


void UsbRaw::toVisa_IntrInStatus() {
    ViStatus status;
    char desc[256];

    status = viSetAttribute(_instr, VI_ATTR_USB_INTR_IN_STATUS,(ViInt16) intrInStatus());

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
}

void UsbRaw::fromVisa_IntrInStatus() {
    ViStatus status;
    char desc[256];
    ViInt16 aViInt16;

    status = viGetAttribute(_instr, VI_ATTR_USB_INTR_IN_STATUS, &aViInt16);

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setIntrInStatus((Pipe) aViInt16);
    }
}

void UsbRaw::toVisa_MaxIntrSize() {
    ViStatus status;
    char desc[256];

    status = viSetAttribute(_instr, VI_ATTR_USB_MAX_INTR_SIZE, (ViUInt16) maxIntrSize());

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
}

void UsbRaw::fromVisa_MaxIntrSize() {
    ViStatus status;
    char desc[256];
    ViUInt16 aViUInt16;

    status = viGetAttribute(_instr, VI_ATTR_USB_MAX_INTR_SIZE, &aViUInt16);

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setMaxIntrSize((quint16) aViUInt16);
    }

}


void UsbRaw::fromVisa_NumIntfcs() {
    ViStatus status;
    char desc[256];
    ViInt16 aViInt16;

    status = viGetAttribute(_instr, VI_ATTR_USB_NUM_INTFCS, &aViInt16);

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setMaxIntrSize((qint16) aViInt16);
    }

}

void UsbRaw::fromVisa_NumPipes() {
    ViStatus status;
    char desc[256];
    ViInt16 aViInt16;

    status = viGetAttribute(_instr, VI_ATTR_USB_NUM_PIPES, &aViInt16);

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setNumPipes((qint16) aViInt16);
    }
}

void UsbRaw::fromVisa_Protocol() {
    ViStatus status;
    char desc[256];
    ViInt16 aViInt16;

    status = viGetAttribute(_instr, VI_ATTR_USB_PROTOCOL, &aViInt16);

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setProtocol((qint16) aViInt16);
    }
}

void UsbRaw::fromVisa_RecvIntrData() {
    ViStatus status;
    char desc[256];
    ViAUInt8 aViAUInt8;

    // to do:  dimension buffer to be of size RevIntrSize
    // maybe allocate buffer at runtime to size usbRaw->recvIntrSize()
    // after reading the fromVisa_UsbRawRecvIntrSize() which sets the value.
    //
    status = viGetAttribute(_instr, VI_ATTR_USB_RECV_INTR_DATA, &aViAUInt8);

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setRecvIntrData((quint8 *) aViAUInt8);
    }
}

void UsbRaw::fromVisa_RecvIntrSize() {
    ViStatus status;
    char desc[256];
    ViUInt16 aViUInt16;

    status = viGetAttribute(_instr, VI_ATTR_USB_RECV_INTR_SIZE, &aViUInt16);

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setRecvIntrSize((quint16) aViUInt16);
    }
}

void UsbRaw::fromVisa_SerialNum() {
    ViStatus status;
    char desc[256];
    char serNum[256];

    status = viGetAttribute(_instr, VI_ATTR_USB_SERIAL_NUM, (ViString) serNum);

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setSerialNum(QString(QByteArray(serNum)));
    }
}

void UsbRaw::fromVisa_Subclass() {
    ViStatus status;
    char desc[256];
    ViInt16 aViInt16;

    status = viGetAttribute(_instr, VI_ATTR_USB_SUBCLASS, &aViInt16);

    if (status < VI_SUCCESS) {
        viStatusDesc(_instr, status, desc);
        emit statusUpdate(QString("  --%1").arg(desc));
    }
    else {
        setSubclass((qint16) aViInt16);
    }
}


