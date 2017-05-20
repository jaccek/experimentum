#include "main_presenter.hpp"
#include "main_router.hpp"

namespace pix {
    MainPresenter::MainPresenter(MainContract::View *view) : mView(view) {
        mRouter = new MainRouter();
    }

    MainPresenter::~MainPresenter() {
        delete mRouter;
    }

    void MainPresenter::onLoadButtonClicked() {
        mapi::Bitmap bitmap = mRouter->loadImage();
        mView->displaySourceImage(bitmap);
    }
}
