#pragma once
//Core Class for OBS-MIDI plugin
#include <qobject.h>
#include "Device_Manager.hpp"
class OBSMIDI :
    public QObject
{
    Q_OBJECT
public:
    OBSMIDI();
    ~OBSMIDI();
    Device_Manager *deviceManager;
};

