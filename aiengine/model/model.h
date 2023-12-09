#ifndef __MODEL_H__
#define __MODEL_H__

#include <stdint.h>
#include <stdlib.h>
#include "../tensor/tensor.h"

typedef struct TupleU64 {
    uint64_t x;
    uint64_t y;
} TupleU64;

static struct TupleU64 *Tuple(uint64_t x, uint64_t y) {
    return (struct TupleU64*) malloc(sizeof(struct TupleU64));
}

typedef enum {
    RELU,
    SOFTMAX,
} ActivationType;

typedef enum {
    CROSS_ENTROPY
} LossFuncType;

typedef enum {
    ADAM
} OptmizerType;

typedef struct Layer {
    ActivationType activation;
} Layer;

struct Layer *Conv2D(uint64_t filters, TupleU64 *kernel_size, ActivationType actv);

struct Layer *MaxPooling2D(TupleU64 *kernel_size);

struct Layer *Flatten();

struct Layer *Dense(uint64_t units, ActivationType actv);

typedef struct Layer* (*ModelAddLayer)(struct NNModel *model, struct Layer *layer);
typedef struct NNModel* (*ModelCompile)(struct NNModel *model, OptmizerType optmizer, LossFuncType lossFunc);
typedef struct NNModel* (*ModelTrain)(struct NNModel *model, struct Tensor *data, uint64_t epochs, uint64_t batchSize, float validationSplit);
typedef struct NNModel* (*ModelEvaluate)(struct NNModel *model);

typedef struct NNModel {
    Layer *layers;
    ModelAddLayer addLayer;

    ModelCompile compile;
    ModelTrain fit;
    ModelEvaluate evaluate;
} NNModel;

struct NNModel *SequentialModel();

#endif /* __MODEL_H__ */