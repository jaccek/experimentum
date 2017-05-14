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

        changeMode(mModesManager->modes()[0]);
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
            action->setObjectName(modeInfo->modeName());
            connect(action, &QAction::triggered, this, &MainWindow::onModeSelected);
    		modeMenu->addAction(action);
    	}
        setMenuBar(menuBar);
    }

    void MainWindow::closeEvent(QCloseEvent *event) {
        deleteCurrentMode();
        delete mModesManager;
        mModesManager = nullptr;
    }

    void MainWindow::onModeSelected() {
        QAction *action = (QAction*) sender();

        QString modeName = action->objectName();
        printf("Creating mode %s\n", modeName.toUtf8().constData());
        auto modeInfo = findModeInfoOrThrowException(modeName);
        changeMode(modeInfo);
    }

    void MainWindow::changeMode(mapi::ModeInfo *modeInfo) {
        deleteCurrentMode();
        createWidgetForMode();
        createMode(modeInfo);
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

    mapi::ModeInfo* MainWindow::findModeInfoOrThrowException(QString &modeName) {
        for (auto modeInfo : mModesManager->modes()) {
            if (modeName.compare(modeInfo->modeName()) == 0) {
                return modeInfo;
            }
        }

        printf("Cannot find mode %s\n", modeName.toUtf8().constData());
        throw 1;
    }

    void MainWindow::createMode(mapi::ModeInfo *modeInfo) {
        mMode = modeInfo->createMode();

        if (mMode == nullptr) {
            printf("Cannot create mode\n");
            throw 1;
        }

        mMode->init(mModeWidget);
    }
}
