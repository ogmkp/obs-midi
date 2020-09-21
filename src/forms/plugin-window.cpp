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

#include <obs-frontend-api.h>


#include "plugin-window.hpp"

PluginWindow::PluginWindow(QWidget *parent) : ui(new Ui::PluginWindow) {
  ui->setupUi(this);
  DM = new DeviceManager();
  HideAllPairs();
  ShowPair(pairs::Scene);
  ShowPair(pairs::Audio);
  blog(LOG_DEBUG, "Plugin window started");
  SetStatus("input", Status::Error);
  SetStatus("output", Status::Connected);
}
void PluginWindow::refresh() {
  get_scene_names();
  SetAvailableDevices();

  ui->cb_obs_output_scene->clear();
  ui->cb_obs_output_scene->addItems(SceneList);
  ui->cb_obs_output_audio_source->clear();
  ui->cb_obs_output_audio_source->addItems(Utils::GetAudioSourceNames());
}
void PluginWindow::get_scene_names() {
  obs_frontend_source_list sceneList = {};
  obs_frontend_get_scenes(&sceneList);
  for (size_t i = 0; i < sceneList.sources.num; i++) {
    SceneList.append(obs_source_get_name(sceneList.sources.array[i]));
  }
  obs_frontend_source_list_free(&sceneList);
}
void PluginWindow::add_midi_device(QString name) {
    blog(LOG_DEBUG, "Adding Midi Device %s", name.toStdString().c_str());
  QTableWidgetItem *device_name = new QTableWidgetItem();
  QTableWidgetItem *device_enabled = new QTableWidgetItem();
  QTableWidgetItem *device_status = new QTableWidgetItem();
  QTableWidgetItem *feedback_enabled = new QTableWidgetItem();
  QTableWidgetItem *feedback_name = new QTableWidgetItem();
  QTableWidgetItem *feedback_status = new QTableWidgetItem();
  int rowcount = this->ui->table_device->rowCount();
  this->ui->table_device->insertRow(rowcount);
  device_name->setText(name);
  device_enabled->setCheckState(Qt::Unchecked);
  device_status->setText(QString("Disconnected"));
  device_status->setTextColor("grey");
  feedback_name->setText("");
  feedback_enabled->setCheckState(Qt::Unchecked);
  feedback_status->setText(QString("unset"));
  this->ui->table_device->setItem(rowcount, 0, device_name);
  this->ui->table_device->setItem(rowcount, 1, device_enabled);
  this->ui->table_device->setItem(rowcount, 2, device_status);
  this->ui->table_device->setItem(rowcount, 3, feedback_enabled);
  this->ui->table_device->setItem(rowcount, 4, feedback_name);
  this->ui->table_device->setItem(rowcount, 5, feedback_status);
}
void PluginWindow::set_headers() {
  ui->table_device->setHorizontalHeaderLabels(
      {"Name", "Enabled", "Status", "Feedback Enabled", "Feedback Port",
       "Feedback Status"});
}
PluginWindow::~PluginWindow() { delete ui; }

void PluginWindow::ShowPair(pairs Pair) {
  switch (Pair) {
  case pairs::Scene:
    ui->label_obs_output_scene->show();
    ui->cb_obs_output_scene->show();
    break;
  case pairs::Source:
    ui->label_obs_output_source->show();
    ui->cb_obs_output_source->show();
    break;
  case pairs::Filter:
    ui->label_obs_output_filter->show();
    ui->cb_obs_output_filter->show();
    break;
  case pairs::Transition:
    ui->label_obs_output_transition->show();
    ui->cb_obs_output_transition->show();
    break;
  case pairs::Item:
    ui->label_obs_output_item->show();
    ui->cb_obs_output_item->show();
    break;
  case pairs::Audio:
    ui->label_obs_output_audio_source->show();
    ui->cb_obs_output_audio_source->show();
    break;
  case pairs::Media:
    ui->label_obs_output_media_source->show();
    ui->cb_obs_output_media_source->show();
    break;
  }
}
void PluginWindow::HidePair(pairs Pair) {
  switch (Pair) {
  case pairs::Scene:
    ui->label_obs_output_scene->hide();
    ui->cb_obs_output_scene->hide();
    blog(LOG_DEBUG, "Hide Scene");
    break;
  case pairs::Source:
    ui->label_obs_output_source->hide();
    ui->cb_obs_output_source->hide();
    blog(LOG_DEBUG, "Hide Source");
    break;
  case pairs::Filter:
    ui->label_obs_output_filter->hide();
    ui->cb_obs_output_filter->hide();
    blog(LOG_DEBUG, "Hide Filter");
    break;
  case pairs::Transition:
    ui->label_obs_output_transition->hide();
    ui->cb_obs_output_transition->hide();
    blog(LOG_DEBUG, "Hide Transition");
    break;
  case pairs::Item:
    ui->label_obs_output_item->hide();
    ui->cb_obs_output_item->hide();
    blog(LOG_DEBUG, "Hide Item");
    break;
  case pairs::Audio:
    ui->label_obs_output_audio_source->hide();
    ui->cb_obs_output_audio_source->hide();
    blog(LOG_DEBUG, "Hide Audio");
    break;
  case pairs::Media:
    ui->label_obs_output_media_source->hide();
    ui->cb_obs_output_media_source->hide();
    blog(LOG_DEBUG, "Hide Media");
    break;
  }
}
void PluginWindow::HideAllPairs() {
  HidePair(pairs::Transition);
  HidePair(pairs::Audio);
  HidePair(pairs::Media);
  HidePair(pairs::Filter);
  HidePair(pairs::Scene);
  HidePair(pairs::Source);
  HidePair(pairs::Item);
}

void PluginWindow::ToggleShowHide() {
  if (!isVisible()) {
    setVisible(true);
    refresh();
  } else {
    setVisible(false);
  }
}

void PluginWindow::SetStatus(QString Label, Status status) {
  QLabel *label = GetLabel(Label);

  switch (status) {
  case Status::Disconnected:
    label->setStyleSheet("QLabel {color: rgb(255, 0, 0);}");
    label->setText("Disconnected");
    break;
  case Status::Disabled:
    label->setStyleSheet("QLabel {color: rgb(128, 128, 128);}");
    label->setText("Disabled");
    break;
  case Status::Connected:
    label->setStyleSheet("QLabel {color: rgb(0,255,0);}");
    label->setText("Connected");
    break;
  case Status::Error:
    label->setStyleSheet("QLabel {color: rgb(255, 0, 0);}");
    label->setText("Error");
    break;
  case Status::Connecting:
    label->setStyleSheet("QLabel {color: rgb(0,0,170);}");
    label->setText("Connecting");
    break;
  }
}
QColor *PluginWindow::GetStatusColor(Status status) {
  QColor *color = new QColor();
  switch (status) {
  case Status::Disconnected:
    color->setRgb(255, 0, 0);
    break;
  case Status::Disabled:
    color->setRgb(128, 128, 128);
    break;
  case Status::Connected:
    color->setRgb(0, 255, 0);
    break;
  case Status::Error:
    color->setRgb(255, 0, 0);
    break;
  case Status::Connecting:
    color->setRgb(0, 0, 170);
    break;
  default:
    color->setRgb(255, 255, 255);
  }
  return color;
}
QString *PluginWindow::GetStatusString(Status status) {
  QString *string = new QString();
  string->clear();
  switch (status) {
  case Status::Disconnected:
    string->append("Disconnected");
    break;
  case Status::Disabled:
    string->append("Disabled");
    break;
  case Status::Connected:
    string->append("Connected");
    break;
  case Status::Error:
    string->append("Error");
    break;
  case Status::Connecting:
    string->append("Connecting");
    break;
  default:
    string->append("UNKNOWN");
    break;
  }
  return string;
}
QLabel *PluginWindow::GetLabel(QString label) {
  if (label == "input") {
    return ui->lbl_status_input;
  } else if (label == "output") {
    return ui->lbl_status_output;
  }
}
void PluginWindow::SetAvailableDevices() {
    blog(LOG_DEBUG, "SetAvailableDevices");
    auto devices = DM->GetDevices();
    
    for (int i = 0; i < devices.count(); i++) {
       QString xname=devices.at(i)->name;
       add_midi_device(xname);
    }
}