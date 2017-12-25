#include "gng_calculator.hpp"
#include <ctime>
#include <cstdlib>
#include <unistd.h>

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

    void GngCalculator::Node::detachEdge(Edge* edge) {
        for (auto iterator = edges.begin(); iterator != edges.end(); ++iterator) {
            if (*iterator == edge) {
                edges.erase(iterator);
                break;
            }
        }
    }

    std::vector<GngCalculator::Node*> GngCalculator::Node::neighbours() {
        std::vector<Node*> neighbours;
        for (auto edge : edges) {
            auto node = edge->firstNode == this ? edge->secondNode : edge->firstNode;
            neighbours.push_back(node);
        }
        return neighbours;
    }

    int GngCalculator::Node::neighboursCount() {
        return edges.size();
    }

    GngCalculator::Edge* GngCalculator::Node::edgeToNode(GngCalculator::Node* node) {
        for (auto edge : edges) {
            if (edge->firstNode == node || edge->secondNode == node) {
                return edge;
            }
        }
        return nullptr;
    }

    void GngCalculator::Node::moveToTarget(mapi::Color &target, float weight) {
        int r = (int) (color.r() + (target.r() - color.r()) * weight);
        int g = (int) (color.g() + (target.g() - color.g()) * weight);
        int b = (int) (color.b() + (target.b() - color.b()) * weight);

        color = mapi::Color(r, g, b);
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

    std::string GngCalculator::name() {
        return "Growing Neural Gas";
    }

    Calculator::State GngCalculator::makeSingleIteration(Calculator::State oldState) {
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
        for (unsigned i = 0; i < mInputs.size(); ++i) {
            // get next input
            mapi::Color color = mInputs[0];
            // mInputs.erase(mInputs.begin());

            // find 2 nearest nodes
            auto nearestNode = findNearestNodeExcept(color, nullptr);
            auto secondNearestNode = findNearestNodeExcept(color, nearestNode);

            // update nearest node error
            nearestNode->error += metric()->distance(nearestNode->color, color);

            // move nearest node and it's neighbours to color
            nearestNode->moveToTarget(color, mNearestNodeMovementWeight);
            for (auto node : nearestNode->neighbours()) {
                node->moveToTarget(color, mNearestNodeNeighboursMovementWeight);
            }

            // increase edges weight (only connected to nearest node)
            for (auto edge : nearestNode->edges) {
                edge->age += 1;
            }

            // reset or create edge between nearest nodes
            auto edge = nearestNode->edgeToNode(secondNearestNode);
            if (edge == nullptr) {
                nearestNode->createEdge(secondNearestNode);
            } else {
                edge->age = 0;
            }
        }
        mInputs.clear();

        // remove too old edges
        for (auto node : mNodes) {
            for (unsigned i = 0; i < node->edges.size(); ++i) {
                auto edge = node->edges[i];
                if (edge->age > mMaxEdgeAge) {
                    delete edge;
                    --i;
                }
            }
        }

        // remove nodes without neighbours
        for (unsigned i = 0; i < mNodes.size(); ++i) {
            if (mNodes[i]->neighboursCount() == 0) {
                delete mNodes[i];
                mNodes.erase(mNodes.begin() + i);
                --i;
            }
        }

        // add new node
        if (((iteration() + 1) % mAddingNodeDelay == 0) && mNodes.size() < (unsigned) centersCount()) {
            mAddingNodeDelay += mNodes.size();
            // find node with max error
            float maxError = -1.0f;
            Node *errorNode = nullptr;
            for (auto node : mNodes) {
                if (node->error > maxError) {
                    maxError = node->error;
                    errorNode = node;
                }
            }

            // find it's neighbours with max error
            maxError = -1.0f;
            Node *secondErrorNode = nullptr;
            for (auto node : errorNode->neighbours()) {
                if (node->error > maxError) {
                    maxError = node->error;
                    secondErrorNode = node;
                }
            }

            // create new node
            auto newNode = new Node();
            newNode->color = mapi::Color(
                    (errorNode->color.r() + secondErrorNode->color.r()) / 2,
                    (errorNode->color.g() + secondErrorNode->color.g()) / 2,
                    (errorNode->color.b() + secondErrorNode->color.b()) / 2);
            mNodes.push_back(newNode);

            // decrease errors
            errorNode->error *= mErrorDecreaseAfterAddFactor;
            secondErrorNode->error *= mErrorDecreaseAfterAddFactor;
            newNode->error = secondErrorNode->error;

            // remove old edge
            delete errorNode->edgeToNode(secondErrorNode);

            // create new edges
            newNode->createEdge(errorNode);
            newNode->createEdge(secondErrorNode);
        }
        printf("Nodes count: %d\n", (int) mNodes.size());

        // decrease error & create new state
        auto newState = State();
        for (auto node : mNodes) {
            node->error *= mErrorDecreaseFactor;
            newState.colors.push_back(node->color);
        }

        return newState;
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
