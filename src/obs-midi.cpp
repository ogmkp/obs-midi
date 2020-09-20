
#include <obs-module.h>
#include <obs-frontend-api.h>

#include <obs-data.h>
#include "obs-midi.h"

#include "forms/plugin-window.hpp"
#include <QtWidgets/QAction>
#include <QtWidgets/QMainWindow>
#include "utils.h"

void ___source_dummy_addref(obs_source_t *) {}
void ___sceneitem_dummy_addref(obs_sceneitem_t *) {}
void ___data_dummy_addref(obs_data_t *) {}
void ___data_array_dummy_addref(obs_data_array_t *) {}
void ___output_dummy_addref(obs_output_t *) {}

void ___data_item_dummy_addref(obs_data_item_t *) {}
void ___data_item_release(obs_data_item_t *dataItem)
{
	obs_data_item_release(&dataItem);
}

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs-midi", "en-US")


bool obs_module_load(void)
{
	blog(LOG_INFO, "MIDI LOADED ");

	// Device Manager Setup

	// UI SETUP
	QMainWindow *mainWindow = (QMainWindow *)obs_frontend_get_main_window();
	PluginWindow *settingsDialog = new PluginWindow(mainWindow);
	const char *menuActionText = obs_module_text("OBS MIDI Settings");
	QAction *menuAction =
		(QAction *)obs_frontend_add_tools_menu_qaction(menuActionText);
	QObject::connect(menuAction, SIGNAL(triggered()), settingsDialog,
			 SLOT(ToggleShowHide()));

	// Setup event handler to start the server once OBS is ready
	auto eventCallback = [](enum obs_frontend_event event, void *param) {
		if (event == OBS_FRONTEND_EVENT_FINISHED_LOADING) {
			obs_frontend_remove_event_callback(
				(obs_frontend_event_cb)param, nullptr);
		}
	};
	obs_frontend_add_event_callback(
		eventCallback, (void *)(obs_frontend_event_cb)eventCallback);

	return true;
}

void obs_module_unload()
{
	

	blog(LOG_INFO, "goodbye!");
}
