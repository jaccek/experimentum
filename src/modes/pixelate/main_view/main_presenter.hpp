#pragma once

#include "main_contract.hpp"

namespace pix {

    class MainPresenter : public MainContract::PresenterForView {
    public:
        MainPresenter(MainContract::View *view);
        virtual ~MainPresenter();

        virtual void onLoadButtonClicked();

    private:
        MainContract::View *mView;
        MainContract::Router *mRouter;
    };
}
