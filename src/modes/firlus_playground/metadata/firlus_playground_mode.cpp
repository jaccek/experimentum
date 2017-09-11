#include "firlus_playground_mode.hpp"

#include <GL/glew.h>        // TODO: temporary!!!
#include <mapi/widget/gl_widget.h>
#include <QHBoxLayout>

namespace fp {

    class FirlusRenderer: public mapi::GlWidget::Renderer {
    public:
        virtual void init() {
            glewInit();

            char *version = (char*) glGetString(GL_VERSION);
            printf("%s\n", version);

            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        }

        virtual void render() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        virtual void resize(int width, int height) {

        }
    };

    void FirlusPlaygroundMode::init(QWidget *mainWidget) {
        QLayout *layout = new QHBoxLayout();
        layout->setContentsMargins(0, 0, 0, 0);

        auto glWidget = new mapi::GlWidget();
        glWidget->setRenderer(new FirlusRenderer());
        layout->addWidget(glWidget);

        mainWidget->setLayout(layout);
    }

    void FirlusPlaygroundMode::loadImage() {
    }
}
