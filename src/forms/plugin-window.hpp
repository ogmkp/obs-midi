/*
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#pragma once
#include "../DeviceManager.h"
#include "../obs-midi.h"
#include "../utils.h"
#include "ui_plugin-window.h"
#include <QDialog>
#include <QtWidgets>
#include <obs-data.h>
#include <obs-module.h>
#include <vector>
enum pairs { Scene, Source, Item, Transition, Audio, Media, Filter };
class PluginWindow : public QDialog {
  Q_OBJECT

public:
  PluginWindow(QWidget *parent);
  ~PluginWindow();
  void ShowPair(pairs);
  void HidePair(pairs);
  void HideAllPairs();
  void add_midi_device(QString Name);
  void set_headers();
  void set_table_device_status(int row, Status status);
public slots:
	void SetAvailableDevices();

  void status_changed(Device *device, Status status);
  QColor get_status_color(Status status);
  QString get_status_string(Status status);
  void refresh();
  void itemChanged(QTableWidgetItem *);

private Q_SLOTS:
  void ToggleShowHide();

private:
	bool deviceExist(QString name); 
  bool startup = true;
  Ui::PluginWindow *ui;
  DeviceManager *DM;
  void get_scene_names();
  QStringList SceneList;
};
