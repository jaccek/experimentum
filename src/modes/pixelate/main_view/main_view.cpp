#include "main_view.hpp"
#include "main_presenter.hpp"

namespace pix {

    const char* const CANCEL_TEXT = "Cancel";
    const char* const CALCULATE_TEXT = "Calculate";
    const char* const LOAD_IMAGE_TEXT = "Load Image";

    MainView::MainView() {
        mPresenter = new MainPresenter(this);
    }

    MainView::~MainView() {
        delete mPresenter;
    }

    void MainView::init(QWidget *mainWidget) {
        mMainWidget = mainWidget;

        QLayout *layout = new QHBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);

        mSourceImageView = createImageWidget();
        layout->addWidget(mSourceImageView);

        mDestinationImageView = createImageWidget();
        layout->addWidget(mDestinationImageView);

        layout->addWidget(createToolsWidget());

        mainWidget->setLayout(layout);
    }

    void MainView::setupMetricsNames(std::vector<Metric*>& metrics)
    {
        mMetrics = metrics;
    }

    void MainView::displaySourceImage(mapi::Bitmap &bitmap) {
        mSourceImageView->setPixmap(QPixmap::fromImage(bitmap.asQImage()));
    }

    void MainView::displayOutputImage(mapi::Bitmap &bitmap) {
        mDestinationImageView->setPixmap(QPixmap::fromImage(bitmap.asQImage()), Qt::FastTransformation);
    }

    void MainView::blockAllWidgetsExceptCancelComputation() {
        mLoadImageButton->setEnabled(false);
        mColorsCountSpinBox->setEnabled(false);
        mCalculateButton->setEnabled(true);
        mCalculateButton->setText(CANCEL_TEXT);
        mMetricsComboBox->setEnabled(false);
    }

    void MainView::unlockCalculateButton() {
        mCalculateButton->setEnabled(true);
    }

    void MainView::unlockAllWidgets() {
        mLoadImageButton->setEnabled(true);
        mColorsCountSpinBox->setEnabled(true);
        mCalculateButton->setEnabled(true);
        mCalculateButton->setText(CALCULATE_TEXT);
        mMetricsComboBox->setEnabled(true);
    }

    void MainView::startTimer() {
        mTimer = new QTimer(this);
        connect(mTimer, &QTimer::timeout, this, &MainView::timerTicked);
        mTimer->start(1000);
    }

    void MainView::stopTimer() {
        mTimer->stop();
        delete mTimer;
        mTimer = nullptr;
    }

    mapi::AutoResizeImageWidget* MainView::createImageWidget() {
        mapi::AutoResizeImageWidget *imageWidget = new mapi::AutoResizeImageWidget();
        imageWidget->setStyleSheet("background-color: white");
        return imageWidget;
    }

    QWidget* MainView::createToolsWidget() {
        QWidget *toolsWidget = new QWidget();
        toolsWidget->setMinimumWidth(200);
        toolsWidget->setMaximumWidth(200);

        QBoxLayout *toolsLayout = new QVBoxLayout();
        toolsLayout->setAlignment(Qt::AlignTop);

        mLoadImageButton = new QPushButton(LOAD_IMAGE_TEXT);
        QObject::connect(mLoadImageButton, &QPushButton::clicked, this, &MainView::loadImageClicked);
        toolsLayout->addWidget(mLoadImageButton);

        mCalculateButton = new QPushButton(CALCULATE_TEXT);
        mCalculateButton->setEnabled(false);
        QObject::connect(mCalculateButton, &QPushButton::clicked, this, &MainView::calculateClicked);
        toolsLayout->addWidget(mCalculateButton);

        toolsLayout->addLayout(createColorsCountSpinBox());

        toolsLayout->addWidget(createMetricsComboBox());

        toolsWidget->setLayout(toolsLayout);
        return toolsWidget;
    }

    QLayout* MainView::createColorsCountSpinBox() {
        QLayout *layout = new QHBoxLayout();

        QLabel *label = new QLabel("Colors count:");
        layout->addWidget(label);

        mColorsCountSpinBox = new QSpinBox();
        mColorsCountSpinBox->setMinimum(5);
        mColorsCountSpinBox->setMaximum(256);
        mColorsCountSpinBox->setValue(mPresenter->colorsCount());
        void (pix::MainView::*slotPointer)(int) = &pix::MainView::colorsCountChanged;
        void (QSpinBox::*signalPointer)(int) = &QSpinBox::valueChanged;
        QObject::connect(mColorsCountSpinBox, signalPointer, this, slotPointer);
        layout->addWidget(mColorsCountSpinBox);

        return layout;
    }

    QComboBox* MainView::createMetricsComboBox() {
        mMetricsComboBox = new QComboBox();

        QStringList names;
        for (auto metric : mMetrics) {
            names << QString(metric->name().c_str());
        }
        mMetricsComboBox->insertItems(0, names);

        void (pix::MainView::*slotPointer)(int) = &pix::MainView::metricChanged;
        void(QComboBox::*signalPointer)(int) = &QComboBox::activated;
        QObject::connect(mMetricsComboBox, signalPointer, this, slotPointer);
        return mMetricsComboBox;
    }

    void MainView::loadImageClicked() {
        mPresenter->onLoadButtonClicked();
    }

    void MainView::calculateClicked() {
        mPresenter->onCalculateClicked();
    }

    void MainView::timerTicked() {
        mPresenter->onTimerTick();
    }

    void MainView::colorsCountChanged(int newValue) {
        mPresenter->onColorsCountChanged(newValue);
    }

    void MainView::metricChanged(int index) {
        mPresenter->onMetricSelected(mMetrics[index]);
    }
}
