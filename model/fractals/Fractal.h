//
// Created by Nataliia Gurova on 28.11.2022.
//

#ifndef C_VERSION_FRACTAL_H
#define C_VERSION_FRACTAL_H

#include <vector>
#include "Fractal.h"
#include "Params.h"
#include "Link.h"

class Fractal
{
public:
    Fractal();
    void setParams(Params &_params);
    Params getParams();

    void calculate();

private:
    Params params;
    std::vector<Link> links;
};

#endif //C_VERSION_FRACTAL_H
