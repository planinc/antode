/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.6
* copyright (c) 2020, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: April 2020
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/
#include "eddl/tensor/tensor.h"
#include "eddl/hardware/cpu/cpu_hw.h"

#ifdef cGPU
#include "eddl/hardware/gpu/gpu_tensor.h"
#include "eddl/hardware/gpu/gpu_hw.h"
#include "eddl/hardware/gpu/nn/gpu_nn.h"
#endif

using namespace std;

void checkCompatibility(Tensor *A, Tensor *B, const string &title){
    if (A->device != B->device) {
        msg("Tensors in different devices", title);
    }

    if (!Tensor::eqsize(A, B)){
        msg("Tensors with different shape", title);
    }
}


void checkCompatibility(Tensor *A, Tensor *B, Tensor *C, const string &title){
    checkCompatibility(A, B, title);
    checkCompatibility(A, C, title);
}

bool Tensor::all(Tensor *A){
    bool res = false;

    if (A->isCPU()) {
        res = cpu_all(A);
    }
#ifdef cGPU
    else if (A->isGPU())
    {
        res = gpu_all(A);
    }
#endif
#ifdef cFPGA
    else {
        res = fpga_all(A);
    }
#endif

    return res;
}

bool Tensor::any(Tensor *A){
    bool res = false;

    if (A->isCPU()) {
        res = cpu_any(A);
    }
#ifdef cGPU
    else if (A->isGPU())
    {
        res = gpu_any(A);
    }
#endif
#ifdef cFPGA
    else {
        res = fpga_any(A);
    }
#endif

   return res;
}

// Logic funcions: Logical ops
void Tensor::isfinite(Tensor *A, Tensor* B){
    checkCompatibility(A, B, "Tensor::isfinite");

    if (A->isCPU()) {
        cpu_isfinite(A, B);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
          gpu_isfinite(A, B);
          }
#endif
#ifdef cFPGA
    else {
         fpga_isfinite(A, B);
        }
#endif
}

void Tensor::isinf(Tensor *A, Tensor* B){
    checkCompatibility(A, B, "Tensor::isinf");

    if (A->isCPU()) {
        cpu_isinf(A, B);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
          gpu_isinf(A, B);
          }
#endif
#ifdef cFPGA
    else {
          fpga_isinf(A, B);
        }
#endif
}

void Tensor::isnan(Tensor *A, Tensor* B){
    checkCompatibility(A, B, "Tensor::isnan");

    if (A->isCPU()) {
        cpu_isnan(A, B);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
          gpu_isnan(A, B);
          }
#endif
#ifdef cFPGA
    else {
          fpga_isnan(A, B);
        }
#endif
}

void Tensor::isneginf(Tensor *A, Tensor* B){
    checkCompatibility(A, B, "Tensor::isneginf");

    if (A->isCPU()) {
        cpu_isneginf(A, B);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
          gpu_isneginf(A, B);
          }
#endif
#ifdef cFPGA
    else {
         fpga_isneginf(A, B);
        }
#endif
}

void Tensor::isposinf(Tensor *A, Tensor* B){
    checkCompatibility(A, B, "Tensor::isposinf");

    if (A->isCPU()) {
        cpu_isposinf(A, B);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
          gpu_isposinf(A, B);
          }
#endif
#ifdef cFPGA
    else {
         fpga_isposinf(A, B);
        }
#endif
}


// Logic funcions: Logical ops

void Tensor::logical_and(Tensor *A, Tensor *B, Tensor *C){
    checkCompatibility(A, B, C, "Tensor::logical_and");

    if (A->isCPU()) {
        cpu_logical_and(A, B, C);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
            gpu_logical_and(A, B, C);
          }
#endif
#ifdef cFPGA
    else {
          fpga_logical_and(A, B, C);
        }
#endif
}

void Tensor::logical_or(Tensor *A, Tensor *B, Tensor *C){
    checkCompatibility(A, B, C, "Tensor::logical_or");

    if (A->isCPU()) {
        cpu_logical_or(A, B, C);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
            gpu_logical_or(A, B, C);
          }
#endif
#ifdef cFPGA
    else {
          fpga_logical_or(A, B, C);
        }
#endif
}

void Tensor::logical_not(Tensor *A, Tensor *B){
    checkCompatibility(A, B, "Tensor::logical_not");

    if (A->isCPU()) {
        cpu_logical_not(A, B);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
            gpu_logical_not(A, B);
          }
#endif
#ifdef cFPGA
    else {
          fpga_logical_not(A, B);
        }
#endif
}

void Tensor::logical_xor(Tensor *A, Tensor *B, Tensor *C){
    checkCompatibility(A, B, C, "Tensor::logical_xor");

    if (A->isCPU()) {
        cpu_logical_xor(A, B, C);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
            gpu_logical_xor(A, B, C);
          }
#endif
#ifdef cFPGA
    else {
          fpga_logical_xor(A, B, C);
        }
#endif
}


bool Tensor::allclose(Tensor *A, Tensor *B, float rtol, float atol, bool equal_nan){
    checkCompatibility(A, B, "Tensor::allclose");

    if (A->isCPU()) {
        return cpu_allclose(A, B, rtol, atol, equal_nan);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
            return gpu_allclose(A, B, rtol, atol, equal_nan);
          }
#endif
#ifdef cFPGA
    else {
          return fpga_allclose(A, B, rtol, atol, equal_nan);
        }
#endif
    return 0;
}


void Tensor::isclose(Tensor *A, Tensor *B, Tensor *C, float rtol, float atol, bool equal_nan){
    checkCompatibility(A, B, C, "Tensor::isclose");

    if (A->isCPU()) {
        cpu_isclose(A, B, C, rtol, atol, equal_nan);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
            gpu_isclose(A, B, C, rtol, atol, equal_nan);
          }
#endif
#ifdef cFPGA
    else {
          fpga_isclose(A, B, C, rtol, atol, equal_nan);
        }
#endif
}


void Tensor::greater(Tensor *A, Tensor *B, Tensor *C){
    checkCompatibility(A, B, C, "Tensor::greater");

    if (A->isCPU()) {
        cpu_greater(A, B, C);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
            gpu_greater(A, B, C);
          }
#endif
#ifdef cFPGA
    else {
            fpga_greater(A, B, C);
        }
#endif
}

void Tensor::greater_equal(Tensor *A, Tensor *B, Tensor *C){
    checkCompatibility(A, B, C, "Tensor::greater_equal");

    if (A->isCPU()) {
        cpu_greater_equal(A, B, C);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
           gpu_greater_equal(A, B, C);
          }
#endif
#ifdef cFPGA
    else {
          fpga_greater_equal(A, B, C);
        }
#endif
}

void Tensor::less(Tensor *A, Tensor *B, Tensor *C){
    checkCompatibility(A, B, C, "Tensor::less");

    if (A->isCPU()) {
        cpu_less(A, B, C);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
            gpu_less(A, B, C);
          }
#endif
#ifdef cFPGA
    else {
         fpga_less(A, B, C);
        }
#endif
}

void Tensor::less_equal(Tensor *A, Tensor *B, Tensor *C){
    checkCompatibility(A, B, C, "Tensor::less_equal");

    if (A->isCPU()) {
        cpu_less_equal(A, B, C);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
            gpu_less_equal(A, B, C);
          }
#endif
#ifdef cFPGA
    else {
          fpga_less_equal(A, B, C);
        }
#endif
}

void Tensor::equal(Tensor *A, Tensor *B, Tensor *C){
    checkCompatibility(A, B, C, "Tensor::equal");

    if (A->isCPU()) {
        cpu_equal(A, B, C);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
            gpu_equal(A, B, C);
          }
#endif
#ifdef cFPGA
    else {
         fpga_equal(A, B, C);
        }
#endif
}

void Tensor::not_equal(Tensor *A, Tensor *B, Tensor *C){
    checkCompatibility(A, B, C, "Tensor::not_equal");

    if (A->isCPU()) {
        cpu_not_equal(A, B, C);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
            gpu_not_equal(A, B, C);
          }
#endif
#ifdef cFPGA
    else {
           fpga_not_equal(A, B, C);
        }
#endif
}



int Tensor::eqsize(Tensor *A, Tensor *B) {
    if (A->ndim != B->ndim) return 0;

    for (int i = 0; i < A->ndim; i++){
        if (A->shape[i] != B->shape[i]) return 0;
    }

    return 1;
}

int Tensor::equal2(Tensor *A, Tensor *B, float epsilon) {
    if (A->device != B->device) msg("Tensors in different devices", "Tensor::equal");

    if (!eqsize(A,B)) return 0;

    if (A->isCPU()) {
        return cpu_equal2(A, B, epsilon);
    }
#ifdef cGPU
    else if (A->isGPU())
          {
            msg("Equal only for CPU Tensors", "Tensor::equal");
          }
#endif
#ifdef cFPGA
    else {
          return fpga_equal2(A, B, epsilon);
        }
#endif

    return 1;
}
