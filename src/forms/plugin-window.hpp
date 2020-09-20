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
#include "ui_plugin-window.h"
#include <QDialog>
#include <QtWidgets>
#include <vector>
enum pairs { Scene, Source, Item, Transition, Audio, Media, Filter };

class PluginWindow : public QDialog {
  Q_OBJECT

public:
  PluginWindow(QWidget *parent);
  void SetAvailableDevices();
  ~PluginWindow();
  void ShowPair(pairs);
  void HidePair(pairs);
  void HideAllPairs();
  void add_midi_device(QString Name);
  void set_headers();
public slots:
  void SetStatus(QString label, QString Status);
  QLabel *GetLabel(QString label);
  void refresh();
private Q_SLOTS:
  void ToggleShowHide();

private:
  Ui::PluginWindow *ui;
  void get_scene_names();
  QStringList SceneList;
};
