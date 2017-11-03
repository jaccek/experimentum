#include "firlus_playground_mode.hpp"

#include <GL/glew.h>        // TODO: temporary!!!
#include <mapi/widget/gl_widget.h>
#include <QHBoxLayout>
#include <firlus/shader/shader.h>
#include <firlus/shape/shape.h>

namespace fp {

    class FirlusRenderer: public mapi::GlWidget::Renderer {
    public:
        virtual void init() {
            glewInit();

            char *version = (char*) glGetString(GL_VERSION);
            printf("%s\n", version);

            glClearColor(0.25f, 1.0f, 0.0f, 1.0f);

            firlus::Vertex vertices[] = {
                {-0.5f, -0.5f, 0.0f},
                { 0.5f, -0.5f, 0.0f},
                { 0.0f,  0.5f, 0.0f}
            };
            firlus::ShapeVerticesInfo info = {
                vertices,
                3
            };
            mShape = new firlus::Shape(info);

            // glGenBuffers(1, &mVBO);
            //
            // glBindBuffer(GL_ARRAY_BUFFER, mVBO);
            // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            // glBindBuffer(GL_ARRAY_BUFFER, 0);

            mShader = new firlus::Shader("modes/firlus_playground_mode/shaders/base.vs",
                    "modes/firlus_playground_mode/shaders/base.fs");
        }

        virtual void render() {
            printf("Render\n");
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            mShape->draw(mShader);

            // mShader->use();
            // glBindBuffer(GL_ARRAY_BUFFER, mVBO);
            //
            // unsigned positionLocation = glGetAttribLocation(mShader->shaderProgram(), "aPos");
            // glEnableVertexAttribArray(positionLocation);
            // glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        virtual void resize(int width, int height) {
            printf("Window resized: %dx%d\n", width, height);
            glViewport(0, 0, width, height);
        }

    private:
        unsigned int mVBO, mVAO;
        firlus::Shader *mShader;
        firlus::Shape *mShape;
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
