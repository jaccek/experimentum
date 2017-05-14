#include "main_window.hpp"

#include <QMenuBar>
#include <QLabel>

namespace e {
    void MainWindow::init(WindowProperties properties) {
        QRect windowRect(properties.position, properties.size);
        setGeometry(windowRect);
        setMinimumSize(QSize(600, 400));

        initMenuBar();

        mMainWidget = new QWidget();

        mMainWidgetLayout = new QVBoxLayout(mMainWidget);
        mMainWidgetLayout->setContentsMargins(0, 0, 0, 0);

        mMainWidget->setLayout(mMainWidgetLayout);
        setCentralWidget(mMainWidget);
    }

    void MainWindow::closeEvent(QCloseEvent *event) {
        delete mModesManager;
        mModesManager = nullptr;
    }

    void MainWindow::changeMode() {
        QAction *action = (QAction*) sender();

        deleteCurrentMode();
        createWidgetForMode();

        // TODO: find mode info, create mode and init it

        // FIXME temp
        mMode = mModesManager->modes()[0]->createMode();
        mMode->init(mModeWidget);
        // end temp

        mModeWidget->update();
    }

    void MainWindow::initMenuBar() {
        QMenuBar *menuBar = new QMenuBar();
        QSizePolicy policy(QSizePolicy::Maximum, QSizePolicy::Minimum);
        menuBar->setSizePolicy(policy);

        QMenu *modeMenu = new QMenu("&Mode");
        menuBar->addMenu(modeMenu);

        mModesManager = new ModesManager();
        std::vector<mapi::ModeInfo*> modeInfos = mModesManager->modes();
    	for(unsigned i = 0; i < modeInfos.size(); ++i) {
    		auto modeInfo = modeInfos[i];
    		QAction *action = new QAction(modeInfo->modeName(), modeMenu);
            connect(action, &QAction::triggered, this, &MainWindow::changeMode);
    		modeMenu->addAction(action);
    	}
        setMenuBar(menuBar);
    }

    void MainWindow::deleteCurrentMode() {
        if (mMode != nullptr) {
            delete mMode;
            mMode = nullptr;
        }

        if (mModeWidget != nullptr) {
            delete mModeWidget;
            mModeWidget = nullptr;
        }
    }

    void MainWindow::createWidgetForMode() {
        mModeWidget = new QWidget();

        // mModeWidget->setStyleSheet("background-color: red");

        mMainWidgetLayout->addWidget(mModeWidget);
        mMainWidget->update();
    }
}
