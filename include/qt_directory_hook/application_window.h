#pragma once
#include <QWidget>
#include <QScopedPointer>

class QString;
class QPushButton;
class QLineEdit;
class QCheckBox;
class QListWidget;
class QFileSystemWatcher;

/// @brief 
class DirHookApplicationWindow : public QWidget
{
    Q_OBJECT
public:

    /// @brief Create main window
    DirHookApplicationWindow(QWidget* parent = nullptr);

    /// @brief default
    virtual ~DirHookApplicationWindow();
    
private:
    
    /// @brief
    static QString getDirectoryName();

    /// @brief
    static int getLastError();

    /// @brief
    void addPathUnderWatch(const QString& pathToAdd);

    /// @brief
    void removePathFromWatch(const QString& pathToRemove);

private slots:
    void selectHookPath();
	void addHookPath();
    void removeHookPath();
	void selectDestinationPath();
	void selectCopyChangedFiles();
    
private:
    
    QPushButton* lookupPathButton_;
    QPushButton* addPathButton_;
    QPushButton* removePathButton_;
    QPushButton* copyToDirButton_;
	QLineEdit* addPathEdit_;
	QLineEdit* copyToDirEdit_;
	QCheckBox* copyToDirChck_;
	QListWidget* pathsList_;
	QListWidget* eventsList_;
	QScopedPointer<QFileSystemWatcher> filesystemHook_;
};