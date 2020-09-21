#include "DeviceManager.h"

/// <summary>
/// Device Class
/// 
/// </summary>
Device::Device() {
}
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
	refresh_device_list();
}
DeviceManager::~DeviceManager() {}
void DeviceManager::add_new_device(QString device_name) {
		Device *newdevice = new Device();
		newdevice->name = device_name;
		newdevice->enabled = false;
		newdevice->feedback_enabled = false;
		newdevice->feedback_name = "";
		newdevice->status = Status::Disabled;
		Devices.append(newdevice);
}
void DeviceManager::append_device() {}
void DeviceManager::edit_device() {}
void DeviceManager::delete_device() {}
void DeviceManager::load_devices_from_config() {}
void DeviceManager::refresh_device_list() {
	for (int i = 0; i < in->get_port_count(); i++) {
		add_new_device(QString::fromStdString(in->get_port_name(i)));
	}
}
void DeviceManager::send_message(rtmidi::message) {}
bool DeviceManager::does_device_exist_in_list(QString name) {
	for (int i = 0; i < in->get_port_count(); i++) {
		if (QString::fromStdString(in->get_port_name(i)) == name) {
			return true;
		}
	}
	return false;
}




