#include "gng_calculator.hpp"
#include <ctime>
#include <cstdlib>

namespace pix {

    GngCalculator::Node::~Node() {
        for (auto edge : edges) {
            delete edge;
        }
        edges.clear();
    }

    void GngCalculator::Node::createEdge(Node* node) {
        Edge *edge = new Edge();

        edge->firstNode = this;
        this->edges.push_back(edge);

        edge->secondNode = node;
        node->edges.push_back(edge);
    }

    std::vector<GngCalculator::Node*> GngCalculator::Node::getNeighbours() {
        std::vector<Node*> neighbours;
        for (auto edge : edges) {
            Node* node = edge->firstNode == this ? edge->secondNode : edge->firstNode;
            neighbours.push_back(node);
        }
        return neighbours;
    }

    void GngCalculator::Node::detachEdge(Edge* edge) {
        for (auto iterator = edges.begin(); iterator != edges.end(); ++iterator) {
            if (*iterator == edge) {
                edges.erase(iterator);
                break;
            }
        }
    }



    GngCalculator::Edge::~Edge() {
        firstNode->detachEdge(this);
        secondNode->detachEdge(this);
    }



    GngCalculator::~GngCalculator() {
        for (auto node : mNodes) {
            delete node;
        }
        mNodes.clear();
    }

    Calculator::State GngCalculator::makeSingleIteration(Calculator::State oldState) {
        // TODO: ugly solution!!!
        if (iteration() == 0) {
            oldState = createInitialState();
        }

        return oldState;
    }

    Calculator::State GngCalculator::createInitialState() {
        State state;
        for (int i = 0; i < 2; ++i) {
            state.centers.push_back(mapi::Color(rand() % 256, rand() % 256, rand() % 256));
        }
        return state;
    }
}
