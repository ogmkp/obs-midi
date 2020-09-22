#include "DeviceManager.h"
#include "obs-midi.h"
/// <summary>
/// Device Class
///
/// </summary>
Device::Device() {}
Device::~Device() {}
void Device::connect() {}
void Device::disconnect() {}

/// <summary>
/// Device Manager Class
/// </summary>
DeviceManager::DeviceManager() {
  in = new rtmidi::midi_in();
  out = new rtmidi::midi_out();
  portCount = in->get_port_count();
  setup_device_status_poller();
}
DeviceManager::~DeviceManager() {}
void DeviceManager::add_new_device(QString device_name) {
  Device *newdevice = new Device();
  newdevice->name = device_name;
  newdevice->enabled = false;
  newdevice->feedback_enabled = false;
  newdevice->feedback_name = "";
  newdevice->status = Status::Disabled;
  connect(this, SIGNAL(do_device_poll()), newdevice, SLOT(poll()));
  Devices.append(newdevice);


}

Device *DeviceManager::get_device_by_name(QString name) {
  for (int i = 0; i < Devices.count(); i++) {
    if (Devices.value(i)->name == name) {
      return Devices.at(i);
    }
  }
}
void DeviceManager::append_device() {}
void DeviceManager::edit_device() {}
void DeviceManager::delete_device() {}
void DeviceManager::load_devices_from_config() {}
void DeviceManager::refresh_device_list() {

  for (int i = 0; i < in->get_port_count(); i++) {
      if (!is_device_in_config(QString::fromStdString(in->get_port_name(i)))) {
          add_new_device(QString::fromStdString(in->get_port_name(i)));
      }
  }
}
void DeviceManager::send_message(rtmidi::message) {}

bool DeviceManager::is_device_in_config(QString name) {
    
    for (int i = 0; i < Devices.count(); i++) {
        if (Devices.at(i)->name == name) {
            return true;
        }
    }
    return false;
}
bool DeviceManager::does_device_exist_in_list(QString name) {
  for (int i = 0; i < in->get_port_count(); i++) {
    if (QString::fromStdString(in->get_port_name(i)) == name) {
      return true;
    }
  }
  return false;
}

void DeviceManager::setup_device_status_poller() {
  /// <summary>
  /// Poll All Devices for status every 2 seconds
  /// </summary>
  device_status_poller = new QTimer();
  device_status_poller->setInterval(2000);
  connect(device_status_poller, SIGNAL(timeout()), this, SLOT(poll_devices()));
  device_status_poller->start();
}

void DeviceManager::poll_devices() {
    emit(do_device_poll());
    portCount = in->get_port_count();
    refresh_device_list();
  for (int i = 0; i < Devices.count(); i++) {
      Device *dev = Devices.at(i);

    emit(status_changed(
        dev,
        dev->status));

  }
}
int Device::get_in_port_by_name(QString name) {
    for (int i = 0; i < midi_in.get_port_count(); i++) {
        if (QString::fromStdString(midi_in.get_port_name())== name) {
            return i;
        }
    }
}
int Device::get_out_port_by_name(QString name) {
    for (int i = 0; i < midi_out.get_port_count(); i++) {
        if (QString::fromStdString(midi_in.get_port_name()) == name) {
            return i;
        }
    }
}
void Device::poll() {
    blog(LOG_DEBUG, "Device Poll -- Device");
    if (enabled) {
        try {
            if (midi_in.is_port_open()) {
                status = Status::Connected;
            }
            else {
                midi_in.open_port(get_in_port_by_name(name));
                status = Status::Disconnected;
            }
        }
        catch (...) {
            status = Status::Unplugged;
        }
    }
    else {
        status = Status::Disabled;
        midi_in.close_port();
    }
    if (feedback_enabled) {
        try {
            if (midi_out.is_port_open()) {
                feedback_status = Status::Connected;
            }
            else {
                feedback_status = Status::Disconnected;
                midi_out.open_port(get_out_port_by_name(feedback_name));
            }
        }
        catch (...) {
            feedback_status = Status::Unplugged;
        }
    }
    else {
        feedback_status = Status::Disabled;
        midi_out.close_port();
    }
}
void Device::set_enabled(bool en) {
    enabled = en;
}