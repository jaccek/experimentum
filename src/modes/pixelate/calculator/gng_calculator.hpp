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
            std::vector<Node*> getNeighbours();

        private:
        };

        struct Edge {
            Node *firstNode;
            Node *secondNode;
            int age = 0;

            ~Edge();
        };

    public:
        virtual ~GngCalculator();

    protected:
        virtual State makeSingleIteration(State oldState);

    private:
        State createInitialState();

    private:
        std::vector<Node*> mNodes;
    };
}
