#pragma once
#include "RtMidi17/rtmidi17.hpp"
#include <QObject>
#include <QTimer>
enum Status { Error, Connected, Disconnected, Unplugged,  Disabled };
class Device : public QObject {
  Q_OBJECT
public:
  Device();
  ~Device();
  QString name;
  bool enabled;
  void set_enabled(bool);
  bool feedback_enabled;
  QString feedback_name;
  Status status;
  Status feedback_status;
public slots:
	void poll();
private:
  void connect();
  void disconnect();
  int get_in_port_by_name(QString name);
  int get_out_port_by_name(QString name);
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
  Device* get_device_by_name(QString name);
  QList<Device*> GetDevices() { return Devices; };
signals:
  void message_received(rtmidi::message);
  void status_changed(Device* device, Status status);
  void do_device_poll();
public slots:
  void send_message(rtmidi::message);

private:
	QTimer *device_status_poller;
	void setup_device_status_poller();
	rtmidi::midi_in* in;
	rtmidi::midi_out* out;
	int portCount=-1;
	QList<Device*> Devices;
  bool does_device_exist_in_list(QString name);
  bool is_device_in_config(QString name);
private slots:
	void poll_devices();

};
