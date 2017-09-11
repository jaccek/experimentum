#pragma once

#include <QOpenGLWidget>

namespace mapi {

    class GlWidget : public QOpenGLWidget
    {
    public:
        class Renderer {
        public:
            virtual void init() = 0;
            virtual void render() = 0;
            virtual void resize(int width, int height) = 0;
        };

    public:
        GlWidget();
        GlWidget(QWidget *parent);
        virtual ~GlWidget();

        // bool canRender();
        virtual void refreshView();

        void setRenderer(Renderer *renderer);

    protected:
        virtual void initializeGL();
        virtual void paintGL();
        virtual void resizeGL(int width, int height);

    private:
        bool mOpenGlInitialized;
        Renderer *mRenderer;
    };
}
