#pragma once

#include "calculator.hpp"

namespace pix {

    /**
        Growing Neural Gas algorithm (source: http://www.booru.net/download/MasterThesisProj.pdf)
    */
    class GngCalculator : public Calculator {
    public:
        virtual ~GngCalculator();

    protected:
        virtual State makeSingleIteration(State oldState);
    };
}
