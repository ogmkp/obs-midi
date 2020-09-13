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
#include <vector>
#include <QDialog>
#include <QtWidgets>
#include "ui_plugin-window.h"

class PluginWindow : public QDialog {
	Q_OBJECT

public:
	PluginWindow(QWidget* parent);
	void SetAvailableDevices();
	~PluginWindow();
	void ShowPair(QString Pair);
	void HidePair(QString Pair);
	void HideAllPairs();
public slots:
	void SetStatus(QString label,QString Status);
	QLabel* GetLabel(QString label);
private Q_SLOTS:
	void ToggleShowHide();
private:
	Ui::PluginWindow* ui;

};
