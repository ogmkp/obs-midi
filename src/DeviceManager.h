#pragma once
#include "RtMidi17/rtmidi17.hpp"
#include <QObject>
enum Status { Error, Connected, Disconnected, Detached, Attached, Disabled, Connecting };
class Device : public QObject {
  Q_OBJECT
public:
  Device();
  ~Device();
  QString name;
  bool enabled;
  bool feedback_enabled;
  QString feedback_name;
  Status status;
  Status feedback_status;
private:
  void connect();
  void disconnect();
  rtmidi::midi_in midi_in;
  rtmidi::midi_out midi_out;
signals:
  void message(rtmidi::message);
};

class DeviceManager : public QObject {
  Q_OBJECT
public:
  DeviceManager();
  ~DeviceManager();
  void add_new_device(QString name);
  void append_device();
  void edit_device();
  void delete_device();
  void load_devices_from_config();
  void save_devices_to_config();
  void refresh_device_list();
  QList<Device*> GetDevices() { return Devices; };
signals:
  void message_received(rtmidi::message);
public slots:
  void send_message(rtmidi::message);

private:
	rtmidi::midi_in* in;
	rtmidi::midi_out* out;
	int portCount=-1;
	QList<Device*> Devices;
  bool does_device_exist_in_list(QString name);
};
