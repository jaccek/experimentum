#pragma once

#include "mode/modes_manager.hpp"
#include <mapi/mode.hpp>
#include <QMainWindow>
#include <QLayout>

namespace e
{
    struct WindowProperties {
        QPoint position;
        QSize size;
    };

    class MainWindow : public QMainWindow {
    public:
        void init(WindowProperties properties);

    protected:
        virtual void closeEvent(QCloseEvent *event);

    private slots:
        void onModeSelected();

    private:
        void initMenuBar();

        void changeMode(mapi::ModeInfo *modeInfo);
        void deleteCurrentMode();
        void createWidgetForMode();
        mapi::ModeInfo* findModeInfoOrThrowException(QString &modeName);
        void createMode(mapi::ModeInfo *modeInfo);

    private:
        ModesManager *mModesManager = nullptr;
        mapi::Mode *mMode = nullptr;

        QWidget *mMainWidget = nullptr;
        QLayout *mMainWidgetLayout = nullptr;
        QWidget *mModeWidget = nullptr;
    };
}
