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

    void MainView::displaySourceImage(mapi::Bitmap &bitmap) {
        mSourceImageView->setPixmap(QPixmap::fromImage(bitmap.asQImage()));
        mDestinationImageView->setPixmap(QPixmap::fromImage(bitmap.asQImage()));    // FIXME: temporary

        mCalculateButton->setEnabled(true);
    }

    void MainView::blockAllWidgetsExceptCancelComputation() {
        mLoadImageButton->setEnabled(false);
        mCalculateButton->setEnabled(true);
        mCalculateButton->setText(CANCEL_TEXT);
    }

    void MainView::unlockAllWidgets() {
        mLoadImageButton->setEnabled(true);
        mCalculateButton->setEnabled(true);
        mCalculateButton->setText(CALCULATE_TEXT);
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

        QLayout *toolsLayout = new QVBoxLayout();
        toolsLayout->setAlignment(Qt::AlignTop);

        mLoadImageButton = new QPushButton(LOAD_IMAGE_TEXT);
        QObject::connect(mLoadImageButton, &QPushButton::clicked, this, &MainView::loadImageClicked);
        toolsLayout->addWidget(mLoadImageButton);

        mCalculateButton = new QPushButton(CALCULATE_TEXT);
        mCalculateButton->setEnabled(false);
        QObject::connect(mCalculateButton, &QPushButton::clicked, this, &MainView::calculateClicked);
        toolsLayout->addWidget(mCalculateButton);

        toolsWidget->setLayout(toolsLayout);
        return toolsWidget;
    }

    void MainView::loadImageClicked() {
        mPresenter->onLoadButtonClicked();
    }

    void MainView::calculateClicked() {
        mPresenter->onCalculateClicked();
    }
}
