#include "model.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Layer *Conv2D(uint64_t filters, TupleU64 *kernel_size, ActivationType actv) {
    struct Conv2DLayer *layer = (struct Conv2DLayer*)malloc(sizeof(Conv2DLayer));
    if (layer == NULL) {
        printf("conv2d layer alloc failed!\n");
        exit(1);
    }

    layer->base.activation = actv;

    return &layer->base;
}

struct Layer *MaxPooling2D(TupleU64 *kernel_size) {
    struct MaxPooling2DLayer *layer = (struct MaxPooling2DLayer*)malloc(sizeof(MaxPooling2DLayer));
    if (layer == NULL) {
        printf("max polling layer alloc failed!\n");
        exit(1);
    }

    return &layer->base;
}


struct Layer *Flatten() {
    struct FlattenLayer *layer = (struct FlattenLayer*)malloc(sizeof(FlattenLayer));
    if (layer == NULL) {
        printf("flatten layer alloc failed!\n");
        exit(1);
    }

    return &layer->base;
}

struct Layer *Dense(uint64_t units, ActivationType actv) {
    struct DenseLayer *layer = (struct DenseLayer*)malloc(sizeof(DenseLayer));
    if (layer == NULL) {
        printf("dense layer alloc failed!\n");
        exit(1);
    }

    return &layer->base;
}

struct Layer* model_add_layer(struct NNModel *model, struct Layer *layer) {

}

struct NNModel* model_compile(struct NNModel *model, OptmizerType optmizer, LossFuncType lossFunc) {

}

struct NNModel* model_fit(struct NNModel *model, struct Tensor *data, uint64_t epochs, uint64_t batchSize, float validationSplit) {

}

struct NNModel* model_evaluate(struct NNModel *model) {

}

struct NNModel *SequentialModel() {
    struct NNModel *model = (struct NNModel*)malloc(sizeof(NNModel));
    if (model == NULL) {
        printf("model alloc failed!\n");
        exit(1);
    }

    model->layers = NULL;
    model->addLayer = model_add_layer;
    model->compile = model_compile;
    model->fit = model_fit;
    model->evaluate = model_evaluate;

    return model;
}