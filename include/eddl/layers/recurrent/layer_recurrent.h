/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.8
* copyright (c) 2020, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: November 2020
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/


#ifndef EDDL_LAYER_RECURRENT_H
#define EDDL_LAYER_RECURRENT_H


#include <string>
#include <cstdio>

#include "eddl/layers/layer.h"

#define TRMODE 1
#define TSMODE 0

using namespace std;


/// RNN Layer
class LCopyStates : public MLayer {
public:
    static int total_layers;

    LCopyStates(vector<Layer *> in, string name, int dev, int mem);

    Layer *share(int c, int bs, vector<Layer *> p) override;

    Layer *clone(int c, int bs, vector<Layer *> p, int todev) override;

    void forward() override;

    void backward() override;

    void resize(int batch) override;

    string plot(int c) override;
};

/// RNN Layer
class LRNN : public MLayer {
public:
    int units;
    bool use_bias;
    bool bidirectional;
    static int total_layers;
    string activation;
    Layer *cps;

    Tensor *preoutput;

    Tensor *Wx;
    Tensor *gWx;
    Tensor *bias;
    Tensor *gbias;

    Tensor *Wy;
    Tensor *gWy;
    Tensor *biasy;


    LRNN(vector<Layer *> in, int units, string activation, bool use_bias, bool bidirectional, string name, int dev, int mem);

    ~LRNN();

    Layer *share(int c, int bs, vector<Layer *> p) override;

    Layer *clone(int c, int bs, vector<Layer *> p, int todev) override;

    void forward() override;

    void backward() override;

    string plot(int c) override;
};


/// LSTM Layer
class LLSTM : public MLayer {
public:
    int units;
    bool use_bias;
    bool bidirectional;
    static int total_layers;
    bool mask_zeros;

    Layer *cps;

    Tensor *state_c;
    Tensor *state_h;
    Tensor *delta_h;
    Tensor *delta_c;

    Tensor *Wih,*Wix;
    Tensor *Wfh,*Wfx;
    Tensor *Woh,*Wox;
    Tensor *Wch,*Wcx;

    Tensor *gWih,*gWix;
    Tensor *gWfh,*gWfx;
    Tensor *gWoh,*gWox;
    Tensor *gWch,*gWcx;

    Tensor *in,*fn,*on,*cn;
    Tensor *inbias,*fnbias,*onbias,*cnbias;
    Tensor *ginbias,*gfnbias,*gonbias,*gcnbias;

    Tensor *incn,*cn1fn;
    Tensor *sh;

    Tensor *mask;
    Tensor *psh;
    Tensor *psc;


    LLSTM(vector<Layer *> in, int units,  bool mask_zeros, bool bidirectional, string name, int dev, int mem);

    ~LLSTM();

    Layer *share(int c, int bs, vector<Layer *> p) override;

    Layer *clone(int c, int bs, vector<Layer *> p, int todev) override;

    void resize(int batch) override;
    void mem_delta() override;
    void free_delta() override;

    void forward() override;

    void backward() override;

    string plot(int c) override;
};


#endif //EDDL_LAYER_RECURRENT_H
