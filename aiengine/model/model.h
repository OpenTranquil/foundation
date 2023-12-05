#ifndef __MODEL_H__
#define __MODEL_H__

#include <stdint.h>
#include "../tensor/tensor.h"

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

struct Layer *Conv2D(ActivationType actv);

struct Layer *MaxPooling2D();

struct Layer *Flatten();

struct Layer *Dense(ActivationType actv);

typedef struct Layer* (*ModelAddLayer)(struct NNModel *model, struct Layer *layer);
typedef struct NNModel* (*ModelCompile)(struct NNModel *model, OptmizerType optmizer, LossFuncType lossFunc);
typedef struct NNModel* (*ModelTrain)(struct NNModel *model, struct Tensor *data, uint64_t epochs, uint64_t batchSize, float validationSplit);
typedef struct NNModel* (*ModelEvaluate)(struct NNModel *model);

typedef struct NNModel {
    Layer *layers;
    ModelAddLayer addLayer;

    ModelCompile compile;
    ModelTrain train;
    ModelEvaluate evaluate;
} NNModel;

struct NNModel *SequentialModel();

#endif /* __MODEL_H__ */