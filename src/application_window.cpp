#include <qt_directory_hook/application_window.h>

#include <QDir>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QFileDialog>
#include <QListWidget>
#include <QFileSystemWatcher>
#include <QTableWidgetItem>
#include <QListIterator>

#if defined(Q_OS_WIN)
#include <Windows.h>
#else defined(Q_OS_LINUX) || defined(Q_OS_MAC)
#include <errno.h>
#endif

#include <cassert>

DirHookApplicationWindow::DirHookApplicationWindow(QWidget* parent/* = nullptr*/) : 
	QWidget(parent),
	copyToDirButton_(),
	lookupPathButton_(),
	addPathButton_(),
	addPathEdit_(),
	copyToDirEdit_(),
	copyToDirChck_(),
	pathsList_(),
	eventsList_(),
    filesystemHook_(new QFileSystemWatcher(parent))
{
	QVBoxLayout* setHookLayout = new QVBoxLayout;

    // 1 row - add path
	QHBoxLayout* addPath = new QHBoxLayout;
	QLabel* addPathLbl = new QLabel("Add path: ");
	addPathEdit_ = new QLineEdit;
	lookupPathButton_ = new QPushButton("...");
	addPathButton_ = new QPushButton("+");
    removePathButton_ = new QPushButton("-");
	addPath->addWidget(addPathLbl);
	addPath->addWidget(addPathEdit_);
	addPath->addWidget(lookupPathButton_);
	addPath->addWidget(addPathButton_);
	connect(lookupPathButton_, &QPushButton::clicked, this, &DirHookApplicationWindow::selectHookPath);
	connect(addPathButton_, &QPushButton::clicked, this, &DirHookApplicationWindow::addHookPath);
    connect(removePathButton_, &QPushButton::clicked, this, &DirHookApplicationWindow::removeHookPath);

    // 2 row - paths list
	QListWidget* pathsList_ = new QListWidget;

	// 3 row - copy to dir
	QHBoxLayout* copyToDir = new QHBoxLayout;
	copyToDirChck_ = new QCheckBox("Copy changed files to dir");
	copyToDirEdit_ = new QLineEdit;
	copyToDirButton_ = new QPushButton("...");
	copyToDir->addWidget(copyToDirChck_);
	copyToDir->addWidget(copyToDirEdit_);
	copyToDir->addWidget(copyToDirButton_);
	copyToDirChck_->setChecked(false);
	connect(copyToDirButton_, &QPushButton::clicked, this, &DirHookApplicationWindow::selectDestinationPath);
	connect(copyToDirChck_, &QCheckBox::clicked, this, &DirHookApplicationWindow::selectCopyChangedFiles);
	selectCopyChangedFiles();

	// 4 row - events list
	eventsList_ = new QListWidget;

    // Setting layout
	setHookLayout->addLayout(addPath);
	setHookLayout->addWidget(pathsList_);
	setHookLayout->addLayout(copyToDir);
	setHookLayout->addWidget(eventsList_);
	this->setLayout(setHookLayout);
}

DirHookApplicationWindow::~DirHookApplicationWindow()
{
}

// static
QString DirHookApplicationWindow::getDirectoryName()
{
	QFileDialog openDir;
	openDir.setDirectory(QDir::homePath());
	openDir.setFileMode(QFileDialog::Directory);
	openDir.setOptions(QFileDialog::ShowDirsOnly);
	QStringList fileName;
	if (openDir.exec()) {
		fileName = openDir.selectedFiles();
		assert(fileName.size() == 1);
	}
	return (fileName.size() == 1) ? fileName[0] : QString();
}

// static
int DirHookApplicationWindow::getLastError()
{
#if defined(Q_OS_WIN)
    return ::GetLastError();
#else defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    return errno;
#endif
}

void DirHookApplicationWindow::addPathUnderWatch(const QString& pathToAdd)
{
    if(!filesystemHook_->addPath(pathToAdd)){
        eventsList_->addItem(QString("Unable to put the directory %1 under watch").arg(pathToAdd));
        eventsList_->addItem(QString("System Error Code = %1").arg(this->getLastError()));
    }
    else{
        eventsList_->addItem(QString("The directory %1 is put under watch").arg(pathToAdd));
    }
}

void DirHookApplicationWindow::removePathFromWatch(const QString& pathToRemove)
{
    if(filesystemHook_->removePath(pathToRemove)){
        eventsList_->addItem(QString("Unable to remove the directory %1 from watch").arg(pathToRemove));
        eventsList_->addItem(QString("System Error Code = %1").arg(this->getLastError()));
    }
    else{
        eventsList_->addItem(QString("The directory %1 is removed from watch").arg(pathToRemove));
    }
}

void DirHookApplicationWindow::selectHookPath()
{
	addPathEdit_->setText(getDirectoryName());
}

void DirHookApplicationWindow::addHookPath()
{
	if(QDir(addPathEdit_->text()).exists()){
		pathsList_->addItem(addPathEdit_->text());
        addPathUnderWatch(addPathEdit_->text());
	}
	else{
		eventsList_->addItem(QString("The directory %1 does not exist").arg(addPathEdit_->text()));
	}
}

void DirHookApplicationWindow::removeHookPath()
{
    QList<QListWidgetItem*> eraseUs = pathsList_->selectedItems();
    QSet<int> selectedRows;
    QListIterator<QListWidgetItem*> iterErasedItems(eraseUs);
    while(iterErasedItems.hasNext()) {
        removePathFromWatch(iterErasedItems.next()->text());
        pathsList_->removeItemWidget(iterErasedItems.next());
    }
}

void DirHookApplicationWindow::selectDestinationPath()
{
	copyToDirEdit_->setText(getDirectoryName());
}

void DirHookApplicationWindow::selectCopyChangedFiles()
{
	copyToDirEdit_->setEnabled(copyToDirChck_->isChecked());
	copyToDirButton_->setEnabled(copyToDirChck_->isChecked());
}
