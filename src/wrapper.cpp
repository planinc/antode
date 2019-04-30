//
// Created by Salva Carrión on 2019-04-10.
//

#include <iostream>

#include "wrapper.h"
#include "eddl.h"
#include "layers/layer.h"
#include <thread>

// Create Tensors
Tensor* Tensor_init(const int* shape, int shape_size, int dev){
    vector<int> v(shape, shape + shape_size);
    return new Tensor(v, dev);
}

int Tensor_device(Tensor*t){
    return t->device;
}

int Tensor_dim(Tensor*t){
    return t->dim;
}

int Tensor_length(Tensor*t){ // Data length
    return t->tam;
}

int* Tensor_shape(Tensor*t){
    return &t->sizes[0];
}

float* Tensor_getData(Tensor*t){
    return t->ptr;
}

void Tensor_point2data(Tensor* t, float* ptr){
    int tam=1;
    for(int i=0;i<t->dim;++i) tam*=t->sizes[i];
    t->tam = tam;
    t->ptr = ptr;
}

// Create Layers
tensor LTensor_init(const int* shape, int shape_size, int dev){
    vector<int> v(shape, shape + shape_size);
    return EDDL::T(v, dev);
}

tensor LTensor_init_fromfile(const char* fname){
    return EDDL::T(fname);
}

void LTensor_div(tensor t, float v){
    t->input->div(v);
}

layer Input_init(Tensor* in, const char* name, int dev){
    return new LInput(in, dev);
}

layer Dense_init(layer parent, int dim, const char* name, int dev){
    return EDDL::Dense(parent, dim, dev);
}

layer Conv_init(layer parent, const int* ks, int ks_size, const int* st, int st_size, const char* p, int dev){
    vector<int> vks(ks, ks + ks_size);
    vector<int> vst(st, st + st_size);
    return EDDL::Conv(parent, vks, vst, p, dev);
}

layer Activation_init(layer parent, const char* act, const char* name, int dev){
    return EDDL::Activation(parent, act, dev);
}

layer Reshape_init(layer parent, const int* shape, int shape_size, const char* name, int dev){
    vector<int> vshape(shape, shape + shape_size);
    return EDDL::Reshape(parent, vshape, name, dev);
}

layer Drop_init(layer parent, float df, const char* name, int dev){
    return EDDL::Drop(parent, df, dev);
}

layer Add_init(Layer** parent, int parent_size, const char* name, int dev){
    vector<Layer*> vparent;
    vparent.reserve(parent_size);
    for( int i = 0; i < parent_size; ++i ){
        vparent.push_back(parent[i]);
    }
    return new LAdd(vparent, dev);
 };

layer Cat_init(Layer** init, int init_size, const char* name, int dev){
   vector<Layer*> vinit;
    vinit.reserve(init_size);
    for( int i = 0; i < init_size; ++i ){
        vinit.push_back(init[i]);
    }
    return new LCat(vinit, dev);
}

model Model_init(Layer* in, int in_size, Layer* out, int out_size){
    vector<Layer*> vin;
    vin.reserve(in_size);
    for( int i = 0; i < in_size; ++i ) {
        vin.push_back(in++);
    }

    vector<Layer*> vout;
    vout.reserve(out_size);
    for( int i = 0; i < out_size; ++i ) {
        vout.push_back(out++);
    }
    return EDDL::Model(vin, vout);
}

void plot(model m, const char* fname){
    EDDL::plot(m, fname);
}

void info(model m){
    EDDL::info(m);
}

void build(model net, optimizer opt, const char** c, int size_c, const char** m, int size_m, int todev){
    vector<string> co, me;

    // Add pointer values to vector of strings
    for(int i = 0; i < size_c; ++i){co.emplace_back(*c);}
    for(int i = 0; i < size_m; ++i){me.emplace_back(*m);}

    net->build(opt, co, me, new CompServ(std::thread::hardware_concurrency(),{},{}));
}


void fit(model m, Tensor* in, Tensor* out, int batch, int epochs){
    vector<Tensor*> tin = {in};
    vector<Tensor*> tout = {out};
    m->fit(tin, tout, batch, epochs);
}

void evaluate(model m, Tensor* in, Tensor* out){
    vector<Tensor*> tin = {in};
    vector<Tensor*> tout = {out};
    m->evaluate(tin, tout);
}

const char* Layer_name(layer l){
    char* name = new char[l->name.length() + 1];
    strcpy(name, l->name.c_str());
    return name;
}

Tensor* Layer_input(layer l){
    return l->input;
}

Tensor* Layer_output(layer l){
    return l->output;
}


// Optimizers
optimizer SGD_init(float lr, float mu){
    return new sgd({lr,mu});
}
