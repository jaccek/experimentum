#pragma once

#include "main_contract.hpp"
#include <mapi/widget/auto_resize_image_widget.hpp>
#include <QtWidgets>

namespace pix {

    class MainView : public MainContract::View, public QObject {
    public:
        MainView();
        ~MainView();

        void init(QWidget *mainWidget);

        virtual void setupMetricsNames(std::vector<Metric*>& metrics);
        virtual void setupCalculatorsNames(std::vector<Calculator*>& calculators);

        virtual void displaySourceImage(mapi::Bitmap &bitmap);
        virtual void displayOutputImage(mapi::Bitmap &bitmap);

        virtual void blockAllWidgetsExceptCancelComputation();
        virtual void unlockCalculateButton();
        virtual void unlockAllWidgets();

        virtual void startTimer();
        virtual void stopTimer();

    private:
        mapi::AutoResizeImageWidget* createImageWidget();
        QWidget* createToolsWidget();
        QLayout* createColorsCountSpinBox();
        QComboBox* createMetricsComboBox();
        QComboBox* createCalculatorsComboBox();

    private slots:
        void loadImageClicked();
        void calculateClicked();
        void timerTicked();
        void colorsCountChanged(int newValue);
        void metricChanged(int index);
        void calculatorChanged(int index);

    private:
        MainContract::PresenterForView *mPresenter;
        std::vector<Calculator*> mCalculators;
        std::vector<Metric*> mMetrics;

        QWidget *mMainWidget;
        mapi::AutoResizeImageWidget *mSourceImageView;
        mapi::AutoResizeImageWidget *mDestinationImageView;
        QPushButton *mCalculateButton;
        QPushButton *mLoadImageButton;
        QSpinBox *mColorsCountSpinBox;
        QComboBox *mMetricsComboBox;
        QComboBox *mCalculatorsComboBox;

        QTimer *mTimer = nullptr;
    };
}
