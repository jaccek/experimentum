#include <mode_info.hpp>
#include <string>
#include <QLabel>
#include <QVBoxLayout>

namespace pix {

    class PixelateMode : public mapi::Mode {
    public:
        virtual void init(QWidget *mainWidget) {
            QLabel *label = new QLabel("test, very long string to show it even if menu cover it");

            QLayout *layout = new QVBoxLayout();
            layout->addWidget(label);
            layout->setAlignment(Qt::AlignCenter);

            mainWidget->setLayout(layout);
            printf("added\n");
        }
    };

    class PixelateModeInfo : public mapi::ModeInfo {
    public:
        PixelateModeInfo() {
            std::string name = "Pixelate";
        }

        virtual ~PixelateModeInfo() {
        }

        virtual const char* modeName() {
            return "Pixelate";
        }

        virtual mapi::Mode* createMode() {
            return new PixelateMode();
        }
    };
}

extern "C" mapi::ModeInfo* getModeInfo() {
    return new pix::PixelateModeInfo();
}
