#include "OBSMIDI.hpp"
#include "obs-frontend-api.h"
#include "forms/plugin-window.hpp"
#include <QObject>
#include <QtWidgets/QAction>
#include <QtWidgets/QMainWindow>
#include <obs-module.h>
OBSMIDI::OBSMIDI() {
	QMainWindow* mainWindow = (QMainWindow*)obs_frontend_get_main_window();
	PluginWindow* pluginWindow = new PluginWindow(mainWindow);
	const char* menuActionText = obs_module_text("OBS MIDI Settings");
	QAction* menuAction =
		(QAction*)obs_frontend_add_tools_menu_qaction(menuActionText);
	QObject::connect(menuAction, SIGNAL(triggered()), pluginWindow,
		SLOT(ToggleShowHide()));
}
OBSMIDI::~OBSMIDI() {}