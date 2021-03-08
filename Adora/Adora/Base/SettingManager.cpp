
#include "SettingManager.h"
#include <qsettings.h>
#include "LanguageManager.h"
#include <qdir.h>

GeneralSetting::GeneralSetting() {

}

GeneralSetting::~GeneralSetting() {

}

void GeneralSetting::load() {

	QSettings settings("Adora", "Adora");

	settings.beginGroup("General");

	this->savePath = settings.value("SavePath").toString();

	settings.endGroup();

	QDir dir(this->savePath);
	dir.mkdir(this->savePath);

	if (dir.exists() == false)
		this->savePath = "";

	if (this->savePath == "") {
	
#ifdef Q_OS_WIN
		QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer", QSettings::NativeFormat);

		settings.beginGroup("Shell Folders");
		this->savePath = settings.value("Personal").toString() + QString::fromLocal8Bit("/Adora");
		settings.endGroup();

		this->savePath = this->savePath.replace("\\", "/");
	
#endif 
	}

	dir.mkdir(this->savePath);
}

void GeneralSetting::save() {

	QSettings settings("Adora", "Adora");

	settings.beginGroup("General");
	settings.setValue("SavePath", this->savePath);
	settings.endGroup();
}


////////////////////////////////////////////////////////////////////

VideoSetting::VideoSetting()
	:useStartAndStopHotkey(false), usePauseAndResumeHotkey(false), includeCursor(false), 
	useHwEncoder(false), fps(30), videoBitrate(1000000) {

}

VideoSetting::~VideoSetting() {


}

void VideoSetting::load() {

	QSettings settings("Adora", "Adora");

	settings.beginGroup("Video");

	if (settings.contains("useStartAndStopHotkey") == true)
		this->useStartAndStopHotkey = settings.value("useStartAndStopHotkey").toBool();

	if (settings.contains("usePauseAndResumeHotkey") == true)
		this->usePauseAndResumeHotkey = settings.value("usePauseAndResumeHotkey").toBool();

	if (settings.contains("includeCursor") == true)
		this->includeCursor = settings.value("includeCursor").toBool();

	if (settings.contains("useHwEncoder") == true)
		this->useHwEncoder = settings.value("useHwEncoder").toBool();

	if (settings.contains("fps") == true)
		this->fps = settings.value("fps").toInt();

	if (settings.contains("videoBitrate") == true)
		this->videoBitrate = settings.value("videoBitrate").toInt();
	

	settings.endGroup();
}


void VideoSetting::save() {

	QSettings settings("Adora", "Adora");

	settings.beginGroup("Video");

	settings.setValue("useStartAndStopHotkey", this->useStartAndStopHotkey);
	settings.setValue("usePauseAndResumeHotkey", this->usePauseAndResumeHotkey);
	settings.setValue("includeCursor", this->includeCursor);
	settings.setValue("useHwEncoder", this->useHwEncoder);
	settings.setValue("fps", this->fps);
	settings.setValue("videoBitrate", this->videoBitrate);

	settings.endGroup();
}

////////////////////////////////////////////////////////////////////

LanguageSetting::LanguageSetting()
	:language(Language::English) {

}

LanguageSetting::~LanguageSetting() {

}


void LanguageSetting::load() {

	QSettings settings("Adora", "Adora");

	settings.beginGroup("Language");

	if (settings.contains("Language") == true)
		this->language = (Language)(settings.value("Language").toInt());

	LanguageManager::getInstance()->setLanguage((LanguageManager::Language)this->language);

	settings.endGroup();
}

void LanguageSetting::save() {

	QSettings settings("Adora", "Adora");

	settings.beginGroup("Language");

	settings.setValue("Language", int(this->language));

	settings.endGroup();
}


///////////////////////////////////////////////////////////////

SettingManager::SettingManager() {

}

SettingManager::~SettingManager() {


}

void SettingManager::load() {

	QSettings settings("Adora", "Adora");
	
	if (settings.contains("AdoraPosition") == true)
		this->adoraPosition = settings.value("AdoraPosition").toPoint();

	this->generalSetting.load();
	this->videoSetting.load();
	this->languageSetting.load();
}

void SettingManager::save() {

	QSettings settings("Adora", "Adora");

	settings.setValue("AdoraPosition", this->adoraPosition);

	this->generalSetting.save();
	this->videoSetting.save();
	this->languageSetting.save();
}