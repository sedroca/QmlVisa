#include "qmlvisaResourceManager.h"


VisaResourceManager::VisaResourceManager(QQuickItem *parent):
    QQuickItem(parent)
{
    static ViStatus status;
    ViChar desc[256];
    /*
     * First we must call viOpenDefaultRM to get the resource manager
     * handle.  We will store this handle in _defaultRM which is
     * a private variable for this class.
     */
    status=viOpenDefaultRM (&_defaultRM);
    //printf("Status from open resource manager: %d\n",status);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_defaultRM, status, desc);
        _statusMsg = QString("Could not open a session to the VISA Resource Manager. %1").arg(desc);
        qDebug() << _statusMsg;
        emit statusMsgChanged();

    }
    else
    {
        _resourceList += "Find Resources";
        _statusMsg = QString("VISA Resource Manager opened");
        qDebug() << _statusMsg;
        emit statusMsgChanged();
    }

}

VisaResourceManager::~VisaResourceManager()
{
    static ViStatus status;
    //  close the resource manager
    status = viClose (_defaultRM);
    _defaultRM = -1;
}

QStringList VisaResourceManager::findResource()
{
    static char instrDescriptor[VI_FIND_BUFLEN];
    static ViUInt32 numInstrs;
    static ViFindList findList;
    static ViStatus status;
    static ViSession instr;
    static QStringList instrList;
    QString qExpr;
    QByteArray qbaExpr;
    int countme;
    ViChar desc[256];
    char outputBuffer[256];
    QString qIntfInstName;

    // clear the instrument list
    instrList.clear();
    /*
     * Find all the VISA resources in our system and store the number of resources
     * in the system in numInstrs.  Notice the different query descriptions a
     * that are available.

        Interface         Expression
    --------------------------------------
        GPIB              "GPIB[0-9]*::?*INSTR"
        VXI               "VXI?*INSTR"
        GPIB-VXI          "GPIB-VXI?*INSTR"
        Any VXI           "?*VXI[0-9]*::?*INSTR"
        Serial            "ASRL[0-9]*::?*INSTR"
        PXI               "PXI?*INSTR"
        All instruments   "?*INSTR"
        All resources     "?*"
    */

    qExpr = "?*";
    qbaExpr = qExpr.toLatin1();
    status = viFindRsrc (_defaultRM, (ViString) qbaExpr.constData(), &findList, &numInstrs, instrDescriptor);
    if (status < VI_SUCCESS)
    {
        viStatusDesc(_defaultRM, status, desc);
        _statusMsg = QString("%1").arg(desc);
        emit statusMsgChanged();
        qDebug() << _statusMsg;
        //        viClose (_defaultRM);
    }
    else
    {
        viStatusDesc(_defaultRM, status, desc);
        _statusMsg = QString("%1").arg(desc);
        emit statusMsgChanged();
        qDebug() << _statusMsg;
    }

    // Check how many resources
    //
    if (numInstrs == 0) {
        instrList += "No Resources Found";
        _statusMsg = QString("No resources found");
        emit statusMsgChanged();
        qDebug() << _statusMsg;
    }
    else  // resources were found
    {
        _statusMsg = QString("%1 instruments, serial ports, and other resources found").arg(numInstrs);
        emit statusMsgChanged();
        qDebug() << _statusMsg;

        _statusMsg = QString("First resource: %1 ").arg(instrDescriptor);
        emit statusMsgChanged();
        qDebug() << _statusMsg;

        // add first instrument to list
        instrList += instrDescriptor;

        status = viOpen (_defaultRM, instrDescriptor, VI_NULL, VI_NULL, &instr);
        if (status < VI_SUCCESS)
        {
            viStatusDesc(_defaultRM, status, desc);
            _statusMsg = QString("An error occurred opening a session to the resource %1: %2 ").arg(instrDescriptor).arg(desc);
            emit statusMsgChanged();
            qDebug() << _statusMsg;
        }
        else  // get some more information about the resource
        {
            // Interface Instrument Name
            //
            // Read only
            //
            status = viGetAttribute (instr, VI_ATTR_INTF_INST_NAME, outputBuffer);
            if (status < VI_SUCCESS)
            {
                viStatusDesc(instr, status, desc);
                _statusMsg = QString("--viGetAttribute for intfInstName failed: %1").arg(desc);
            }
            else
            {
                qIntfInstName = QString::fromLocal8Bit(outputBuffer);
                _statusMsg = QString("Interface instrument name: ")+ qIntfInstName;
            }
            emit statusMsgChanged();
            qDebug() << _statusMsg;
            viClose (instr);
        }


        countme = numInstrs;
        while (--countme)
        {
            //            _statusMsg = QString("%1 instruments left").arg(countme);
            //            emit statusMsgChanged();
            //            qDebug() << _statusMsg;

            /* stay in this loop until we find all instruments */
            status = viFindNext (findList, instrDescriptor);  /* find next desriptor */
            if (status < VI_SUCCESS)
            {
                viStatusDesc(_defaultRM, status, desc);
                _statusMsg = QString("An error occurred finding the next resource: %1").arg(desc);
                emit statusMsgChanged();
                qDebug() << _statusMsg;
            }
            else
            {
                _statusMsg = QString("Next resource: %1").arg(instrDescriptor);
                emit statusMsgChanged();
                qDebug() << _statusMsg;

                // add next instrument to list
                instrList += instrDescriptor;

                /* Now we will open a session to the instrument we just found */
                status = viOpen (_defaultRM, instrDescriptor, VI_NULL, VI_NULL, &instr);
                if (status < VI_SUCCESS)
                {
                    viStatusDesc(_defaultRM, status, desc);
                    _statusMsg = QString("An error occurred opening a session to the resource %1: %2").arg(instrDescriptor).arg(desc);
                    emit statusMsgChanged();
                    qDebug() << _statusMsg;
                }
                else
                {
                    // Interface Instrument Name
                    //
                    // Read only
                    //
                    status = viGetAttribute (instr, VI_ATTR_INTF_INST_NAME, outputBuffer);
                    if (status < VI_SUCCESS)
                    {
                        viStatusDesc(instr, status, desc);
                        _statusMsg = QString("--viGetAttribute for intfInstName failed: %1").arg(desc);
                    }
                    else
                    {
                        qIntfInstName = QString::fromLocal8Bit(outputBuffer);
                        _statusMsg = QString("Interface instrument name: ")+ qIntfInstName;
                    }
                    emit statusMsgChanged();
                    qDebug() << _statusMsg;

                    /* Now close the session we just opened.                            */
                    /* In actuality, we would probably use an attribute to determine    */
                    /* if this is the instrument we are looking for.                    */
                    viClose (instr);
                }
            }
        }    /* end while */
    } /* end if */
    status = viClose(findList);
    if (instrList != _resourceList)
    {
        _resourceList = instrList;
        emit resourceListChanged();
    }
    return instrList;
}

// Resource manager - Resource list property read
//
QStringList VisaResourceManager::resourceList()
{
    return _resourceList;
}

// Resource manager - Expr property read
//
QString VisaResourceManager::expr()
{
    return _expr;
}

// Resource Manager - Expr property write
//
void VisaResourceManager::setExpr(const QString &ex)
{

    if (ex != _expr) {
        _expr = ex;
        emit exprChanged();
    }
}

// ResourceManager - StatusMsg property read
//
QString VisaResourceManager::statusMsg()
{
    return _statusMsg;
}


