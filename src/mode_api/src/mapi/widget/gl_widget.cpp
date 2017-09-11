#include <GL/glew.h>
#include "mapi/widget/gl_widget.h"

namespace mapi {

    GlWidget::GlWidget() : QOpenGLWidget() {
        mOpenGlInitialized = false;
    }

    GlWidget::GlWidget(QWidget *parent) : QOpenGLWidget(parent) {
        mOpenGlInitialized = false;
    }

    GlWidget::~GlWidget() {
    }

    // bool GlWidget::canRender() {
    //     return mOpenGlInitialized;
    // }

    void GlWidget::refreshView() {
        update();
    }

    void GlWidget::setRenderer(Renderer *renderer) {
        mRenderer = renderer;
    }

    void GlWidget::initializeGL() {
    	//glewExperimental = true;
    	// glewInit();
        //
        // char *version = (char*) glGetString(GL_VERSION);
        // printf("%s\n", version);
        //
        // glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        mOpenGlInitialized = true;
        if (mRenderer != nullptr) {
            mRenderer->init();
        }
    }

    void GlWidget::paintGL() {
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (mRenderer != nullptr) {
            mRenderer->render();
        }
    }

    void GlWidget::resizeGL(int width, int height) {
        if (mRenderer != nullptr) {
            mRenderer->resize(width, height);
        }
    }
}
