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
        auto edge = new Edge();

        edge->firstNode = this;
        this->edges.push_back(edge);

        edge->secondNode = node;
        node->edges.push_back(edge);
    }

    std::vector<GngCalculator::Node*> GngCalculator::Node::getNeighbours() {
        std::vector<Node*> neighbours;
        for (auto edge : edges) {
            auto node = edge->firstNode == this ? edge->secondNode : edge->firstNode;
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



    GngCalculator::GngCalculator() {
        srand(time(nullptr));
    }

    GngCalculator::~GngCalculator() {
        for (auto node : mNodes) {
            delete node;
        }
        mNodes.clear();
    }

    Calculator::State GngCalculator::makeSingleIteration(Calculator::State oldState) {
        // TODO: ugly solution!!!
        // if (iteration() == 0) {
        //     oldState = createInitialState();
        // }

        // TODO: refactor
        if (mNodes.size() == 0) {
            for (int i = 0; i < 2; ++i) {
                auto color = mapi::Color(rand() % 256, rand() % 256, rand() % 256);
                mNodes.push_back(new Node { color });
            }
            mNodes[0]->createEdge(mNodes[1]);
        }

        // TODO: refactor
        // crate inputs in random order
        if (mInputs.size() == 0) {
            for (auto item : colors()) {
                for (int i = 0; i < item.count; ++i) {
                    if (mInputs.size() == 0) {
                        mInputs.push_back(item.color);
                    } else {
                        int idx = rand() % (mInputs.size() + 1);     // TODO: +1 may crash application
                        mInputs.insert(mInputs.begin() + idx, item.color);
                    }
                }
            }
        }

        // TODO: refactor
        // get next input
        mapi::Color color = mInputs[0];
        mInputs.erase(mInputs.begin());

        // algorithm step
        auto nearestNode = findNearestNodeExcept(color, nullptr);
        auto secondNearestNode = findNearestNodeExcept(color, nearestNode);

        // TODO: move finded nodes to color
        // TODO: increase edges weight (only connected to nearest node)
        // TODO: update nearest node error
        // TODO: reset or create edge between nearest nodes
        // TODO: remove too old edges and disconnected nodes

        if ((iteration() + 1) % ADDING_NODE_DELAY) {
            // TODO: add new nodes
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

    GngCalculator::Node* GngCalculator::findNearestNodeExcept(mapi::Color &color, GngCalculator::Node *exceptionNode) {
        float minDistance = 100000000.0f;
        Node *nearestNode = nullptr;

        for (auto node : mNodes) {
            if (node == exceptionNode) {
                continue;
            }
            float distance = metric()->distance(color, node->color);
            if (distance < minDistance) {
                minDistance = distance;
                nearestNode = node;
            }
        }

        return nearestNode;
    }
}
