#include <qt_directory_hook/application_window.h>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QFileDialog>
#include <QListWidget>

DirHookApplicationWindow::DirHookApplicationWindow()
{
	QVBoxLayout* setHookLayout = new QVBoxLayout;

    // 1 row - add path
	QHBoxLayout* addPath = new QHBoxLayout;
	QLabel* addPathLbl = new QLabel("Add path: ");
	QLineEdit* addPathEdit = new QLineEdit;
	QPushButton* addPathButton = new QPushButton("...");
	addPath->addWidget(addPathLbl);
	addPath->addWidget(addPathEdit);
	addPath->addWidget(addPathButton);

    // 2 row - paths list
	QListWidget* pathsList = new QListWidget;

	// 3 row - copy to dir
	QHBoxLayout* copyToDir = new QHBoxLayout;
	QCheckBox* copyToDirChck = new QCheckBox;
	QLineEdit* copyToDirEdit = new QLineEdit;
	QPushButton* copyToDirButton = new QPushButton("...");

	// 4 row - events list
	QListWidget* eventsList = new QListWidget;

    // Setting layout
	setHookLayout->addLayout(addPath);
	setHookLayout->addWidget(pathsList);
	setHookLayout->addLayout(copyToDir);
	setHookLayout->addWidget(eventsList);
	this->setLayout(setHookLayout);
}

DirHookApplicationWindow::~DirHookApplicationWindow()
{
}
