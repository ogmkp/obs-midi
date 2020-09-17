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

#include "../obs-midi.h"
#include "plugin-window.hpp"
#include <obs-data.h>
#include <obs-module.h>
PluginWindow::PluginWindow(QWidget *parent) : ui(new Ui::PluginWindow) {
  ui->setupUi(this);
  HideAllPairs();
  blog(LOG_DEBUG, "Plugin window started");
  SetStatus("input", "Error");
  SetStatus("output", "Connected");

}

void PluginWindow::add_midi_device(QString name) {
    QTableWidgetItem* n = new QTableWidgetItem();
    QTableWidgetItem* n2 = new QTableWidgetItem();
    QTableWidgetItem* n3 = new QTableWidgetItem();
    QTableWidgetItem* n4 = new QTableWidgetItem();
    QTableWidgetItem* n5 = new QTableWidgetItem();
    QTableWidgetItem* n6 = new QTableWidgetItem();
    int rowcount = this->ui->table_device->rowCount();
    this->ui->table_device->insertRow(rowcount);
    n->setText(name);
    n2->setText(QString("Disconnected"));
    n2->setTextColor("grey");
    n3->setCheckState(Qt::Unchecked);
    n4->setCheckState(Qt::Unchecked);
    n5->setText(QString("unset"));
    this->ui->table_device->setItem(rowcount, 0, n);
    this->ui->table_device->setItem(rowcount, 1, n2);
    this->ui->table_device->setItem(rowcount, 2, n3);
    this->ui->table_device->setItem(rowcount, 3, n4);
    this->ui->table_device->setItem(rowcount, 4, n5);
    this->ui->table_device->setItem(rowcount, 5, n6);
}
void PluginWindow::set_headers() {
    ui->table_device->setHorizontalHeaderLabels({ "Name","Status","Enabled","Feedback Enabled","Feedback Port" });
}
PluginWindow::~PluginWindow() { delete ui; }

void PluginWindow::ShowPair(QString Pair) {
  if (Pair == "scene") {
    ui->label_obs_output_scene->show();
    ui->cb_obs_output_scene->show();
    // ui->cb_obs_output_scene->addItems(GetScenes());
  } else if (Pair == "source") {
    ui->label_obs_output_source->show();
    ui->cb_obs_output_source->show();
    // ui->cb_obs_output_source->addItems(
    // GetSources(ui->cb_obs_output_scene->currentText()));
  } else if (Pair == "filter") {
    ui->label_obs_output_filter->show();
    ui->cb_obs_output_filter->show();
    // ui->cb_obs_output_filter->addItems(GetFilters(ui->cb_obs_output_source->currentText()));
  } else if (Pair == "transition") {
    ui->label_obs_output_transition->show();
    ui->cb_obs_output_transition->show();

  } else if (Pair == "item") {
    ui->label_obs_output_item->show();
    ui->cb_obs_output_item->show();

  } else if (Pair == "audio") {
    ui->label_obs_output_audio_source->show();
    ui->cb_obs_output_audio_source->show();

  } else if (Pair == "media") {
    ui->label_obs_output_media_source->show();
    ui->cb_obs_output_media_source->show();
  }
}
void PluginWindow::HidePair(QString Pair) {
  if (Pair == "scene") {
    ui->label_obs_output_scene->hide();
    ui->cb_obs_output_scene->hide();
    blog(LOG_DEBUG, "Hide Scene");
  } else if (Pair == "source") {
    ui->label_obs_output_source->hide();
    ui->cb_obs_output_source->hide();
    blog(LOG_DEBUG, "Hide Source");
  } else if (Pair == "filter") {
    ui->label_obs_output_filter->hide();
    ui->cb_obs_output_filter->hide();
    blog(LOG_DEBUG, "Hide Filter");
  } else if (Pair == "transition") {
    ui->label_obs_output_transition->hide();
    ui->cb_obs_output_transition->hide();
    blog(LOG_DEBUG, "Hide Transition");
  } else if (Pair == "item") {
    ui->label_obs_output_item->hide();
    ui->cb_obs_output_item->hide();
    blog(LOG_DEBUG, "Hide Item");
  } else if (Pair == "audio") {
    ui->label_obs_output_audio_source->hide();
    ui->cb_obs_output_audio_source->hide();
    blog(LOG_DEBUG, "Hide Audio");
  } else if (Pair == "media") {
    ui->label_obs_output_media_source->hide();
    ui->cb_obs_output_media_source->hide();
    blog(LOG_DEBUG, "Hide Media");
  }
}
void PluginWindow::HideAllPairs() {
  HidePair("transition");
  HidePair("audio");
  HidePair("media");
  HidePair("filter");
  HidePair("scene");
  HidePair("source");
  HidePair("item");
}
void PluginWindow::ToggleShowHide() {
  if (!isVisible()) {
    setVisible(true);
  } else {
    setVisible(false);
  }
}

void PluginWindow::SetStatus(QString Label, QString Status) {
  QLabel *label = GetLabel(Label);
  label->setText(Status);
  if (Status == "Disconnected") {
    label->setStyleSheet("QLabel {color: rgb(255, 0, 0);}");
  } else if (Status == "Disabled") {
    label->setStyleSheet("QLabel {color: rgb(128, 128, 128);}");
  } else if (Status == "Connected") {
    label->setStyleSheet("QLabel {color: rgb(0,255,0);}");
  } else if (Status == "Error") {
    label->setStyleSheet("QLabel {color: rgb(255, 0, 0);}");
  } else if (Status == "Connecting") {
    label->setStyleSheet("QLabel {color: rgb(0,0,170);}");
  }
}
QLabel *PluginWindow::GetLabel(QString label) {
  if (label == "input") {
    return ui->lbl_status_input;
  } else if (label == "output") {
    return ui->lbl_status_output;
  }
}
