#pragma once

#include "calculator.hpp"

namespace pix {

    /**
        Growing Neural Gas algorithm (source: http://www.booru.net/download/MasterThesisProj.pdf)
    */
    class GngCalculator : public Calculator {
    private:
        struct Node;
        struct Edge;

        struct Node {
            mapi::Color color;
            std::vector<Edge*> edges;
            float error = 0;

            ~Node();

            void createEdge(Node* node);
            void detachEdge(Edge* edge);

            std::vector<Node*> neighbours();
            int neighboursCount();
            Edge* edgeToNode(Node* node);

            void moveToTarget(mapi::Color &target, float weight);

        private:
        };

        struct Edge {
            Node *firstNode;
            Node *secondNode;
            int age = 0;

            ~Edge();
        };

    public:
        GngCalculator();
        virtual ~GngCalculator();

    protected:
        virtual State makeSingleIteration(State oldState);

    private:
        Node* findNearestNodeExcept(mapi::Color &color, Node *exceptionNode);

    private:
        std::vector<Node*> mNodes;
        std::vector<mapi::Color> mInputs;

        float mNearestNodeMovementWeight = 0.05f;
        float mNearestNodeNeighboursMovementWeight = 0.0006f;
        int mMaxEdgeAge = 100;
        int mAddingNodeDelay = 300;

        float mErrorDecreaseFactor = 0.9995f;
        float mErrorDecreaseAfterAddFactor = 0.5f;
    };
}
